#include <stdlib.h> // free
#include <stdio.h>

#include "weight_calculator.h"

#define DEFAULT_ENTRIES 7

int main(int argc, char *argv[])
{
  printf("Starting program\n");
  int entries = DEFAULT_ENTRIES;
  if (argc == 1)
  {
    printf("Usage: logfile number_of_entries\n");
    return 0;
  }
  if (argc >= 3)
  {
    entries = atoi(argv[2]);
  }


  FILE *fileptr = fopen(argv[1], "r");

  int result = calculate_weight(fileptr, entries);

  fclose(fileptr);

  return result;
}
