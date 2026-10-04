#include <stdio.h>

#include <stdlib.h> // free

#include <ctype.h> // isdigit

#include "regression.h"
#include "datetonumber.h"

#define MAX_ENTRIES 10

struct weight_entry
{
  int year;
  int month;
  int day;
  double weight;
};


int main(int argc, char *argv[])
{
  printf("Starting program\n");
  // Read file
  int c;
  int is_comment = 0;

  struct weight_entry we;
  struct weight_entry wes[MAX_ENTRIES];
  double arr[MAX_ENTRIES][2];

  int wesindex = 0;

  char *lineptr = NULL;
  size_t n;

  // Debugging
  int current_line = 0;

  while (getline(&lineptr, &n, stdin) != EOF)
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

    // TODO inefficient shifting operation top maintain MAX_ENTRIES
    if (wesindex >= MAX_ENTRIES)
    {
      // shift every entry
      for (int j = 0; j < MAX_ENTRIES - 1; j++)
      {
        arr[j][0] = arr[j + 1][0];
        arr[j][1] = arr[j + 1][1];
      }
      wesindex = MAX_ENTRIES - 1;
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

  // free
  free(lineptr);
  return 0;
}
