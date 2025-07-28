#include <iostream>
using namespace std;

bool recursion(int vector[3][8], const int posicion){
    for (int i = 0; i< 8; i++){
        bool found = false;
        for (int j = 0; j < 8; j++){
            if (vector[0][j]== i){
                found = true;
                break;
            }
        }
        if (!found){
            vector[0][posicion] = i; // Place the queen in the current row
            vector[1][posicion] = posicion+i;
            vector[2][posicion] = posicion-i;
            for (int j = 0; j < posicion; j++){
                if (vector[1][j]== vector[1][posicion] || vector[2][j] == vector[2][posicion]){
                    return false; // Conflict found
                }
            }
            if (posicion == 7 || recursion(vector, posicion + 1)){
                return true; // If we reach the last row or recursion is successful
            }
        }
    }
}

int main(){
    int vector[3][8];
    for (int i = 0; i < 8; i++) {
        vector[0][i] = -1; // Initialize the first row
        vector[1][i] = -1; // Initialize the second row
        vector[2][i] = -1; // Initialize the third row
    }
    if (recursion(vector, 0)) {
        cout << "Solution found:" << endl;
        for (int i = 0; i < 8; i++) {
            cout << vector[0][i] << " ";
        }
    }
    else {
        cout << "No solution found." << endl;
    }
    return 0;
}