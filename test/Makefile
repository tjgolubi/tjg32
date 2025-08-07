# Copyright 2025 Terry Golubiewski, all rights reserved.

export PROJNAME:=tjg32
export PROJDIR := $(abspath ..)
# SWDEV := $(PROJDIR)/SwDev
include $(SWDEV)/project.mk

TJG:=$(PROJDIR)/tjg
CRC:=$(PROJDIR)/src

# Must use "=" instead of ":=" because $E will be defined below.
CRC_TEST_E=CrcTest.$E
CRC_TIME_E=CrcTime.$E
TARGET1=$(CRC_TEST_E)
TARGET2=$(CRC_TIME_E)
TARGETS=$(TARGET1) $(TARGET2)

SRC1:=CrcTest.cpp
SRC2:=CrcTime.cpp
SOURCE:=$(SRC1) $(SRC2)

SYSINCL:=$(addsuffix /include, $(UNITS)/core $(UNITS)/systems $(GSL))
INCLUDE:=$(PROJDIR)/src

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
