#!/usr/bin/make
####################
MKDIRS = bin

CONFIG = \
	.clangd

SUBDIRS := \
	src \
	test
SUBDIRS_BUILD := $(patsubst %, build_%, $(SUBDIRS))
SUBDIRS_CLEAN := $(patsubst %, clean_%, $(SUBDIRS))

all: $(CONFIG) $(MKDIRS) $(SUBDIRS_BUILD)

$(MKDIRS):
	@mkdir -p $@

.clangd:
	@./configure

$(SUBDIRS_BUILD): FORCE
	@echo "Building subdir: $(patsubst build_%, %, $@)"
	@cd $(patsubst build_%, %, $@); $(MAKE);

clean: $(SUBDIRS_CLEAN)
	rm -rf $(MKDIRS) $(CONFIG)
	
$(SUBDIRS_CLEAN): FORCE
	@echo "Cleaning subdir: $(patsubst clean_%, %, $@)"
	@cd $(patsubst clean_%, %, $@); $(MAKE) clean;

FORCE:

.PHONY: all clean
