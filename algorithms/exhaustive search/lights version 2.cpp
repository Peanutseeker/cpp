#include <iostream>
#include <cstring>
#include <climits>
using namespace std;

const int SIZE = 5;

// More robust turn function
void turn(int lights[SIZE][SIZE], int row, int col) {
    lights[row][col] = 1 - lights[row][col];
    
    // Check adjacent cells with boundary checks
    if (row > 0) lights[row-1][col] = 1 - lights[row-1][col];
    if (row < SIZE-1) lights[row+1][col] = 1 - lights[row+1][col];
    if (col > 0) lights[row][col-1] = 1 - lights[row][col-1];
    if (col < SIZE-1) lights[row][col+1] = 1 - lights[row][col+1];
}

// Comprehensive check for all lights
bool allLightsOn(int lights[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (lights[i][j] == 0) return false;
        }
    }
    return true;
}

int solve(int initialState[SIZE][SIZE]) {
    int minSteps = INT_MAX;
    
    // Try all possible first row combinations (2^5 = 32)
    for (int mask = 0; mask < 32; mask++) {
        // Create a copy of the initial state to work on
        int lights[SIZE][SIZE];
        memcpy(lights, initialState, sizeof(lights));
        
        int steps = 0;
        
        // Apply first row clicks based on mask
        for (int j = 0; j < SIZE; j++) {
            if (mask & (1 << j)) {
                turn(lights, 0, j);
                steps++;
            }
        }
        
        // Propagate clicks for subsequent rows
        for (int i = 1; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                // If light in the row above is off, turn this one
                if (lights[i-1][j] == 0) {
                    turn(lights, i, j);
                    steps++;
                }
            }
        }
        
        // Check if all lights are on
        if (allLightsOn(lights)) {
            minSteps = min(minSteps, steps);
        }
    }
    
    return (minSteps <= 24) ? minSteps : -1;
}

int main() {
    int lights[SIZE][SIZE];
    
    // Input lights
    for (int i = 0; i < SIZE; i++) {
        string row;
        getline(cin, row);
        for (int j = 0; j < SIZE; j++) {
            lights[i][j] = (row[j] == '1') ? 1 : 0;
        }
    }
    
    cout << solve(lights) << endl;
    
    return 0;
}