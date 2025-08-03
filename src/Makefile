# Copyright 2025 Terry Golubiewski, all rights reserved.

export PROJNAME:=tjg32
export PROJDIR := $(abspath ..)
SWDEV := $(PROJDIR)/SwDev
include $(SWDEV)/project.mk

EXT:=$(abspath $(PROJDIR)/ext)
GSL:=$(EXT)/GSL

# Must use "=" instead of ":=" because $E will be defined below.
TJG32_E=tjg32.$E
CRC_TEST_E=CrcTest.$E
LOOKUP_E=Lookup.$E
TARGET1=$(TJG32_E)
TARGET2=$(CRC_TEST_E)
TARGET3=$(LOOKUP_E)
TARGETS=$(TARGET1) $(TARGET2) $(TARGET3)

SRC1 := tjg32.cpp
SRC2 := CrcTest.cpp
SRC3 := Lookup.cpp
SOURCE := $(SRC1) $(SRC2) $(SRC3)

SYSINCL:=$(addsuffix /include, $(GSL))
INCLUDE:=$(PROJDIR)

# Must use "=" because LIBS will be changed below.
LIBS=

CFLAGS=-O2

include $(SWDEV)/$(COMPILER).mk
include $(SWDEV)/build.mk

.ONESHELL:

.PHONY: all test clean scour install uninstall

all: depend $(TARGETS)

$(TARGET1): $(OBJ1) $(LIBS)
	$(LINK)

$(TARGET2): $(OBJ2) $(LIBS)
	$(LINK)

$(TARGET3): $(OBJ3) $(LIBS)
	$(LINK)

test:   depend $(CRC_TEST_E)
	./$(CRC_TEST_E)
