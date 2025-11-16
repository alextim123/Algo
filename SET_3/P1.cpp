#include <iostream>
#include <vector>
using namespace std;

void heapify(vector<int>& A, int n, int i) {
    int cur = i;
    while (true) {
        int l = 2 * cur + 1;
        int r = l + 1;
        int largest = cur;
        if (l < n && A[l] > A[largest]) largest = l;
        if (r < n && A[r] > A[largest]) largest = r;
        if (largest == cur) break;
        swap(A[cur], A[largest]);
        cur = largest;
    }
}

void buildMaxHeap(vector<int>& A, int n) {
    for (int i = n/2 - 1; i >= 0; --i)
        heapify(A, n, i);
}

void heapSort(vector<int>& A, int n) {
    buildMaxHeap(A, n);
    for (int i = n-1; i >= 1; --i) {
        swap(A[0], A[i]);
        heapify(A, i, 0);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; ++i)
        cin >> A[i];
    heapSort(A, n);
    if (n > 0) {
        cout << A[0];
        for (int i = 1; i < n; ++i) {
            cout << ' ' << A[i];
        }
    }
    cout << '\n';
    return 0;
}
