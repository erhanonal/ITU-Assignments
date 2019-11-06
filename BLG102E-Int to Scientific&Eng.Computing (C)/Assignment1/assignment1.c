//Erhan Önal 01.03.218

#include <stdio.h>  //printf, scanf
#include <stdlib.h> //EXIT_SUCCESS, EXIT_FAILURE

int main() {

  // This segment takes the date input and checks the date
  int year = 0, month = 0, day = 0;
  printf("Enter date [year month day]: ");
  scanf("%d %d %d", &year, &month, &day);

  if (year < 0) {
    printf("Invalid date.\n");
    return EXIT_FAILURE;
  }

  if (month < 0 || month > 12) {
    printf("Invalid date.\n");
    return EXIT_FAILURE;
  }

  if (month == 2) {
    if (day < 1 || day > 28) {
      printf("Invalid date.\n");
      return EXIT_FAILURE;
    }
  } else if (month == 4 || month == 6 || month == 9 || month == 11) {
    if (day < 1 || day > 30) {
      printf("Invalid date.\n");
      return EXIT_FAILURE;
    }
  } else {
    if (day < 1 || day > 31) {
      printf("Invalid date.\n");
      return EXIT_FAILURE;
    }
  }

  // This segment takes end year input and checks end year
  int end_year = 0;
  printf("Enter end year: ");
  scanf("%d", &end_year);

  if (end_year < 1 || end_year < year) {
    printf("Invalid Input.\n");
    return EXIT_FAILURE;
  }

  // This segment converts the input into compatible integers with Zeller's
  // Congruence

  int actual_year = year;
  if (month == 1 || month == 2) {
    month += 12;
    year -= 1;
  }

  int century = year / 100;
  int offset_years = year % 100;

  // This segment calculates the corresponding day for the given date

  int corresponding_day = (day + (13 * (month + 1) / 5) + offset_years +
                           (offset_years / 4) + (century / 4) + 5 * century) %
                          7;
  switch (corresponding_day) {
  case 0:
    printf("It's a Saturday.\n");
    break;
  case 1:
    printf("It's a Sunday.\n");
    break;
  case 2:
    printf("It's a Monday.\n");
    break;
  case 3:
    printf("It's a Tuesday.\n");
    break;
  case 4:
    printf("It's a Wednesday.\n");
    break;
  case 5:
    printf("It's a Thursday.\n");
    break;
  case 6:
    printf("It's a Friday.\n");
    break;
  default:
    printf("Invalid Input.");
  }

  // This Segment calculates how many times the given day and month falls on the
  // same weekday between given year and the end year

  int matched_days = 0;
  int actual_end_year = end_year;
  if (year != actual_year) {
    end_year -= 1;
  }
  for (int i = year + 1; i <= end_year; i++) {
    int century_i = i / 100;
    int offset_years_i = i % 100;
    int corresponding_day_i =
        (day + (13 * (month + 1) / 5) + offset_years_i + (offset_years_i / 4) +
         (century_i / 4) + 5 * century_i) %
        7;
    if (corresponding_day == corresponding_day_i) {
      matched_days++;
    }
  }

  printf("Same day-and-month on same weekday between %d and %d: %d\n",
         actual_year + 1, actual_end_year, matched_days);

  return EXIT_SUCCESS;
}
