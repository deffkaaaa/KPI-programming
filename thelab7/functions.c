#include <stdio.h>
#include <math.h>

#define MIN_PRECISION 1
#define MAX_PRECISION 9
#define MIN_VALUE (-100)
#define MAX_VALUE 100
#define DECIMAL_PLACES 9

double isValidY(double y)
{
    double intPart = 0;
    int inputValid = 0;
    while (!inputValid)
    {
        printf("\x1B[36m"
               "\nEnter the y [-100; 100]:\n"
               "\x1B[0m");
        if (scanf("%lf", &y) != 1 || getchar() != '\n')
        {
            printf("\x1B[31m"
                   "Invalid input. Please enter a number.\n"
                   "\x1B[0m");
            fflush(stdin);
            continue;
        }
        else if (y < MIN_VALUE || y > MAX_VALUE)
        {
            printf("\x1B[31m"
                   "Sorry, but you`ve entered a value that is out of acceptable range. Please enter a number between -100 and 100 inclusively.\n"
                   "\x1B[0m");
            continue;
        }
        else if (modf(y * pow(10, DECIMAL_PLACES), &intPart) != 0.0)
        {
            printf("\x1B[31m"
                   "Entered value doesn't have the specified precision. Please enter a number with accuracy to 9 decimal places.\n"
                   "\x1B[0m");
            continue;
        }
        else
        {
            inputValid = 1;
        }
    }
    return y;
}
double isValidScope(char *name, double min, double max, int decimalPlaces)
{
    double num = 0, intPart = 0;
    int inputValid = 0;
    while (!inputValid)
    {
        printf("\x1B[36m"
               "Enter the %s [-100; 100]:\n"
               "\x1B[0m",
               name);
        if (scanf("%lf", &num) != 1 || getchar() != '\n')
        {
            printf("\x1B[31m"
                   "Oops! It seems that you haven`t entered a number. Please try again.\n"
                   "\x1B[0m");
            fflush(stdin);
            continue;
        }
        else if (num < MIN_VALUE || num > MAX_VALUE)
        {
            printf("\x1B[31m"
                   "Sorry, but you`ve entered a value that is out of acceptable range. Please enter a number between -100 and 100 inclusively.\n"
                   "\x1B[0m");
            continue;
        }
        else if (modf(num * pow(10, DECIMAL_PLACES), &intPart) != 0.0)
        {
            printf("\x1B[31m"
                   "Entered value doesn't have the specified precision. Please enter a number with accuracy to 9 decimal places.\n"
                   "\x1B[0m");
            continue;
        }
        else
        {
            inputValid = 1;
        }
    }
    return num;
}
int isValidPrecision(int epsilon)
{
    int inputValid = 0;
    while (!inputValid)
    {
        printf("\x1B[36m"
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
        else if (epsilon == 0)
        {
            printf("\x1B[31m"
                   "Sorry but precision cannot be equal to 0.\n"
                   "\x1B[0m");
            fflush(stdin);
            continue;
        }
        else
        {
            inputValid = 1;
        }
    }
    return epsilon;
}
int oppositeLimits(double a1, double a2)
{
    int isContrary = 0;
    if (a1 > a2)
    {
        isContrary = 1;
    }
    return isContrary;
}
int isValidChoice(char *name, int choice)
{
    int inputValid = 0;
    while (!inputValid)
    {
        printf("\x1B[36m"
               "\nChoose %s of equation by pressing 1 or 2:\n"
               "\x1B[0m",
               name);
        if (scanf("%d", &choice) != 1 || getchar() != '\n')
        {
            printf("\x1b[31m"
                   "Ohh, sorry but there`s an error in your input. Please press 1 or 2.\n"
                   "\x1b[0m");
            fflush(stdin);
            continue;
        }
        else if (choice < 1 || choice > 2)
        {
            printf("\x1b[31m"
                   "Invalid input. Please try again by pressing 1 or 2.\n"
                   "\x1b[0m");
            continue;
        }
        else
        {
            inputValid = 1;
        }
    }

    return choice;
}