HOME = .
SRC = $(HOME)/src
BIN = $(HOME)/bin
INC = $(HOME)/include
OBJ = $(HOME)/obj

CXXFLAGS = -std=c++17 -O3 -Wall -Wextra -Wfloat-equal -Wpedantic

ifeq ($(debug), 1)
# target para debug (cambiamos flags y el mensaje)
CXXFLAGS = -std=c++17 -g -Wall -Wextra -Wfloat-equal -Wpedantic
endif

all: crear_carpetas \
	  $(BIN)/ejercicio1


$(BIN)/% : $(SRC)/%.cpp $(OBJ)/funciones.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -I$(INC)


$(OBJ)/funciones.o : $(SRC)/funciones.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@ -I$(INC)

clean:
	-rm $(BIN)/*
	-rm $(OBJ)/*

crear_carpetas:
	@-mkdir -p $(OBJ)
	@-mkdir -p $(BIN)
