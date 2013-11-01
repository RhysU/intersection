/* This is free and unencumbered software released into the public domain. */

#include "isect.h"

int isect(double a, double b, double x, double y, double *l, double *u)
{
    const int A=a<b, B=a<x, C=a<y, D=b<x, E=b<y;
    const int ret = B&~E|B&~D|B&~C|C&~E|C&~D|~B&C|D&~E|~C&D|~B&D|~D&E|~C&E|~B&E;
    if (ret) {
        const int F=x<y;
        *l  = a*(A&B&~C&~E&~F|A&~B&C&~D&F  ); /* alower */
        *u  = a*(~A&B&~C&D&~F|~A&~B&C&E&F  ); /* aupper */
        *l += b*(~A&~C&D&~E&~F|~A&~B&~D&E&F); /* blower */
        *u += b*(A&B&D&~E&~F|A&C&~D&E&F    ); /* bupper */
        *l += x*(A&B&C&~D&F|~A&~B&D&E&F    ); /* xlower */
        *u += x*(A&B&~D&~E&~F|~A&~B&~C&D&~F); /* xupper */
        *l += y*(A&B&C&~E&~F|~A&~C&D&E&~F  ); /* ylower */
        *u += y*(A&C&~D&~E&F|~A&~B&~C&E&F  ); /* yupper */
    }
    return ret;
}
