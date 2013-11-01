Background for Half Open, Ordered Intervals
-------------------------------------------

Given half-open intervals [a, b) and [x, y) where a <= b and x <= y,

 + 1a) Do they intersect?
 + 1b) If they intersect, what is their intersection?

Question (1a) is answered nicely by
[Steven W. McDougall](http://world.std.com/~swmcd/steven/tech/interval.html).
To recap, the possible ordering permutations of a, b, x, and y such that a <= b
and x <= y are examined:

    case  perm.    inter.
    ----  -------  ------
      1   a b x y  none
      2   a x b y  [x, b)
      3   a x y b  [x, y)
      4   x a b y  [a, b)
      5   x a y b  [a, y)
      6   x y a b  none

where the middle four cases possess nontrivial intersections.  Case 1 is
identified by b <= x and Case 6 by y <= a.  One can identify the intersecting
cases via negation these two situations yielding `!(b <= x || y <= a)` which can
be simplified to find Answer (1a), `x < b && y < a`.  When condition (1a) holds,
the intersection interval is [`max(a,x)` `min(b,y)`)

Extension to the Open, Unordered Interval Case
----------------------------------------------

Given open intervals (a, b) and (x, y) where an ordering relation is known for
neither a and b nor x and y.  Call these *unordered intervals*.  Again,

 + 2a) Do they intersect?
 + 2b) If they intersect, what is their ordered intersection?

By *ordered intersection* I mean interval endpoints (p, q) such that p < q.
This information was available in Answer (1b) by assumption.  Now it must be
deduced.

Unlike before, the full range of ordering permutations must be examined:

    case   perm.   inter.  a<b  x<y
    ----  -------  ------  ---  ---
      1   a b x y  none     T    T
      2   a b y x  none     T
      3   a x b y  (x, b)   T    T
      4   a x y b  (x, y)   T    T
      5   a y b x  (y, b)   T
      6   a y x b  (y, x)   T
      7   b a x y  none          T
      8   b a y x  none
      9   b x a y  (x, a)        T
     10   b x y a  (x, y)        T
     11   b y a x  (y, a)
     12   b y x a  (y, x)
     13   x a b y  (a, b)   T    T
     14   x a y b  (a, y)   T    T
     15   x b a y  (b, a)        T
     16   x b y a  (b, y)        T
     17   x y a b  none     T    T
     18   x y b a  none          T
     19   y a b x  (a, b)   T
     20   y a x b  (a, x)   T
     21   y b a x  (b, a)
     22   y b x a  (b, x)
     23   y x a b  none     T
     24   y x b a  none

It again makes sense to first identify these eight cases where no intersection
occurs.  Cases 1, 2, 7, and 8 are captured by max(a,b) <= min(x,y) while cases
17, 18, 23, and 24 occur when max(x,y) <= min(a,b).  Negating these conditions
and then distributing, `(max(a,b) > min(x,y) && max(x,y) > min(a,b))` provides
Answer (2a).

The minimal boolean expressions necessary to address Question (2b) do not jump
out at me.  Consequently, I will employ the
[Quine--McCluskey
algorithm](http://en.wikipedia.org/wiki/Quine%E2%80%93McCluskey_algorithm) as
implemented by qmc(1) commonly available on Debian-ish Linux Distributions.
Downloads of the [qmc source](http://packages.debian.org/source/sid/qmc) can be
had from Debian but I've not had much luck tracking down the
[project](http://qmc.pollaknet.at/) or its author Thomas Pollack.

Given six input booleans related to partial ordering results, there are nine
output functions of interest.  The first output is the presence or absence of
an intersection and it is included to be a sanity check against Answer (2a).
The remaining outputs are whether or not each of a, b, x, or y is either the
lower or upper boundary of the intersection.  In the absence of an
intersection, these eight outputs will all be false.  While don't care results
may produce simpler reduced expressions, producing all false results permits
computing a single intersection boundary at minimal cost.

    case   perm.   a<b a<x a<y b<x b<y x<y  inter. (abxy, abxy)
    ----  -------  --- --- --- --- --- ---  ------ ------------
      1   a b x y   1   1   1   1   1   1   none    0000  0000
      2   a b y x   1   1   1   1   1   0   none    0000  0000
      3   a x b y   1   1   1   0   1   1   (x, b)  0010  0100
      4   a x y b   1   1   1   0   0   1   (x, y)  0010  0001
      5   a y b x   1   1   1   1   0   0   (y, b)  0001  0100
      6   a y x b   1   1   1   0   0   0   (y, x)  0001  0010
      7   b a x y   0   1   1   1   1   1   none    0000  0000
      8   b a y x   0   1   1   1   1   0   none    0000  0000
      9   b x a y   0   0   1   1   1   1   (x, a)  0010  1000
     10   b x y a   0   0   0   1   1   1   (x, y)  0010  0001
     11   b y a x   0   1   0   1   1   0   (y, a)  0001  1000
     12   b y x a   0   0   0   1   1   0   (y, x)  0001  0010
     13   x a b y   1   0   1   0   1   1   (a, b)  1000  0100
     14   x a y b   1   0   1   0   0   1   (a, y)  1000  0001
     15   x b a y   0   0   1   0   1   1   (b, a)  0100  1000
     16   x b y a   0   0   0   0   1   1   (b, y)  0100  0001
     17   x y a b   1   0   0   0   0   1   none    0000  0000
     18   x y b a   0   0   0   0   0   1   none    0000  0000
     19   y a b x   1   1   0   1   0   0   (a, b)  1000  0100
     20   y a x b   1   1   0   0   0   0   (a, x)  1000  0010
     21   y b a x   0   1   0   1   0   0   (b, a)  0100  1000
     22   y b x a   0   0   0   1   0   0   (b, x)  0100  0010
     23   y x a b   1   0   0   0   0   0   none    0000  0000
     24   y x b a   0   0   0   0   0   0   none    0000  0000

Towards checking qmc against our Answer (2a):

    case   perm.   a<b a<x a<y b<x b<y x<y  inter. (abxy, abxy)
    ----  -------  --- --- --- --- --- ---  ------ ------------
      1   a b x y   A   B   C   D    E  F   none    0000  0000
      2   a b y x   A   B   C   D    E /F   none    0000  0000
      7   b a x y  /A   B   C   D    E  F   none    0000  0000
      8   b a y x  /A   B   C   D    E /F   none    0000  0000
     17   x y a b   A  /B  /C  /D  / E  F   none    0000  0000
     18   x y b a  /A  /B  /C  /D  / E  F   none    0000  0000
     23   y x a b   A  /B  /C  /D  / E /F   none    0000  0000
     24   y x b a  /A  /B  /C  /D  / E /F   none    0000  0000

The command for qmc to simply for the presence of an intersection is

     qmc -s "/[   A   B   C   D    E  F
               +  A   B   C   D    E /F
               + /A   B   C   D    E  F
               + /A   B   C   D    E /F
               +  A  /B  /C  /D  / E  F
               + /A  /B  /C  /D  / E  F
               +  A  /B  /C  /D  / E /F
               + /A  /B  /C  /D  / E /F]"

caveat a need to smash it all onto one line and eliminate whitespace.  If
needed, 'man 1 qmc' displays program options and 'qmc -d' describes its syntax.
The result for the presence of an intersection comes back as

    B*/E+B*/D+B*/C+C*/E+C*/D+/B*C+D*/E+/C*D+/B*D+/D*E+/C*E+/B*E

which written as a C non-short-circuiting operation is

    int A=a<b, B=a<x, C=a<y, D=b<x, E=b<y, F=x<y;
    int isect = B&~E|B&~D|B&~C|C&~E|C&~D|~B&C|D&~E|~C&D|~B&D|~D&E|~C&E|~B&E;


The truth table for whether or not point a is the lower bound in the
existence of an intersection is

    case   perm.   a<b a<x a<y b<x b<y x<y  inter. (abxy, abxy)
    ----  -------  --- --- --- --- --- ---  ------ ------------
     13   x a b y   A  /B   C  /D   E   F   (a, b)  1000  0100
     14   x a y b   A  /B   C  /D  /E   F   (a, y)  1000  0001
     19   y a b x   A   B  /C   D  /E  /F   (a, b)  1000  0100
     20   y a x b   A   B  /C  /D  /E  /F   (a, x)  1000  0010

giving rise to the following qmc invocation:

    qmc -s "A/BC/DEF+A/BC/D/EF+AB/CD/E/F+AB/C/D/E/F"

The result (as given by qmc or written as a C expression) is

    A*B*/C*/E*/F+A*/B*C*/D*F

    int A=a<b, B=a<x, C=a<y, D=b<x, E=b<y, F=x<y;
    int alower = A&B&~C&~E&~F|A&~B&C&~D&F;

To find the expression for whether or not b is the lower bound:

    case   perm.   a<b a<x a<y b<x b<y x<y  inter. (abxy, abxy)
    ----  -------  --- --- --- --- --- ---  ------ ------------
     15   x b a y  /A  /B   C  /D   E   F   (b, a)  0100  1000
     16   x b y a  /A  /B  /C  /D   E   F   (b, y)  0100  0001
     21   y b a x  /A   B  /C   D  /E  /F   (b, a)  0100  1000
     22   y b x a  /A  /B  /C   D  /E  /F   (b, x)  0100  0010

    qmc -s "/A/BC/DEF+/A/B/C/DEF+/AB/CD/E/F+/A/B/CD/E/F"

    /A*/C*D*/E*/F+/A*/B*/D*E*F

    int A=a<b, B=a<x, C=a<y, D=b<x, E=b<y, F=x<y;
    int blower = ~A&~C&D&~E&~F|~A&~B&~D&E&F;

To find the expression for whether or not x is the lower bound:

    case   perm.   a<b a<x a<y b<x b<y x<y  inter. (abxy, abxy)
    ----  -------  --- --- --- --- --- ---  ------ ------------
      3   a x b y   A   B   C  /D   E   F   (x, b)  0010  0100
      4   a x y b   A   B   C  /D  /E   F   (x, y)  0010  0001
      9   b x a y  /A  /B   C   D   E   F   (x, a)  0010  1000
     10   b x y a  /A  /B  /C   D   E   F   (x, y)  0010  0001

    qmc -s "ABC/DEF+ABC/D/EF+/A/BCDEF+/A/B/CDEF"

    A*B*C*/D*F+/A*/B*D*E*F

    int A=a<b, B=a<x, C=a<y, D=b<x, E=b<y, F=x<y;
    int xlower = A&B&C&~D&F|~A&~B&D&E&F;

Likewise for y:

    case   perm.   a<b a<x a<y b<x b<y x<y  inter. (abxy, abxy)
    ----  -------  --- --- --- --- --- ---  ------ ------------
      5   a y b x   A   B   C   D  /E  /F   (y, b)  0001  0100
      6   a y x b   A   B   C  /D  /E  /F   (y, x)  0001  0010
     11   b y a x  /A   B  /C   D   E  /F   (y, a)  0001  1000
     12   b y x a  /A  /B  /C   D   E  /F   (y, x)  0001  0010

    qmc -s "ABCD/E/F+ABC/D/E/F+/AB/CDE/F+/A/B/CDE/F"

    A*B*C*/E*/F+/A*/C*D*E*/F

    int A=a<b, B=a<x, C=a<y, D=b<x, E=b<y, F=x<y;
    int ylower = A&B&C&~E&~F|~A&~C&D&E&~F;

The truth table for whether or not point a is the upper bound in the
existence of an intersection is

    case   perm.   a<b a<x a<y b<x b<y x<y  inter. (abxy, abxy)
    ----  -------  --- --- --- --- --- ---  ------ ------------
      9   b x a y  /A  /B   C   D   E   F   (x, a)  0010  1000
     11   b y a x  /A   B  /C   D   E  /F   (y, a)  0001  1000
     15   x b a y  /A  /B   C  /D   E   F   (b, a)  0100  1000
     21   y b a x  /A   B  /C   D  /E  /F   (b, a)  0100  1000

    qmc -s "/A/BCDEF+/AB/CDE/F+/A/BC/DEF+/AB/CD/E/F"

    /A*B*/C*D*/F+/A*/B*C*E*F

    int A=a<b, B=a<x, C=a<y, D=b<x, E=b<y, F=x<y;
    int aupper = ~A&B&~C&D&~F|~A&~B&C&E&F;

To find the expression for whether or not b is the upper bound:

    case   perm.   a<b a<x a<y b<x b<y x<y  inter. (abxy, abxy)
    ----  -------  --- --- --- --- --- ---  ------ ------------
      3   a x b y   A   B   C  /D   E   F   (x, b)  0010  0100
      5   a y b x   A   B   C   D  /E  /F   (y, b)  0001  0100
     13   x a b y   A  /B   C  /D   E   F   (a, b)  1000  0100
     19   y a b x   A   B  /C   D  /E  /F   (a, b)  1000  0100

    qmc -s "ABC/DEF+ABCD/E/F+A/BC/DEF+AB/CD/E/F"

    A*B*D*/E*/F+A*C*/D*E*F

    int A=a<b, B=a<x, C=a<y, D=b<x, E=b<y, F=x<y;
    int bupper = A&B&D&~E&~F|A&C&~D&E&F;

To find the expression for whether or not x is the upper bound:

    case   perm.   a<b a<x a<y b<x b<y x<y  inter. (abxy, abxy)
    ----  -------  --- --- --- --- --- ---  ------ ------------
      6   a y x b   A   B   C  /D  /E  /F   (y, x)  0001  0010
     12   b y x a  /A  /B  /C   D   E  /F   (y, x)  0001  0010
     20   y a x b   A   B  /C  /D  /E  /F   (a, x)  1000  0010
     22   y b x a  /A  /B  /C   D  /E  /F   (b, x)  0100  0010

    qmc -s "ABC/D/E/F+/A/B/CDE/F+AB/C/D/E/F+/A/B/CD/E/F"

    A*B*/D*/E*/F+/A*/B*/C*D*/F

    int A=a<b, B=a<x, C=a<y, D=b<x, E=b<y, F=x<y;
    int xupper = A&B&~D&~E&~F|~A&~B&~C&D&~F;

And finally for y:

    case   perm.   a<b a<x a<y b<x b<y x<y  inter. (abxy, abxy)
    ----  -------  --- --- --- --- --- ---  ------ ------------
      4   a x y b   A   B   C  /D  /E   F   (x, y)  0010  0001
     10   b x y a  /A  /B  /C   D   E   F   (x, y)  0010  0001
     14   x a y b   A  /B   C  /D  /E   F   (a, y)  1000  0001
     16   x b y a  /A  /B  /C  /D   E   F   (b, y)  0100  0001

    qmc -s "ABC/D/EF+/A/B/CDEF+A/BC/D/EF+/A/B/C/DEF"

    A*C*/D*/E*F+/A*/B*/C*E*F

    int A=a<b, B=a<x, C=a<y, D=b<x, E=b<y, F=x<y;
    int yupper = A&C&~D&~E&F|~A&~B&~C&E&F;


Blurring one's eyes a bit, these boolean expressions answer specialized order
statistic questions for an input of size four under some bizarre circumstances
where we claim we do not want any answer.  With appropriate tracking, k-th
selection algorithms could likely be used to achieve these results.  Allegedly
Knuth's TAOCP volume 3 section 5.3.3 provides an exact upper bound on similar
questions.  Similarly, we could decide to just sort, read off the results, and
then compare to determine if the 2nd and 3rd order statistic implies an
intersection occurred.  Concepts like Sorting Networks
http://en.wikipedia.org/wiki/Sorting_network would be useful here.

Code and Unit Tests
-------------------

Anyhow, let's put all of this nonsense together into a usable function...

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
     */
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

Then let's test the logic with [FCTX](http://fctx.wildbearsoftware.com/).
Comprehensive test cases, employing 1234 in lieu of abxy, are fairly easy to
come by here as we've already enumerated what we expect to occur:

    #include "fct.h"

    FCT_BGN()
    {
        FCT_QTEST_BGN(isect)
        {
            // Table driven test inputs and expected results
            // Test index   =  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
            const int a[24] = {1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,4};
            const int b[24] = {2,2,3,3,4,4,1,1,3,3,4,4,1,1,2,2,4,4,1,1,2,2,3,3};
            const int x[24] = {3,4,2,4,2,3,3,4,1,4,1,3,2,4,1,4,1,2,2,3,1,3,1,2};
            const int y[24] = {4,3,4,2,3,2,4,3,4,1,3,1,4,2,4,1,2,1,3,2,3,1,2,1};
            const int I[24] = {0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0};
            const int L[24] = {0,0,2,2,2,2,0,0,2,2,2,2,2,2,2,2,0,0,2,2,2,2,0,0};
            const int H[24] = {0,0,3,3,3,3,0,0,3,3,3,3,3,3,3,3,0,0,3,3,3,3,0,0};

            // Test each column in the table above
            for (size_t j = 0; j < 24; ++j) {
                double lo, hi;
                const int res = isect(a[j], b[j], x[j], y[j], &lo, &hi);
                fct_xchk(res == I[j], "Test %d wrong: %d vs %d", j+1, res, I[j]);
                if (I[j]) {
                    fct_xchk(lo == L[j], "Lower %d wrong: %d vs %g", j, lo, L[j]);
                    fct_xchk(hi == H[j], "Upper %d wrong: %d vs %g", j, hi, H[j]);
                }
            }
        }
        FCT_QTEST_END();
    }
    FCT_END();

Notice that the test case indices do not match the case numbers cataloged
above.  This test driver gives function isect() a clean bill of health.  I have
confidence in it as a (now fixed) mistake in feeding the "aupper" conditions to
qmc produced an invalid result which the tests let me uncover.

As drafted, `isect()` has six compares, a whole slew of bitwise operations, and
then some floating point operations.  Is this a performant idea?  Would it be
better to introduce branches to eliminate unnecessary computations?  How about
at `-O3` on your favorite compiler?  Having never benchmarked it, I dunno.  Is
there a cleaner way to do all of this that doesn't look like a hammer mechanic
did it?  Probably.

On thing likely worth doing is deferring computing the intersection segment
unless an intersection actually exists...

    /* Revised */
    int isect(double a, double b, double x, double y, double *l, double *u)
    {
        const int A=a<b, B=a<x, C=a<y, D=b<x, E=b<y;
        const int ret = B&~E|B&~D|B&~C|C&~E|C&~D|~B&C|D&~E|~C&D|~B&D|~D&E|~C&E|~B&E;
        if (ret) {
            const int F=x<y;
            *l  = a*(A&B&~C&~E&~F|A&~B&C&~D&F  ); /* alower */
            *u  = a*(~A&B&~C&D&~F|~A&~B&C&E&F  ); /* aupper */
            *u += b*(A&B&D&~E&~F|A&C&~D&E&F    ); /* bupper */
            *l += b*(~A&~C&D&~E&~F|~A&~B&~D&E&F); /* blower */
            *u += x*(A&B&~D&~E&~F|~A&~B&~C&D&~F); /* xupper */
            *l += x*(A&B&C&~D&F|~A&~B&D&E&F    ); /* xlower */
            *l += y*(A&B&C&~E&~F|~A&~C&D&E&~F  ); /* ylower */
            *u += y*(A&C&~D&~E&F|~A&~B&~C&E&F  ); /* yupper */
        }
        return ret;
    }

...as this permits returning as quickly as possible when no intersection
occurs.  The floating point and bitwise operations have been interspersed to
hopefully let an optimizer fill the pipeline.  Lastly, the operations have been
interleaved to possibly assist the optimizer with common subexpression
elimination.  This revision passes the same test suite as the original.  I
suspect it will perform better.  Though, in theory, a [Sufficiently Smart
Compiler](http://c2.com/cgi/wiki?SufficientlySmartCompiler) should produce the
same output from both versions.
