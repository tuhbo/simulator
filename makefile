CC = gcc
CFLAGS = -Wall -g -O2 -Werror

EXE = program

SRC = ./src

CODE = $(SRC)/cpu/mmu.c $(SRC)/disk/code.c $(SRC)/memory/instruction.c $(SRC)/memory/dram.c $(SRC)/main.c

main:
	$(CC) $(CFLAGS) -I$(SRC) $(CODE) -o $(EXE)

run:
	./$(EXE)