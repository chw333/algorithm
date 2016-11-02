#! /usr/bin/make

CC=gcc
CFLAGS= -g -ansi -Wall -pedantic
LDFLAGS= -lm

CONTEST = bbox xword matcher monkey trees puzzle theseus
DIRS = $(PRACTICE) $(CONTEST)

%.sout : %.sin $(MAIN)
	./$(MAIN) < $< > $@

%.tout : %.tin $(MAIN)
	./$(MAIN) < $< > $@

%.class : %.java
	javac $<

ifdef MAIN
all: $(MAIN) $(EXTRA) $(MAIN).tout $(MAIN).sout

clean:
	-$(RM) $(MAIN) $(MAIN)_g $(EXTRA) *.sout *.tout

else

all:
	@for d in $(DIRS); do                    \
		if test -f $$d/Makefile; then    \
			$(MAKE) -C $$d all ;     \
		fi;                              \
	done

clean:
	@for d in $(DIRS); do                    \
		if test -f $$d/Makefile; then    \
			$(MAKE) -C $$d clean ;   \
		fi;                              \
	done
endif

.PHONY: all clean
# vim: noexpandtab
