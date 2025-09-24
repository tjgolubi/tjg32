# @file
# @copyright 2025 Terry Golubiewski, all rights reserved.
# @author Terry Golubiewski

export PROJNAME := tjg32
export PROJDIR  := $(abspath ..)
# SWDEV := $(PROJDIR)/SwDev
include $(SWDEV)/project.mk

APP   := $(abspath $(HOME)/App)
BOOST := $(APP)/boost
MP11  := $(APP)/mp11
GSL   := $(APP)/GSL
GTEST := $(APP)/googletest

PRJ   := $(abspath $(HOME)/prj)
FILE  := $(PRJ)/file

TJG := $(PROJDIR)/tjg
CRC := $(PROJDIR)/crc

PROJ_LIB := $(PROJDIR)/lib
PROJ_SRC := $(PROJDIR)/src
PROJ_INC := $(PROJDIR)

GTEST_LIB:=$(GTEST)/build/lib
GTEST_INC:=$(GTEST)/googletest

# Must use "=" instead of ":=" because $E will be defined below.
CRC_TEST_E=CrcTest.$E
CRC_TIME_E=CrcTime.$E
BIT_REVERSE_E=bit_reverse.$E
INTEGER_E=Integer.$E
CRC_FILE_E=CrcFile.$E
INT128_IO_E=int128_io.$E

TGT1=$(CRC_TEST_E)
TGT2=$(CRC_TIME_E)
TGT3=$(BIT_REVERSE_E)
TGT4=$(INTEGER_E)
TGT5=$(CRC_FILE_E)
TGT6=$(INT128_IO_E)
TARGETS=$(TGT1) $(TGT2) $(TGT3) $(TGT4) $(TGT5) $(TGT6)

SRC1:=CrcTest.cpp
SRC2:=CrcTime.cpp
SRC3:=bit_reverse.cpp
SRC4:=Integer.cpp
SRC5:=CrcFile.cpp
SRC6:=int128_io.cpp
SOURCE:=$(SRC1) $(SRC2) $(SRC3) $(SRC4) $(SRC5) $(SRC6)

#SYSINCL:=$(addsuffix /include, $(UNITS)/core $(UNITS)/systems $(GSL))
SYSINCL:=$(BOOST) $(addsuffix /include, $(MP11) $(GSL) $(GTEST_INC))
INCLUDE:=$(PROJ_INC) $(FILE)/src

# Must use "=" because LIBS will be changed below.
LIBS = $(PROJ_LIB)/libtjg32$(COMPILER)$(DBGSFX).$A
LIBS+= $(FILE)/src/libFile$(COMPILER)$(DBGSFX).$A

#DEBUG=1

LIBPATH:=$(GTEST_LIB)

SHELL:=/usr/bin/bash
.ONESHELL:
.SHELLFLAGS:=-eu -o pipefail -c

include $(SWDEV)/$(COMPILER).mk
include $(SWDEV)/build.mk

LDLIBS+=-lgtest -lgtest_main

.PHONY: test success

log/%.log: %.$E
	@set -v
	./$< 2>&1 | tee $(notdir $@)
	mkdir -p $(dir $@)
	mv $(notdir $@) $@

log/%.json: %.$E
	@set -v
	./$< --gtest_output=json:$(notdir $@)
	mkdir -p $(dir $@)
	mv $(notdir $@) $@

CLEAN += log

LOGFILES:=$(patsubst %.exe, log/%.log, $(TARGETS))
LOGFILES:=$(patsubst %/int128_io.log, %/int128_io.json, $(LOGFILES))
LOGFILES:=$(patsubst %/CrcTest.log, %/CrcTest.json, $(LOGFILES))
LOGFILES:=$(patsubst %/CrcFile.log, %/CrcFile.json, $(LOGFILES))

success:
	@echo "All tests passed."

test: depend $(LOGFILES) success

$(TGT1): $(OBJ1) $(LIBS)
	$(LINK)

$(TGT2): $(OBJ2) $(LIBS)
	$(LINK)

$(TGT3): $(OBJ3) $(LIBS)
	$(LINK)

$(TGT4): $(OBJ4) $(LIBS)
	$(LINK)

$(TGT5): $(OBJ5) $(LIBS)
	$(LINK)

$(TGT6): $(OBJ6) $(LIBS)
	$(LINK)
