#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define max_size 10
#define min_size 2
#define MAX_PRECISION 9
#define MIN_PRECISION 1
#define DBL_EPSILON 1.0
#define MIN_VALUE (-99999)
#define MAX_VALUE 99999

int isValidSize(int matrixSize);
void isValidMatrix(int matrixSize, int epsilon, double *rhs, double **matrix);
int isValidPrecision(int epsilon);
double *matrixCalc(double **matrix, double *x, double *xp, int matrixSize, int epsilon);
double *xpCalc(double *xp, double **matrix, int matrixSize);
double **matrixMemoryAlloc(int rows, int columns);
double maxDeltaCalc(double *delta, int matrixSize);
void printMatrix(int matrixSize, double **matrix, double *rhs, int epsilon);
void printX(double *x, int epsilon, int matrixSize);

int main()
{
    char again[2];
    int matrixSize = 0, epsilon = 0;
    double rhs[max_size];
    printf("\x1B[1;35m"
           "\nSLA(Y)E 💅 CALCULATOR\n"
           "\x1B[0m");
    printf("\x1B[36m"
           "Here`s an example for entering equations:\n"
           "\x1B[0m");
    printf("⎛ a₁₁x₁ + a₁₂x₂ + ... + a₁ₙxₙ = b₁\n");
    printf("⎪ a₂₁x₁ + a₂₂x₂ + ... + a₂ₙxₙ = b₂\n");
    printf("⎪ ...............................\n");
    printf("⎝ aₙ₁x₁ + aₙ₂x₂ + ... + aₙₙxₙ = bₙ\n");
    do
    {
        matrixSize = isValidSize(matrixSize);
        epsilon = isValidPrecision(epsilon);

        double **matrix = matrixMemoryAlloc(matrixSize, matrixSize + 1);
        isValidMatrix(matrixSize, epsilon, rhs, matrix);
        double *xp = xpCalc(NULL, matrix, matrixSize);

        double *x = matrixCalc(matrix, NULL, xp, matrixSize, epsilon);

        printMatrix(matrixSize, matrix, rhs, epsilon);
        printX(x, epsilon, matrixSize);

        free(x);
        free(xp);
        for (int i = 0; i < matrixSize; i++)
        {
            free(matrix[i]);
        }
        free(matrix);
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
int isValidSize(int matrixSize)
{
    int inputValid = 0;
    while (!inputValid)
    {
        printf("\x1B[36m"
               "\nEnter the size of SLAE [2; 10]:\n"
               "\x1B[0m");
        if (scanf("%d", &matrixSize) != 1 || getchar() != '\n')
        {
            printf("\x1B[31m"
                   "Invalid input. Please enter a whole number from 2 to 10.\n"
                   "\x1B[0m");
            fflush(stdin);
            continue;
        }
        else if (matrixSize < min_size || matrixSize > max_size)
        {
            printf("\x1B[31m"
                   "Oops! It seems that you`ve exceeded the limits of permissible values. Enter a number between 2 and 10 inclusively.\n"
                   "\x1B[0m");
            continue;
        }
        else
        {
            inputValid = 1;
        }
    }
    return matrixSize;
}
void isValidMatrix(int matrixSize, int epsilon, double *rhs, double **matrix)
{
    for (int i = 0; i < matrixSize; i++)
    {
        printf("\x1B[35m"
               "\nEquation %d\n"
               "\x1B[0m",
               i + 1);
        int isConvergent = 0;
        while (!isConvergent)
        {
            for (int j = 0; j < matrixSize; j++)
            {
                int inputValid = 0;
                while (!inputValid)
                {
                    printf("\x1B[36m"
                           "Enter the coefficient a%d%d [-99999; 99999]:\n"
                           "\x1B[0m",
                           i + 1, j + 1);
                    if (scanf("%lf", &matrix[i][j]) != 1 || getchar() != '\n')
                    {
                        printf("\x1B[31m"
                               "Check your input. Most likely, you didn`t enter a number. Please try again.\n"
                               "\x1B[0m");
                        fflush(stdin);
                        continue;
                    }
                    else if (matrix[i][j] < MIN_VALUE || matrix[i][j] > MAX_VALUE)
                    {
                        printf("\x1B[31m"
                               "Oops! Your value is out of range. Enter a number between -99999 and 99999 inclusively.\n"
                               "\x1B[0m");
                        continue;
                    }
                    else if (fabs(matrix[i][j] - round(matrix[i][j] * pow(10, epsilon)) / pow(10, epsilon)) > DBL_EPSILON)
                    {
                        printf("\x1B[31m"
                               "Entered value doesn't have the specified precision. Please enter a number with accuracy to %d decimal places.\n"
                               "\x1B[0m",
                               epsilon);
                        continue;
                    }
                    else
                    {
                        inputValid = 1;
                    }
                }
            }
            int inputValid = 0;
            while (!inputValid)
            {
                printf("\x1B[36m"
                       "Enter the constant b%d [-99999; 99999]:\n"
                       "\x1B[0m",
                       i + 1);
                if (scanf("%lf", &rhs[i]) != 1 || getchar() != '\n')
                {
                    printf("\x1B[31m"
                           "Invalid input. You might not have entered a number. Please try again.\n"
                           "\x1B[0m");
                    fflush(stdin);
                    continue;
                }
                else if (rhs[i] < MIN_VALUE || rhs[i] > MAX_VALUE)
                {
                    printf("\x1B[31m"
                           "Oops! Your value is out of range. Enter a number between -99999 and 99999 inclusively.\n"
                           "\x1B[0m");
                    continue;
                }
                else if (fabs(rhs[i] - round(rhs[i] * pow(10, epsilon)) / pow(10, epsilon)) > DBL_EPSILON)
                {
                    printf("\x1B[31m"
                           "Entered value does not have the specified precision. Please enter a number with accuracy to %d decimal places.\n"
                           "\x1B[0m",
                           epsilon);
                    continue;
                }
                else
                {
                    inputValid = 1;
                    matrix[i][matrixSize] = rhs[i];
                }
            }
            double sum = 0;
            for (int j = 0; j < matrixSize; j++)
            {
                if (i != j)
                {
                    sum += matrix[i][j];
                }
            }
            if (fabs(matrix[i][i]) < fabs(sum))
            {
                printf("\x1B[31m"
                       "The convergence condition is violated in equation %d. Please try again.\n"
                       "\x1B[0m",
                       i + 1);
            }
            else
            {
                isConvergent = 1;
            }
        }
    }
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
double *matrixCalc(double **matrix, double *x, double *xp, int matrixSize, int epsilon)
{
    x = (double *)malloc((matrixSize) * sizeof(double));
    double *delta = (double *)malloc((matrixSize) * sizeof(double));
    double maxDelta = 0;
    do
    {
        for (int i = 0; i < matrixSize; i++)
        {
            double sum = 0;
            for (int j = 0; j < matrixSize; j++)
            {
                if (i != j)
                {
                    sum += matrix[i][j] * xp[j];
                }
            }
            x[i] = (matrix[i][matrixSize] - sum) / matrix[i][i];
            delta[i] = fabs(x[i] - xp[i]);
            xp[i] = x[i];
        }
        maxDelta = maxDeltaCalc(delta, matrixSize);
    } while (maxDelta >= pow(10, -epsilon));
    free(delta);
    return x;
}
double *xpCalc(double *xp, double **matrix, int matrixSize)
{
    xp = (double *)malloc((matrixSize) * sizeof(double));
    for (int i = 0; i < matrixSize; i++)
    {
        xp[i] = matrix[i][matrixSize] / matrix[i][i];
    }
    return xp;
}
double **matrixMemoryAlloc(int rows, int columns)
{
    double **matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (double *)malloc(columns * sizeof(double));
    }
    return matrix;
}
double maxDeltaCalc(double *delta, int matrixSize)
{
    double maxDelta = delta[0];
    for (int i = 0; i < matrixSize; i++)
    {
        if (delta[i] > maxDelta)
        {
            maxDelta = delta[i];
        }
    }
    return maxDelta;
}
void printMatrix(int matrixSize, double **matrix, double *rhs, int epsilon)
{
    printf("\x1B[32m"
           "\nHere`s your SLAE:\n"
           "\x1B[0m");
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            if (j >= 0)
            {
                if (matrix[i][j] >= 0)
                {
                    printf(" + ");
                }
                else
                {
                    printf(" - ");
                }
            }
            printf("%.*lf * x%d", epsilon, fabs(matrix[i][j]), j + 1);
        }
        printf(" = %.*lf\n", epsilon, rhs[i]);
    }
}
void printX(double *x, int epsilon, int matrixSize)
{
    printf("\x1B[32m"
           "\nThe solution of the SLAE:\n"
           "\x1B[0m");
    for (int i = 0; i < matrixSize; i++)
    {
        printf("x%d = %.*lf\n", i + 1, epsilon, x[i]);
    }
}