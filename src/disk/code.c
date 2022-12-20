#include "memory/instruct.h"

inst_t program[INST_LEN] = {
  {
    MOV,
    {REG, 0, 0, (uint64_t *)&reg.rax, NULL},
    {REG, 0, 0, (uint64_t *)&reg.rbx, NULL},
    "mov rax rbx"
  }
};