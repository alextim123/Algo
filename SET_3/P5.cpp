#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstdint>

using namespace std;

using Row = vector<uint64_t>;
using Matrix = vector<Row>;

Row parse_row(const string& s, int n, int blocks) {
    Row row(blocks, 0);
    int bit_idx = 0;
    for (char c : s) {
        int nibble;
        if ('0' <= c && c <= '9') nibble = c - '0';
        else if ('A' <= c && c <= 'F') nibble = 10 + c - 'A';
        else if ('a' <= c && c <= 'f') nibble = 10 + c - 'a';
        else nibble = 0;
        for (int b = 3; b >= 0 && bit_idx < n; --b, ++bit_idx) {
            if (nibble & (1 << b)) {
                int block = bit_idx / 64;
                int offset = bit_idx % 64;
                row[block] |= (uint64_t(1) << offset);
            }
        }
    }
    return row;
}

Matrix read_matrix(int n, int blocks) {
    Matrix mat(n, Row(blocks));
    int hex_len = (n + 3) / 4;
    for (int i = 0; i < n; ++i) {
        string token;
        cin >> token;
        mat[i] = parse_row(token, n, blocks);
    }
    return mat;
}

Row mat_vec(const Matrix& mat, const Row& v, int n, int blocks) {
    Row res(blocks, 0);
    for (int i = 0; i < n; ++i) {
        int parity = 0;
        const Row& row = mat[i];
        for (int b = 0; b < blocks; ++b) {
            parity ^= (__builtin_popcountll(row[b] & v[b]) & 1);
        }
        if (parity) {
            int block = i / 64;
            int off = i % 64;
            res[block] |= (uint64_t(1) << off);
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    int blocks = (n + 63) / 64;

    Matrix A = read_matrix(n, blocks);
    Matrix B = read_matrix(n, blocks);
    Matrix C = read_matrix(n, blocks);

    mt19937_64 rng(1234567);
    const int K = 8;

    Row mask(blocks, ~uint64_t(0));
    if (n % 64 != 0) {
        mask.back() = (uint64_t(1) << (n % 64)) - 1;
    }

    for (int t = 0; t < K; ++t) {
        Row r(blocks);
        for (int b = 0; b < blocks; ++b) r[b] = rng() & mask[b];

        Row Br = mat_vec(B, r, n, blocks);
        Row ABr = mat_vec(A, Br, n, blocks);
        Row Cr = mat_vec(C, r, n, blocks);

        bool equal = true;
        for (int b = 0; b < blocks; ++b) {
            if ((ABr[b] ^ Cr[b]) & mask[b]) { equal = false; break; }
        }
        if (!equal) {
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES\n";
    return 0;
}
