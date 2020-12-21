#include "csortingalgorithms.h"
#include <QElapsedTimer>

int stopTime  = 10000;

CSortingAlgorithms::CSortingAlgorithms(int size){
    this->size = size;
    arr = new int [this->size];
    for(int i=0; i<this->size; ++i)
        arr[i] = rand()%10000;
}

void CSortingAlgorithms::swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void CSortingAlgorithms::printArray(std::string str){

    std::ofstream file;
    file.open(str + ".txt", std::ios::out | std::ios::trunc);
    for(int i=0; i<size; ++i)
        file << std::setw(5) << arr[i];
    file.close();
}

void CSortingAlgorithms::setArr(const CSortingAlgorithms &obj){
    this->size = obj.size;
    this->arr = new int [this->size];
    for(int i=0; i<this->size; ++i)
        this->arr[i] = obj.arr[i];
}

void CSortingAlgorithms::generateArr(int size){
    this->size = size;
    arr = new int [this->size];
    for(int i=0; i<this->size; ++i)
        arr[i] = rand()%100000;
}

void CSortingAlgorithms::bubbleSort(){
    QElapsedTimer timer;
    timer.restart();
    for(int i = 0; i < size; ++i){
        bool swapped = false;
        for(int j = 0; j < size - 1; ++j){
            if(arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if(timer.elapsed()> stopTime){
            time = -1;
            return;
        }
        if(!swapped) break;
    }
    printArray("BubbleSort" + std::to_string(size));
    time =  timer.elapsed();
}

void CSortingAlgorithms::selectionSort(){
    QElapsedTimer timer;
    timer.restart();
    int  min;
    for (int i = 0; i < size-1; ++i) {
        min = i;
        for(int j = i+1; j < size; ++j){
            if(arr[j] < arr[min]){
                min = j;
            }
        }
        swap(&arr[i],&arr[min]);
        if(timer.elapsed() > stopTime){
            time = -1;
            return;
        }
    }
    printArray("SelectionSort" + std::to_string(size));
    time =  timer.elapsed();
}

void CSortingAlgorithms::shellSort(){
    QElapsedTimer timer;
    timer.restart();
    for (int gap = size/2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            double temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap){
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
        if(timer.elapsed() > stopTime){
            time = -1;
            return;
        }
    }
    time = timer.elapsed();
    printArray("ShellSort" + std::to_string(size));
}

void CSortingAlgorithms::mergeSorting(int left, int right){
    QElapsedTimer timer;
    timer.restart();
    mergeSort(left,right);
    time = timer.elapsed();
    printArray("MergeSort" + std::to_string(size));
}

void CSortingAlgorithms::mergeSort(int left, int right){
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

void CSortingAlgorithms::merge(int left, int mid, int right) {
    int leftN = mid - left + 1;
    int rightN = right - mid;
    std::vector<int> L(leftN), R(rightN);

    for (int i = 0; i < leftN; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < rightN; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < leftN && j < rightN) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < leftN)
        arr[k++] = L[i++];

    while (j < rightN)
        arr[k++] = R[j++];
}

void CSortingAlgorithms::quickSorting(int left, int right){
    QElapsedTimer timer;
    timer.restart();
    quickSort(left,right);
    time = timer.elapsed();
    printArray("QuickSort" + std::to_string(size));
}

int CSortingAlgorithms::partition(int low, int high) {
    double pivot = arr[high];
    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(&i, &j);
            i++;
        }
    }
    swap(&arr[i], &arr[high]);
    return i;
}

void CSortingAlgorithms::quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

void CSortingAlgorithms::countingSort(){
    QElapsedTimer timer;
    timer.restart();
    int min = arr[0], max = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] < min)
            min = arr[i];

        else if (arr[i] > max)
            max = arr[i];
    }
    int *countArr = new int[max - min + 1];
    for (int i = 0; i < max - min+1; ++i)
        countArr[i] = 0;

    for (int i = 0; i < size; ++i)
        countArr[arr[i] - min] += 1;

    for (int i = 1; i < max - min + 1; ++i)
        countArr[i] += countArr[i - 1];

    int *tmpArr = new int[size];

    for (int i = size - 1; i >= 0; --i)
        tmpArr[--countArr[arr[i] - min]] = arr[i];

    for (int i = 0; i < size; ++i)
        arr[i] = tmpArr[i];

    time = timer.elapsed();
    delete[]tmpArr;
    delete[]countArr;
    printArray("CountingSort" + std::to_string(size));
}

CSortingAlgorithms::~CSortingAlgorithms(){
    delete [] arr;
}
