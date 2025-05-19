#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int N = 5;
int minTries = INT_MAX;
vector<pair<int, int>> solution;
vector<pair<int, int>> tempSolution;

void turn(vector<vector<int>>& lights, int i, int j) {
    // Toggle the clicked light and adjacent lights
    lights[i][j] ^= 1;
    if (i > 0) lights[i-1][j] ^= 1;
    if (i < N-1) lights[i+1][j] ^= 1;
    if (j > 0) lights[i][j-1] ^= 1;
    if (j < N-1) lights[i][j+1] ^= 1;
}

bool isAllLit(const vector<vector<int>>& lights) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (lights[i][j] == 0) return false;
        }
    }
    return true;
}

void DFS(vector<vector<int>>& lights, int pos, int steps) {
    // Base cases
    if (steps >= minTries) return;  // Prune if we've already found a better solution
    if (isAllLit(lights)) {
        minTries = steps;
        solution = tempSolution;
        return;
    }
    if (pos >= N * N) return;  // We've tried all positions

    int row = pos / N;
    int col = pos % N;

    // Try not clicking this position
    DFS(lights, pos + 1, steps);

    // Try clicking this position
    turn(lights, row, col);
    tempSolution.push_back({row, col});
    DFS(lights, pos + 1, steps + 1);
    tempSolution.pop_back();
    turn(lights, row, col);  // Backtrack
}

int main() {
    vector<vector<int>> lights(N, vector<int>(N));
    
    // Input
    for (int i = 0; i < N; i++) {
        string line;
        getline(cin, line);
        for (int j = 0; j < N; j++) {
            lights[i][j] = line[j] - '0';
        }
    }

    // Solve
    DFS(lights, 0, 0);

    // Output
    if (minTries == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << "Minimum clicks needed: " << minTries << endl;
        cout << "Solution sequence:" << endl;
        for (const auto& move : solution) {
            cout << "Click position: (" << move.first << "," << move.second << ")" << endl;
        }
    }
    return 0;
}