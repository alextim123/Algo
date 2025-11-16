#include <iostream>
#include <vector>
#include <random>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    mt19937 rng(1234567);

    vector<int> pos(N);
    int idx = 0;
    for (int r = 1; r <= N; r += 2) pos[idx++] = r - 1;
    for (int r = 2; r <= N; r += 2) pos[idx++] = r - 1;

    vector<int> rowCnt(N, 0), diag1(2 * N - 1, 0), diag2(2 * N - 1, 0);
    auto addQueen = [&](int c, int r, int delta) {
        rowCnt[r] += delta;
        diag1[r + c] += delta;
        diag2[r - c + N - 1] += delta;
    };

    for (int c = 0; c < N; ++c) addQueen(c, pos[c], 1);

    auto conflicts = [&](int c, int r) {
        return (rowCnt[r] - (pos[c] == r)) +
               (diag1[r + c] - 1) +
               (diag2[r - c + N - 1] - 1);
    };

    auto solve = [&]() -> bool {
        vector<int> badCols;
        int maxIter = 200 * N;
        for (int iter = 0; iter < maxIter; ++iter) {
            badCols.clear();
            for (int c = 0; c < N; ++c) {
                if (conflicts(c, pos[c]) > 0) badCols.push_back(c);
            }
            if (badCols.empty()) return true;

            uniform_int_distribution<int> pick(0, (int)badCols.size() - 1);
            int col = badCols[pick(rng)];

            int bestRow = pos[col];
            int bestConflict = conflicts(col, bestRow);
            for (int r = 0; r < N; ++r) {
                int cur = (rowCnt[r] - (pos[col] == r)) +
                          (diag1[r + col]) +
                          (diag2[r - col + N - 1]);
                cur -= 2;
                if (cur < bestConflict) {
                    bestConflict = cur;
                    bestRow = r;
                }
            }

            if (bestRow != pos[col]) {
                addQueen(col, pos[col], -1);
                pos[col] = bestRow;
                addQueen(col, pos[col], 1);
            }
        }
        return false;
    };

    for (int attempt = 0; attempt < 5; ++attempt) {
        if (solve()) break;
        shuffle(pos.begin(), pos.end(), rng);
        fill(rowCnt.begin(), rowCnt.end(), 0);
        fill(diag1.begin(), diag1.end(), 0);
        fill(diag2.begin(), diag2.end(), 0);
        for (int c = 0; c < N; ++c) addQueen(c, pos[c], 1);
    }

    for (int c = 0; c < N; ++c) {
        cout << pos[c] + 1 << (c + 1 == N ? '\n' : ' ');
    }
    return 0;
}
