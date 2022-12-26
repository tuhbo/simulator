#include "cpu/register.h"
#include "cpu/mmu.h"
#include "disk/elf.h"
#include "memory/instruction.h"
#include "memory/dram.h"
#include <stdio.h>

static void print_register() {
  printf("rax = %16lx\trbx = %16lx\trcx=%16lx\trdx = %16lx\n",
          reg.rax, reg.rbx, reg.rcx, reg.rdx);
  printf("rsi = %16lx\trdi = %16lx\trbp=%16lx\trsp = %16lx\n",
          reg.rsi, reg.rdi, reg.rbp, reg.rsp);
  printf("rip = %16lx\n", reg.rip);
}

static void print_stack() {
  int n = 10;

  uint64_t *high = (uint64_t *)&mm[va2pa(reg.rsp)];
  high = &high[n];

  uint64_t rsp_start = reg.rsp + n * 8;

  for (int i = 0; i < 2 * n; i++) {
    uint64_t *ptr = (uint64_t *)(high - i);
    printf("%016lx: %16lx", rsp_start, (uint64_t)*ptr);

    if (i == n) {
      printf(" <== rsp");
    }

    rsp_start -= 8;

    printf("\n");
  }
}

int main() {
  init_handler_table();

  reg.rax = 0x12340000;
  reg.rbx = 0x0;
  reg.rcx = 0x8000660;
  reg.rdx = 0xabcd;
  reg.rsi = 0x7ffffffee2f8;
  reg.rdi = 0x1;
  reg.rbp = 0x7ffffffee210;
  reg.rsp = 0x7ffffffee1f0;

  reg.rip = (uint64_t)&program[11];

  write64bits_dram(va2pa(0x7ffffffee210), 0x08000660);
  write64bits_dram(va2pa(0x7ffffffee208), 0x0);
  write64bits_dram(va2pa(0x7ffffffee200), 0xabcd);
  write64bits_dram(va2pa(0x7ffffffee1f8), 0x12340000);
  write64bits_dram(va2pa(0x7ffffffee1f0), 0x08000660);

  print_register();
  print_stack();

  for (int i = 0; i < 15; i++) {
    instruction_cycle();
    print_register();
    print_stack();
  }

  int match = 1;

  match = match && (reg.rax == 0x1234abcd);
  match = match && (reg.rbx == 0x0);
  match = match && (reg.rcx == 0x8000660);
  match = match && (reg.rdx == 0x12340000);
  match = match && (reg.rsi == 0xabcd);
  match = match && (reg.rdi == 0x12340000);
  match = match && (reg.rbp == 0x7ffffffee210);
  match = match && (reg.rsp == 0x7ffffffee1f0);

  if (match) {
    printf("register match\n");
  } else {
    printf("register not match \n");
  }

  match = match && (read64bits_dram(va2pa(0x7ffffffee210)) == 0x08000660);
  match = match && (read64bits_dram(va2pa(0x7ffffffee208)) == 0x1234abcd);
  match = match && (read64bits_dram(va2pa(0x7ffffffee200)) == 0xabcd);
  match = match && (read64bits_dram(va2pa(0x7ffffffee1f8)) == 0x12340000);
  match = match && (read64bits_dram(va2pa(0x7ffffffee1f0)) == 0x08000660);

  if (match) {
    printf("memory match\n");
  } else {
    printf("memory not match\n");
  }
  return 0;
}