#include <iostream>
#include <string>
#include "functions.h"
using namespace std;

void printSortedArray(int array[], int length){

    cout << "\tSorted array: ";
    for (int i = 0; i < length; i++)
        cout << array[i] << " ";

    string back;
    cin >> back;
    mainMenu();
}

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void bubbleSort(int array[], int length){

    for (int i = 0; i < length - 1; i++)
        for (int j = 0; j < length-i-1; j++)
            if (array[j] > array[j+1])
                swap(&array[j], &array[j+1]);

    printSortedArray(array, length);
}

void selectionSort(int array[], int length){

    for (int i = 0; i < length; i++){
        int min = i;
        for (int j = i + 1; j < length; j++){
            if (array[j] < array[min])
                min = j;
        }
        if ( min != i )
            swap(&array[min], &array[i]);
    }

    printSortedArray(array, length);
}

void insertionSort(int array[], int length){

    for (int i = 1; i < length; i++){
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key){
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }

    printSortedArray(array, length);
}

void merge(int *array, int low, int middle, int high) {

    int i, j, key;
    int n1 = middle - low + 1;
    int n2 = high - middle;
    int leftArray[n1], rightArray[n2];

    for (i = 0; i < n1; i++)
        leftArray[i] = array[low+i];

    for (j = 0; j < n2; j++)
        rightArray[j] = array[middle+1+j];

    i = 0; j = 0; key = low;
    while (i < n1 && j < n2){

        if (leftArray[i] <= rightArray[j]){
            array[key] = leftArray[i];
            i++;
        }
        else{
            array[key] = rightArray[j];
            j++;
        }
        key++;
    }
    while (i<n1){
        array[key] = leftArray[i];
        i++;
        key++;
    }
    while (j<n2){
        array[key] = rightArray[j];
        j++;
        key++;
    }
}

void mergeSortRecursive(int *array, int low, int high){
    if (low < high){
        int middle = (high + low)/2;
        mergeSortRecursive(array, low, middle);
        mergeSortRecursive(array, middle + 1, high);
        merge(array, low, middle, high);
    }
}

void mergeSort(int array[], int length){
    mergeSortRecursive(array, 0, length - 1);
    printSortedArray(array, length);
}

int partition(int *array, int low, int high){
    int pivot = array[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++){
        if (array[j] < pivot){
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quickSortRecursive(int *array,int low,int high){
    if (low < high){
        int pivot = partition(array, low, high);
        quickSortRecursive(array, low, pivot - 1);
        quickSortRecursive(array, pivot + 1, high);
    }
}

void quickSort(int *array, int length){
    quickSortRecursive(array, 0, length - 1);
    printSortedArray(array, length);
}

void heapify(int *array, int length, int i){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < length && array[l] > array[largest])
        largest = l;
    else
        largest = i;

    if (r < length && array[r] > array[largest])
        largest = r;

    if (largest != i){
        swap(array[i], array[largest]);
        heapify(array, length, largest);
    }
}

void buildMaxHeap(int *array, int length){
    for (int i = length / 2 - 1 ; i >= 0; i--)
        heapify(array, length, i);
}

void heapSort(int *array, int length){

    buildMaxHeap(array, length);

    for (int i = length - 1; i > 0; i--){
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }
    printSortedArray(array, length);
}

void countSort(int *array, int length){
    int output[length];
    int k = array[0];
    for(int i = 0; i < length; i++){
        k = max(k, array[i]);
    }
    int count[k];
    for (int i = 0; i <= k; i++){
        count[i] = 0;
    }

    for (int i = 0; i < length; i++){
        count[array[i]]++;
    }

    for (int i = 1; i <= k; i++){
        count[i]+=count[i-1];
    }

    for (int i = 0; i < length; i++){
        output[count[array[i]] - 1] = array[i];
        count[array[i]]--;
    }

    for (int i=0; i < length; i++){
        array[i] = output[i];
    }
    printSortedArray(array, length);
}