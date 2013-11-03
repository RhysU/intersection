/*
 * Copyright (C) 2013 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef OMSECT_H

/**
 * Given points \c a, \c b, \c x, and \c y under the assumption <code>a <=
 * b</code>, do intervals \c ab and \c xy overlap and if so what is the
 * order-matching interval?  Order-matching means an interval with endpoints
 * (p, q) such that p < q whenever x <= y and p > q whenever x > y.
 *
 * \param[in ] a Left endpoint on the first interval
 * \param[in ] b Right endpoint on the first interval
 * \param[in ] x Endpoint on the second interval
 * \param[in ] y Another on the second interval
 * \param[out] l if method returns \c true, set to be the lower
 *               endpoint of the order-matching intersection.
 * \param[out] h if method returns \c true, set to be the lower
 *               endpoint of the order-matching intersection.
 * \return True if the segments intersect.  False otherwise.
 */
int omsect(double a, double b, double x, double y, double *l, double *u);

#endif
