# Makefile aplicado para todos los ejercicios del proyecto

CXX := g++
CXXFLAGS := -std=c++98 -O2 -Wall -Wextra -Wpedantic
INCLUDES := -Iinclude
SRC_DIR ?= ejercicios_arboles
BIN_DIR := bin
OUTPUT_MODE := ex
FIXED_OUTPUT_NAME ?= arboles
BUILD_SCOPE := one

ifeq ($(OS),Windows_NT)
EXE_EXT := .exe
MKDIR_BIN := if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
RM_BIN := if exist "$(BIN_DIR)" rmdir /S /Q "$(BIN_DIR)"
else
EXE_EXT := 
MKDIR_BIN := mkdir -p $(BIN_DIR)
RM_BIN := rm -rf $(BIN_DIR)
endif

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
TARGETS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%$(EXE_EXT),$(SOURCES))

EX ?= 90_test_clases_arboles
DATA_DIR ?= talleres_arboles
IN ?= $(DATA_DIR)/in.txt
OUT ?= $(DATA_DIR)/out.txt

ifeq ($(OUTPUT_MODE),fixed)
OUTPUT_NAME := $(FIXED_OUTPUT_NAME)
else
OUTPUT_NAME := $(EX)
endif

ifeq ($(BUILD_SCOPE),all)
ALL_TARGETS := $(TARGETS)
else
ALL_TARGETS := one
endif

ifeq ($(OS),Windows_NT)
RUN_EXE = ".\\$(BIN_DIR)\\$(OUTPUT_NAME)$(EXE_EXT)"
else
RUN_EXE = "./$(BIN_DIR)/$(OUTPUT_NAME)$(EXE_EXT)"
endif

.PHONY: all one run run-file list clean help

all: $(ALL_TARGETS)


$(BIN_DIR)/%$(EXE_EXT): $(SRC_DIR)/%.cpp
	@$(MKDIR_BIN)
	$(CXX) $(CXXFLAGS) $(INCLUDES) "$<" -o "$@"

$(BIN_DIR)/$(FIXED_OUTPUT_NAME)$(EXE_EXT): $(SRC_DIR)/$(EX).cpp
	@$(MKDIR_BIN)
	$(CXX) $(CXXFLAGS) $(INCLUDES) "$<" -o "$@"

one: $(BIN_DIR)/$(OUTPUT_NAME)$(EXE_EXT)

run: one
	$(RUN_EXE)

run-file: one
	$(RUN_EXE) < $(IN) > $(OUT)

ifeq ($(OS),Windows_NT)
list:
	@echo Ejecutables disponibles:
	@if "$(BUILD_SCOPE)" == "all" (for %%f in ($(TARGETS)) do @echo %%f) else if "$(OUTPUT_MODE)" == "fixed" (echo $(BIN_DIR)\\$(FIXED_OUTPUT_NAME)$(EXE_EXT) ^(desde $(SRC_DIR)\\$(EX).cpp^)) else (echo $(BIN_DIR)\\$(EX)$(EXE_EXT))
else
list:
	@echo "Ejecutables disponibles:"
	@if [ "$(BUILD_SCOPE)" = "all" ]; then for f in $(TARGETS); do echo $$f; done; elif [ "$(OUTPUT_MODE)" = "fixed" ]; then echo "$(BIN_DIR)/$(FIXED_OUTPUT_NAME)$(EXE_EXT) (desde $(SRC_DIR)/$(EX).cpp)"; else echo "$(BIN_DIR)/$(EX)$(EXE_EXT)"; fi
endif

clean:
	@$(RM_BIN)

help:
	@echo "Comandos disponibles:"
	@echo "  Edita OUTPUT_MODE := ex o OUTPUT_MODE := fixed"
	@echo "  Edita FIXED_OUTPUT_NAME := arboles, pruebas, etc."
	@echo "  Edita BUILD_SCOPE := one o BUILD_SCOPE := all"
	@echo "  Edita SRC_DIR := ejercicios_arboles, ejercicios_lpc, talleres_lpc, etc."
	@echo "  make all"
	@echo "  make one EX=90_test_clases_arboles SRC_DIR=ejercicios_arboles"
	@echo "  make run EX=90_test_clases_arboles SRC_DIR=ejercicios_arboles"
	@echo "  make run EX=91_test_ejercicios_arboles SRC_DIR=ejercicios_arboles"
	@echo "  make run-file EX=1-2024_puma SRC_DIR=talleres_lpc DATA_DIR=talleres_lpc"
	@echo "  make run-file EX=1-2024_puma SRC_DIR=talleres_lpc IN=talleres_lpc/in_1-2024.txt OUT=talleres_lpc/out.tmp.txt"
	@echo "  En modo ex genera bin/nombre_del_archivo$(EXE_EXT)"
	@echo "  En modo fixed genera bin/nombre_fijo$(EXE_EXT) usando el .cpp indicado en EX"
	@echo "  En modo one, make compila solo EX"
	@echo "  En modo all, make compila todos los .cpp con sus propios nombres"
	@echo "  make list"
	@echo "  make clean"
