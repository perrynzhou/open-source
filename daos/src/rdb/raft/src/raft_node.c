/**
 * Copyright (c) 2013, Willem-Hendrik Thiart
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 *
 * @file
 * @brief Representation of a peer
 * @author Willem Thiart himself@willemthiart.com
 * @version 0.1
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "raft.h"

#define RAFT_NODE_VOTED_FOR_ME        (1 << 0)
#define RAFT_NODE_VOTING              (1 << 1)
#define RAFT_NODE_HAS_SUFFICIENT_LOG  (1 << 2)

typedef struct
{
    void* udata;

    raft_index_t next_idx;
    raft_index_t match_idx;

    int flags;

    raft_node_id_t id;

    /* lease expiration time */
    raft_time_t lease;
    /* time when this node becomes part of leader's configuration */
    raft_time_t effective_time;
} raft_node_private_t;

raft_node_t* raft_node_new(void* udata, raft_node_id_t id)
{
    raft_node_private_t* me;
    me = (raft_node_private_t*)calloc(1, sizeof(raft_node_private_t));
    if (!me)
        return NULL;
    me->udata = udata;
    me->next_idx = 1;
    me->match_idx = 0;
    me->id = id;
    me->flags = RAFT_NODE_VOTING;
    me->lease = 0;
    me->effective_time = 0;
    return (raft_node_t*)me;
}

void raft_node_free(raft_node_t* me_)
{
    free(me_);
}

raft_index_t raft_node_get_next_idx(raft_node_t* me_)
{
    raft_node_private_t* me = (raft_node_private_t*)me_;
    return me->next_idx;
}

void raft_node_set_next_idx(raft_node_t* me_, raft_index_t nextIdx)
{
    raft_node_private_t* me = (raft_node_private_t*)me_;
    /* log index begins at 1 */
    me->next_idx = nextIdx < 1 ? 1 : nextIdx;
}

raft_index_t raft_node_get_match_idx(raft_node_t* me_)
{
    raft_node_private_t* me = (raft_node_private_t*)me_;
    return me->match_idx;
}

void raft_node_set_match_idx(raft_node_t* me_, raft_index_t matchIdx)
{
    raft_node_private_t* me = (raft_node_private_t*)me_;
    me->match_idx = matchIdx;
}

void* raft_node_get_udata(raft_node_t* me_)
{
    raft_node_private_t* me = (raft_node_private_t*)me_;
    return me->udata;
}

void raft_node_set_udata(raft_node_t* me_, void* udata)
{
    raft_node_private_t* me = (raft_node_private_t*)me_;
    me->udata = udata;
}

void raft_node_vote_for_me(raft_node_t* me_, const int vote)
{
    raft_node_private_t* me = (raft_node_private_t*)me_;
    if (vote)
        me->flags |= RAFT_NODE_VOTED_FOR_ME;
    else
        me->flags &= ~RAFT_NODE_VOTED_FOR_ME;
}

int raft_node_has_vote_for_me(raft_node_t* me_)
{
    raft_node_private_t* me = (raft_node_private_t*)me_;
    return (me->flags & RAFT_NODE_VOTED_FOR_ME) != 0;
}

void raft_node_set_voting(raft_node_t* me_, int voting)
{
    raft_node_private_t* me = (raft_node_private_t*)me_;
    if (voting)
    {
        assert(!raft_node_is_voting(me_));
        me->flags |= RAFT_NODE_VOTING;
    }
    else
    {
        assert(raft_node_is_voting(me_));
        me->flags &= ~RAFT_NODE_VOTING;
    }
}

int raft_node_is_voting(raft_node_t* me_)
{
    raft_node_private_t* me = (raft_node_private_t*)me_;
    return (me->flags & RAFT_NODE_VOTING) != 0;
}

int raft_node_has_sufficient_logs(raft_node_t* me_)
{
    raft_node_private_t* me = (raft_node_private_t*)me_;
    return (me->flags & RAFT_NODE_HAS_SUFFICIENT_LOG) != 0;
}

void raft_node_set_has_sufficient_logs(raft_node_t* me_)
{
    raft_node_private_t* me = (raft_node_private_t*)me_;
    me->flags |= RAFT_NODE_HAS_SUFFICIENT_LOG;
}

raft_node_id_t raft_node_get_id(raft_node_t* me_)
{
    raft_node_private_t* me = (raft_node_private_t*)me_;
    return (NULL == me) ? -1 : me->id;
}

void raft_node_set_lease(raft_node_t* me_, raft_time_t lease)
{
    raft_node_private_t* me = (raft_node_private_t*)me_;
    if (me->lease < lease)
        me->lease = lease;
}

raft_time_t raft_node_get_lease(raft_node_t* me_)
{
    raft_node_private_t* me = (raft_node_private_t*)me_;
    return me->lease;
}

void raft_node_set_effective_time(raft_node_t* me_, raft_time_t effective_time)
{
    raft_node_private_t* me = (raft_node_private_t*)me_;
    me->effective_time = effective_time;
}

raft_time_t raft_node_get_effective_time(raft_node_t* me_)
{
    raft_node_private_t* me = (raft_node_private_t*)me_;
    return me->effective_time;
}