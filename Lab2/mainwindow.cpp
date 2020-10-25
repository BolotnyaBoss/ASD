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
    arr = new int[arg1];
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
        ui->input_1->item(0,i)->text().toInt(&ok);
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
    size = ui->count->text().toInt();
    changed_size = 0;
    delete [] changed_arr_1;
    changed_arr_1 = new int[size];
    for(int i = 0; i < size; ++i)
    {
        if(arr[i]%3)
        {
            changed_arr_1[changed_size] = arr[i];
            changed_size++;
        }
    }
    ui->input_2->clear();
    ui->input_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_2->setRowCount(1);
    ui->input_2->setColumnCount(changed_size);
    for(int i = 0; i < changed_size; ++i)
    {
            changed_arr_1[i] = changed_arr_1[i]*changed_arr_1[i];
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
        arr[i] = qrand() % ((100 + 1) - (0)) + (0);
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
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
QString Selection(int *arr, int size, double & time)
{
    const auto begin = std::chrono::high_resolution_clock::now();
    QString log = "";
    log+="Unsorted array:\n";
    for(int j = 0; j < size-1; ++j)
    {
        log+=QString::number(arr[j]) + " ";
    }
    log+=QString::number(arr[size-1]) + "\n\n";
    int max_index, max;
    for(int i = 0; i < size-1; ++i)
    {
        max = arr[i];
        max_index = i;
        log+=QString("%1 iteration:\n").arg(i+1);
        for(int j = i+1; j < size; ++j)
        {
            if (max<arr[j]){
                max=arr[j];
              max_index = j;}
        }
        swap(&arr[max_index], &arr[i]);
        for(int j = 0; j < size-1; ++j)
        {
            log+=QString::number(arr[j]) + " ";
        }
        log+=QString::number(arr[size-1]) + "\n";
    }
    log+="\nSorted array:\n";
    for(int j = 0; j < size-1; ++j)
    {
        log+=QString::number(arr[j]) + " ";
    }
    log+=QString::number(arr[size-1]) + "\n";
    auto end = std::chrono::high_resolution_clock::now() - begin;
    time = std::chrono::duration<double, std::milli>(end).count();
    return log;
}

QString BubbleFlag(int *arr, int size, double & time)
{
    const auto begin = std::chrono::high_resolution_clock::now();
    bool flag = false;
    double tmp;
    QString log = "";
    log+="Unsorted array:\n";
    for(int j = 0; j < size-1; ++j)
    {
        log+=QString::number(arr[j]) + " ";
    }
    log+=QString::number(arr[size-1]) + "\n\n";
    for(int i = 0; i < size; i++)
    {
        flag = false;
        log+=QString("%1 iteration:\n").arg(i+1);
        for(int j = 0; j < size-1; ++j)
        {
            if(arr[j] > arr[j+1])
            {
                flag = true;
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
            log+=QString::number(arr[j]) + " ";
        }
        log+=QString::number(arr[size-1]) + "\n";
        if(!flag) break;
    }
    log+="\nSorted array:\n";
    for(int j = 0; j < size-1; ++j)
    {
        log+=QString::number(arr[j]) + " ";
    }
    log+=QString::number(arr[size-1]) + "\n";
    auto end = std::chrono::high_resolution_clock::now() - begin;
    time = std::chrono::duration<double, std::milli>(end).count();
    return log;
}

void MainWindow::on_pushButton_4_clicked()
{// click on sort
    double SS_time;
    ui->BS->setText(Selection(changed_arr_1, changed_size, SS_time));
    ui->output_1->setRowCount(1);
    ui->output_1->setColumnCount(changed_size);
    for (int i = 0; i < changed_size; ++i)
    {
        ui->output_1->setItem(0, i,new QTableWidgetItem(QString::number(changed_arr_1[i])));
    }

    ui->time_1->setText(QString::number(SS_time));
}

void MainWindow::on_pushButton_5_clicked()
{ // click on exit
    close();
}
