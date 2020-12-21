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

    arr = nullptr;
    size = -1;
    numOfComparisons=0;
    numOfNulls = 0;
    sum = 0;
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
        arr[i] = ui->input_1->item(0, i)->text().toInt();
    }
    ui->statusbar->showMessage("Array saved");
}

void MainWindow::on_pushButton_clicked()
{//generate random values
    for(int i = 0; i<ui->count->text().toInt(); ++i)
    {
        arr[i] = qrand() % ((100 + 1) - (-100)) + (-100);
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

QString MainWindow::printArray(int array[], int size) {
    QString log = "";
    for (int i = 0; i < size-1; i++)
       log+=QString::number(array[i]) + " ";
    log+=QString::number(array[size-1]) + "\n\n";
    return log;
}

void MainWindow::linearSearch(int arr[],QString* log) {
    numOfComparisons=0;
    numOfNulls = 0;
    sum = 0;
    for(int i = 0; i < ui->count->text().toInt(); i++){
        if(arr[i]<0) sum += arr[i];
    }
    *log+="Sum of negative elements of array is:"+QString::number(sum)+"\n";
    if(sum<0) sum *= -1;
    for(int i = 0; i < ui->count->text().toInt(); i++){
        if(!arr[i]){
            arr[i] = sum;
            numOfNulls++;
        }
        numOfComparisons++;
        *log+= printStep(arr,ui->count->text().toInt(),i);
    }

}

void MainWindow::on_pushButton_4_clicked()
{
    QString log = "";
    log+="Input array:\n";
    log+= printArray(arr, ui->count->text().toInt());
    log+="Searching...:\n";
    const auto begin = std::chrono::high_resolution_clock::now();
    linearSearch(arr,&log);
    auto end = std::chrono::high_resolution_clock::now() - begin;
    auto time = std::chrono::duration<double, std::milli>(end).count();
    log+="\nOutput array:\n";
    log+= printArray(arr, ui->count->text().toInt());
    ui->BS->setText(log);
    QString out = "";
    out+= "Count of nulls is: "+QString::number(numOfNulls);
    out+= "\nCount of comparisons is: "+QString::number(numOfComparisons);
    out+="\nSum of negative elements of array is:"+QString::number(sum);
    ui->output_1->setText(out);
    ui->time_1->setText(QString::number(time));
}

void MainWindow::on_pushButton_5_clicked()
{ // click on exit
    close();
}
