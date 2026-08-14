#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

// 1. Bubble Sort - O(n^2)
void bubbleSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 2. Insertion Sort - O(n^2)
void insertionSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 3. Merge Sort - O(n log n)
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++; k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++; k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
}

// Wrapper for Merge Sort to match the signature of the other sorts
void mergeSortWrapper(vector<int> arr) {
    mergeSort(arr, 0, arr.size() - 1);
}

int main() {
    // Generate a large array of random numbers
    int n = 5000;
    vector<int> data(n);
    for (int i = 0; i < n; i++) {
        data[i] = rand() % 10000;
    }

    cout << "Comparing Sorting Algorithms on " << n << " elements:\n";
    cout << "--------------------------------------------------\n";

    // Measure Bubble Sort
    auto start = high_resolution_clock::now();
    bubbleSort(data);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Bubble Sort time:    " << duration.count() << " ms (O(n^2))\n";

    // Measure Insertion Sort
    start = high_resolution_clock::now();
    insertionSort(data);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Insertion Sort time: " << duration.count() << " ms (O(n^2))\n";

    // Measure Merge Sort
    start = high_resolution_clock::now();
    mergeSortWrapper(data);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Merge Sort time:     " << duration.count() << " ms (O(n log n))\n";

    return 0;
}