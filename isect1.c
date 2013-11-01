/* This is free and unencumbered software released into the public domain. */

#include "isect.h"

int isect(double a, double b, double x, double y, double *l, double *u)
{
    const int A=a<b, B=a<x, C=a<y, D=b<x, E=b<y, F=x<y;

    const int ret = B&~E|B&~D|B&~C|C&~E|C&~D|~B&C|D&~E|~C&D|~B&D|~D&E|~C&E|~B&E;
    const int alower = A&B&~C&~E&~F|A&~B&C&~D&F;
    const int blower = ~A&~C&D&~E&~F|~A&~B&~D&E&F;
    const int xlower = A&B&C&~D&F|~A&~B&D&E&F;
    const int ylower = A&B&C&~E&~F|~A&~C&D&E&~F;
    const int aupper = ~A&B&~C&D&~F|~A&~B&C&E&F;
    const int bupper = A&B&D&~E&~F|A&C&~D&E&F;
    const int xupper = A&B&~D&~E&~F|~A&~B&~C&D&~F;
    const int yupper = A&C&~D&~E&F|~A&~B&~C&E&F;

    *l = a*alower + b*blower + x*xlower + y*ylower;
    *u = a*aupper + b*bupper + x*xupper + y*yupper;

    return ret;
}
