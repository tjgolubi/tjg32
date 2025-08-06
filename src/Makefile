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
CRC_TEST_E=CrcTest.$E
LOOKUP_E=Lookup.$E
CRC_TIME_E=CrcTime.$E
TARGET1=$(TJG32_E)
TARGET2=$(CRC_TEST_E)
TARGET3=$(LOOKUP_E)
TARGET4=$(CRC_TIME_E)
TARGETS=$(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4)

SRC1:=tjg32.cpp
SRC2:=CrcTest.cpp
SRC3:=Lookup.cpp
SRC4:=CrcTime.cpp
SOURCE:=$(SRC1) $(SRC2) $(SRC3) $(SRC4)

SYSINCL:=$(addsuffix /include, $(UNITS)/core $(UNITS)/systems $(GSL))
INCLUDE:=$(PROJDIR)

# Must use "=" because LIBS will be changed below.
LIBS=

#DEBUG=1

include $(SWDEV)/$(COMPILER).mk
include $(SWDEV)/build.mk

.ONESHELL:

.PHONY: all clean scour install uninstall

all: depend $(TARGETS)

$(TARGET1): $(OBJ1) $(LIBS)
        $(LINK)

$(TARGET2): $(OBJ2) $(LIBS)
        $(LINK)

$(TARGET3): $(OBJ3) $(LIBS)
        $(LINK)

$(TARGET4): $(OBJ4) $(LIBS)
        $(LINK)
