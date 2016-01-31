#######################################################################################################################
# Variables
#------------------------------------------- Compiler and linker ------------------------------------------------------
CXX = g++
LD = g++
DEBUGGER = valgrind
#--------------------------------------------- Compiling flags --------------------------------------------------------
# C++ 2011: -std=c++11, for older compiler -std=c++0x.
ISO_FLAGS = -std=c++11
WARNINGS_FLAGS = -Wall -c
OPTIMIZATION_FLAGS = -O3
PROFILING_FLAGS = -fprofile-arcs -ftest-coverage -fprofile-arcs
DEBUGGIN_FLAGS = -ggdb
CXX_FLAGS = $(ISO_FLAGS) $(OPTIMIZATION_FLAGS)
#----------------------------------------------- Linking flags --------------------------------------------------------
LIN_PROFILING_FLAGS = -fprofile-arcs -pthread -pg
LD_FLAGS = 
#--------------------------------------------- Other variables --------------------------------------------------------
EXE = test
OBJECTS = objects/main.o objects/KnapsackAlgorithm.o
OBJECTS_GENETIC = objects/main_genetic.o
#######################################################################################################################
# Targets
all: build

build: $(EXE)

run: build
	./$(EXE)

run-genetic: genetic
	./$(EXE)

debug: build
	$(DEBUGGER) ./$(EXE)

debug-memory: build
	$(DEBUGGER) --leak-check=full --show-leak-kinds=all ./$(EXE)

test: $(TEST)
	./$(TEST)

rebuild:
	make clean; make

rerun:
	make clean; make run

rerun-genetic:
	make clean; make run-genetic

clean:
	rm -r objects; rm $(EXE);

#######################################################################################################################
# Main
$(EXE): objectDir $(OBJECTS)
	$(LD) $(OBJECTS) -o $(EXE) $(LD_FLAGS)

objectDir: 
	mkdir -p objects

objects/main.o: src/main.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

objects/KnapsackAlgorithm.o: src/KnapsackAlgorithm.cpp src/KnapsackAlgorithm.hpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@


genetic: objectDir $(OBJECTS_GENETIC)
	$(LD) $(OBJECTS_GENETIC) -o $(EXE) $(LD_FLAGS)

objects/main_genetic.o: src/main_genetic.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@