# Makefile aplicado para todos los ejercicios del proyecto

CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wpedantic
INCLUDES := -Iinclude
SRC_DIR := ejercicios
BIN_DIR := bin

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
TARGETS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%,$(SOURCES))

EX ?= 02_sorted_intersect
IN ?= in.txt
OUT ?= out.txt

.PHONY: all one run run-file list clean help

all: $(TARGETS)

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@

one: $(BIN_DIR)/$(EX)

run: one
	./$(BIN_DIR)/$(EX)

run-file: one
	./$(BIN_DIR)/$(EX) < $(IN) > $(OUT)

list:
	@echo "Ejecutables disponibles:"
	@for f in $(TARGETS); do echo $$f; done

clean:
	rm -rf $(BIN_DIR)

help:
	@echo "Comandos disponibles:"
	@echo "  make all"
	@echo "  make one EX=09_longest_zigzag"
	@echo "  make run EX=09_longest_zigzag"
	@echo "  make run-file EX=09_longest_zigzag IN=caso.txt OUT=resultado.txt"
	@echo "  make list"
	@echo "  make clean"
