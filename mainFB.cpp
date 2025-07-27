#include <iostream>
#include <omp.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

void printChessboard(int chess[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << chess[i][j] << " | ";
        }
        cout << endl;
        cout << "-------------------------------" << endl;
    }
    cout << endl;
}

bool recursion(int chess[8][8], const int queenRow, const int queenCol, int count)
{
    // Base case or recursive logic can be implemented here
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (chess[i][j] == 0)
            {
                // Example logic: mark the cell as visited
                chess[i][j] = -1; // Marking the cell as visited
                count++;
                // #pragma omp parallel for
                for (int row = i + 1; row < 8; row++)
                {
                    chess[row][j] = chess[row][j] + 1;
                }

                for (int row = i - 1; row >= 0; row--)
                {
                    chess[row][j] = chess[row][j] + 1;
                }

                // #pragma omp parallel for
                for (int column = j + 1; column < 8; column++)
                {
                    chess[i][column] = chess[i][column] + 1;
                }

                for (int column = j - 1; column >= 0; column--)
                {
                    chess[i][column] = chess[i][column] + 1;
                }
                // #pragma omp parallel for

                for (int row = i + 1, column = j + 1; row < 8 && column < 8; row++, column++)
                {
                    chess[row][column] = chess[row][column] + 1; // Diagonal increment
                }

                //#pragma omp parallel for
                for (int row = i - 1, column = j - 1; row >= 0 && column >= 0; row--, column--)
                {
                    chess[row][column] = chess[row][column] + 1; // Diagonal increment
                }

                //#pragma omp parallel for
                for (int row = i + 1, column = j - 1; row <8 && column >= 0; row++, column--)
                {
                    chess[row][column] = chess[row][column] + 1; // Anti-diagonal increment
                }

                //#pragma omp parallel for
                for (int row = i - 1, column = j + 1; row >= 0 && column < 8; row--, column++)
                {
                    chess[row][column] = chess[row][column] + 1; // Anti-diagonal increment
                }

                if (count == 8)
                {
                    return true; // Base case: all queens are placed successfully
                }
                if (recursion(chess, i, j, count))
                {
                    return true; // If recursion returns true, propagate the success
                }
                else
                {
                    chess[i][j] = 0; // Backtrack: unmark the cell
                    count--;         // Decrement the count
                                     // Print the chessboard after backtracking
                    for (int row = i + 1; row < 8; row++)
                    {
                        chess[row][j] = chess[row][j] - 1;
                    }

                    for (int row = i - 1; row >= 0; row--)
                    {
                        chess[row][j] = chess[row][j] - 1;
                    }

                    // #pragma omp parallel for
                    for (int column = j + 1; column < 8; column++)
                    {
                        chess[i][column] = chess[i][column] - 1;
                    }

                    for (int column = j - 1; column >= 0; column--)
                    {
                        chess[i][column] = chess[i][column] - 1;
                    }

                    //#pragma omp parallel for
                    for (int row = i + 1, column = j + 1; row < 8 && column < 8; row++, column++)
                    {
                        chess[row][column] = chess[row][column] - 1; // Diagonal increment
                    }

                    //#pragma omp parallel for
                    for (int row = i - 1, column = j - 1; row >= 0 && column >= 0; row--, column--)
                    {
                        chess[row][column] = chess[row][column] - 1; // Diagonal increment
                    }


                    //#pragma omp parallel for
                    for (int row = i + 1, column = j - 1; row < 8 && column >= 0; row++, column--)
                    {
                        chess[row][column] = chess[row][column] - 1; // Anti-diagonal increment
                    }

                    //#pragma omp parallel for
                    for (int row = i - 1, column = j + 1; row >= 0 && column < 8; row--, column++)
                    {
                        chess[row][column] = chess[row][column] - 1; // Anti-diagonal increment
                    }
                }
                // You can add more logic here to handle the recursion or backtracking
            }
        }
    }
    return false; // Placeholder return value
}

int main()
{
    auto inicio = high_resolution_clock::now();
    int chess[8][8]; // Declare a 2D array to represent the chessboard

    // #pragma omp parallel for collapse(2)
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            chess[i][j] = 0; // Initialize the chessboard with 0s
        }
    }

    recursion(chess, 0, 0, 0); // Start the recursion from the first cell
    printChessboard(chess);    // Print the initial chessboard state
    auto fin = high_resolution_clock::now();
    auto duracion = duration_cast<milliseconds>(fin - inicio);

    cout << "Tiempo: " << duracion.count() << " ms\n";
    return 0;
}