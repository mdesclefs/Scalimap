.PHONY: clean, mrproper
.SUFFIXES:

CXX=mpiCC
CXX = g++
#CFLAGS=-W -Wall -ansi -pedantic -std=c++0x
CFLAGS= -Wall -ansi -pedantic -std=c++0x
LDFLAGS=

EXEC:= bin/Scalimap
EXECTEST:= bin/ScalimapTest

BUILDDIR:= build/
SRCDIR:= src/
TESTDIR:= test/

FILE:= main.o Pixel.o Image.o ScalingAlgorithm.o ScalingUp.o
OBJ:= $(addprefix $(BUILDDIR), $(FILE)) 

TESTFILE:= ScalingUpTest.o
TESTOBJ:= $(addprefix $(TESTDIR), $(TESTFILE))


all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $^ -o $(EXEC) $(CFLAGS)

$(BUILDDIR)%.o: $(SRCDIR)%.cpp
	$(CXX) -c $< -o $@ $(CFLAGS)
	
	
test: //$(EXECTEST)

$(EXECTEST): $(TESTOBJ)
	$(CXX) $^ -o $(EXEC) $(CFLAGS)

$(TESTDIR)%.o: $(TESTDIR)%.cpp
	$(CXX) -c $< -o $@ $(CFLAGS)

$(BUILDDIR)%.o: $(SRCDIR)%.cpp
	$(CXX) -lcppunit -c $< -o $@ $(CFLAGS)
	
clean:
	@rm -rf build/*.o
	
mrproper: clean
	@rm -rf $(EXEC)