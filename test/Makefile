# Copyright 2025 Terry Golubiewski, all rights reserved.

export PROJNAME:=tjg32
export PROJDIR := $(abspath ..)
# SWDEV := $(PROJDIR)/SwDev
include $(SWDEV)/project.mk

APP:=$(abspath $(HOME)/App)
BOOST:=$(APP)/boost
MP11:=$(APP)/mp11

TJG:=$(PROJDIR)/tjg
CRC:=$(PROJDIR)/crc

# Must use "=" instead of ":=" because $E will be defined below.
CRC_TEST_E=CrcTest.$E
CRC_TIME_E=CrcTime.$E
REFLECT_E=Reflect.$E
INTEGER_E=Integer.$E
CRCFILE_E=CrcFile.$E

TARGET1=$(CRC_TEST_E)
TARGET2=$(CRC_TIME_E)
TARGET3=$(REFLECT_E)
TARGET4=$(INTEGER_E)
TARGET5=$(CRCFILE_E)
TARGETS=$(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5)

SRC1:=CrcTest.cpp
SRC2:=CrcTime.cpp
SRC3:=Reflect.cpp
SRC4:=Integer.cpp
SRC5:=CrcFile.cpp
SOURCE:=$(SRC1) $(SRC2) $(SRC3) $(SRC4) $(SRC5)

#SYSINCL:=$(addsuffix /include, $(UNITS)/core $(UNITS)/systems $(GSL))
SYSINCL:=$(addsuffix /include, $(MP11))
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
