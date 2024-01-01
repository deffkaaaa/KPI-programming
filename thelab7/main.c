#include <stdio.h>
#include <math.h>
#include "functions.c"

#define EPSILON 1e-6

double theFirstF_AX(double argument, double y);
double theSecondF_AX(double y, double argument);
double calculateDerivative(double (*fpr)(double y, double argument), double x, double y);
double calculateXByBisection(double (*fpr)(double y, double x), double x, double a1, double a2, double y, int epsilon);
double calculateXByNewton(double (*fpr)(double y, double x), double y, int epsilon);
void switchForCos(int choice, double y, double a1, double a2, int isContrary, int epsilon, double x);
void switchForSin(int choice, double y, double a1, double a2, int isContrary, int epsilon, double x);

enum menuOption
{
    COS_EQUATION = 1,
    SIN_EQUATION = 2,
    BISECTION = 1,
    NEWTON = 2
};

int main()
{
    int choice = 0, epsilon = 0, isContrary = 0;
    double x = 0, y = 0, a1 = 0, a2 = 0;
    char again[2];

    printf("\x1B[1;33m"
           "\nNON-LINEAR EQUATION CALCULATOR\n"
           "\x1B[0m");
    do
    {
        printf("\n1. cos(y/x) - 2*sin(1/x) + 1/x = 0, x ∈ [a1; a2]\n");
        printf("2. sin(lnx) - cos(lnx) + y*lnx = 0, x ∈ [a1; a2]\n");
        choice = isValidChoice("the type", choice);
        switch (choice)
        {
        case COS_EQUATION:
            switchForCos(choice, y, a1, a2, isContrary, epsilon, x);
            break;
        case SIN_EQUATION:
            switchForSin(choice, y, a1, a2, isContrary, epsilon, x);
            break;
        default:
            printf("\x1B[31m"
                   "Invalid choice. Please, press 1 or 2.\n"
                   "\x1B[0m");
            break;
        }
        printf("\x1B[32m"
               "\nCompleted successfully!\n"
               "\x1B[0m");
        printf("\x1B[37m"
               "Press Enter to continue or any other not system key + Enter to exit.\n"
               "\x1B[0m");
        fgets(again, sizeof(again), stdin);
        fflush(stdin);
    } while (again[0] == '\n');
    return 0;
}

double theFirstF_AX(double y, double argument)
{
    return cos(y / argument) - 2. * sin(1. / argument) + 1. / argument;
}
double theSecondF_AX(double y, double argument)
{
    return sin(log(argument)) - cos(log(argument)) + y * log(argument);
}
double calculateDerivative(double (*fpr)(double y, double argument), double x, double y)
{
    return ((*fpr)(y, x + EPSILON) - (*fpr)(y, x)) / EPSILON;
}
double calculateXByBisection(double (*fpr)(double y, double x), double x, double a1, double a2, double y, int epsilon)
{
    do
    {
        x = (a1 + a2) / 2.;
        (*fpr)(y, a1) * (*fpr)(y, x) > 0 ? (a1 = x) : (a2 = x);
    } while (fabs(a2 - a1) > pow(10, -epsilon));
    return x;
}
double calculateXByNewton(double (*fpr)(double y, double x), double y, int epsilon)
{
    double delta = 0, x = 1;
    do
    {
        delta = ((*fpr)(y, x) / calculateDerivative(fpr, x, y));
        x = x - delta;
    } while (fabs(delta) > pow(10, -epsilon));
    return x;
}
void switchForCos(int choice, double y, double a1, double a2, int isContrary, int epsilon, double x)
{
    printf("\n1. Bisection method\n");
    printf("2. Newton`s method\n");
    choice = isValidChoice("a solution method", choice);
    switch (choice)
    {
    case BISECTION:
        y = isValidY(y);
        do
        {
            a1 = isValidScope("lower limit", MIN_VALUE, MAX_VALUE, DECIMAL_PLACES);
            a2 = isValidScope("upper limit", MIN_VALUE, MAX_VALUE, DECIMAL_PLACES);
            isContrary = oppositeLimits(a1, a2);
            if (isContrary)
            {
                printf("\x1B[31m"
                       "Oops! There`s an error occured. Your lower and upper limits cannot be opposite.\n"
                       "\x1B[0m");
            }
        } while (isContrary == 1);
        epsilon = isValidPrecision(epsilon);
        x = calculateXByBisection(theFirstF_AX, x, a1, a2, y, epsilon);
        printf("\x1B[32m"
               "\nSolution:\n"
               "\x1B[0m");
        printf("\nx = %.*lf\n", epsilon, x);
        break;
    case NEWTON:
        y = isValidY(y);
        do
        {
            a1 = isValidScope("lower limit", MIN_VALUE, MAX_VALUE, DECIMAL_PLACES);
            a2 = isValidScope("upper limit", MIN_VALUE, MAX_VALUE, DECIMAL_PLACES);
            isContrary = oppositeLimits(a1, a2);
            if (isContrary)
            {
                printf("\x1B[31m"
                       "Oops! There`s an error occured. Your lower and upper limits cannot be opposite.\n"
                       "\x1B[0m");
            }
        } while (isContrary == 1);
        epsilon = isValidPrecision(epsilon);
        x = calculateXByNewton(theFirstF_AX, y, epsilon);
        printf("\x1B[32m"
               "\nSolution:\n"
               "\x1B[0m");
        printf("\nx = %.*lf\n", epsilon, x);
        break;
    default:
        break;
    }
}
void switchForSin(int choice, double y, double a1, double a2, int isContrary, int epsilon, double x)
{
    printf("\n1. Bisection method\n");
    printf("2. Newton`s method\n");
    choice = isValidChoice("a solution method", choice);
    switch (choice)
    {
    case BISECTION:
        y = isValidY(y);
        do
        {
            a1 = isValidScope("lower limit", MIN_VALUE, MAX_VALUE, DECIMAL_PLACES);
            a2 = isValidScope("upper limit", MIN_VALUE, MAX_VALUE, DECIMAL_PLACES);
            isContrary = oppositeLimits(a1, a2);
            if (isContrary)
            {
                printf("\x1b[31m"
                       "Oops! There`s an error occured. Your lower and upper limits cannot be opposite.\n"
                       "\x1b[0m");
            }
        } while (isContrary == 1);
        epsilon = isValidPrecision(epsilon);
        x = calculateXByBisection(theSecondF_AX, x, a1, a2, y, epsilon);
        printf("\x1B[32m"
               "\nSolution:\n"
               "\x1B[0m");
        printf("\nx = %.*lf\n", epsilon, x);
        break;
    case NEWTON:
        y = isValidY(y);
        do
        {
            a1 = isValidScope("lower limit", MIN_VALUE, MAX_VALUE, DECIMAL_PLACES);
            a2 = isValidScope("upper limit", MIN_VALUE, MAX_VALUE, DECIMAL_PLACES);
            isContrary = oppositeLimits(a1, a2);
            if (isContrary)
            {
                printf("\x1b[31m"
                       "Oops! There`s an error occured. Your lower and upper limits cannot be opposite.\n"
                       "\x1b[0m");
            }
        } while (isContrary == 1);
        epsilon = isValidPrecision(epsilon);
        x = calculateXByNewton(theSecondF_AX, y, epsilon);
        printf("\x1B[32m"
               "\nSolution:\n"
               "\x1B[0m");
        printf("\nx = %.*lf\n", epsilon, x);
        break;
    default:
        break;
    }
}