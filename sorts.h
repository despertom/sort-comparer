#pragma once

class Sorts {
public:
    static int partition(std::vector<int> &toSort, int first, int last);
    static void quickSort(std::vector<int> &toSort, int first, int last);
    static void quickSort(std::vector<int> &toSort);
    static void merge(std::vector<int> &toSort, int first, int mid, int last);
    static void mergeSort(std::vector<int> &toSort, int first, int last);
    static void mergeSort(std::vector<int> &toSort);
    static void bubbleSort(std::vector<int> &toSort);
    static void selectionSort(std::vector<int> &toSort);
    static void insertionSort(std::vector<int> &toSort);
    static void heapify(std::vector<int> &toSort, int n, int i);
    static void heapSort(std::vector<int> &toSort);
    static void printVector(std::vector<int> &vec);
};
