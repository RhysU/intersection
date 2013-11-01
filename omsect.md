Given open intervals (a, b) and (x, y) where a <= b holds but an ordering
relation is unknown for x and y.  Three questions are of interest:

 + Do they intersect?
 + If they intersect, what is their order-matching intersection?

By *order-matching intersection* I mean an intersection interval with
endpoints (p, q) such that p < q whenever x <= y and p > q whenever x > y.

Given five input booleans related to partial ordering results, there are nine
output functions of interest.  The first output is the presence or absence of
an intersection.  The remaining outputs are whether or not each of a, b, x, or
y is either the lower or upper boundary of the intersection.  In the absence
of an intersection, these eight outputs will all be false.

    case   perm.   a<x a<y b<x b<y x<y  omint. (abxy, abxy)
    ----  -------  --- --- --- --- ---  ------ ------------
      1   a b x y   1   1   1   1   1   none    0000  0000
      2   a b y x   1   1   1   1   0   none    0000  0000
      3   a x b y   1   1   0   1   1   (x, b)  0010  0100
      4   a x y b   1   1   0   0   1   (x, y)  0010  0001
      5   a y b x   1   1   1   0   0   (b, y)  0100  0001
      6   a y x b   1   1   0   0   0   (y, x)  0001  0010
      7   x a b y   0   1   0   1   1   (a, b)  1000  0100
      8   x a y b   0   1   0   0   1   (a, y)  1000  0001
      9   x y a b   0   0   0   0   1   none    0000  0000
     10   y a b x   1   0   1   0   0   (b, a)  0100  1000
     11   y a x b   1   0   0   0   0   (x, a)  0010  1000
     12   y x a b   0   0   0   0   0   none    0000  0000


To check for the presence of an intersection, we negate the non-intersection
cases.  That is,

    case   perm.   a<x a<y b<x b<y x<y  omint. (abxy, abxy)
    ----  -------  --- --- --- --- ---  ------ ------------
      1   a b x y   B   C   D   E   F   none    0000  0000
      2   a b y x   B   C   D   E  /F   none    0000  0000
      9   x y a b  /B  /C  /D  /E   F   none    0000  0000
     12   y x a b  /B  /C  /D  /E  /F   none    0000  0000

    qmc -s "/[BCDEF+BCDE/F+/B/C/D/EF+/B/C/D/E/F]"

    B*/E+B*/D+B*/C+C*/E+C*/D+/B*C+D*/E+/C*D+/B*D+/D*E+/C*E+/B*E

    int B=a<x, C=a<y, D=b<x, E=b<y, F=x<y;
    int omsect = B&~E|B&~D|B&~C|C&~E|C&~D|~B&C|D&~E|~C&D|~B&D|~D&E|~C&E|~B&E;


Obtaining an expression for when a is the lower bound:

    case   perm.   a<x a<y b<x b<y x<y  omint. (abxy, abxy)
    ----  -------  --- --- --- --- ---  ------ ------------
      7   x a b y  /B   C  /D   E   F   (a, b)  1000  0100
      8   x a y b  /B   C  /D  /E   F   (a, y)  1000  0001

    qmc -s "/BC/DEF+/BC/D/EF"

    /B*C*/D*F

    int alower = ~B&C&~D&F;

Obtaining an expression for when b is the lower bound:

    case   perm.   a<x a<y b<x b<y x<y  omint. (abxy, abxy)
    ----  -------  --- --- --- --- ---  ------ ------------
      5   a y b x   B   C   D  /E  /F   (b, y)  0100  0001
     10   y a b x   B  /C   D  /E  /F   (b, a)  0100  1000

    qmc -s "BCD/E/F+B/CD/E/F"

    B*D*/E*/F

    int blower = B&D&~E&~F;

Obtaining an expression for when x is the lower bound:

    case   perm.   a<x a<y b<x b<y x<y  omint. (abxy, abxy)
    ----  -------  --- --- --- --- ---  ------ ------------
      3   a x b y   B   C  /D   E   F   (x, b)  0010  0100
      4   a x y b   B   C  /D  /E   F   (x, y)  0010  0001
     11   y a x b   B  /C  /D  /E  /F   (x, a)  0010  1000

    qmc -s "BC/DEF+BC/D/EF+B/C/D/E/F"

    int xlower = B&C&~D&F|B&~C&~D&~E&~F;

And now for y being the lower bound which can be done by inspection:

    case   perm.   a<x a<y b<x b<y x<y  omint. (abxy, abxy)
    ----  -------  --- --- --- --- ---  ------ ------------
      6   a y x b   B   C  /D  /E  /F   (y, x)  0001  0010

    BC/D/E/F

    int ylower = BC~D~E~F;


Though a <= b by assumption, a can be the upper bound when y < x.
Finding an expression for when a is the upper bound:

    case   perm.   a<x a<y b<x b<y x<y  omint. (abxy, abxy)
    ----  -------  --- --- --- --- ---  ------ ------------
     10   y a b x   B  /C   D  /E  /F   (b, a)  0100  1000
     11   y a x b   B  /C  /D  /E  /F   (x, a)  0010  1000

    qmc -s "B/CD/E/F+B/C/D/E/F"

    B*/C*/E*/F

    int aupper = B&~C&~E&~F;

Obtaining an expression for when b is the upper bound:

    case   perm.   a<x a<y b<x b<y x<y  omint. (abxy, abxy)
    ----  -------  --- --- --- --- ---  ------ ------------
      3   a x b y   B   C  /D   E   F   (x, b)  0010  0100
      7   x a b y  /B   C  /D   E   F   (a, b)  1000  0100

    qmc -s "BC/DEF+/BC/DEF"

    C*/D*E*F

    int bupper = C&~D&E&F;

Obtaining an expression for when x is the upper bound by inspection:

    case   perm.   a<x a<y b<x b<y x<y  omint. (abxy, abxy)
    ----  -------  --- --- --- --- ---  ------ ------------
      6   a y x b   B   C  /D  /E  /F   (y, x)  0001  0010

    BC/D/E/F

    int xupper = BC~D~E~F;

Finally, when y is the upper bound:

    case   perm.   a<x a<y b<x b<y x<y  omint. (abxy, abxy)
    ----  -------  --- --- --- --- ---  ------ ------------
      4   a x y b   B   C  /D  /E   F   (x, y)  0010  0001
      5   a y b x   B   C   D  /E  /F   (b, y)  0100  0001
      8   x a y b  /B   C  /D  /E   F   (a, y)  1000  0001

    qmc -s "BC/D/EF+BCD/E/F+/BC/D/EF"

    C*/D*/E*F+B*C*D*/E*/F

    int yupper = C&~D&~E&F|B&C&D&~E&~F;


Now, getting to the implementation...

/**
 * Given points \c a, \c b, \c x, and \c y under the assumption <code>a <=
 * b\</code>, do intervals \c ab and \c xy overlap and if so what is the
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
        *u += x*(BC~D~E~F);               /* xupper */
        *l += y*(BC~D~E~F);               /* ylower */
        *u += y*(C&~D&~E&F|B&C&D&~E&~F);  /* yupper */
    }
    return ret;
}
