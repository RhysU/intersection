/* This is free and unencumbered software released into the public domain. */

#include "isect.h"

int isect(double a, double b, double x, double y, double *l, double *u)
{
    const int A=a<b, B=a<x, C=a<y, D=b<x, E=b<y;
    const int ret = B&~(C&D&E)|C&~(D&E)|D&~(E)|~B&(C|D|E)|~C&(D|E)|~D&E;
    if (ret) {
        const int F=x<y;
        *l  = a*(A&(B&~C&~E&~F|~B&C&~D&F));  /* alower */
        *u  = a*(~A&(B&~C&D&~F|~B&C&E&F));   /* aupper */
        *l += b*(~A&(~C&D&~E&~F|~B&~D&E&F)); /* blower */
        *u += b*(A&(B&D&~E&~F|C&~D&E&F));    /* bupper */
        *l += x*(F&(A&B&C&~D|~A&~B&D&E));    /* xlower */
        *u += x*(~F&(A&B&~D&~E|~A&~B&~C&D)); /* xupper */
        *l += y*(~F&(A&B&C&~E|~A&~C&D&E));   /* ylower */
        *u += y*(F&(A&C&~D&~E|~A&~B&~C&E));  /* yupper */
    }
    return ret;
}
