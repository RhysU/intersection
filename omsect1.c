/* This is free and unencumbered software released into the public domain. */

#include <assert.h>

#include "omsect.h"

int omsect(double a, double b, double x, double y, double *l, double *u)
{
    assert(a<b);
    const int B=a<x, C=a<y, D=b<x, E=b<y;
    const int ret = B&~E|B&~D|B&~C|C&~E|C&~D|~B&C|D&~E|~C&D|~B&D|~D&E|~C&E|~B&E;
    if (ret) {
        const int F=x<y;
        *l  = a*(~B&C&~D&F);                      /* alower */
        *u  = a*(B&~C&~E&~F);                     /* aupper */
        *l += b*(B&D&~E&~F);                      /* blower */
        *u += b*(C&~D&E&F);                       /* bupper */
        *l += x*(B&~D&~E&~F|B&C&~D&~E|B&C&~D&F);  /* xlower */
        *u += y*(B&C&~E&~F|B&C&~D&~E|C&~D&~E&F);  /* yupper */
    }
    return ret;
}
