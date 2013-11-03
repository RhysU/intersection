/*
 * Copyright (C) 2013 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <assert.h>

#include "omsect.h"

int omsect(double a, double b, double x, double y, double *l, double *u)
{
    assert(a<b);
    int D=b<x, E=b<y, C=a<y, B=a<x;
    int ret = (D&~E)|(~D&E)|(C&~(D&E))|(~C&(D|E))|(B&~(C&D&E))|(~B&(C|D|E));
    if (ret) {
        int F=x<y;
        *l  = a*(~B&C&~D&F);                       /* alower */
        *u  = a*(B&~C&~E&~F);                      /* aupper */
        *l += b*(B&D&~E&~F);                       /* blower */
        *u += b*(C&~D&E&F);                        /* bupper */
        *l += x*(B&(~D&((~E&~F)|(C&(~E|F)))));     /* xlower */
        *u += y*(C&(~E&((B&((~D)|(~F)))|(~D&F)))); /* yupper */
    }
    return ret;
}
