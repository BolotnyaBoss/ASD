#ifndef CSORTINGALGORITHMS_H
#define CSORTINGALGORITHMS_H
#include <QTextEdit>
#include <QTime>
#include<QTableWidget>
#include <QLineEdit>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <QMessageBox>
#include <QDebug>
#include<vector>

class CSortingAlgorithms {

private:
    int *arr;
    int size;
    double time;

public:
    CSortingAlgorithms(){}
    CSortingAlgorithms(int);
    ~CSortingAlgorithms();

    void generateArr(int);
    void setArr(const CSortingAlgorithms &);
    void printArray(std::string);

    void bubbleSort();
    void selectionSort();
    void shellSort ();

    void mergeSorting(int, int);
    void mergeSort(int,int);
    void merge(int, int, int);

    void quickSorting(int, int);
    int partition(int, int);
    void quickSort(int, int);
    void countingSort();

    void swap(int *, int*);
    int *getArray() { return arr;};
    int getSize() {return size;}
    long double getTime(){return time;}
};

#endif // CSORTINGALGORITHMS_H
