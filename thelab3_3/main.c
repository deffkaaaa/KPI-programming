#include <stdio.h>
#include <math.h>

double isValid(char);
double a = 0, b = 0, c = 0, u = 0, v = 0;
double x1 = 0, x2 = 0, x3 = 0;
char again[2];

int main()
{
    printf("===CUBIC EQUATION CALCULATOR===\n");
    printf("DISCLAIMER: The output values might be approximate if you enter too small number.\n");
    printf("Enter coefficients of equation x^3 + ax^2 + bx + c (with accuracy to 6 decimal places).\n");
    do
    {
        a = isValid('a');
        b = isValid('b');
        c = isValid('c');
        double q = (2. * pow(a, 3) / 27.) - (a * b / 3.) + c;
        double p = b - (a * a / 3.);
        double d = (pow(p, 3) / 27.) + (q * q / 4.);
        printf("D = %lf\n", d);
        if (d > 0)
        {
            u = cbrt(-q / 2. + sqrt(d));
            v = cbrt(-q / 2. - sqrt(d));
            x1 = u + v - a / 3.;
            x2 = -(u + v) / 2. - a / 3.;
            x3 = ((sqrt(3.) * (u - v)) / 2.);
            printf("x1 = %lf\t x2 = %lf + %lfi\t x3 = %lf - %lfi\n", x1, x2, x3, x2, x3);
        }
        else if (d == 0)
        {
            u = cbrt(-q / 2.);
            x1 = 2.0 * u;
            x2 = -u;
            printf("x1 = %lf\t x2 = x3 = %lf\n", x1, x2);
        }
        else if (d < 0)
        {
            double r = sqrt(-p * p * p / 27.);
            double fi = acos(-q / (2. * r));
            x1 = (2. * cbrt(r) * cos(fi / 3.) - (a / 3.));
            x2 = (2. * cbrt(r) * cos((fi + 2. * M_PI) / 3.) - (a / 3.));
            x3 = (2. * cbrt(r) * cos((fi + 4. * M_PI) / 3.) - (a / 3.));
            printf("x1 = %lf\t x2 = %lf\t x3 = %lf\n", x1, x2, x3);
        }
        else if (-pow(p, 3) / 27.0 < 0)
        {
            printf("Sorry, but entered number is invalid.\n");
            fflush(stdin);
            continue;
        }
        printf("Completed successfully!\n");
        printf("Press Enter to continue or any other not system key + Enter to exit.\n");
        fgets(again, 2, stdin);
        fflush(stdin);
    } while (again[0] == '\n');
    return 0;
}

double isValid(char coef)
{
    double num = 0;
    int inputValid = 0;
    while (!inputValid)
    {
        printf("Enter the coefficient '%c' of equation (from -1000 to 1000):\n", coef);
        if (scanf("%lf", &num) != 1 || getchar() != '\n' || num < -1000 || num > 1000)
        {
            printf("Invalid input. Enter an integer number from -1000 to 1000.\n");
            fflush(stdin);
            continue;
        }
        else if ((int)(num * 1000000) != num * 1000000.)
        {
            printf("Please enter a valid number with accuracy to 6 decimal places.\n");
            fflush(stdin);
            continue;
        }
        else
        {
            inputValid = 1;
        }
    }
    return num;
}