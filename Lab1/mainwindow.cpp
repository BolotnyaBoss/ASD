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
    filtred_arr_1 = nullptr;
    filtred_arr_2 = nullptr;
    size = 0;
    position = -1;
    filtred_size = 0;
    max = -99999999,0;
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
    max = -999999;
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
            ui->statusbar->showMessage(QString("Can not convert item at %1 column to double").arg(i+1));
            return;
        }
        arr[i] = ui->input_1->item(0, i)->text().toDouble();
    }
    for(int i = 0; i < ui->count->text().toInt(); ++i)
    {
        if(arr[i] > max)
        {
            max = arr[i];
            position = i;
        }
    }
    ui->statusbar->showMessage("Array saved");
    ui->max_lable->setText(QString("%1").arg(max));
}

void MainWindow::on_pushButton_3_clicked()
{//click on change
    size = ui->count->text().toInt();
    filtred_size = 0;
    delete [] filtred_arr_1;
    delete [] filtred_arr_2;
    filtred_arr_1 = new double[size];
    filtred_arr_2 = new double[size];
    for(int i = 0; i < size; ++i)
    {
        if(i > position)
        {
            filtred_arr_1[filtred_size] = arr[i];
            filtred_arr_2[filtred_size] = arr[i];
            filtred_size++;
        }
    }
    ui->input_2->clear();
    ui->input_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->input_2->setRowCount(1);
    ui->input_2->setColumnCount(filtred_size);
    for(int i = 0; i < filtred_size; ++i)
    {
        ui->input_2->setItem(0, i,new QTableWidgetItem(QString::number(filtred_arr_1[i])));
    }
}

void MainWindow::on_pushButton_clicked()
{//generate random values
    max = -999999;
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
    for(int i = 0; i < ui->count->text().toInt(); ++i)
    {
        if(arr[i] > max)
        {
            max = arr[i];
            position = i;
        }
    }
    ui->statusbar->showMessage("Array saved");
    ui->max_lable->setText(QString("%1").arg(max));
}

QString Bubble(double *arr, int size, double & time)
{
    const auto begin = std::chrono::high_resolution_clock::now();
    float tmp;
    QString log = "";
    log+="Unsorted array:\n";
    for(int j = 0; j < size-1; ++j)
    {
        log+=QString::number(arr[j]) + " ";
    }
    log+=QString::number(arr[size-1]) + "\n\n";
    for(int i = 0; i < size; ++i)
    {
        log+=QString("%1 iteration:\n").arg(i+1);
        for(int j = 0; j < size-1; ++j)
        {
            if(arr[j] > arr[j+1])
            {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
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

QString BubbleFlag(double *arr, int size, double & time)
{
    const auto begin = std::chrono::high_resolution_clock::now();
    bool flag = true;
    float tmp;
    QString log = "";
    log+="Unsorted array:\n";
    for(int j = 0; j < size-1; ++j)
    {
        log+=QString::number(arr[j]) + " ";
    }
    log+=QString::number(arr[size-1]) + "\n\n";
    for(int i = 0; i < size && flag; i++)
    {
        flag = true;
        log+=QString("%1 iteration:\n").arg(i+1);
        for(int j = 0; j < size-1-i; ++j)
        {
            if(arr[j] > arr[j+1])
            {
                flag = false;
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
            log+=QString::number(arr[j]) + " ";
        }
        log+=QString::number(arr[size-1]) + "\n";
//        if(flag) break;
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
    double BS_time, BSF_time;
    ui->BS->setText(Bubble(filtred_arr_1, filtred_size, BS_time));
    ui->BSF->setText(BubbleFlag(filtred_arr_2, filtred_size, BSF_time));

    ui->output_1->setRowCount(1);
    ui->output_1->setColumnCount(filtred_size);
    for (int i = 0; i < filtred_size; ++i)
    {
        ui->output_1->setItem(0, i,new QTableWidgetItem(QString::number(filtred_arr_1[i])));
    }

    ui->time_1->setText(QString::number(BS_time));
    ui->time_2->setText(QString::number(BSF_time));
}

void MainWindow::on_pushButton_5_clicked()
{ // click on exit
    close();
}
