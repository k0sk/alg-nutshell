#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

void swap_el(std::vector<int> &A, int i, int j) {
    int tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

void heapify(std::vector<int> &A, int idx, int max_idx) {
    int left = 2 * idx + 1,
        right = 2 * idx + 2;

    int largest = idx;
    if (left < max_idx && A[left] > A[idx]) largest = left;
    if (right < max_idx && A[right] > A[largest]) largest = right;

    if (largest != idx) {
        swap_el(A, idx, largest);
        heapify(A, largest, max_idx);
    }
}

void build_heap(std::vector<int> &A) {
    for (int i = A.size() / 2 - 1; i >= 0; i--){
        heapify(A, i, A.size());
    }
}

void heap_sort(std::vector<int> &A) {
    build_heap(A);

    for (int i = A.size() - 1; i >= 1; i--) {
        swap_el(A, 0, i);
        heapify(A, 0, i);
    }
}

TEST_CASE("Array is sorted", "[heap_sort]") {
    int A_SIZE = 100;
    srand(time(NULL));

    std::vector<int> A(A_SIZE), ANS(A_SIZE);
    for (int i = A_SIZE - 1; i >= 0; i--) {
        int tmp = rand() % A_SIZE;
        A[i] = ANS[i] = tmp;
    }

    heap_sort(A);
    sort(ANS.begin(), ANS.end());

    for (int i = 0; i < A_SIZE; i++) {
        REQUIRE(A[i] == ANS[i]);
    }
}

