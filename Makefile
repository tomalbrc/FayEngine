#
# File:  Makefile (for library)
#

CC=g++
CXXFLAGS = -std=c++11
INCLUDE=-I/usr/local/include -I/usr/local/include/SDL2 -Isrc -Isrc/nodes -Isrc/actions

LIB=lib/libFayEngine.a
LIBDEST=/usr/local/


LIBSRC=$(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
LIBHEADER=$(wildcard src/*.h*) $(wildcard src/*/*.h*)
LIBOBJ=$(LIBSRC:.cpp=.o)

all:
	@echo lib Makefile - Making lib
	@make default
	
default: $(LIB)
	@echo "lib Makefile - made $(LIB)"
	@echo "lib Makefile - copying headers to include/"
	@cp -R $(LIBHEADER) include/

install: all
	@echo "lib Makefile - installing lib $(LIB) > $(LIBDEST)$(LIB)"
	@install -m 444 $(LIB) $(LIBDEST)
	@echo "lib Makefile - installing header include/ > /usr/local/include/FayEngine"
	@cp -R include/ /usr/local/include/FayEngine

clean:
	@echo "lib Makefile - removing .o"
	@rm -f $(LIBOBJ)
	@echo "lib Makefile - removing .a"
	@rm -f lib/*.a
	@echo "lib Makefile - clean done"

$(LIB): $(LIBOBJ)
	@echo "lib Makefile - archiving $(LIB)"
	@ar r $(LIB) $(LIBOBJ)

%.o: %.cpp
	@echo "lib Makefile - compiling $<"
	@$(CC) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

