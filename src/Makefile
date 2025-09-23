# Copyright 2025 Terry Golubiewski, all rights reserved.

PROJNAME := tjg32
PROJDIR  := $(abspath ..)
#SWDEV = $(PROJDIR)/SwDev

include $(SWDEV)/project.mk

PROJ_LIB := $(PROJDIR)/lib
PROJ_SRC := $(PROJDIR)/src
PROJ_INC := $(PROJDIR)

TGT1 = $(PROJ_LIB)/libtjg32$(COMPILER)$(DBGSFX).$A
TARGETS = $(PROJ_LIB) $(TGT1)
SRC1   := int128_io.cpp
SOURCE := $(SRC1)
EXTERN :=
LIBS   :=
SYSINCL:=
INCLUDE:= $(PROJ_INC)
EXTERN :=

include $(SWDEV)/$(COMPILER).mk
include $(SWDEV)/build.mk

$(PROJ_LIB):
	mkdir -p $@

$(TGT1): $(OBJ1) $(EXTERN)
