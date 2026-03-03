# Makefile aplicado para todos los ejercicios del proyecto

CXX := g++
CXXFLAGS := -std=c++11 -O2 -Wall -Wextra -Wpedantic
INCLUDES := -Iinclude
SRC_DIR := talleres
BIN_DIR := bin

ifeq ($(OS),Windows_NT)
EXE_EXT := .exe
MKDIR_BIN := if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
RM_BIN := if exist "$(BIN_DIR)" rmdir /S /Q "$(BIN_DIR)"
RUN_EXE = .\\$(BIN_DIR)\\$(EX)$(EXE_EXT)
else
EXE_EXT := 
MKDIR_BIN := mkdir -p $(BIN_DIR)
RM_BIN := rm -rf $(BIN_DIR)
RUN_EXE = ./$(BIN_DIR)/$(EX)$(EXE_EXT)
endif

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
TARGETS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%$(EXE_EXT),$(SOURCES))

EX ?= 1-2025_semana_santa
DATA_DIR ?= talleres
IN ?= $(DATA_DIR)/in.txt
OUT ?= $(DATA_DIR)/out.txt

.PHONY: all one run run-file list clean help

all: $(TARGETS)


$(BIN_DIR)/%$(EXE_EXT): $(SRC_DIR)/%.cpp
	@$(MKDIR_BIN)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@

one: $(BIN_DIR)/$(EX)$(EXE_EXT)

run: one
	$(RUN_EXE)

run-file: one
	$(RUN_EXE) < $(IN) > $(OUT)

ifeq ($(OS),Windows_NT)
list:
	@echo Ejecutables disponibles:
	@for %%f in ($(TARGETS)) do @echo %%f
else
list:
	@echo "Ejecutables disponibles:"
	@for f in $(TARGETS); do echo $$f; done
endif

clean:
	@$(RM_BIN)

help:
	@echo "Comandos disponibles:"
	@echo "  make all"
	@echo "  make one EX=09_longest_zigzag"
	@echo "  make run EX=09_longest_zigzag"
	@echo "  make run-file EX=09_longest_zigzag"
	@echo "  make run-file EX=09_longest_zigzag DATA_DIR=talleres"
	@echo "  make run-file EX=09_longest_zigzag IN=talleres/caso.txt OUT=talleres/resultado.txt"
	@echo "  make list"
	@echo "  make clean"
