# Copyright 2025 Terry Golubiewski, all rights reserved.

export PROJNAME:=tjg32
export PROJDIR := $(abspath .)
SWDEV := $(PROJDIR)/SwDev
include $(SWDEV)/project.mk

TARGETS=

SOURCE:=

.ONESHELL:

.PHONY: all test clean scour

all:
	$(MAKE) -C src

test:
	$(MAKE) -C src test

clean:
	$(MAKE) -C src clean

scour:
	$(MAKE) -C src scour
