#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <headers/common.h>

/**
 * @brief string to number
 * 
 * @param str string
 * @param start start index inclusive
 * @param end end index inclusive(-1 is the end of string)
 * @return uint64_t 
 */
uint64_t string2uint_range(const char *str, int start, int end) {
  end = (end == -1) ? strlen(str) - 1 : end;

  uint64_t value = 0;
  int sign = 0;

  int state = 0;

  for (int i = start; i <= end; ++i) {
    char c = str[i];

    if (state == 0) {
      if (c == '0') {
        state = 1;
        value = 0;
        continue;
      } else if (c >= '1' && c <= '9') {
        state = 2;
        value = (c -'0');
        continue;
      } else if (c == '-') {
        state = 3;
        sign = 1;
        continue;
      } else if (c == ' ') {
        state = 0;
        continue;
      } else {
        goto fail;
      }
    } else if (state == 1) {
      if (c >= '0' && c <= '9') {
        state = 2;
        value = value * 10 + (c - '0');
      } else if (c == 'x') {
        state = 4;
        continue;
      } else if (c == ' ') {
        state = 6;
        continue;
      } else {
        goto fail;
      }
    } else if (state == 2) {
      if (c >= '0' && c <= '9') {
        state = 2;
        uint64_t old_value = value;
        value = value * 10 + (c - '0');
        if (old_value > value) {
          printf("(uint64_t)%s overflow: cannot convert\n", str);
          goto fail;
        }
        continue;
      } else if (c == ' ') {
        state = 6;
        continue;
      }
    } else if (state == 3) {
      if (c == '0') {
        state = 1;
        continue;
      } else if (c >= '1' && c <= '9') {
        state = 2;
        value = c - '0';
        continue;
      } else {
        goto fail;
      }
    } else if (state == 4) {
      if (c >= '0' && c <= '9') {
        state = 5;
        value = value * 16 + (c - '0');
        continue;
      } else if (c >= 'a' && c <= 'f') {
        state = 5;
        value = value * 16 + (c - 'a' + 10);
        continue;
      } else {
        goto fail;
      }
    } else if (state == 5) {
      if (c >= '0' && c <= '9') {
        state = 5;
        uint64_t old_value = value;
        value = value * 16 + (c - '0');
        if (old_value > value) {
          printf("(uint64_t)%s overflow: cannot convert\n", str);
          goto fail;
        }
        continue;
      } else if (c >= 'a' && c <= 'f') {
        state = 5;
        uint64_t old_value = value;
        value = value * 16 + (c - 'a' + 10);
        if (old_value > value) {
          printf("(uint64_t)%s overflow: cannot convert\n", str);
          goto fail;
        }
        continue;
      } else {
        goto fail;
      }
    } else if (state == 6) {
      if (c == ' ') {
        state = 6;
        continue;
      } else {
        goto fail;
      }
    }
  }

  if (sign == 0) {
    return value;
  } else if (sign == 1) {
    if ((value & 0x8000000000000000) != 0) {
      printf("(int64_t)%s: signed overflow: cannot convert\n", str);
      exit(0);
    }
    int64_t new_value = -1 * (int64_t)value; 
    return *((uint64_t *)&new_value);
  }
fail:
  printf("type convert: <%s> cannot be converted to interget\n", str);
  exit(0);
}

// covert string to int64_t
uint64_t string2uint(const char *str) {
  return string2uint_range(str, 0, -1);
}
