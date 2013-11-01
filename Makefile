# GNU-like toolchain assumed

HOWSTRICT ?= -std=c99
HOWFAST   ?= -g -O2 -DNDEBUG
CFLAGS    ?= $(HOWSTRICT) $(HOWFAST)

CASES=isect1 isect2
all: $(CASES)

# Common FCTX-based test driver
isect-test.o: isect-test.c  fct.h

# Implementation 1 linked against common test driver
isect1.o:     isect1.c      isect.h
isect1:       isect-test.o  isect1.o

# Implementation 2 linked against common test driver
isect2.o:     isect2.c      isect.h
isect2:       isect-test.o  isect2.o

clean:
	rm -f $(CASES) *.o

check: $(CASES)
	@echo
	./isect1
	@echo
	./isect2
