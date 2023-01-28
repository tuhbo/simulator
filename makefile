CC = gcc
CFLAGS = -Wall -g -Werror -Wno-unused-function

EXE = simulator

SRC_DIR = ./src

COMMON = $(SRC_DIR)/common/print.c $(SRC_DIR)/common/convert.c

CPU = $(SRC_DIR)/hardware/cpu/mmu.c $(SRC_DIR)/hardware/cpu/isa.c
MEMORY = $(SRC_DIR)/hardware/memory/dram.c

MAIN = $(SRC_DIR)/main.c

.PHONY:simulator
simulator:
	$(CC) $(CFLAGS) -I$(SRC_DIR) $(COMMON) $(CPU) $(MEMORY) $(DISK) $(MAIN) -o $(EXE)

run:
	./$(EXE)

clean:
	rm -rf *.o $(EXE)