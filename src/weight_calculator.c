#include <stdio.h>
#include <stdlib.h> // free
#include <ctype.h> // isdigit

#include "weight_calculator.h"
#include "regression.h"
#include "datetonumber.h"

#define MAX_ENTRIES 100

struct weight_entry
{
  int year;
  int month;
  int day;
  double weight;
};

int calculate_weight(FILE *fileptr, int entries)
{
  if (entries > MAX_ENTRIES)
  {
    printf("Too many entries in argument. Maximum %d entries\n", MAX_ENTRIES);
    return 1;
  }
  // Read file
  int c;

  struct weight_entry we;
  double arr[MAX_ENTRIES][2];

  int wesindex = 0;

  char *lineptr = NULL;
  size_t n;

  // Debugging
  int current_line = 0;

  while (getline(&lineptr, &n, fileptr) != EOF)
  {
    // fill date
    char *p = lineptr;
    int i = 0;

    // Remove whitespace
    for (; (c = *(p + i)) == ' '; i++);
    if (c == '\n' || c == '#')
    {
      continue;
    }
    
    for (; (c = *(p + i)) != '-'; i++)
    {
      if (!isdigit(c))
      {
        printf("Error: Invalid format for year at line %d\n%s",
          current_line, lineptr);
        free(lineptr);
        return 1;
      }
    }
    *(p + i) = '\0';
    we.year = atoi(p);
    p = p + i + 1;
    i = 0;

    for (; (c = *(p + i)) != '-'; i++)
    {
      if (!isdigit(c))
      {
        printf("Error: Invalid format for month at line %d\n%s",
          current_line, lineptr);
        free(lineptr);
        return 1;
      }
    }
    *(p + i) = '\0';
    we.month = atoi(p);
    p = p + i + 1;
    i = 0;

    for (; (c = *(p + i)) != ' '; i++)
    {
      if (!isdigit(c))
      {
        printf("Error: Invalid format for day at line %d\n%s",
          current_line, lineptr);
        free(lineptr);
        return 1;
      }
    }
    *(p + i) = '\0';
    we.day = atoi(p);
    p = p + i + 1;
    i = 0;

    for (; (c = *(p + i)) != ' ' && c != '\n'; i++)
    {
      if (!isdigit(c) && c != '.')
      {
        printf("Error: Invalid format for weight at line %d\n%s",
          current_line, lineptr);
        free(lineptr);
        return 1;
      }
    }
    *(p + i) = '\0';
    we.weight = atof(p);
    p = p + i + 1;
    i = 0;

    // TODO inefficient shifting operation top maintain entry count
    if (wesindex >= entries)
    {
      // shift every entry
      for (int j = 0; j < entries - 1; j++)
      {
        arr[j][0] = arr[j + 1][0];
        arr[j][1] = arr[j + 1][1];
      }
      wesindex = entries - 1;
    }
    arr[wesindex][0] = date_to_number(we.year, we.month, we.day);
    arr[wesindex][1] = we.weight;
    wesindex++;

    current_line++;
  }
  double b0;
  double b1;
  calculate_simple_linear_regression(arr, wesindex, &b0, &b1);
  printf("b0: %f, b1: %f\n", b0, b1);

  // free resource
  free(lineptr);
  return 0;
}
