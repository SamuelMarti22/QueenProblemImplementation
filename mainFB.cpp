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
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (chess[i][j] == 0)
            {
                chess[i][j] = -1;
                count++;

                // Vertical ↓
                for (int row = i + 1; row < 8; row++)
                    chess[row][j] = chess[row][j] + 1;

                // Vertical ↑
                for (int row = i - 1; row >= 0; row--)
                    chess[row][j] = chess[row][j] + 1;

                // Horizontal →
                for (int column = j + 1; column < 8; column++)
                    chess[i][column] = chess[i][column] + 1;

                // Horizontal ←
                for (int column = j - 1; column >= 0; column--)
                    chess[i][column] = chess[i][column] + 1;

                //  DIAGONALES ARREGLADAS 

                // ↘ diagonal abajo-derecha
                for (int k = 1; k < 8; k++)
                {
                    int row = i + k;
                    int column = j + k;
                    if (row < 8 && column < 8)
                        chess[row][column] += 1;
                }

                // ↖ diagonal arriba-izquierda
                for (int k = 1; k < 8; k++)
                {
                    int row = i - k;
                    int column = j - k;
                    if (row >= 0 && column >= 0)
                        chess[row][column] += 1;
                }

                // ↙ diagonal abajo-izquierda
                for (int k = 1; k < 8; k++)
                {
                    int row = i + k;
                    int column = j - k;
                    if (row < 8 && column >= 0)
                        chess[row][column] += 1;
                }

                // ↗ diagonal arriba-derecha
                for (int k = 1; k < 8; k++)
                {
                    int row = i - k;
                    int column = j + k;
                    if (row >= 0 && column < 8)
                        chess[row][column] += 1;
                }

                //  FIN DE BUCLES DIAGONALES

                if (count == 8)
                {
                    return true;
                }
                if (recursion(chess, i, j, count))
                {
                    return true;
                }
                else
                {
                    chess[i][j] = 0;
                    count--;

                    // Vertical ↓
                    for (int row = i + 1; row < 8; row++)
                        chess[row][j] = chess[row][j] - 1;

                    // Vertical ↑
                    for (int row = i - 1; row >= 0; row--)
                        chess[row][j] = chess[row][j] - 1;

                    // Horizontal →
                    for (int column = j + 1; column < 8; column++)
                        chess[i][column] = chess[i][column] - 1;

                    // Horizontal ←
                    for (int column = j - 1; column >= 0; column--)
                        chess[i][column] = chess[i][column] - 1;

                    // 🔽🔽🔽 DIAGONALES BACKTRACK 🔽🔽🔽

                    // ↘ diagonal abajo-derecha
                    for (int k = 1; k < 8; k++)
                    {
                        int row = i + k;
                        int column = j + k;
                        if (row < 8 && column < 8)
                            chess[row][column] -= 1;
                    }

                    // ↖ diagonal arriba-izquierda
                    for (int k = 1; k < 8; k++)
                    {
                        int row = i - k;
                        int column = j - k;
                        if (row >= 0 && column >= 0)
                            chess[row][column] -= 1;
                    }

                    // ↙ diagonal abajo-izquierda
                    for (int k = 1; k < 8; k++)
                    {
                        int row = i + k;
                        int column = j - k;
                        if (row < 8 && column >= 0)
                            chess[row][column] -= 1;
                    }

                    // ↗ diagonal arriba-derecha
                    for (int k = 1; k < 8; k++)
                    {
                        int row = i - k;
                        int column = j + k;
                        if (row >= 0 && column < 8)
                            chess[row][column] -= 1;
                    }

                    // 🔼🔼🔼 FIN DE BACKTRACK 🔼🔼🔼
                }
            }
        }
    }
    return false;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    int chess[8][8];
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            chess[i][j] = 0;
        }
    }
    recursion(chess, 0, 0, 0);
    printChessboard(chess);

    auto end = std::chrono::high_resolution_clock::now();   // ⏱ Fin

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Tiempo de ejecución: " << duration.count() << " ns\n";
    return 0;
}
