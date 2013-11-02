# GNU-like toolchain assumed

HOWSTRICT ?= -std=c99
HOWFAST   ?= -g -O2 # -DNDEBUG
CFLAGS    ?= $(HOWSTRICT) $(HOWFAST)

CASES=isect1 isect2 omsect1 omsect2
all: $(CASES)

# Common FCTX-based test drivers
isect-test.o:  isect-test.c  fct.h
omsect-test.o: omsect-test.c fct.h

# Implementations linked against common test driver
isect1.o:  isect1.c      isect.h
isect1:    isect-test.o  isect1.o
isect2.o:  isect2.c      isect.h
isect2:    isect-test.o  isect2.o
omsect1.o: omsect1.c     omsect.h
omsect1:   omsect-test.o omsect1.o
omsect2.o: omsect2.c     omsect.h
omsect2:   omsect-test.o omsect2.o

clean:
	rm -f $(CASES) *.o

check: $(CASES)
	@(set -e; for case in $(CASES); do echo; ./$$case; done)
