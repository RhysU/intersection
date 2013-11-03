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
        // Test index   =  0 1 2 3 4 5 6 7 8 9 0 1
        const int a[12] = {1,1,1,1,1,1,2,2,2,2,3,3};
        const int b[12] = {2,2,3,3,4,4,3,3,4,4,4,4};
        const int x[12] = {3,4,2,4,2,3,1,4,1,3,1,2};
        const int y[12] = {4,3,4,2,3,2,4,1,3,1,2,1};
        const int I[12] = {0,0,1,1,1,1,1,1,1,1,0,0};
        const int L[12] = {0,0,2,3,2,3,2,3,2,3,0,0};
        const int H[12] = {0,0,3,2,3,2,3,2,3,2,0,0};

        // Test each column in the table above
        for (size_t j = 0; j < 12; ++j) {
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
