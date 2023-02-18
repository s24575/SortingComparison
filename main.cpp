#include <stdio.h>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

constexpr int N = 1000000;

auto rng = std::default_random_engine{};

std::vector<int> get_random_array() {
    static std::vector<int> v;
    if (v.size()) return v;
    v.reserve(N);
    for (int i = 0; i < N; ++i) {
        v.push_back(i);
    }
    std::shuffle(v.begin(), v.end(), rng);
    return v;
}

std::vector<int> get_sorted_array() {
    std::vector<int> v;
    v.reserve(N);
    for (int i = 0; i < N; ++i) {
        v.push_back(i);
    }
    return v;
}

std::vector<int> get_reverse_sorted_array() {
    std::vector<int> v;
    v.reserve(N);
    for (int i = N - 1; i >= 0; --i) {
        v.push_back(i);
    }
    return v;
}

void heapify(std::vector<int>& v, int parent, int n) {
    int left = 2 * parent + 1;
    int right = 2 * parent + 2;

    if (left < n && (right < n && v[left] > v[right] && v[left] > v[parent] || right >= n && v[left] > v[parent])) {
        std::swap(v[left], v[parent]);
        heapify(v, left, n);
    }
    else if (left < n && right < n && v[left] <= v[right] && v[right] > v[parent] || left >= n && right < n && v[right] > v[parent]) {
        std::swap(v[right], v[parent]);
        heapify(v, right, n);
    }
}

void make_heap(std::vector<int>& v){
    int n = v.size();
    for (int i = n - 1; i >= 0; --i) {
        heapify(v, i, n);
    }
}

void heapsort(std::vector<int>& v) {
    for (int i = N - 1; i >= 0; --i) {
        std::swap(v[0], v[i]);
        heapify(v, 0, i);
    }
}

void heapsort_test() {
    // random
    std::vector<int> v = get_random_array();
    auto start = std::chrono::high_resolution_clock::now();
    make_heap(v);
    heapsort(v);
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time = stop - start;
    printf("%.2fms - heapsort random\n", time.count());

    // sorted
    v = get_sorted_array();
    start = std::chrono::high_resolution_clock::now();
    make_heap(v);
    heapsort(v);
    stop = std::chrono::high_resolution_clock::now();
    time = stop - start;
    printf("%.2fms - heapsort sorted\n", time.count());

    // reverse sorted
    v = get_reverse_sorted_array();
    start = std::chrono::high_resolution_clock::now();
    make_heap(v);
    heapsort(v);
    stop = std::chrono::high_resolution_clock::now();
    time = stop - start;
    printf("%.2fms - heapsort reverse sorted\n", time.count());
}

int partition(std::vector<int>& v, int lo, int hi) {
    const int pivot = v[hi];
    int smaller = lo;
    for (int i = lo; i < hi; ++i) {
        if (v[i] <= pivot) {
            std::swap(v[smaller++], v[i]);
        }
    }
    std::swap(v[smaller], v[hi]);
    return smaller;
}

void quicksort(std::vector<int>& v, int lo, int hi) {
    if (lo < hi) {
        const int q = partition(v, lo, hi);
        quicksort(v, lo, q - 1);
        quicksort(v, q + 1, hi);
    }
}
    
void quicksort_test() {
    // random
    std::vector<int> v = get_random_array();
    auto start = std::chrono::high_resolution_clock::now();
    quicksort(v, 0, N - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time = stop - start;
    printf("%.2fms - quicksort random\n", time.count());

    // sorted
    v = get_sorted_array();
    start = std::chrono::high_resolution_clock::now();
    quicksort(v, 0, N - 1);
    stop = std::chrono::high_resolution_clock::now();
    time = stop - start;
    printf("%.2fms - quicksort sorted\n", time.count());
    
    // reverse sorted
    v = get_reverse_sorted_array();
    start = std::chrono::high_resolution_clock::now();
    quicksort(v, 0, N - 1);
    stop = std::chrono::high_resolution_clock::now();
    time = stop - start;
    printf("%.2fms - quicksort reverse sorted\n", time.count());
}

void merge(std::vector<int>& v, int lo, int mid, int hi) {
    int i = lo;
    int j = mid + 1;
    std::vector<int> copy;
    copy.reserve(hi - lo + 1);
    while (i <= mid && j <= hi) {
        if (v[i] <= v[j]) {
            copy.push_back(v[i++]);
        }
        else {
            copy.push_back(v[j++]);
        }
    }
    while (i <= mid) {
        copy.push_back(v[i++]);
    }
    while (j <= hi) {
        copy.push_back(v[j++]);
    }
    std::memcpy(&v[lo], &copy[0], sizeof(int) * copy.size());
}

void mergesort(std::vector<int>& v, int lo, int hi) {
    if (lo < hi) {
        const int mid = (lo + hi) / 2;
        mergesort(v, lo, mid);
        mergesort(v, mid + 1, hi);
        merge(v, lo, mid, hi);
    }
}

void mergesort_test() {
    // random
    std::vector<int> v = get_random_array();
    auto start = std::chrono::high_resolution_clock::now();
    mergesort(v, 0, N - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time = stop - start;
    printf("%.2fms - mergesort random\n", time.count());

    // sorted
    v = get_sorted_array();
    start = std::chrono::high_resolution_clock::now();
    mergesort(v, 0, N - 1);
    stop = std::chrono::high_resolution_clock::now();
    time = stop - start;
    printf("%.2fms - mergesort sorted\n", time.count());

    // reverse sorted
    v = get_reverse_sorted_array();
    start = std::chrono::high_resolution_clock::now();
    mergesort(v, 0, N - 1);
    stop = std::chrono::high_resolution_clock::now();
    time = stop - start;
    printf("%.2fms - mergesort reverse sorted\n", time.count());
}

int main() {
    printf("Elements: %d\n", N);
    heapsort_test();
    quicksort_test();
    mergesort_test();
}

/* OUTPUT:
Elements: 1000000
175.31ms - heapsort random
88.42ms - heapsort sorted
93.66ms - heapsort reverse sorted

99.80ms - quicksort random
768195.74ms - quicksort sorted
639533.27ms - quicksort reverse sorted

343.26ms - mergesort random
186.52ms - mergesort sorted
205.90ms - mergesort reverse sorted
*/