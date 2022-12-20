#include "cpu/register.h"
#include <stdio.h>

int main() {
  reg.rax = 0x1234abcd5678ffaa;

  printf("eax:%x\n", reg.eax);
  return 0;
}