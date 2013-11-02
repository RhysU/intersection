/* This is free and unencumbered software released into the public domain. */

#include "fct.h"
#include "omsect.h"

FCT_BGN()
{
    FCT_QTEST_BGN(omsect)
    {
        // Table driven test inputs and expected results
        // Test index   =  0 1 2 3 4 5 6 7 8 9 0 1
        const int a[12] = {1,1,1,1,1,1,3,3,3,4,4,4};
        const int b[12] = {2,2,3,3,4,4,1,1,4,1,1,3};
        const int x[12] = {3,4,2,4,2,3,2,4,1,2,3,1};
        const int y[12] = {4,3,4,2,3,2,4,2,2,3,2,2};
        const int I[12] = {0,0,1,1,1,1,1,1,0,1,1,0};
        const int L[12] = {0,0,2,3,2,3,2,3,0,2,3,0};
        const int H[12] = {0,0,3,2,3,2,3,2,0,3,2,0};

        // Test each column in the table above
        for (size_t j = 0; j < 12; ++j) {
            double lo, hi;
            const int res = omsect(a[j], b[j], x[j], y[j], &lo, &hi);
            fct_xchk(res == I[j], "Test %d wrong: %d vs %d", j+1, res, I[j]);
            if (I[j]) {
                fct_xchk(lo == L[j], "Lower %d wrong: %d vs %g", j, lo, L[j]);
                fct_xchk(hi == H[j], "Upper %d wrong: %d vs %g", j, hi, H[j]);
            }
        }
    }
    FCT_QTEST_END();
}
FCT_END();