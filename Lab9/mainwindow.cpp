#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->input_1->clear();
    ui->input_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_1->setRowCount(1);

    ui->input_2->clear();
    ui->input_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_2->setRowCount(1);

    arr = nullptr;
    size = -1;
    numOfComparisons=0;
    numOfNulls = 0;
    ressize = -1;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_count_valueChanged(int arg1)
{
    ui->input_1->setColumnCount(arg1);
    ui->input_2->setColumnCount(arg1);
    delete [] arr;
    arr = new int[arg1];
}

void MainWindow::on_pushButton_2_clicked()
{// click on enter
    int* arrA = new int[ui->count->text().toInt()];
    int* arrB = new int[ui->count->text().toInt()];
    bool ok = true;
    if(!arr)
    {
        ui->statusbar->showMessage("Fill Array");
        return;
    }

    for(int i = 0; i<ui->count->text().toInt(); ++i)
    {
        QTableWidgetItem *item1(ui->input_1->item(0,i));
        if (!item1)
        {
            ui->statusbar->showMessage("Fill Array");
            return;
        }
        ui->input_1->item(0,i)->text().toInt(&ok);
        if(!ok)
        {
            ui->statusbar->showMessage(QString("Can not convert item at %1 column to integer").arg(i+1));
            return;
        }
        arrA[i] = ui->input_1->item(0, i)->text().toInt();
        arrB[i] = ui->input_2->item(0, i)->text().toInt();
    }
    for(int i = 0; i<ui->count->text().toInt(); ++i)
    {
        arr[i] = (i&1)? arrB[i]:arrA[i];
    }
    ui->statusbar->showMessage("Array saved");
}

void MainWindow::on_pushButton_clicked()
{//generate random values
    int* arrA = new int[ui->count->text().toInt()];
    int* arrB = new int[ui->count->text().toInt()];
    for(int i = 0; i<ui->count->text().toInt(); ++i)
    {
        arrA[i] = qrand() % ((100 + 1) - (-100)) + (-100);
        arrB[i] = qrand() % ((100 + 1) - (-100)) + (-100);
    }
    ui->input_1->clear();
    ui->input_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_1->setRowCount(1);
    ui->input_1->setColumnCount(ui->count->text().toInt());
    for(int i = 0; i < ui->count->text().toInt(); ++i)
    {
        ui->input_1->setItem(0, i,new QTableWidgetItem(QString::number(arrA[i])));
        ui->input_2->setItem(0, i,new QTableWidgetItem(QString::number(arrB[i])));
        arr[i] = (i&1)? arrB[i]:arrA[i];
    }
    ui->statusbar->showMessage("Array saved");
}

QString MainWindow::printStep(int array[], int size, int index) {
    QString log = "";
    log+= "Step"+QString::number(index+1)+":\n";
    for (int i = 0; i < size-1; i++)
       if(i == index) log+="|" +QString::number(array[i])+"|" + " ";
       else log+=" "+QString::number(array[i]) + "  ";
    if(size-1 == index) log+="|" +QString::number(array[size-1])+"|" + " ";
    else log+=QString::number(array[size-1]) + "\n";
    return log;
}
QString MainWindow::printArray1(int array[], int a, int b) {
    QString log = "";
    for (int i = a; i < b; i++)
       log+=QString::number(array[i]) + " ";
    log+="\n";
    return log;
}

QString MainWindow::printArray(int array[], int size) {
    QString log = "";
    for (int i = 0; i < size; i++)
       log+=QString::number(array[i]) + " ";
    log+="\n";
    return log;
}
QString MainWindow::printDivideby5(int array[], int size) {
    QString log = "";
    for (int i = 0; i < size; i++)
       if(arr[i]%5 == 0)log+=QString::number(array[i]) + " ";
    return log;
}
void MainWindow::binarySearch(int arr[],QString* log) {
    numOfComparisons=0;
    numOfNulls = 0;
    int low = 0, high = ui->count->text().toInt() - 1;
        low = 0;
        high = ui->count->text().toInt() - 1;
        int startIndex = -1;
        *log+="\nSearch start:\n";
        while (low <= high) {
                        int mid = (high - low) / 2 + low;
                        if (abs(arr[mid]%5) > 0) {
                            high = mid - 1;
                        } else if (abs(arr[mid]%5) == 0) {
                            startIndex = mid;
                            high = mid - 1;
                        } else
                            low = mid + 1;
                       numOfComparisons++;
               *log+= printStep(arr,ui->count->text().toInt(),mid);
            }
            int endIndex = -1;
            low = 0;
            high = ui->count->text().toInt() - 1;
            *log+="\nSearch end:\n";
            while (low <= high) {
                int mid = (high - low) / 2 + low;
                                if (abs(arr[mid]%5) > 0) {
                                    high = mid - 1;
                                } else if (abs(arr[mid]%5) == 0) {
                                    endIndex = mid;
                                    low = mid + 1;
                                } else
                                    low = mid + 1;

           numOfComparisons++;
           *log+= printStep(arr,ui->count->text().toInt(),mid);
        }
        *log+="\nOutput array:\n";
        *log+= printArray1(arr,startIndex, endIndex+1);
        numOfNulls = endIndex - startIndex +1;
}
void Shell(int *arr, int size)
{
    for(int gap = size/2, k = 0; gap > 0; gap /= 2, k++)
    {
        for(int i = gap; i < size; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && abs(arr[j - gap]%5)>abs(temp%5); j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}
int count(int res[],int size){
    int k =0;
    for(int i = 0; i < size; i++){
        if(!res[i]%5) k++;
    }
    return k;
}
void MainWindow::on_pushButton_4_clicked()
{
    QString log = "";
    log+="Input array:\n";
    log+= printArray(arr, ui->count->text().toInt());
    log+="Array after sorting:\n";
    Shell(arr,ui->count->text().toInt());
    log+= printArray(arr, ui->count->text().toInt());
    ressize = count(arr,ui->count->text().toInt());
    int* res = new int[ressize];
    log+="Searching...:\n";
    const auto begin = std::chrono::high_resolution_clock::now();
    binarySearch(arr,&log);
    auto end = std::chrono::high_resolution_clock::now() - begin;
    auto time = std::chrono::duration<double, std::milli>(end).count();

    ui->BS->setText(log);
    QString out = "";
    out+= "Numbers that divide by 5: "+printDivideby5(arr,ui->count->text().toInt());
    out+= "\nCount of numbers that divide by 5 is: "+QString::number(numOfNulls);
    out+= "\nCount of comparisons is: "+QString::number(numOfComparisons);
    ui->output_1->setText(out);
    ui->time_1->setText(QString::number(time));
}

void MainWindow::on_pushButton_5_clicked()
{ // click on exit
    close();
}
