# Copyright 2025 Terry Golubiewski, all rights reserved.

export PROJNAME:=tjg32
export PROJDIR := $(abspath ..)
# SWDEV := $(PROJDIR)/SwDev
include $(SWDEV)/project.mk

APP:=$(abspath $(HOME)/App)
GSL:=$(APP)/GSL
UNITS:=$(APP)/mp-units/src

# Must use "=" instead of ":=" because $E will be defined below.
TJG32_E=tjg32.$E
TARGET1=$(TJG32_E)
TARGETS=$(TARGET1)

SRC1 := tjg32.cpp
SOURCE := $(SRC1)

SYSINCL:=$(addsuffix /include, $(UNITS)/core $(UNITS)/systems $(GSL))
INCLUDE:=$(PROJDIR)

# Must use "=" because LIBS will be changed below.
LIBS=

include $(SWDEV)/$(COMPILER).mk
include $(SWDEV)/build.mk

.ONESHELL:

.PHONY: all clean scour install uninstall

all: $(TARGETS)

$(TARGET1): $(OBJ1) $(LIBS)
        $(LINK)
