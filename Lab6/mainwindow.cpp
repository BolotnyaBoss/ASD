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

    size = ui->count->text().toInt();
    changed_size = 0;
    delete [] changed_arr_1;
    changed_arr_1 = new double[size];
    for(int i = 0; i < size; ++i)
    {
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
            changed_arr_1[i] = (int)(10*changed_arr_1[i])&1?  fabs(changed_arr_1[i]) : fabs(((int)(10*tan(changed_arr_1[i])))/10.0 - changed_arr_1[i]);
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
        arr[i] = (qrand() % ((100 + 1) - (-100)) + (-100))/10.0;
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

QString MainWindow::printArray(double array[], int size) {
    QString log = "";
    for (int i = 0; i < size-1; i++)
       log+=QString::number(array[i]) + " ";
    log+=QString::number(array[size-1]) + "\n\n";
    return log;
}

QString MainWindow::printArray1(int array[], int size) {
    QString log = "";
    for (int i = 0; i < size-1; i++)
       log+=QString::number(array[i]) + " ";
    log+=QString::number(array[size-1]) + "\n\n";
    return log;
}
void MainWindow::countingSort(double changed_arr_1[],QString* log) {
    int* input = new int[changed_size];
    for(int i = 0; i < changed_size; ++i)
    {
        input[i] = (int)(10 * changed_arr_1[i]);
    }
    int min = input[0];
    int max = input[0];
    for(int i = 0; i < changed_size; ++i)
    {
        if(input[i] < min) min = input[i];
        if(input[i] > max) max = input[i];
    }
    int size = max+1;
    int* count = new int[size];
        for(int i = 0; i < size; i++) {
            count[i] = 0;
        }
        for(int i = 0; i < changed_size; i++)
            count[input[i]]++;
        (*log) += "Count array :\n";
        (*log) += printArray1(count,size);
        for(int i = 0, j = 0; i <= size; i++){
            while(count[i]-- > 0)
                input[j++] = i;
        }
        for (int i = 0; i < changed_size; i++)
            changed_arr_1[i] = input[i]/10.;

}

void MainWindow::on_pushButton_4_clicked()
{
    QString log = "";
    log+="Unsorted array:\n";
    log+= printArray(changed_arr_1, changed_size);
    log+="Sorting...:\n";
    const auto begin = std::chrono::high_resolution_clock::now();
    countingSort(changed_arr_1,&log);
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
