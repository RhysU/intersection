# GNU-like toolchain assumed

HOWSTRICT ?= -std=c99 -pedantic
HOWFAST   ?= -g -O3
CFLAGS    ?= $(HOWSTRICT) $(HOWFAST)

CASES=isect1 isect2 isect3 isect4 omsect1 omsect2 omsect3
all: $(CASES)

# Numbered implementations of isect() linked against common FCTX test driver
isect-test.o: isect-test.c fct.h
isect1.o:     isect1.c     isect.h
isect2.o:     isect2.c     isect.h
isect3.o:     isect3.c     isect.h
isect4.o:     isect4.c     isect.h
isect1:       isect-test.o isect1.o
isect2:       isect-test.o isect2.o
isect3:       isect-test.o isect3.o
isect4:       isect-test.o isect4.o

# Numbered implementations of omsect() linked against common FCTX test driver
omsect-test.o:  omsect-test.c  fct.h
omsect1.o:      omsect1.c      omsect.h
omsect2.o:      omsect2.c      omsect.h
omsect3.o:      omsect3.c      omsect.h
omsect1:        omsect-test.o  omsect1.o
omsect2:        omsect-test.o  omsect2.o
omsect3:        omsect-test.o  omsect3.o

# Only the final "production" versions of each have all warnings silenced
isect4.o:  CFLAGS += -Wall -Wextra
omsect3.o: CFLAGS += -Wall -Wextra

clean:
	rm -f $(CASES) *.o

check: $(CASES)
	@(set -e; for case in $(CASES); do echo; ./$$case; done)
