//
// (C) Copyright 2020-2022 Intel Corporation.
//
// SPDX-License-Identifier: BSD-2-Clause-Patent
//

package ranklist

import (
	"testing"

	"github.com/google/go-cmp/cmp"
	"github.com/pkg/errors"

	"github.com/daos-stack/daos/src/control/common/test"
)

func TestRankList_RankSet(t *testing.T) {
	for name, tc := range map[string]struct {
		ranks    string
		addRanks []Rank
		expOut   string
		expCount int
		expRanks []Rank
		expErr   error
	}{
		"empty start list": {
			ranks:    "",
			expOut:   "",
			expCount: 0,
			expRanks: []Rank{},
		},
		"invalid with hostnames": {
			ranks:  "node2-1,node1-2.suffix1,node1-[45,47].suffix2,node3,node1-3",
			expErr: errors.New("unexpected alphabetic character(s)"),
		},
		"simple ranged rank list": {
			ranks:    "0-10",
			expOut:   "0-10",
			expCount: 11,
			expRanks: []Rank{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
		},
		"deranged rank list": {
			ranks:    "1,2,3,5,6,8,10,10,1",
			expOut:   "1-3,5-6,8,10",
			expCount: 7,
			expRanks: []Rank{1, 2, 3, 5, 6, 8, 10},
		},
		"ranged rank list": {
			ranks:    "2,3,10-19,0-9",
			addRanks: []Rank{30, 32},
			expOut:   "0-19,30,32",
			expCount: 22,
			expRanks: []Rank{
				0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
				10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
				30, 32,
			},
		},
		"adding to empty list": {
			ranks:    "",
			addRanks: []Rank{30, 32},
			expOut:   "30,32",
			expCount: 2,
			expRanks: []Rank{30, 32},
		},
		"invalid list with spaces": {
			ranks:  "1, 5",
			expErr: errors.New("unexpected whitespace character(s)"),
		},
	} {
		t.Run(name, func(t *testing.T) {
			rs, gotErr := CreateRankSet(tc.ranks)
			test.CmpErr(t, tc.expErr, gotErr)
			if tc.expErr != nil {
				return
			}
			for _, r := range tc.addRanks {
				rs.Add(r)
			}

			if diff := cmp.Diff(tc.expOut, rs.String()); diff != "" {
				t.Fatalf("unexpected value (-want, +got):\n%s\n", diff)
			}

			gotCount := rs.Count()
			if gotCount != tc.expCount {
				t.Fatalf("\nexpected count to be %d; got %d", tc.expCount, gotCount)
			}

			ranks := rs.Ranks()
			if diff := cmp.Diff(tc.expRanks, ranks); diff != "" {
				t.Fatalf("unexpected ranks (-want, +got):\n%s\n", diff)
			}

		})
	}
}
