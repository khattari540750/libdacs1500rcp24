// test.c
#include <stdio.h>
#include "libdacs1500.h"

void
print_hoge (int num)
{
  int i;
  for (i = 0; i < num; i++) {
    printf("hoge\n");
  }
}
