/*
 * Copyright (C) 2013 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "fct.h"
#include "isect.h"

FCT_BGN()
{
    FCT_QTEST_BGN(isect)
    {
        // Table driven test inputs and expected results
        // Test index   =  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
        const int a[24] = {1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,4};
        const int b[24] = {2,2,3,3,4,4,1,1,3,3,4,4,1,1,2,2,4,4,1,1,2,2,3,3};
        const int x[24] = {3,4,2,4,2,3,3,4,1,4,1,3,2,4,1,4,1,2,2,3,1,3,1,2};
        const int y[24] = {4,3,4,2,3,2,4,3,4,1,3,1,4,2,4,1,2,1,3,2,3,1,2,1};
        const int I[24] = {0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0};
        const int L[24] = {0,0,2,2,2,2,0,0,2,2,2,2,2,2,2,2,0,0,2,2,2,2,0,0};
        const int H[24] = {0,0,3,3,3,3,0,0,3,3,3,3,3,3,3,3,0,0,3,3,3,3,0,0};

        // Test each column in the table above
        for (size_t j = 0; j < 24; ++j) {
            double lo, hi;
            const int res = isect(a[j], b[j], x[j], y[j], &lo, &hi);
            fct_xchk(res == I[j], "I[%d]: %d vs %d", j, res, I[j]);
            if (I[j]) {
                fct_xchk(lo == L[j], "L[%d]: %g expecting %d", j, lo, L[j]);
                fct_xchk(hi == H[j], "U[%d]: %g expecting %d", j, hi, H[j]);
            }
        }
    }
    FCT_QTEST_END();
}
FCT_END()
