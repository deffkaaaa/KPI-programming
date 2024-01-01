#include <stdio.h>

int isLeapYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0 ) || (year % 400 == 0)) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int year = 0, month = 0, date = 0, n = 0;
    int day = 0;
    char again[2];
    const char *days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    printf("===CALENDAR===\n");

    do {
        int inputValid = 0;
        while (!inputValid) {
            printf("Enter the year (1900-2099):\n");
            if (scanf("%d", &year) != 1 || getchar() != '\n' || year < 1900 || year > 2099) {
                printf("Enter a whole number from 1900 to 2099.\n");
                fflush(stdin);
                continue;
            } else if (year < 0) {
                printf("Sorry, but your number cannot be less than zero.\n");
                fflush(stdin);
                continue;
            } else {
                inputValid = 1;
            }
        }
        inputValid = 0;
        while (!inputValid) {
            printf("Enter the month (1-12):\n");
            if (scanf("%d", &month) != 1 || getchar() != '\n' || month < 1) {
                printf("Enter a whole number from 1 to 12.\n");
                fflush(stdin);
                continue;
            } else if (month > 12) {
                printf("There are only 12 months in a year.\n");
                fflush(stdin);
                continue;
            } else if (month < 0) {
                printf("Your number must be positive.\n");
                fflush(stdin);
                continue;
            } else {
                inputValid = 1;
            }
            inputValid = 0;
            while (!inputValid) {
                if (month == 4 || month == 6 || month == 9 || month == 11) {
                    printf("Enter the day (1-30):\n");
                    if (scanf("%d", &date) != 1 || getchar() != '\n' || date < 1) {
                        printf("Please enter a whole number from 1 to 30.\n");
                        fflush(stdin);
                        continue;
                    } else if (date > 30) {
                        printf("This month does not have more than 30 days.\n");
                        fflush(stdin);
                        continue;
                    } else {
                        inputValid = 1;
                    }
                } else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 ||
                           month == 12) {
                    printf("Enter the day (1-31):\n");
                    if (scanf("%d", &date) != 1 || getchar() != '\n' || date < 1) {
                        printf("Enter a whole number from 1 to 31.\n");
                        fflush(stdin);
                        continue;
                    } else if (date > 31) {
                        printf("Months do not have more than 31 days.\n");
                        fflush(stdin);
                        continue;
                    } else {
                        inputValid = 1;
                    }
                } else if (month == 2 && isLeapYear(year) == 1) {
                    printf("Enter the day (1-29):\n");
                    if (scanf("%d", &date) != 1 || getchar() != '\n' || date < 1) {
                        printf("Enter a whole number from 1 to 29.\n");
                        fflush(stdin);
                        continue;
                    } else if (date > 29) {
                        printf("This month does not have more than 29 days in a leap year.\n");
                        fflush(stdin);
                        continue;
                    } else {
                        inputValid = 1;
                    }
                } else if (month == 2 && isLeapYear(year) == 0) {
                    printf("Enter the day (1-28):\n");
                    if (scanf("%d", &date) != 1 || getchar() != '\n' || date < 1) {
                        printf("Enter a whole number from 1 to 28.\n");
                        fflush(stdin);
                        continue;
                    } else if (date > 28) {
                        printf("This month does not have more than 28 days in a not leap year.\n");
                        fflush(stdin);
                        continue;
                    } else {
                        inputValid = 1;
                    }
                } else {
                    inputValid = 1;
                }
            }
            if (month > 2) {
                n = 0;
            } else if (isLeapYear(year)) {
                n = 1;
            } else {
                n = 2;
            }
            day = ((int) (365.25 * year) + (int) (30.56 * month) + date + n) % 7;
            printf("The day is: %s\n", days[day]);
            printf("Completed successfully!\n");
            printf("Press Enter to continue or any other not system key + Enter to exit.\n");
            fgets(again, 2, stdin);
            fflush(stdin);
        }
    } while (again[0] == '\n');
    return 0;
}