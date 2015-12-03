ifdef VERBOSE
		Q =
		E = @true 
else
		Q = @
		E = @echo 
endif

CFILES := $(shell find src -mindepth 1 -maxdepth 4 -name "*.c")
CXXFILES := $(shell find src -mindepth 1 -maxdepth 4 -name "*.cpp")

INFILES := $(CFILES) $(CXXFILES)

OBJFILES := $(CXXFILES:src/%.cpp=%) $(CFILES:src/%.c=%)
DEPFILES := $(CXXFILES:src/%.cpp=%) $(CFILES:src/%.c=%)
OFILES := $(OBJFILES:%=obj/%.o)

BINFILE = bin/network_sim

COMMONFLAGS = 
LDFLAGS = -lstdc++ -ljsoncpp -L/usr/local/lib 

ifdef DEBUG
		COMMONFLAGS := $(COMMONFLAGS) -g
endif
CFLAGS = $(COMMONFLAGS) -std=c99
CXXFLAGS = $(COMMONFLAGS) -std=c++11 -I/usr/local/include
DEPDIR = deps
all: $(BINFILE)
ifeq ($(MAKECMDGOALS),)
-include Makefile.dep
endif
ifneq ($(filter-out clean, $(MAKECMDGOALS)),)
-include Makefile.dep
endif

CC = gcc
CXX = g++


-include Makefile.local

.PHONY: clean all depend
.SUFFIXES:
obj/%.o: src/%.c
		$(Q)if [ ! -d `dirname $@` ]; then mkdir -p `dirname $@`; fi
		$(Q)$(CC) -o $@ -c $< $(CFLAGS)
obj/%.o: src/%.cpp
		$(Q)if [ ! -d `dirname $@` ]; then mkdir -p `dirname $@`; fi
		$(CXX) -o $@ -c $< $(CXXFLAGS)
Makefile.dep: $(CFILES) $(CXXFILES)
		$(Q)xsfor i in $(^); do $(CXX) $(CXXFLAGS) -MM "$${i}" -MT obj/`basename $${i%.*}`.o; done > $@

		
$(BINFILE): $(OFILES)
		$(CXX) -o $@ $(OFILES) $(LDFLAGS)
clean:
		rm -f $(BINFILE) obj/*.o 
		rm -f obj/event/*.o 
		rm -f obj/tcpalgorithm/*.o