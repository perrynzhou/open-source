/**
 * (C) Copyright 2016-2022 Intel Corporation.
 *
 * SPDX-License-Identifier: BSD-2-Clause-Patent
 */
/**
 * This file is part of daos
 *
 * tests/suite/daos_epoch_recovery.c
 */
#define D_LOGFAC	DD_FAC(tests)
#include "daos_test.h"
#include "daos_iotest.h"
#include <daos/container.h>

enum io_op {
	UPDATE,
	VERIFY
};

static void
io(enum io_op op, test_arg_t *arg, daos_handle_t coh, daos_obj_id_t oid,
	const char *value)
{
	struct ioreq	req;
	const char	dkey[] = "epoch_recovery dkey";
	const int	nakeys = 4;
	const size_t	nakeys_strlen = 4 /* "9999" */;
	const char     *akey_fmt = "epoch_recovery akey%d";
	char	       *akey[nakeys];
	char	       *rec[nakeys];
	daos_size_t	rec_size[nakeys];
	int		rx_nr[nakeys];
	daos_off_t	offset[nakeys];
	const char     *val_fmt = "epoch_recovery val%d '%s'";
	daos_size_t	rsize;
	int		i;

	ioreq_init(&req, coh, oid, DAOS_IOD_SINGLE, arg);

	rsize = strlen(val_fmt) + nakeys_strlen + strlen(value) + 1;

	for (i = 0; i < nakeys; i++) {
		D_ALLOC(akey[i], strlen(akey_fmt) + nakeys_strlen + 1);
		assert_non_null(akey[i]);
		sprintf(akey[i], akey_fmt, i);
		rec_size[i] = rsize;
		rx_nr[i] = 1;
		rec[i] = calloc(rec_size[i], 1);
		assert_non_null(rec[i]);
		offset[i] = i * 20;
	}

	if (op == UPDATE) {
		print_message("preparing records\n");
		for (i = 0; i < nakeys; i++) {
			snprintf(rec[i], rec_size[i], val_fmt, i, value);
			print_message("  akey[%d] '%s' val '%d %s'\n", i,
				      akey[i], (int)rec_size[i], rec[i]);
		}

		insert(dkey, nakeys, (const char **)akey, /*iod_size*/ rec_size,
		       rx_nr, offset, (void **)rec, DAOS_TX_NONE, &req, 0);
	} else {	/* op == VERIFY */
		char *rec_verify;

		D_ALLOC_ARRAY(rec_verify, (int)rsize);
		assert_non_null(rec_verify);
		print_message("verifying...\n");
		lookup(dkey, nakeys, (const char **)akey, offset, rec_size,
		       (void **)rec, rec_size, DAOS_TX_NONE, &req, false);
		for (i = 0; i < nakeys; i++) {
			print_message("  akey[%d] '%s' val '%d %s'\n", i,
				      akey[i], (int)req.iod[i].iod_size,
				      rec[i]);
			snprintf(rec_verify, rsize, val_fmt, i, value);
			assert_int_equal(req.iod[i].iod_size,
					 rsize);
			assert_memory_equal(rec[i], rec_verify,
					    req.iod[i].iod_size);
		}
		D_FREE(rec_verify);
	}
}

enum epoch_recovery_op {
	CONT_CLOSE,
	POOL_DISCONNECT
};

static void
epoch_recovery(test_arg_t *arg, enum epoch_recovery_op op)
{
	uuid_t		uuid;
	char		str[37];
	daos_handle_t	coh;
	daos_obj_id_t	oid;
	daos_epoch_t	snap;
	int		rc;

	par_barrier(PAR_COMM_WORLD);

	print_message("creating and opening container "DF_UUIDF"\n",
		      DP_UUID(uuid));
	rc = daos_cont_create(arg->pool.poh, &uuid, NULL /* properties */,
			      NULL /* ev */);
	assert_rc_equal(rc, 0);
	uuid_unparse(uuid, str);
	rc = daos_cont_open(arg->pool.poh, str, DAOS_COO_RW, &coh,
			    NULL /* info */, NULL /* ev */);
	assert_rc_equal(rc, 0);

	oid = daos_test_oid_gen(arg->coh, OC_RP_XSF, 0, 0, arg->myrank);

	/* Every rank updates timestep 1. */
	io(UPDATE, arg, coh, oid, "timestamp 1");

	/** Take a snapshot at this point to rollback to. */
	rc = daos_cont_create_snap(coh, &snap, NULL, NULL);
	assert_rc_equal(rc, 0);

	/* Every rank updates timestep 2. */
	io(UPDATE, arg, coh, oid, "timestamp 2");

	par_barrier(PAR_COMM_WORLD);

	print_message("closing container\n");
	rc = daos_cont_close(coh, NULL /* ev */);
	assert_rc_equal(rc, 0);

	par_barrier(PAR_COMM_WORLD);

	if (op == POOL_DISCONNECT) {
		print_message("disconnecting from pool\n");
		rc = daos_pool_disconnect(arg->pool.poh, NULL /* ev */);
		assert_rc_equal(rc, 0);
		print_message("reconnecting to pool\n");
		if (arg->myrank == 0) {
			rc = daos_pool_connect(arg->pool.pool_str, arg->group,
					       DAOS_PC_RW,
					       &arg->pool.poh, NULL /* info */,
					       NULL /* ev */);
			assert_rc_equal(rc, 0);
		}
		handle_share(&arg->pool.poh, HANDLE_POOL, arg->myrank,
			     arg->pool.poh, 1);
	}

	print_message("reopening container\n");
	rc = daos_cont_open(arg->pool.poh, str, DAOS_COO_RO, &coh,
			    &arg->co_info, NULL /* ev */);
	assert_rc_equal(rc, 0);

	/** TODO - query last snapshot taken and rollback to that */

	/** Verify that timestep 1 is there (not 2). */
	/** TODO - since rollback is not supported, verify 2 instead of 1. */
	io(VERIFY, arg, coh, oid, "timestamp 2");

	rc = daos_cont_close(coh, NULL /* ev */);
	assert_rc_equal(rc, 0);
	par_barrier(PAR_COMM_WORLD);
}

static void
cont_close_discard(void **state)
{
	epoch_recovery(*state, CONT_CLOSE);
}

static void
pool_disconnect_discard(void **state)
{
	epoch_recovery(*state, POOL_DISCONNECT);
}

static const struct CMUnitTest epoch_recovery_tests[] = {
	{"ERECOV1: container close discards uncommitted data",
	 cont_close_discard, NULL, test_case_teardown},
	{"ERECOV2: pool disconnect discards uncommitted data",
	 pool_disconnect_discard, NULL, test_case_teardown}
};

static int
setup(void **state)
{
	return test_setup(state, SETUP_POOL_CONNECT, true, DEFAULT_POOL_SIZE,
			  0, NULL);
}

int
run_daos_epoch_recovery_test(int rank, int size)
{
	int rc = 0;

	rc = cmocka_run_group_tests_name("DAOS_Epoch_Recovery",
					 epoch_recovery_tests, setup,
					 test_teardown);
	par_barrier(PAR_COMM_WORLD);
	return rc;
}
