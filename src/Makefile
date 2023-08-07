CC = cc
CFLAGS = -O3 -Wextra -Wall -Wundef -Wfloat-equal -Wstrict-prototypes -Wunreachable-code
DFLAGS = -MM -MP

SUBDIRS := \
	queue \
	event-loop
SUBDIRS_BUILD := $(patsubst %, build_%, $(SUBDIRS))
SUBDIRS_CLEAN := $(patsubst %, clean_%, $(SUBDIRS))

all: $(SUBDIRS_BUILD) 

$(SUBDIRS_BUILD): FORCE
	@echo "Building subdir: $(patsubst build_%, %, $@)";
	@cd $(patsubst build_%, %, $@); CC="$(CC)" CFLAGS="$(CFLAGS)" DFLAGS="$(DFLAGS)" $(MAKE);

clean: $(SUBDIRS_CLEAN)

$(SUBDIRS_CLEAN): FORCE
	@echo "Cleaning subdir: $(patsubst build_%, %, $@)";
	@cd $(patsubst clean_%, %, $@); CC="$(CC)" CFLAGS="$(CFLAGS)" DFLAGS="$(DFLAGS)" $(MAKE) clean;

FORCE:

.PHONY: all clean
