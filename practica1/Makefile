HOME = .
SRC = $(HOME)/src
BIN = $(HOME)/bin

CXXFLAGS = -std=c++17 -O3 -Wall -Wextra -Wfloat-equal -Wpedantic

ifeq ($(debug), 1)
# target para debug (cambiamos flags y el mensaje)
CXXFLAGS = -std=c++17 -Og -Wall -Wextra -Wfloat-equal -Wpedantic
endif

all: $(BIN)/ejercicio1 $(BIN)/ejercicio2 $(BIN)/ejercicio3 $(BIN)/ejercicio4


$(BIN)/% : $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
