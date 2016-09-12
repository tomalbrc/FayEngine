#
# File:  Makefile (for library)
#

CC=c++
CXXFLAGS=-std=c++0x
INCLUDE=-I/usr/local/include -I/usr/include/SDL2 -I/usr/local/include/SDL2 -Isrc -Isrc/nodes -Isrc/actions

LIB=libFayEngine.a
LIBDEST=/usr/local/lib/


LIBSRC=$(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
LIBHEADER=$(wildcard src/*.h*) $(wildcard src/*/*.h*)
LIBOBJ=$(LIBSRC:.cpp=.o)

all:
	@mkdir -p lib
	@mkdir -p include
	@echo lib Makefile - Making lib
	@make default
	
default: $(LIB)
	@echo "lib Makefile - made $(LIB)"
	@echo "lib Makefile - copying headers to include/"
	@cp -R $(LIBHEADER) include/

install: all
	@echo "lib Makefile - installing lib $(LIB) > $(LIBDEST)$(LIB)"
	@cp "lib/$(LIB)" "$(LIBDEST)"
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
	@ar rvs lib/$(LIB) $(LIBOBJ)

%.o: %.cpp
	@echo "lib Makefile - compiling $<"
	@$(CC) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

