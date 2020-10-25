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
    size = 0;
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
    arr = new QString [arg1];
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
//        ui->input_1->item(0,i)->text().toString(&ok);
//        if(!ok)
//        {
//            ui->statusbar->showMessage(QString("Can not convert item at %1 column to double").arg(i+1));
//            return;
//        }
        arr[i] = ui->input_1->item(0, i)->text();
    }
    ui->statusbar->showMessage("Array saved");
}

void MainWindow::on_pushButton_3_clicked()
{//click on change
    size = ui->count->text().toInt();
    changed_size = 0;
    delete [] changed_arr_1;
    changed_arr_1 = new QString[size];
    for(int i = 0; i < size; ++i)
    {
        if(arr[i].length() <= 8)
        {
            changed_arr_1[changed_size] = arr[i];
            changed_size++;
        }
    }
    //if(changed_size%2) changed_size--;
    ui->input_2->clear();
    ui->input_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_2->setRowCount(1);
    ui->input_2->setColumnCount(changed_size);
    for(int i = 0; i < changed_size; ++i)
    {
        ui->input_2->setItem(0, i,new QTableWidgetItem(changed_arr_1[i]));
    }
}

void MainWindow::on_pushButton_clicked()
{//generate random values
    for(int i = 0; i<ui->count->text().toInt(); ++i)
    {
        arr[i] = sities[qrand() % ((237 + 1) - (-1)) + (-1)];
    }
    ui->input_1->clear();
    ui->input_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_1->setRowCount(1);
    ui->input_1->setColumnCount(ui->count->text().toInt());
    for(int i = 0; i < ui->count->text().toInt(); ++i)
    {
        ui->input_1->setItem(0, i,new QTableWidgetItem(arr[i]));
    }
    ui->statusbar->showMessage("Array saved");
}
QString Shell(QString *arr, int size, double & time)
{
    const auto begin = std::chrono::high_resolution_clock::now();
    QString log = "";
    log+="Unsorted array:\n";
    for(int j = 0; j < size-1; ++j)
    {
        log+=arr[j] + " ";
    }
    log+=arr[size-1] + "\n\n";
    for(int gap = size/2, k = 0; gap > 0; gap /= 2, k++)
    {
        log+=QString("%1 iteration:\n").arg(k+1);
        for(int i = gap; i < size; i++)
        {
            QString temp = arr[i];
            int j;
            for (j = i; j >= gap && QString::compare(arr[j - gap],temp) > 0; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
            if(i!=(size-1)){
                for(int j = 0; j < size-1; ++j)
                {
                    log+=arr[j] + " ";
                }
            log+=arr[size-1] + "\n";}
        }
        for(int j = 0; j < size-1; ++j)
        {
            log+=arr[j] + " ";
        }
        log+=arr[size-1] + "\n";
    }
    log+="\nSorted array:\n";
    for(int j = 0; j < size-1; ++j)
    {
        log+=arr[j] + " ";
    }
    log+=arr[size-1] + "\n";
    auto end = std::chrono::high_resolution_clock::now() - begin;
    time = std::chrono::duration<double, std::milli>(end).count();
    return log;
}
void MainWindow::on_pushButton_4_clicked()
{// click on sort
    double SS_time;
    ui->BS->setText(Shell(changed_arr_1, changed_size, SS_time));
    ui->output_1->setRowCount(1);
    ui->output_1->setColumnCount(changed_size);
    for (int i = 0; i < changed_size; ++i)
    {
        ui->output_1->setItem(0, i,new QTableWidgetItem(changed_arr_1[i]));
    }

    ui->time_1->setText(QString::number(SS_time));
}

void MainWindow::on_pushButton_5_clicked()
{ // click on exit
    close();
}
