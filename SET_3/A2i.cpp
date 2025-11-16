#include <iostream>
#include <vector>
using namespace std;

void insertionSort(vector<int>& a, int l, int r) {
    for (int i = l + 1; i < r; ++i) {
        int x = a[i], j = i - 1;
        while (j >= l && a[j] > x) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = x;
    }
}

void merge(vector<int>& a, int l, int m, int r) {
    int n1 = m - l, n2 = r - m;
    vector<int> left(a.begin() + l, a.begin() + m);
    vector<int> right(a.begin() + m, a.begin() + r);

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            a[k++] = left[i++];
        else
            a[k++] = right[j++];
    }
    while (i < n1)
        a[k++] = left[i++];
    while (j < n2)
        a[k++] = right[j++];
}

void mergeInsertionSort(vector<int>& a, int l, int r) {
    if (r - l <= 15) {
        insertionSort(a, l, r);
        return;
    }
    int m = l + (r - l) / 2;
    mergeInsertionSort(a, l, m);
    mergeInsertionSort(a, m, r);
    merge(a, l, m, r);
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    mergeInsertionSort(a, 0, n);

    for (int i = 0; i < n; ++i)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}
