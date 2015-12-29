#
# Makefile 
#

CC=g++

SOURCES=./src/*.cpp ./src/actions/*.cpp ./src/nodes/*.cpp
IDIR=-I/usr/local/include/SDL2 -I./src/nodes -I./src/actions -I./src
OTHER=-std=c++11 -D_THREAD_SAFE
OTHER_LINUX=-std=gnu++11 -D_REENTRANT

CREATE_DIRS=mkdir -p lib; mkdir -p include; mkdir -p build
CLEAN_DIRS=rm -rf lib/*; rm -rf include/*
MOVE_OUTPUT=mv *.o build/
MAKE_LIB=ar rvs lib/libFayEngine.a build/*.o
COPY_HEADERS=find src/ -name "*.h*" -exec cp {} include/ ";"

END=$(MOVE_OUTPUT); $(MAKE_LIB); $(COPY_HEADERS);

linux:
	$(CREATE_DIRS)
	$(CLEAN_DIRS)
	$(CC) -c $(OTHER_LINUX) $(SOURCES) $(IDIR)
	$(END)
mac:
	$(CREATE_DIRS)
	$(CLEAN_DIRS)
	$(CC) -c $(SOURCES) $(IDIR) $(OTHER)
	$(END)
install:
	mkdir -p /usr/local/include/FayEngine
	cp -R include/*.h* /usr/local/include/FayEngine/
	cp lib/lib*.a /usr/local/lib
	# "############################################################"
	# "Installed to /usr/local/lib and /usr/local/include/FayEngine"
	# "############################################################"


