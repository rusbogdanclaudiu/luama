#
# Makefile
#
# $Id$
#
# Makefile for macchina.io Linux Devices Bundle
#


#.PHONY: .lua
#.lua:
#	@echo "compiling lua"
#	$(MAKE) linux -C ./src/lua

#$(objdirs): .lua

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global


#INCLUDE += -I$(PROJECT_BASE)/devices/Devices/include

TARGET := $@
CLEAN_LUA := $(shell if [ $TARGET == 'clean' ]; then $(MAKE) clean -C ./src/lua/; else $(MAKE) linux -C ./src/lua/; fi ) 

LIBRARY += -L./src/lua/src 

#objects = LinuxLED BundleActivator 
objects = BundleActivator 


target         = io.macchina.luama
target_version = 1
target_libs    = PocoRemotingNG PocoOSP PocoUtil PocoXML PocoFoundation lua

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o./bundles luama.bndlspec

#compiling happens here:
include $(POCO_BASE)/build/rules/dylib
