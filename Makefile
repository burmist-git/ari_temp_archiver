########################################################################
#                                                                      #
# Copyright(C) 2019 - LBS - (Single person developer.)                 #
# Sun Apr 21 23:12:30 JST 2019                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# Script description:                                                  #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
########################################################################

ROOTCFLAGS  = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS    = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS   = $(shell $(ROOTSYS)/bin/root-config --glibs)
ROOTLDFLAGS = $(shell $(ROOTSYS)/bin/root-config --ldflags)

# add xml files
#ROOTLIBS += -lMLP -lXMLIO

OUTLIB = /home/hvala/ari_temp_archiver/obj/

CXX  = g++
CXX += -I./     

CXXFLAGS  = -g -Wall -fPIC -Wno-deprecated
CXXFLAGS += $(ROOTCFLAGS)
CXXFLAGS += $(ROOTLIBS)
CXXFLAGS += $(ROOTGLIBS)
CXXFLAGS += $(ROOTLDFLAGS)
CXXFLAGSDICT = -g -Wall -fPIC -Wno-deprecated

.PHONY: makedir runana_ari_temp_arch clean

#----------------------------------------------------#

all: makedir ari_temp_archiver_converter runana_ari_temp_arch

makedir:
	mkdir -p $(OUTLIB);

ari_temp_archiver_converter: ari_temp_archiver_converter.cc
	$(CXX) -DARI_TEMP_ARCHIVER_CONVERT_MAIN -o $@ $< $(CXXFLAGS)

runana_ari_temp_arch:
	make -f Makefileana_ari_temp_arch

clean: 
	rm -f *~
	rm -f .*~
	rm -f ari_temp_archiver_converter
	make -f Makefileana_ari_temp_arch clean
