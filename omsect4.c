/*
 * Copyright (C) 2013, 2026 Rhys Ulerich
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
    int B=a<x, C=a<y, D=b<x, E=b<y;
    int ret = (B|C) & ~(D&E);
    if (ret) {
        *l = a*(~B&C&~D) + x*(B&~D) + b*(B&D&~E);
        *u = a*(B&~C)    + y*(C&~E) + b*(C&~D&E);
    }
    return ret;
}
