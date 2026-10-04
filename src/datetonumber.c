#include "datetonumber.h"

int months[] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

int date_to_number(int year, int month, int day)
{
  // probably correct
  int completed_year = year - 1;
  int leap_years_4 = completed_year / 4;
  int leap_years_100 = completed_year / 100;
  int leap_years_400 = completed_year / 400;
  int total_leap_years = leap_years_4 - leap_years_100 + leap_years_400;
  int total_days = year * 365 + total_leap_years + months[month] + day;

  return total_days;
}
