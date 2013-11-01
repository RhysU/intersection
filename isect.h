/* This is free and unencumbered software released into the public domain. */

#ifndef ISECT_H

/**
 * Given points \c a, \c b, \c x, and \c y, do intervals \c ab and \c xy
 * overlap and if so what is the overlapping interval?
 *
 * \param[in ] a Endpoint on the first interval
 * \param[in ] b Another endpoint on the first interval
 * \param[in ] x Endpoint on the second interval
 * \param[in ] y Another on the second interval
 * \param[out] l if method returns \c true, set to be the lower
 *               endpoint of the intersection.
 * \param[out] h if method returns \c true, set to be the lower
 *               endpoint of the intersection.
 * \return True if the segments intersect.  False otherwise.
 *
 * \see http://github.com/RhysU/intersection for implementation commentary.
 */
int isect(double a, double b, double x, double y, double *l, double *u);

#endif
