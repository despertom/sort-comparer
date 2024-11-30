// dylan esperto
#include <iostream>
#include <vector>
#include "sorts.h"

// Partition method for quicksort.
int Sorts::partition(std::vector<int> &toSort, const int first, const int last) {
    const int pivot = toSort[first];
    int up = first, down = last;
    do {
        for (; up < last; up++)
            if(pivot < toSort[up])
                break;
        for (; down > first; down--)
            if(pivot > toSort[down])
                break;
        if (up < down)
            std::swap(toSort[up], toSort[down]);
    } while (up < down);
    std::swap(toSort[first], toSort[down]);
    return down;
}

// Quicksort. Sorts vector in place to ascending order.
void Sorts::quickSort(std::vector<int> &toSort, const int first, const int last) {
    if (first < last) {
        const int pivot = partition(toSort, first, last);
        quickSort(toSort, first, pivot);
        quickSort(toSort, pivot + 1, last);
    }
}

// Easy to use mergesort. Returns sorted array.
void Sorts::quickSort(std::vector<int> &toSort) {
    quickSort(toSort, 0, toSort.size() - 1);
}

// Merge for mergeSort.
void Sorts::merge(std::vector<int> &toSort, const int first, const int mid, const int last) {
    // copy unsorted section
    int unsorted[last - first + 1];
    for (int i = first; i <= last; i++)
        unsorted[i - first] = toSort[i];
    int a = first, b = mid + 1, i = first;
    // Copy from each side based on correct order.
    while (a <= mid && b <= last)
        if (unsorted[a - first] < unsorted[b - first])
            toSort[i++] = unsorted[a++ - first];
        else
            toSort[i++] = unsorted[b++ - first];
    // Move leftover to array
    while (a <= mid)
        toSort[i++] = unsorted[a++ - first];
    while (b <= last)
        toSort[i++] = unsorted[b++ - first];
}

// Mergesort. Sorts in ascending order.
void Sorts::mergeSort(std::vector<int> &toSort, const int first, const int last) {
    if (first < last) {
        const int middle = (first + last) / 2;
        mergeSort(toSort, first, middle);
        mergeSort(toSort, middle + 1, last);
        merge(toSort, first, middle, last);
    }
}

// Easy to use mergesort. Returns sorted array.
void Sorts::mergeSort(std::vector<int> &toSort) {
    mergeSort(toSort, 0, toSort.size() - 1);
}

void Sorts::bubbleSort(std::vector<int> &toSort) {
    for (int pass = 1; pass < toSort.size(); pass++)
        for (int i = 1; i < toSort.size() - pass + 1; i++)
            if (toSort[i] < toSort[i - 1])
                std::swap(toSort[i - 1], toSort[i]);
}

void Sorts::selectionSort(std::vector<int> &toSort) {
    for (int i = 0; i < toSort.size() - 1; i++) {
        // Find where the smallest element is
        int min = i;
        for (int j = i + 1; j < toSort.size(); j++)
            if (toSort[j] < toSort[min])
                min = j;
        // Move the min element to the right place
        std::swap(toSort[i], toSort[min]);
    }
}

void Sorts::insertionSort(std::vector<int> &toSort) {
    for (int i = 1; i < toSort.size(); i++) {
        int value = toSort[i];
        int j = i - 1;
        while (j >= 0 && toSort[j] > value) {
            std::swap(toSort[j + 1], toSort[j]);
            j = j - 1;
        }
        toSort[j + 1] = value;
    }
}

void Sorts::printVector(std::vector<int> &vec) {
    for (int i : vec)
        std::cout << i << " ";
    std::cout << std::endl;
}

// int main() {
//     {
//         auto start = std::chrono::high_resolution_clock::now();
//         std::vector<int> toSort = {1, 5, 2, 6, 7, 9, -1, -5, -2, 0, 10, -59};
//         mergeSort(toSort);
//         auto end = std::chrono::high_resolution_clock::now();
//         std::cout
//             << "Merge sort took: "
//             << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
//             << std::endl;
//     }
//     {
//         auto start = std::chrono::high_resolution_clock::now();
//         std::vector<int> toSort = {1, 5, 2, 6, 7, 9, -1, -5, -2, 0, 10, -59};
//         quickSort(toSort);
//         auto end = std::chrono::high_resolution_clock::now();
//         std::cout
//             << "Quicksort took: "
//             << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
//             << std::endl;
//     }
//     {
//         auto start = std::chrono::high_resolution_clock::now();
//         std::vector<int> toSort = {1, 5, 2, 6, 7, 9, -1, -5, -2, 0, 10, -59};
//         bubbleSort(toSort);
//         auto end = std::chrono::high_resolution_clock::now();
//         std::cout
//             << "Bubble sort took: "
//             << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
//             << std::endl;
//     }
//     return 0;
// }
