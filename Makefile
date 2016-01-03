#
# File:  Makefile (for library)
#

CC=g++
CXXFLAGS = -std=c++11
INCLUDE=-I/usr/local/include -I/usr/local/include/SDL2 -Isrc -Isrc/nodes -Isrc/actions

LIB=lib/libFayEngine.a
LIBDEST=/usr/local


LIBSRC=$(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
LIBOBJ=$(LIBSRC:.cpp=.o)

all:
	@echo lib Makefile - Making lib
	@make default
	
default: $(LIB)
	@echo "lib Makefile - Done ($(LIB))"

install: all
	@echo lib Makefile - installing $(LIB)
	@install -m 444 $(LIB) $(LIBDEST)

$(LIB): $(LIBOBJ)
	@echo lib Makefile - archiving $(LIB)
	@$(AR) r $(LIB) $(wildcard build/*.o)

%.o: %.cpp
	@echo lib Makefile - compiling $<
	@$(CC) $(CXXFLAGS) $(INCLUDE) -c $< -o build/$(@F)

