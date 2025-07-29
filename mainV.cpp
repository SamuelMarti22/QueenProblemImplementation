#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

void imprimirTablero(int vector[3][8])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << vector[i][j] << " | ";
        }
        cout << endl;
    }
    cout << endl;
}

bool recursion(int vector[3][8], const int posicion)
{
    for (int i = 0; i < 8; i++)
    {
        bool found = false;
        for (int j = 0; j < 8; j++)
        {
            if (vector[0][j] == i)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            vector[0][posicion] = i; // Place the queen in the current row
            vector[1][posicion] = posicion + i;
            vector[2][posicion] = posicion - i;
            for (int j = 0; j < posicion; j++)
            {
                // Check for conflicts with previously placed queens
                if (vector[1][j] == vector[1][posicion] || vector[2][j] == vector[2][posicion])
                {
                    found = true;
                }
            }
            if (found)
            {
                vector[0][posicion] = -1; // Reset the position if conflict found
                continue; // Try the next row
            }
            if (posicion == 7 || recursion(vector, posicion + 1))
            {
                return true; // If we reach the last row or recursion is successful
            }
        }
    }
    return false; // No valid position found
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    int vector[3][8];
    for (int i = 0; i < 8; i++)
    {
        vector[0][i] = -1; // Initialize the first row
        vector[1][i] = -1; // Initialize the second row
        vector[2][i] = -1; // Initialize the third row
    }
    if (recursion(vector, 0))
    {
        cout << "Solution found:" << endl;
        imprimirTablero(vector);
    }
    else
    {
        cout << "No solution found." << endl;
    }
    auto end = std::chrono::high_resolution_clock::now();   // ⏱ Fin

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Tiempo de ejecución: " << duration.count() << " ns\n";
    return 0;
}