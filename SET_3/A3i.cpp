#include <iostream>
#include <vector>
#include <cmath>
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

void heapify(vector<int>& a, int n, int i, int l) {
    int largest = i, left = 2 * (i - l) + 1 + l, right = 2 * (i - l) + 2 + l;
    if (left < l + n && a[left] > a[largest]) largest = left;
    if (right < l + n && a[right] > a[largest]) largest = right;
    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest, l);
    }
}

void heapSort(vector<int>& a, int l, int r) {
    int n = r - l;
    for (int i = l + n/2 - 1; i >= l; --i) heapify(a, n, i, l);
    for (int i = r - 1; i > l; --i) {
        swap(a[l], a[i]);
        heapify(a, i - l, l, l);
    }
}

int partition(vector<int>& a, int l, int r) {
    int pivot = a[l + (r - l) / 2];
    int i = l, j = r - 1;
    while (i <= j) {
        while (a[i] < pivot) ++i;
        while (a[j] > pivot) --j;
        if (i <= j) swap(a[i++], a[j--]);
    }
    return i;
}

void introsort(vector<int>& a, int l, int r, int depth_limit) {
    if (r - l < 16) {
        insertionSort(a, l, r);
        return;
    }
    if (depth_limit == 0) {
        heapSort(a, l, r);
        return;
    }
    int p = partition(a, l, r);
    introsort(a, l, p, depth_limit - 1);
    introsort(a, p, r, depth_limit - 1);
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    int depth_limit = n > 0 ? 2 * static_cast<int>(log2(n)) : 0;
    introsort(a, 0, n, depth_limit);

    for (int i = 0; i < n; ++i)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}
