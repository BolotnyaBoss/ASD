#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QFileDialog>
#include <QVector>
#include <QTextStream>
#include <QTableWidgetItem>
#include <chrono>
#include <cmath>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_count_valueChanged(int arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    QString printArray(int array[], int size);

    QString printArray1(int array[], int a, int b);

    QString printStep(int array[], int size, int index);

    QString MainWindow::printDivideby5(int array[], int size);

    void binarySearch(int changed_arr_1[],QString* log);

private:
    Ui::MainWindow *ui;
    int *arr;
    int size;
    int ressize;
    int numOfComparisons;
    int numOfNulls;
};
#endif // MAINWINDOW_H
