#!/usr/bin/make
####################
top_builddir = ../..
I = $(top_builddir)/src/include
INC = -I$(I)
MKDIRS = d

SERVER_SRCS := \
	main.c

SERVER_OBJS := $(patsubst %.c, %.o, $(SERVER_SRCS))
SERVER_DEPS := $(patsubst %.c, d/%.d, $(SERVER_SRCS))
# SERVER_BIN := $(top_builddir)/bin/server

all: $(MKDIRS) $(SERVER_OBJS) $(SERVER_DEPS)

ifneq ($(wildcard d/*.d),)
-include $(SERVER_DEPS)
endif

$(MKDIRS):
	mkdir -p $@

# $(SERVER_BIN): $(SERVER_OBJS)
# 	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

d/%.d: %.c
	$(CC) $(DFLAGS) $(INC) -c -o $@ $<

clean:  
	rm -f *.o
	rm -f *.d
	rm -rf $(MKDIRS)

.PHONY: all clean
