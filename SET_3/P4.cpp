#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Frac {
    int num, den;
    string repr;
};

int main() {
    int n;
    cin >> n;
    vector<Frac> arr(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        int p = s.find('/');
        arr[i].num = stoi(s.substr(0, p));
        arr[i].den = stoi(s.substr(p+1));
        arr[i].repr = s;
    }

    stable_sort(arr.begin(), arr.end(), [](const Frac& a, const Frac& b) {
        return 1LL * a.num * b.den < 1LL * b.num * a.den;
    });

    for (int i = 0; i < n; ++i)
        cout << arr[i].repr << " ";
    cout << endl;
    return 0;
}
