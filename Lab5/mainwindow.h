#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QFileDialog>
#include <QTextStream>
#include <QTableWidgetItem>
#include <chrono>

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

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    QString printArray(double arr[], int size);

    int partition(double q[], int l, int r,QString* log, int k);

    void quickSort(double array[], int low, int high,QString* log,int k);

private:
    Ui::MainWindow *ui;
    double *arr;
    double *changed_arr_1;
    int size;
    int changed_size;
};
#endif // MAINWINDOW_H
