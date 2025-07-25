# Copyright 2025 Terry Golubiewski, all rights reserved.

export PROJNAME:=tjg32
export PROJDIR := $(abspath ..)
# SWDEV := $(PROJDIR)/SwDev
include $(SWDEV)/project.mk

APP:=$(abspath $(HOME)/App)
GSL:=$(APP)/GSL
UNITS:=$(APP)/mp-units/src

# Must use "=" instead of ":=" because $E will be defined below.
LSB32_E=lsb32.$E
MSB32_E=msb32.$E
TARGET1=$(LSB32_E)
TARGET2=$(MSB32_E)
TARGETS=$(TARGET1) $(TARGET2)

SRC1 := lsb32.cpp
SRC2 := msb32.cpp
SOURCE := $(SRC1) $(SRC2)

SYSINCL:=$(addsuffix /include, $(UNITS)/core $(UNITS)/systems $(GSL))
INCLUDE:=$(PROJDIR)

# Must use "=" because LIBS will be changed below.
LIBS=

CFLAGS=-O2

include $(SWDEV)/$(COMPILER).mk
include $(SWDEV)/build.mk

.ONESHELL:

.PHONY: all clean scour install uninstall

all: $(TARGETS)

$(TARGET1): $(OBJ1) $(LIBS)
        $(LINK)

$(TARGET2): $(OBJ2) $(LIBS)
        $(LINK)
