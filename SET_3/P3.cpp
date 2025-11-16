#include <iostream>
#include <vector>
using namespace std;

void radixSort(vector<int>& a) {
    const int base = 256;
    int n = a.size();
    vector<int> b(n);
    for (int it = 0; it < 4; ++it) {
        vector<int> cnt(base, 0);
        for (int i = 0; i < n; ++i) {
            int cur = (a[i] >> (it * 8)) & 255;
            cnt[cur]++;
        }
        for (int i = 1; i < base; ++i)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; --i) {
            int cur = (a[i] >> (it * 8)) & 255;
            b[--cnt[cur]] = a[i];
        }
        swap(a, b);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);

    for (int i = 0; i < n; ++i) cin >> a[i];

    vector<int> shift(n);
    for (int i = 0; i < n; ++i)
        shift[i] = a[i] + 1000000000;

    radixSort(shift);

    for (int i = 0; i < n; ++i)
        cout << (shift[i] - 1000000000) << " ";
    cout << endl;
    return 0;
}
