.PHONY: clean, mrproper
.SUFFIXES:

#CXX=mpiCC #Linux
CXX=mpic++ #OS X
#CXX = g++
#CFLAGS=-W -Wall -ansi -pedantic -std=c++0x
CFLAGS= -Wall -ansi -pedantic -std=c++0x
LDFLAGS=

MPI_COMPILE_FLAGS = $(shell mpicc --showme:compile)
MPI_LINK_FLAGS = $(shell mpicc --showme:link)

EXEC:= bin/Scalimap
EXECTEST:= bin/ScalimapTest

BUILDDIR:= build/
SRCDIR:= src/
TESTDIR:= test/

FILE:= main.o ScaliException.o Utils.o Pixel.o Image.o ScalingAlgorithm.o ScalingUp.o ScalingDown.o
OBJ:= $(addprefix $(BUILDDIR), $(FILE)) 

TESTFILE:= ScalingUpTest.o
TESTOBJ:= $(addprefix $(TESTDIR), $(TESTFILE))


all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $^ -o $(EXEC) $(LDFLAGS)

$(BUILDDIR)%.o: $(SRCDIR)%.cpp
	$(CXX) $(MPI_COMPILE_FLAGS) -c $< $(MPI_LINK_FLAGS) -o $@ $(CFLAGS)
	
	
#test: //$(EXECTEST)

#$(EXECTEST): $(TESTOBJ)
#	$(CXX) $^ -o $(EXEC) $(LDFLAGS)

#$(TESTDIR)%.o: $(TESTDIR)%.cpp
#	$(CXX) -c $< -o $@ $(CFLAGS)

#$(BUILDDIR)%.o: $(SRCDIR)%.cpp
#	$(CXX) -lcppunit -c $< -o $@ $(CFLAGS)
	
clean:
	@rm -rf build/*.o
	
mrproper: clean
	@rm -rf $(EXEC)