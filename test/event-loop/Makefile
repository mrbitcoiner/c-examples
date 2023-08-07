#!/usr/bin/make
####################
top_builddir = ../..
INC = -I$(top_builddir)/src/include

MKDIRS = d

ALL_SRC := \
	main.c

ALL_OBJ := \
	$(top_builddir)/src/queue/main.o \
	$(top_builddir)/src/event-loop/lib.o \
	$(patsubst %.c, %.o, $(ALL_SRC))

ALL_BIN := \
	test

ALL_DEPS := \
	$(patsubst %.c, d/%.d, $(ALL_SRC))

all: $(MKDIRS) $(ALL_BIN) $(ALL_DEPS)  

ifneq ($(wildcard d/*.d),)
-include $(ALL_DEPS)
endif

$(MKDIRS):
	mkdir -p $@

$(ALL_BIN): $(ALL_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

d/%.d: %.c
	$(CC) $(DFLAGS) $(INC) -o $@ $<

clean:
	rm -f *.o
	rm -rf $(ALL_BIN) $(MKDIRS)

.PHONY: all clean
