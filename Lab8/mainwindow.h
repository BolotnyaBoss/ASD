#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QFileDialog>
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

    QString printStep(int array[], int size, int index);

    void linearSearch(int changed_arr_1[],QString* log);

private:
    Ui::MainWindow *ui;
    int *arr;
    int size;
    int numOfComparisons;
    int numOfNulls;
    int sum;
};
#endif // MAINWINDOW_H
