#include <stdio.h>
#include "functions.c"

#define MIN_CHOICE 1
#define MAX_CHOICE 4

struct complex calculateParts(double a, double b, double c, double d);
struct complex calculateTheFirstCircuit(double L, double C, double R, double omega, struct complex Z);
struct complex calculateTheSecondCircuit(double L, double C, double R, double omega, struct complex Z);
struct complex calculateTheThirdCircuit(double L, double C, double R1, double R2, double omega, struct complex Z);
struct complex calculateTheFourthCircuit(double L, double C, double R1, double R2, double omega, struct complex Z);
struct complex (*calculateTwoFirstCircuits[2])(double L, double C, double R, double omega, struct complex Z) = {calculateTheFirstCircuit, calculateTheSecondCircuit};
struct complex (*calculateTwoLastCircuits[2])(double L, double C, double R1, double R2, double omega, struct complex Z) = {calculateTheThirdCircuit, calculateTheFourthCircuit};
void chooseTheCircuit(int *choice, double *L, double *C, double *R, double *R1, double *R2);
void calculateLimits(double *f_min, double *f_max, int *isContrary);
void calculateCircuit(int choice, double L, double C, double R, double R1, double R2, double f_min, double f_max, double df);

enum menuOption
{
       theFirstCircuit = 1,
       theSecondCircuit = 2,
       theThirdCircuit = 3,
       theFourthCircuit = 4
};

struct complex
{
       double realPart;
       double imagPart;
};

int main()
{
       int choice = 0, isContrary = 0;
       double L = 0, C = 0, R = 0, R1 = 0, R2 = 0, f = 0, f_min = 0, f_max, df = 0, omega = 0;
       struct complex Z;
       Z.realPart = 0;
       Z.imagPart = 0;

       printf("\x1B[1;34m"
              "\n\t\t\t\tCOMPLEX RESISTANCE CALCULATOR\n"
              "\x1B[0m");
       do
       {
              chooseTheCircuit(&choice, &L, &C, &R, &R1, &R2);
              calculateLimits(&f_min, &f_max, &isContrary);

              df = isValidStep("F min and F max", f_max, MAX_VALUE, DECIMAL_PLACES);
              calculateCircuit(choice, L, C, R, R1, R2, f_min, f_max, df);

              printf("\x1B[32m"
                     "\nCompleted successfully!\n"
                     "\x1B[0m");
              printf("\x1B[90m"
                     "\nPress Enter if you want to continue. In case you want to exit - press any other key + Enter.\n"
                     "\x1B[0m");

              fflush(stdin);
       } while (getchar() == '\n');

              return 0;
}
struct complex calculateParts(double a, double b, double c, double d)
{
       struct complex Z;
       Z.realPart = (a * c + b * d) / (pow(c, 2) + pow(d, 2));
       Z.imagPart = (b * c - a * d) / (pow(c, 2) + pow(d, 2));
       return Z;
}
struct complex calculateTheFirstCircuit(double L, double C, double R, double omega, struct complex Z)
{
       double a, b, c, d = 0;
       a = L / C;
       b = -1. * (R / (omega * C));
       c = R;
       d = omega * L - 1. / (omega * C);
       Z = calculateParts(a, b, c, d);
       return Z;
}
struct complex calculateTheSecondCircuit(double L, double C, double R, double omega, struct complex Z)
{
       double a, b, c, d = 0;
       a = L / C;
       b = R / (omega * C);
       c = R;
       d = omega * L - 1. / (omega * C);
       Z = calculateParts(a, b, c, d);
       return Z;
}
struct complex calculateTheThirdCircuit(double L, double C, double R1, double R2, double omega, struct complex Z)
{
       double a, b, c, d = 0;
       a = R1 * R2;
       b = R1 * (omega * L - 1. / (omega * C));
       c = R1 + R2;
       d = omega * L - 1. / (omega * C);
       Z = calculateParts(a, b, c, d);
       return Z;
}
struct complex calculateTheFourthCircuit(double L, double C, double R1, double R2, double omega, struct complex Z)
{
       double a, b, c, d = 0;
       a = R1 * R2 + L / C;
       b = omega * L * R1 - R2 / (omega * C);
       c = R1 + R2;
       d = (omega * L - 1. / (omega * C));
       Z = calculateParts(a, b, c, d);
       return Z;
}
void calculateCircuit(int choice, double L, double C, double R, double R1, double R2, double f_min, double f_max, double df)
{
       struct complex Z;
       double f0 = 1. / (2 * M_PI * sqrt(L * C));
       printf("\x1B[32m"
              "\nResonant frequency: %lf\n"
              "\x1B[0m",
              f0);

       double f = f_min;
       printf("\x1B[32m"
              "\nSolution:\n"
              "\x1B[0m");
       printf("\x1B[34m"
              "\n| %-10s| %-47s|\n"
              "\x1B[0m",
              "f", "Z");
       printf("\x1B[34m"
              "--------------------------------------------------------------\n"
              "\x1B[0m");
       do
       {
              double omega = 2 * M_PI * f;
              switch (choice)
              {
              case theFirstCircuit:
                     Z = calculateTwoFirstCircuits[0](L, C, R, omega, Z);
                     break;
              case theSecondCircuit:
                     Z = calculateTwoFirstCircuits[1](L, C, R, omega, Z);
                     break;

              case theThirdCircuit:
                     Z = calculateTwoLastCircuits[0](L, C, R1, R2, omega, Z);
                     break;

              case theFourthCircuit:
                     Z = calculateTwoLastCircuits[1](L, C, R1, R2, omega, Z);
                     break;

              default:
                     break;
              }
              if (Z.imagPart >= 0)
              {
                     printf("\x1B[34m"
                            "| %-10g| %-20g + i * %-20g|\n"
                            "\x1B[0m",
                            f, Z.realPart, Z.imagPart);
              }
              else
              {
                     printf("\x1B[34m"
                            "| %-10g| %-20g - i * %-20g|\n"
                            "\x1B[0m",
                            f, Z.realPart, -Z.imagPart);
              }

              f += df;

       } while (f <= f_max);
}
void calculateLimits(double *f_min, double *f_max, int *isContrary)
{
       do
       {
              *f_min = isValidDouble("the minimum frequency (F min)", MAX_VALUE, DECIMAL_PLACES);
              *f_max = isValidDouble("the maximum frequency (F max)", MAX_VALUE, DECIMAL_PLACES);
              *isContrary = oppositeLimits(*f_min, *f_max);
              if (*isContrary)
              {
                     printf("\x1b[31m"
                            "Oops! There`s an error occured. Your lower and upper limits cannot be opposite.\n"
                            "\x1b[0m");
              }
       } while (*isContrary == 1);
}
void chooseTheCircuit(int *choice, double *L, double *C, double *R, double *R1, double *R2)
{
       printCircuits();
       *choice = isValidChoice("the circuit you want to calculate (press 1, 2, 3 or 4)", *choice, MIN_CHOICE, MAX_CHOICE);
       *L = isValidDouble("the Inductance (L) (millihenry)", MAX_VALUE, DECIMAL_PLACES);
       *C = isValidDouble("the Capacitance (C) (microfarad)", MAX_VALUE, DECIMAL_PLACES);
       switch (*choice)
       {
       case theFirstCircuit:
              *R = isValidDouble("the Resistance (R) (Ohm)", MAX_VALUE, DECIMAL_PLACES);

              break;
       case theSecondCircuit:
              *R = isValidDouble("the Resistance (R) (Ohm)", MAX_VALUE, DECIMAL_PLACES);

              break;
       case theThirdCircuit:
              *R1 = isValidDouble("the first Resistance (R1) (Ohm)", MAX_VALUE, DECIMAL_PLACES);
              *R2 = isValidDouble("the second Resistance (R2) (Ohm)", MAX_VALUE, DECIMAL_PLACES);

              break;
       case theFourthCircuit:
              *R1 = isValidDouble("the first Resistance (R1) (Ohm)", MAX_VALUE, DECIMAL_PLACES);
              *R2 = isValidDouble("the second Resistance (R2) (Ohm)", MAX_VALUE, DECIMAL_PLACES);
              break;
       default:
              break;
       }
}