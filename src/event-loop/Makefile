#!/usr/bin/make
####################
top_builddir = ../..
I = $(top_builddir)/src/include
INC = -I$(I)
MKDIRS = d

ALL_SRC := \
	lib.c

ALL_OBJ := $(patsubst %.c, %.o, $(ALL_SRC))
ALL_DEP := $(patsubst %.c, d/%.d, $(ALL_SRC))

all: $(MKDIRS) $(ALL_OBJ) $(ALL_DEP)

ifneq ($(wildcard d/*.d),)
-include $(ALL_DEP)
endif

$(MKDIRS):
	mkdir -p $@

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

d/%.d: %.c
	$(CC) $(DFLAGS) $(INC) -c -o $@ $<

clean:  
	rm -f *.o
	rm -f *.d
	rm -rf $(MKDIRS)

.PHONY: all clean
