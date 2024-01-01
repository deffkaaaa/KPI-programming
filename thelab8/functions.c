#include <stdio.h>
#include <math.h>

#define MIN_PRECISION 1
#define MAX_PRECISION 9
#define DECIMAL_PLACES 9
#define MIN_VALUE 0
#define MAX_VALUE 9999

int isValidPrecision(int epsilon)
{
    int inputValid = 0;
    while (!inputValid)
    {
        printf("\x1B[33m"
               "Enter the number of digits after comma (from 1 to 9 decimal places):\n"
               "\x1B[0m");
        if (scanf("%d", &epsilon) != 1 || getchar() != '\n' || (epsilon < MIN_PRECISION && epsilon != 0) || epsilon > MAX_PRECISION)
        {
            printf("\x1B[31m"
                   "Invalid input. Please enter an integer from 1 to 9.\n"
                   "\x1B[0m");
            fflush(stdin);
            continue;
        }
        if (epsilon == 0)
        {
            printf("\x1B[31m"
                   "Sorry but precision cannot be equal to 0.\n"
                   "\x1B[0m");
            fflush(stdin);
            continue;
        }
        inputValid = 1;
    }
    return epsilon;
}
double isValidDouble(char *message, int max_value, int decimal_places)
{
    double num = 0;
    double intPart = 0;
    int inputValid = 0;
    while (!inputValid)
    {
        printf("\x1B[33m"
               "\nEnter %s (0; %d]:\n"
               "\x1B[0m",
               message, max_value);
        if (scanf("%lf", &num) != 1 || getchar() != '\n')
        {
            printf("\x1B[31m"
                   "Invalid input. Please enter a number.\n"
                   "\x1B[0m");
            fflush(stdin);
            continue;
        }
        if (num < 0 || num > MAX_VALUE)
        {
            printf("\x1B[31m"
                   "It seems you`ve entered a value that is out of acceptable range. Please enter a number between 0 and %d.\n"
                   "\x1B[0m",
                   max_value);
            continue;
        }
        if (num == 0)
        {
            printf("\x1B[31m"
                   "Sorry, but the input cannot be equal to zero. Please try again.\n"
                   "\x1B[0m");
            continue;
        }
        if (modf(num * pow(10, decimal_places), &intPart) != 0.0)
        {
            printf("\x1B[31m"
                   "Entered value doesn't have the specified precision. Please enter a number with accuracy to %d decimal places.\n"
                   "\x1B[0m",
                   decimal_places);
            continue;
        }
        inputValid = 1;
    }
    return num;
}
int isValidInt(char *message, int min_value, int max_value)
{
    int num = 0;
    int inputValid = 0;
    while (!inputValid)
    {
        printf("\x1B[33m"
               "\nEnter %s [%d; %d]:\n"
               "\x1B[0m",
               message, min_value, max_value);
        if (scanf("%d", &num) != 1 || getchar() != '\n')
        {
            printf("\x1B[31m"
                   "Invalid input. Please enter a whole number.\n"
                   "\x1B[0m");
            fflush(stdin);
            continue;
        }
        if (num < MIN_VALUE || num > MAX_VALUE)
        {
            printf("\x1B[31m"
                   "Sorry but you`ve entered a value that is out of acceptable range. Please enter a number between %d and %d inclusively.\n"
                   "\x1B[0m",
                   min_value, max_value);
            continue;
        }
        inputValid = 1;
    }
    return num;
}
int isValidChoice(char *message, int choice, int min_choice, int max_choice)
{
    int inputValid = 0;
    while (!inputValid)
    {
        printf("\x1B[33m"
               "\nChoose %s:\n"
               "\x1B[0m",
               message);
        if (scanf("%d", &choice) != 1 || getchar() != '\n')
        {
            printf("\x1b[31m"
                   "Ohh, sorry but there`s an error in your input. Please try again by pressing the specified keys.\n"
                   "\x1b[0m");
            fflush(stdin);
            continue;
        }
        if (choice < min_choice || choice > max_choice)
        {
            printf("\x1b[31m"
                   "Ohh, it seems that there`s an error occured. You`ve entered a number that is out of range of %d and %d.\n"
                   "\x1b[0m",
                   min_choice, max_choice);
            continue;
        }
        inputValid = 1;
    }

    return choice;
}
int oppositeLimits(double min_limit, double max_limit)
{
    int isContrary = 0;
    if (min_limit > max_limit)
    {
        isContrary = 1;
    }
    return isContrary;
}
void printCircuits()
{
    printf("\x1B[34m"
           "\n1)                                                       2)\n");
    printf("        ┌───────┐      ┌─┐ ┌─┐ ┌─┐ ┌─┐                           ┌───────┐             │ │\n");
    printf("o────┬──┤       ├──────┘ └─┘ └─┘ └─┘ └──┬────o           o────┬──┤       ├─────────────┤ ├───────┬────o\n");
    printf("     │  └───────┘             L         │                     │  └───────┘             │ │       │\n");
    printf("     │      R                           │                     │      R                           │\n");
    printf("     │                                  │                     │                         C        │\n");
    printf("     │                                  │                     │                                  │\n");
    printf("     │                                  │                     │                                  │\n");
    printf("     │                    C             │                     │                                  │\n");
    printf("     │                                  │                     │                   L              │\n");
    printf("     │                   │ │            │                     │            ┌─┐ ┌─┐ ┌─┐ ┌─┐       │\n");
    printf("     └───────────────────┤ ├────────────┘                     └────────────┘ └─┘ └─┘ └─┘ └───────┘\n");
    printf("                         │ │\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("3)                                                       4)\n");
    printf("        ┌───────┐             │ │                                ┌───────┐\n");
    printf("o────┬──┤       ├─────────────┤ ├───────┬────o           o────┬──┤       ├───────────────────────┬────o\n");
    printf("     │  └───────┘             │ │       │                     │  └───────┘                       │\n");
    printf("   ┌─┴─┐    R2                          │                   ┌─┴─┐    R2                          │\n");
    printf("   │   │                       C        │                   │   │                                │\n");
    printf("   │   │ R1                             │                   │   │ R1                             │\n");
    printf("   │   │                                │                   │   │                                │\n");
    printf("   └─┬─┘                                │                   └─┬─┘                                │\n");
    printf("     │                   L              │                     │                                  │\n");
    printf("     │            ┌─┐ ┌─┐ ┌─┐ ┌─┐       │                  ───┴───                               │\n");
    printf("o────┴────────────┘ └─┘ └─┘ └─┘ └───────┘                  _______ C                             │\n");
    printf("                                                              │                   L              │\n");
    printf("                                                              │            ┌─┐ ┌─┐ ┌─┐ ┌─┐       │\n");
    printf("                                                         o────┴────────────┘ └─┘ └─┘ └─┘ └───────┘\n"
           "\x1B[0m");
}
double isValidStep(char *message, double last_limit, int max_step, int decimal_places)
{
    double num = 0;
    double intPart = 0;
    int inputValid = 0;
    while (!inputValid)
    {
        printf("\x1B[33m"
               "Enter the change step between %s (0; %d]:\n"
               "\x1B[0m",
               message, max_step);
        if (scanf("%lf", &num) != 1 || getchar() != '\n' || fabs(num) > last_limit)
        {
            printf("\x1B[31m"
                   "It seems you`ve entered an invalid value of change step. Please enter a number between 0 and %g.\n"
                   "\x1B[0m",
                   last_limit);
            fflush(stdin);
            continue;
        }
        if (modf(num * pow(10, decimal_places), &intPart) != 0.0)
        {
            printf("\x1B[31m"
                   "Entered value doesn't have the specified precision. Please enter a number with accuracy to %d decimal places.\n"
                   "\x1B[0m",
                   decimal_places);
            continue;
        }
        if (num == 0 || num < 0)
        {
            printf("\x1B[31m"
                   "Sorry but change step cannot be equal to 0 or less than 0.\n"
                   "\x1B[0m");
            fflush(stdin);
            continue;
        }
        inputValid = 1;
    }
    return num;
}