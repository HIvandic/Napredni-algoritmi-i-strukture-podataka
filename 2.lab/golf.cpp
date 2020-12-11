#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <iostream>


using namespace std;

typedef unsigned int uint;

// N = br redaka, M = br stupaca
// problem = N×M polje koje sadrzi brojeve cvjetova
// solution = optimalna putanja koja pocine u (0, 0), a zavrsava u (N-1, M-1)
uint solve(const uint N, const uint M, uint16_t* const problem, std::vector<std::pair<uint, uint>>& solution) {
    int i, j;
    uint value;
    uint* distance;
    uint left, up, start;
    distance = (uint*)std::malloc(N * M * sizeof(uint));

    //pocetna tocka ista
    *distance = *problem;

    //prvi stupac stalnim pomacima dolje
    for (i = 1; i < N; ++i) {
        *(distance + i * M + 0) = *(distance + (i - 1) * M + 0) + *(problem + i * M + 0);
    }

    //prvi red stalnim pomacima desno
    for (i = 1; i < M; ++i) {
        *(distance + 0 + i) = *(distance + 0 + i - 1) + *(problem + 0 + i);
    }
    for (i = 1; i < N; ++i) {
        for (j = 1; j < M; ++j) {
            left = *(distance + i * M + j - 1);
            up = *(distance + (i - 1) * M + j);
            if (left < up) {
                *(distance + i * M + j) = *(problem + i * M + j) + left;
            }
            else {
                *(distance + i * M + j) = *(problem + i * M + j) + up;
            }
        }
    }
    start = *(distance + N * M - 1);
    value = *(distance + N * M - 1);
    i = N - 1;
    j = M - 1;
    while (i != 0 || j != 0) {
        solution.insert(solution.begin(), std::make_pair(i, j));
        if (j != 0) {
            left = *(distance + i * M + j - 1);
        }
        else {
            left = -1;
        }
        if (i != 0) {
            up = *(distance + (i - 1) * M + j);
        }
        else {
            up == -1;
        }
        if (start == left + *(problem + i * M + j)) {
            start = left;
            j -= 1;
        }
        else {
            start = up;
            i -= 1;
        }
    }

    //jos dodaj prvi element
    solution.insert(solution.begin(), std::make_pair(0, 0));
    free(distance);
    return value;
}
int main() {

    //uint16_t polje[] = {1, 7, 9, 2, 8, 6, 6, 7, 1, 3, 2, 8};

    uint16_t polje[] = { 100, 
                         200, 
                         300};
    uint16_t* ptr;
    ptr = polje;
    vector<pair<unsigned int, unsigned int>> solution;

    uint16_t brCvijeca = solve(3, 1, ptr, solution);

    cout << "Kolicina cvijeca: " << brCvijeca;
    cout << "\n";

    for (int i = 0; i < solution.size(); ++i) {
        cout << "(" << solution[i].first << ", " << solution[i].second << ")" << endl;
    }

    return 0;
}