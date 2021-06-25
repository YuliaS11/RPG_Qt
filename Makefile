
CXX=g++
GCC_CXXFLAGS=-std=c++14 -Wall -O2 -g -MMD -Werror=vla # use -MMD to generate dependencies
CLANG_CXXFLAGS=-std=c++14 -Wall -O2 -g -MMD -Werror=vla
CXXFLAGS=$(GCC_CXXFLAGS)
QT_PACKAGES=`pkg-config --cflags --libs Qt5Core` # list of used QT Packages
HEADERS=-Iinclude # list of all .h files in the include directory
SOURCES=$(wildcard src/*.cc) # list of all c++ source files in the src directory
OBJECTS=${SOURCES:src/%=build/%} # update path to build folder
OBJECTS:=${OBJECTS:.cc=.o} # .o files depend upon c++ source files with same names
DEPENDS=${OBJECTS:.o=.d} # .d file is list of dependencies for corresponding c++ course file
ifeq ($(OS),Windows_NT)
	EXEC=bin/RPG_Qt.exe
else
	EXEC=bin/RPG_Qt
endif


my-target: export PKG_CONFIG_PATH=$(QT_PATH)

# First target in the makefile is the default target.
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) $(QT_PACKAGES)

build/%.o: src/%.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(QT_PACKAGES) $(HEADERS)

-include ${DEPENDS}

.PHONY: clean
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)

.PHONY: run
run:
	$(EXEC)

.PHONY: debug
debug:
	gdb-multiarch $(EXEC)