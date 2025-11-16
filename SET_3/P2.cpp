#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    if (n == 0) {
        cout << "\n";
        return 0;
    }
    const int SHIFT = 1000000;
    const int RANGE = 2 * SHIFT + 1;
    vector<int> cnt(RANGE, 0);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        cnt[x + SHIFT]++;
    }

    for (int i = 0; i < RANGE; ++i)
        for (int j = 0; j < cnt[i]; ++j)
            cout << i - SHIFT << " ";
    cout << endl;
    return 0;
}
