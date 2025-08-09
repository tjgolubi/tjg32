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
INTMATH_E=IntMath.$E
INTEGER_E=Integer.$E
META_E=meta.$E

TARGET1=$(CRC_TEST_E)
TARGET2=$(CRC_TIME_E)
TARGET3=$(REFLECT_E)
TARGET4=$(INTMATH_E)
TARGET5=$(INTEGER_E)
TARGET6=$(META_E)
TARGETS=$(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5) $(TARGET6)

SRC1:=CrcTest.cpp
SRC2:=CrcTime.cpp
SRC3:=Reflect.cpp
SRC4:=IntMath.cpp
SRC5:=Integer.cpp
SRC6:=meta.cpp
SOURCE:=$(SRC1) $(SRC2) $(SRC3) $(SRC4) $(SRC5) $(SRC6)

#SYSINCL:=$(addsuffix /include, $(UNITS)/core $(UNITS)/systems $(GSL))
SYSINCL:=
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

$(TARGET5): $(OBJ5) $(LIBS)
        $(LINK)

$(TARGET6): $(OBJ6) $(LIBS)
        $(LINK)
