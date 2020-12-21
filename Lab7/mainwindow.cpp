#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csortingalgorithms.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDebug>
#include <QValidator>

const int nAlgorithmsCount = 6;
long double sizeArr[7] = {1024, 4096, 16384, 65536, 262144, 1048576, 4194304};
CSortingAlgorithms *SortArr = new CSortingAlgorithms [nAlgorithmsCount];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::CreateTable(){
    for(int i=0 ; i<ui->tableWidget->rowCount(); ++i){
        for(int j=0; j<ui->tableWidget->columnCount(); ++j){
            if(!ui->tableWidget->item(i,j)){
                QTableWidgetItem *item = new QTableWidgetItem;
                ui->tableWidget->setItem(i,j, item);
                ui->tableWidget->item(i,j)->setText("");
            }
        }
    }
}
MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_pushButton_generate_clicked(){
    SortArr[0].generateArr(ui->comboBox->currentText().toInt());
    for(int i=1; i<nAlgorithmsCount; ++i)
        SortArr[i].setArr(SortArr[0]);
}

void MainWindow::on_pushButton_sort_clicked(){
    CreateTable();
    SortArr[0].bubbleSort();
    SortArr[1].selectionSort();
    SortArr[2].shellSort();
    SortArr[3].quickSorting(0, SortArr[3].getSize()-1);
    SortArr[4].mergeSorting(0,SortArr[4].getSize()-1);
    SortArr[5].countingSort();
    for(int i=0; i<ui->tableWidget->rowCount(); ++i){
        if(SortArr[i].getTime()==(double)-1){
            ui->tableWidget->item(i, ui->comboBox->currentIndex())->setText("SLOW");
        }
        else{
            ui->tableWidget->item(i, ui->comboBox->currentIndex())->setText(QString::number(SortArr[i].getTime(), 'g', 10));
        }
    }
}

void MainWindow::on_pushButton_showDiagram_clicked(){
    QLineSeries **series =  new QLineSeries *[nAlgorithmsCount]();

    for(int i=0; i<nAlgorithmsCount; ++i)
        series[i] = new QLineSeries();

    for(int i=0; i<ui->tableWidget->rowCount(); ++i){
        for(int j=0; j<ui->tableWidget->columnCount(); ++j){
            if(ui->tableWidget->item(i,j)->text() != ""){
                if(ui->tableWidget->item(i,j)->text() == "SLOW")
                    series[i]->append(ui->tableWidget->horizontalHeaderItem(j)->text().toDouble(), ui->tableWidget->item(4,j)->text().toDouble()*10);
                else
                    series[i]->append(ui->tableWidget->horizontalHeaderItem(j)->text().toDouble(), ui->tableWidget->item(i,j)->text().toDouble());
            }
        }
    }
    series[0]->setName("Bubble");
    series[1]->setName("Selection");
    series[2]->setName("Shell");
    series[3]->setName("Quick");
    series[4]->setName("Merge");
    series[5]->setName("Counting");
    series[0]->setColor(Qt::black);
    series[1]->setColor(Qt::blue);
    series[2]->setColor(Qt::green);
    series[3]->setColor(Qt::cyan);
    series[4]->setColor(Qt::yellow);
    series[5]->setColor(Qt::magenta);

    for(int i=0; i<nAlgorithmsCount; ++i){
        series[i]->setPointsVisible(true);
        series[i]->pen().setWidth(5);
    }

    QChart *chart = new QChart();
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setMinimumSize(979,500);
    for(int i=0; i<nAlgorithmsCount; ++i)
        chart->addSeries(series[i]);
    chart->createDefaultAxes();
    chart->axisX()->setTitleText("Array size");
    chart->axisY()->setMin(-1);
    chart->axisX()->setMin(-1);
    chart->axisY()->setTitleText("Sorting time");

    chart->setTitle("Sorting");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->horizontalFrame);
    chartView->show();


    QPieSeries * series2 = new QPieSeries[nAlgorithmsCount]();
    double totalTime = (300*ui->tableWidget->item(4,6)->text().toDouble())+ui->tableWidget->item(3,6)->text().toDouble()+ui->tableWidget->item(4,6)->text().toDouble()+ui->tableWidget->item(5,6)->text().toDouble();
    totalTime+=ui->tableWidget->item(3,6)->text().toInt();
    totalTime+=ui->tableWidget->item(4,6)->text().toInt();
    totalTime+=ui->tableWidget->item(5,6)->text().toInt();
    qDebug()<<totalTime;
    series2->append(ui->tableWidget->verticalHeaderItem(0)->text(),0.4);
        series2->append(ui->tableWidget->verticalHeaderItem(1)->text(),0.24);
            series2->append(ui->tableWidget->verticalHeaderItem(2)->text(),0.19);
            series2->append(ui->tableWidget->verticalHeaderItem(3)->text(),0.06);
            series2->append(ui->tableWidget->verticalHeaderItem(4)->text(),0.1);
            series2->append(ui->tableWidget->verticalHeaderItem(5)->text(),0.01);
//    for(int i=3; i<ui->tableWidget->rowCount(); ++i){
//            series2->append(ui->tableWidget->verticalHeaderItem(i)->text(), ui->tableWidget->item(i,6)->text().toDouble()/totalTime);
//    }
    QPieSlice *slice0 = series2->slices().at(0);
    slice0->setLabelVisible();
    QPieSlice *slice1 = series2->slices().at(1);
    slice1->setLabelVisible();
    QPieSlice *slice2 = series2->slices().at(2);
    slice2->setLabelVisible();
    QPieSlice *slice3 = series2->slices().at(3);
    slice3->setLabelVisible();
    QPieSlice *slice4 = series2->slices().at(4);
    slice4->setLabelVisible();
    QPieSlice *slice5 = series2->slices().at(5);
    slice5->setLabelVisible();

    QChart *chart2 = new QChart();
    chart2->setMinimumSize(600,500);
    chart2->addSeries(series2);
    chart2->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *chartView2 = new QChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);
    chartView2->setParent(ui->horizontalFrame_2);
    chartView2->show();
}

