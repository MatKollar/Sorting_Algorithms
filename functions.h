#ifndef SORTING_ALGORITHMS_ALGORITHMS_H
#define SORTING_ALGORITHMS_ALGORITHMS_H
#include <vector>

struct timeComplexity;
struct sortingAlgorithm;

int mainMenu();
void printAlgorithms();
char userSelection();
void algorithmInit(char selection);
void algorithmDescription(sortingAlgorithm &algorithm);
void userInput(sortingAlgorithm &algorithm);
std::vector<int> filterNumbers(int &length);
void printSortedArray(int array[], int length);
void swap(int *a, int *b);
void bubbleSort(int array[], int length);
void selectionSort(int array[], int length);
void insertionSort(int array[], int length);
void merge(int *array, int low, int middle, int high);
void mergeSortRecursive(int *array, int low, int high);
void mergeSort(int array[], int length);
int partition(int *array, int low, int high);
void quickSortRecursive(int *array,int low,int high);
void quickSort(int *array, int length);
void heapify(int *array, int length, int i);
void buildMaxHeap(int *array, int length);
void heapSort(int *array, int length);

#endif //SORTING_ALGORITHMS_ALGORITHMS_H