/*
 * Copyright (C) 2013 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "fct.h"
#include "omsect.h"

FCT_BGN()
{
    FCT_QTEST_BGN(omsect)
    {
        // Table driven test inputs and expected results
        // Test index   =  0 1 2 3 4 5 6 7 8 9 0 1 2 3
        const int a[14] = {1,1,1,1,1,1,2,2,2,2,3,3,1,1};
        const int b[14] = {2,2,3,3,4,4,3,3,4,4,4,4,2,2};
        const int x[14] = {3,4,2,4,2,3,1,4,1,3,1,2,2,3};
        const int y[14] = {4,3,4,2,3,2,4,1,3,1,2,1,3,2};
        const int I[14] = {0,0,1,1,1,1,1,1,1,1,0,0,1,1};
        const int L[14] = {0,0,2,3,2,3,2,3,2,3,0,0,2,2};
        const int H[14] = {0,0,3,2,3,2,3,2,3,2,0,0,2,2};

        // Test each column in the table above
        for (size_t j = 0; j < 14; ++j) {
            double lo, hi;
            const int res = omsect(a[j], b[j], x[j], y[j], &lo, &hi);
            fct_xchk(res == I[j], "I[%02d]: %d vs %d", j, res, I[j]);
            if (I[j]) {
                fct_xchk(lo == L[j], "L[%02d]: %g expecting %d", j, lo, L[j]);
                fct_xchk(hi == H[j], "U[%02d]: %g expecting %d", j, hi, H[j]);
            }
        }
    }
    FCT_QTEST_END();
}
FCT_END()
