# Copyright 2025 Terry Golubiewski, all rights reserved.

export PROJNAME:=tjg32
export PROJDIR := $(abspath ..)
# SWDEV := $(PROJDIR)/SwDev
include $(SWDEV)/project.mk

TJG:=$(PROJDIR)/tjg
CRC:=$(PROJDIR)/crc

# Must use "=" instead of ":=" because $E will be defined below.
CRC_TEST_E=CrcTest.$E
CRC_TIME_E=CrcTime.$E
REFLECT_E=Reflect.$E

TARGET1=$(CRC_TEST_E)
TARGET2=$(CRC_TIME_E)
TARGET3=$(REFLECT_E)
TARGETS=$(TARGET1) $(TARGET2) $(TARGET3)

SRC1:=CrcTest.cpp
SRC2:=CrcTime.cpp
SRC3:=Reflect.cpp
SOURCE:=$(SRC1) $(SRC2) $(SRC2)

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
