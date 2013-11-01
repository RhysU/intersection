/* This is free and unencumbered software released into the public domain. */

#include "omsect.h"

int omsect(double a, double b, double x, double y, double *l, double *u)
{
    const int B=a<x, C=a<y, D=b<x, E=b<y;
    const int ret = B&~E|B&~D|B&~C|C&~E|C&~D|~B&C|D&~E|~C&D|~B&D|~D&E|~C&E|~B&E;
    if (ret) {
        const int F=x<y;
        *l  = a*(~B&C&~D&F);              /* alower */
        *u  = a*(B&~C&~E&~F);             /* aupper */
        *l += b*(B&D&~E&~F);              /* blower */
        *u += b*(C&~D&E&F);               /* bupper */
        *l += x*(B&C&~D&F|B&~C&~D&~E&~F); /* xlower */
        *u += x*(B&C&~D&~E&~F);           /* xupper */
        *l += y*(B&C&~D&~E&~F);           /* ylower */
        *u += y*(C&~D&~E&F|B&C&D&~E&~F);  /* yupper */
    }
    return ret;
}
