OUT = ./out
BIN = ./bin
SRC = ./src

TEX_FILE = presentacion_MARS.tex
OUT_NAME = $(strip $(OUT))$(strip $(basename $(TEX_FILE))).pdf

.PHONY = all clean crear_carpetas

TEXCC = pdflatex
TEXCCFLAGS = -output-directory=$(OUT)

CXX = g++
CXXFLAGS = -O3 -lcryptopp

CARPETA_ENCONTRADA = $(wildcard $(OUT))

FICHEROS_TEX = $(wildcard src/*)

all: crear_carpetas $(OUT_NAME) demo

$(OUT_NAME) : $(TEX_FILE) $(FICHEROS_TEX)
	$(TEXCC) $(TEXCCFLAGS) $(TEX_FILE)
	# volvemos a compilar, para que genere bien el indice
	$(TEXCC) $(TEXCCFLAGS) $(TEX_FILE)

demo: $(BIN)/prueba_texto_mars $(BIN)/prueba_encriptar_fichero_mars $(BIN)/prueba_desencriptar_fichero_mars

$(BIN)/prueba_texto_mars: $(SRC)/prueba_texto_mars.cpp
	@echo "Compilando prueba de MARS con texto"
	$(CXX) $< -o $@ $(CXXFLAGS)

$(BIN)/prueba_encriptar_fichero_mars: $(SRC)/prueba_encriptar_fichero_mars.cpp
	@echo "Compilando encriptación de fichero con MARS"
	$(CXX) $< -o $@ $(CXXFLAGS)

$(BIN)/prueba_desencriptar_fichero_mars: $(SRC)/prueba_desencriptar_fichero_mars.cpp
	@echo "Compilando desencriptación de fichero con MARS"
	$(CXX) $< -o $@ $(CXXFLAGS)


clean:
	-rm -I $(OUT)/*
	-rm -I $(BIN)/*

crear_carpetas:
ifeq ($(CARPETA_ENCONTRADA),)
	@echo "Creando carpeta de salida"
	@mkdir -p $(OUT)
endif
