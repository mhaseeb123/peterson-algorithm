# Makefile for C++ programs

BUILD = DEBUG

LINKCC = $(CXX)

# CXXFLAGS denotes flags for the C++ compiler
CXX = g++

ifeq (${BUILD}, DEBUG)
 BUILD_FLAGS = -O0 -g 
else
 BUILD_FLAGS = -O3
endif

CXXFLAGS = ${BUILD_FLAGS} -Wall -Wextra -Wno-unused-parameter

SRCS = $(wildcard src/*.cpp)
PROGS = $(patsubst %.cpp,%.o,$(SRCS))
EXEC := PetersonMutex.exe

all: $(PROGS) $(EXEC)

PetersonMutex.exe: $(PROGS)
	$(LINKCC) -o $@ -Wl,-Map=$@.map $(PROGS) -lpthread

%.o : %.c
	$(CXX) -c $(CXXFLAGS) -I./ $< -o $@

clean:
	rm -rf $(PROGS) $(EXEC) $(EXEC).map

.PHONY: all clean