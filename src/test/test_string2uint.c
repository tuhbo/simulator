#include <stdio.h>
#include <headers/common.h>


static void TestString2Uint() {
  const char *nums[12] = {
    "0",
    "-0",
    "0x0",
    "1234",
    "0x1234",
    "0xabcd",
    "-0xabcd",
    "-1234",
    "2147483647",
    "-2147483648",
    "0x8000000000000000",
    "0xffffffffffffffff"
  };

  for (int i = 0; i < 12; i++) {
    printf("%s => %lx\n", nums[i], string2uint_range(nums[i], 0, -1));
  }
}

int main() {
  TestString2Uint();
  return 0;
}
