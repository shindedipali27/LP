#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

// Vector Addition
void vectorAddition()
{
    int n = 100;

    vector<int> A(n), B(n), C(n);

    srand(time(0));

    // Initialize vectors
    for(int i = 0; i < n; i++)
    {
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }

    double start = (double)clock() / CLOCKS_PER_SEC;

    // Parallel Vector Addition
    #pragma omp parallel for
    for(int i = 0; i < n; i++)
    {
        C[i] = A[i] + B[i];
    }

    double end = (double)clock() / CLOCKS_PER_SEC;

    cout << "\nAddition of two large vectors:\n";

    cout << "\nVector A:\n";
    for(int i = 0; i < n; i++)
    {
        cout << A[i] << " ";
    }

    cout << "\n\nVector B:\n";
    for(int i = 0; i < n; i++)
    {
        cout << B[i] << " ";
    }

    cout << "\n\nResultant Vector C:\n";
    for(int i = 0; i < n; i++)
    {
        cout << C[i] << " ";
    }

    cout << "\n\nExecution Time: "
         << end - start
         << " seconds\n";
}

// Matrix Multiplication
void matrixMultiplication()
{
    int n = 3;

    int A[3][3] =
    {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int B[3][3] =
    {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    int C[3][3];

    double start = (double)clock() / CLOCKS_PER_SEC;

    // Parallel Matrix Multiplication
    #pragma omp parallel for collapse(2)
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            C[i][j] = 0;

            for(int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    double end = (double)clock() / CLOCKS_PER_SEC;

    cout << "\n\nMatrix Multiplication:\n";

    cout << "\nMatrix A:\n";
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << A[i][j] << " ";
        }

        cout << endl;
    }

    cout << "\nMatrix B:\n";
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << B[i][j] << " ";
        }

        cout << endl;
    }

    cout << "\nResultant Matrix C:\n";
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << C[i][j] << " ";
        }

        cout << endl;
    }

    cout << "\nExecution Time: "
         << end - start
         << " seconds\n";
}

int main()
{
    vectorAddition();

    matrixMultiplication();

    return 0;
}
