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

    ui->output_1->clear();
    ui->output_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->output_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->output_1->setRowCount(1);

    arr = nullptr;
    changed_arr_1 = nullptr;
    size = -1;
    changed_size = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_count_valueChanged(int arg1)
{
    ui->input_1->setColumnCount(arg1);
    delete [] arr;
    arr = new double[arg1];
}

void MainWindow::on_pushButton_2_clicked()
{// click on enter
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
        ui->input_1->item(0,i)->text().toDouble(&ok);
        if(!ok)
        {
            ui->statusbar->showMessage(QString("Can not convert item at %1 column to integer").arg(i+1));
            return;
        }
        arr[i] = ui->input_1->item(0, i)->text().toDouble();
    }
    ui->statusbar->showMessage("Array saved");
}

void MainWindow::on_pushButton_3_clicked()
{//click on change
    double min = arr[0];
    size = ui->count->text().toInt();
    changed_size = 0;
    delete [] changed_arr_1;
    changed_arr_1 = new double[size];
    for(int i = 0; i < size; ++i)
    {
        if(arr[i] < min) min = arr[i];
            changed_arr_1[changed_size] = arr[i];
            changed_size++;
    }
    ui->input_2->clear();
    ui->input_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_2->setRowCount(1);
    ui->input_2->setColumnCount(changed_size);
    for(int i = 0; i < changed_size; ++i)
    {
            if(changed_arr_1[i] < 0.0) changed_arr_1[i] *= min;
    }
    for(int i = 0; i < changed_size; ++i)
    {
        ui->input_2->setItem(0, i,new QTableWidgetItem(QString::number(changed_arr_1[i])));
    }
}

void MainWindow::on_pushButton_clicked()
{//generate random values
    for(int i = 0; i<ui->count->text().toInt(); ++i)
    {
        arr[i] = (qrand() % ((1000 + 1) - (-1000)) + (-1000))/10.0;
    }
    ui->input_1->clear();
    ui->input_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_1->setRowCount(1);
    ui->input_1->setColumnCount(ui->count->text().toInt());
    for(int i = 0; i < ui->count->text().toInt(); ++i)
    {
        ui->input_1->setItem(0, i,new QTableWidgetItem(QString::number(arr[i])));
    }
    ui->statusbar->showMessage("Array saved");
}
void swap(double *x, double *y)
{
    double temp = *x;
    *x = *y;
    *y = temp;
}
QString MainWindow::printArray(double arr[], int size) {
    QString log = "";
    for (int i = 0; i < size-1; i++)
       log+=QString::number(arr[i]) + " ";
    log+=QString::number(arr[size-1]) + "\n\n";
    return log;
}

// Function to partition the array on the basis of pivot element
int MainWindow::partition(double array[], int l, int r,QString* log,int k) {
    int i = l+1, j;
    int pivot = array[l];
    for (j = l+1; j <= r; j++)
    {
        if ( array[j] >= pivot )
        {
            swap(&array[i++],&array[j]);
        }
    }
    swap(&array[l],&array[i-1]);
    (*log)+=QString("%1 iteration:\n").arg(k+1);
    (*log)+= printArray(array,ui->count->text().toInt());
    return (i-1);
}

void MainWindow::quickSort(double array[], int low, int high,QString* log,int k) {
    if (low < high) {
        int pi = partition(array, low, high,log,k);
        k++;
        quickSort(array, low, pi - 1,log,k);
        quickSort(array, pi + 1, high,log,k);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    int k = 0;
    QString log = "";
    log+="Unsorted array:\n";
    log+= printArray(changed_arr_1, changed_size);
    log+="Sorting...:\n";
    const auto begin = std::chrono::high_resolution_clock::now();
    quickSort(changed_arr_1,0,changed_size-1,&log,k);
    auto end = std::chrono::high_resolution_clock::now() - begin;
    auto time = std::chrono::duration<double, std::milli>(end).count();
    log+="\nSorted array:\n";
    log+= printArray(changed_arr_1, changed_size);
    ui->BS->setText(log);
    ui->output_1->setRowCount(1);
    ui->output_1->setColumnCount(changed_size);
    for (int i = 0; i < changed_size; ++i)
    {
        ui->output_1->setItem(0, i,new QTableWidgetItem(QString::number(changed_arr_1[i])));
    }

    ui->time_1->setText(QString::number(time));
}

void MainWindow::on_pushButton_5_clicked()
{ // click on exit
    close();
}
