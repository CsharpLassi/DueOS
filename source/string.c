#include "string.h"

int StringCompare(char* str1,char* str2)
{
  //TODO
  while(*str1 != '\0' && str2 != '\0')
  {
    if (*str1 != *str2) return 0;
    str1++;
    str2++;
  }

  return 1;
}
