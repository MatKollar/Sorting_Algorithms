#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct timeComplexity{
    string bestCase;
    string averageCase;
    string worstCase;
};

typedef struct timeComplexity timeComplexity;

struct sortingAlgorithm{
    string name;
    timeComplexity timeComplexity;
    string spaceComplexity;
    string stability;
    string pseudoCode;
    void (*algorithm)(int array[], int length){};
};

int mainMenu();

/*------------------------------------- Algorithms implementation ----------------------------------------------*/

void printSortedArray(int array[], int length){

    cout << "\tSorted array: ";
    for(int i = 0; i < length; i++)
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

    for(int i = 0; i < length; i++){
        int min = i;
        for(int j = i + 1; j < length; j++){
            if(array[j] < array[min])
                min = j;
        }
        if( min != i )
            swap(&array[min], &array[i]);
    }

    printSortedArray(array, length);
}

void insertionSort(int array[], int length){

    for(int i = 1; i < length; i++){
        int key = array[i];
        int j = i - 1;
        while(j >= 0 && array[j] > key){
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

        if(leftArray[i] <= rightArray[j]) {
            array[key] = leftArray[i];
            i++;
        }
        else{
            array[key] = rightArray[j];
            j++;
        }
        key++;
    }
    while (i<n1) {
        array[key] = leftArray[i];
        i++;
        key++;
    }
    while (j<n2) {
        array[key] = rightArray[j];
        j++;
        key++;
    }
}

void mergeSortRecursive(int *array, int low, int high) {
    if(low < high) {
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
    if(low < high){
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

    for (int i = length - 1; i > 0; i--) {
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }
    printSortedArray(array, length);
}
/*-------------------------------------------------------------------------------------------------------*/
vector<int> filterNumbers(int &length) {

    string userInput;
    stringstream ss;
    vector<int> numbers;
    int number;

    while (true){
        cin >> userInput;

        if (userInput == "m") {
            mainMenu();
        }

        ss << userInput;

        if (stringstream(userInput) >> number){
            numbers.push_back(number);
            length++;
        }

        if (cin.peek() == '\n') {
            break;
        }
    }

    return numbers;
}

void userInput(sortingAlgorithm &algorithm){
    int length = 0;
    vector<int> numbers = filterNumbers(length);
    int *unsortedArray = &numbers[0];
    algorithm.algorithm(unsortedArray, length);
}

void algorithmDescription(sortingAlgorithm &algorithm){
    system("cls");
    cout << "\n\t\t\t\t" << algorithm.name << endl;
    cout << "\n\tTime Complexity: " << endl;
    cout << "\n\t\tBest Case: " << algorithm.timeComplexity.bestCase << endl;
    cout << "\t\tAverage Case: " << algorithm.timeComplexity.averageCase << endl;
    cout << "\t\tWorst Case: " << algorithm.timeComplexity.worstCase << endl;
    cout << "\n\tSpace Complexity: " << algorithm.spaceComplexity << endl;
    cout << "\n\tStability: " << algorithm.stability << endl;
    cout << "\n\tPseudoCode: \n\n" << algorithm.pseudoCode << endl;
    cout << "\n\n\tEnter numbers separated by a space, which will be sorted using the " << algorithm.name << " algorithm" << endl;
    cout << "\t\t\t(If you want to return to main menu enter m)\n\n\t";

    userInput(algorithm);
}

void algorithmInit(char selection){
    sortingAlgorithm algorithm;

    switch(selection){
        case '0':
            algorithm.name = "Bubble Sort";
            algorithm.timeComplexity.bestCase = "O(n)";
            algorithm.timeComplexity.averageCase = "O(n^2)";
            algorithm.timeComplexity.worstCase = "O(n^2)";
            algorithm.spaceComplexity = "O(1)";
            algorithm.stability = "stable";
            algorithm.pseudoCode = "\tBUBBLESORT(A)\n\t"
                                   "    for i = 0 to A.length - 1\n\t"
                                   "        for j = 0 to A.length - i - 1\n\t"
                                   "            if A[j] > A[j + 1]\n\t"
                                   "                exchange A[j] with A[j + 1]\n";
            algorithm.algorithm = bubbleSort;
            break;

        case '1':
            algorithm.name = "Selection Sort";
            algorithm.timeComplexity.bestCase = "O(n^2)";
            algorithm.timeComplexity.averageCase = "O(n^2)";
            algorithm.timeComplexity.worstCase = "O(n^2)";
            algorithm.spaceComplexity = "O(1)";
            algorithm.stability = "not stable";
            algorithm.pseudoCode = "\tSELECTION-SORT(A)\n\t"
                                   "    for i = 0 to A.length\n\t"
                                   "        min = i\n\t"
                                   "        for j = i + 1 to A.length\n\t"
                                   "            if A[j] < A[min]\n\t"
                                   "                min = j\n\t"
                                   "        if min != i\n\t"
                                   "            exchange A[min] with A[i]\n";
            algorithm.algorithm = selectionSort;
            break;

        case '2':
            algorithm.name = "Insertion Sort";
            algorithm.timeComplexity.bestCase = "O(n)";
            algorithm.timeComplexity.averageCase = "O(n^2)";
            algorithm.timeComplexity.worstCase = "O(n^2)";
            algorithm.spaceComplexity = "O(1)";
            algorithm.stability = "stable";
            algorithm.pseudoCode = "\tINSERTION-SORT(A)\n\t"
                                   "    for i = 1 to A.length\n\t"
                                   "        key = A[i]\n\t"
                                   "        // Insert A[i] into the sorted sequence [A..i - 1].\n\t"
                                   "        j = i - 1\n\t"
                                   "        while j >= 0 and A[j] > key\n\t"
                                   "            A[j + 1] = A[j]\n\t"
                                   "            j = j - 1\n\t"
                                   "        A[j + 1] = key\n\t";
            algorithm.algorithm = insertionSort;
            break;

        case '3':
            algorithm.name = "Merge Sort";
            algorithm.timeComplexity.bestCase = "O(n*log n)";
            algorithm.timeComplexity.averageCase = "O(n*log n)";
            algorithm.timeComplexity.worstCase = "O(n*log n)";
            algorithm.spaceComplexity = "O(n)";
            algorithm.stability = "stable";
            algorithm.pseudoCode = "\tMERGE(A, low, middle, high)\n\t"
                                   "    n1 = middle - low + 1\n\t"
                                   "    n2 = high - middle\n\t"
                                   "    let L[n1] and R[n2] be new arrays\n\t"
                                   "    for i = 0 to n1\n\t"
                                   "        L[i] = A[low + 1]\n\t"
                                   "    for j = 0 to n2\n\t"
                                   "        R[j] = A[middle + j + 1]\n\t"
                                   "    i = 0, j = 0, k = low\n\t"
                                   "    while i <= n1 and j < n2\n\t"
                                   "        if L[i] <= R[j]\n\t"
                                   "            A[k] = L[i]\n\t"
                                   "            i = i + 1\n\t"
                                   "        else \n\t"
                                   "            A[k] = R[j]\n\t"
                                   "            j = j + 1\n\t"
                                   "            k = k + 1\n\t"
                                   "    while i < n1\n\t"
                                   "        A[k] = L[i]\n\t"
                                   "        i = i + 1\n\t"
                                   "        k = k + 1\n\t"
                                   "    while j < n2\n\t"
                                   "        A[k] = R[j]\n\t"
                                   "        j = j + 1\n\t"
                                   "        k = k + 1\n\n\t"
                                   "MERGE-SORT(A, low, high)\n\t"
                                   "    if low < high\n\t"
                                   "        middle = (high + low) / 2\n\t"
                                   "        MERGE-SORT(A, low, middle)\n\t"
                                   "        MERGE-SORT(A, middle + 1, high)\n\t"
                                   "        MERGE(A, low, middle, high)\n\t";

            algorithm.algorithm = mergeSort;
            break;

        case '4':
            algorithm.name = "Quick Sort";
            algorithm.timeComplexity.bestCase = "O(n*log n)";
            algorithm.timeComplexity.averageCase = "O(n*log n)";
            algorithm.timeComplexity.worstCase = "O(n^2)";
            algorithm.spaceComplexity = "O(log n)";
            algorithm.stability = "not stable";
            algorithm.pseudoCode = "\tPARTITION(A, low, high)\n\t"
                                   "    pivot = A[high]\n\t"
                                   "    i = low - 1\n\t"
                                   "    for j = low to high - 1\n\t"
                                   "        if A[j] <= pivot\n\t"
                                   "                i = i + 1\n\t"
                                   "                exchange A[i] with A[j]\n\t"
                                   "    exchange A[i + 1] with A[high]\n\t"
                                   "    return i + 1\n\n\t"
                                   "QUICKSORT(A, low, high)\n\t"
                                   "    if low < high\n\t"
                                   "        pivot = PARTITION(A, low, high)\n\t"
                                   "        QUICKSORT(A, low, pivot - 1)\n\t"
                                   "        QUICKSORT(A, pivot + 1, high)\n\t";

            algorithm.algorithm = quickSort;
            break;

        case '5':
            algorithm.name = "Heap Sort";
            algorithm.timeComplexity.bestCase = "O(n*log n)";
            algorithm.timeComplexity.averageCase = "O(n*log n)";
            algorithm.timeComplexity.worstCase = "O(n*log n)";
            algorithm.spaceComplexity = "O(1)";
            algorithm.stability = "not stable";
            algorithm.pseudoCode = "\tHEAPIFY(A, i)\n\t"
                                   "    l = left(i)\n\t"
                                   "    r = right(i)\n\t"
                                   "    if l <= A.heapsize and A[l] > A[i]\n\t"
                                   "        largest = l\n\t"
                                   "    else largest = i\n\t"
                                   "    if r <= A.heapsize and A[r] > A[largest]\n\t"
                                   "        largest = r\n\t"
                                   "    if largest != i\n\t"
                                   "        exchange A[i] with A[largest]\n\t"
                                   "        heapify[A,largest]\n\n\t"
                                   "BUILD-MAX-HEAP(A)\n\t"
                                   "    for i = A.length/2 - 1 downto 0\n\t"
                                   "        HEAPIFY(A, i)\n\n\t"
                                   "HEAP-SORT(A)\n\t"
                                   "    BUILD-MAX-HEAP(A)\n\t"
                                   "    for i = A.length - 1 downto 0\n\t"
                                   "        exchange A[0] with A[i]\n\t"
                                   "        HEAPIFY(A, 0)\n\t";

            algorithm.algorithm = heapSort;
            break;

        case 'q':
            exit(0);

        default:
            mainMenu();
            break;
    }
    algorithmDescription(algorithm);
}

char userSelection(){
    char selection;
    cin >> selection;
    return selection;
}

void printAlgorithms(){
    cout << "\n\t[0] Bubble Sort" << endl;
    cout << "\n\t[1] Selection Sort" << endl;
    cout << "\n\t[2] Insertion Sort" << endl;
    cout << "\n\t[3] Merge Sort" << endl;
    cout << "\n\t[4] Quick Sort" << endl;
    cout << "\n\t[5] Heap Sort" << endl;
    cout << "\n\t";
}

int mainMenu(){
    system("cls");
    cout << "\n\t\t\t\tSorting Algorithms" << endl;
    cout << "\tYou can select the sorting algorithm by entering the appropriate number." << endl;
    cout << "\t\t\t\t(To quit enter q)" << endl;
    printAlgorithms();

    char selection = userSelection();
    algorithmInit(selection);

    return 0;
}

int main() {
    mainMenu();
    return 0;
}
