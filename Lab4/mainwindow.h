#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QTableWidget>
//#include "mergesort.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static void FillTable(QTableWidget* table, const std::vector<std::vector<double>> &matr);
    int N;
    int M;
private:
    void mergeSort(std::vector<std::vector<double>> array, int l, int r);

    void merge(std::vector<std::vector<double>> array, int l, int m, int r);
    Ui::MainWindow *ui;
    std::vector<std::vector<double>> matrix;

private slots:
    void on_setMatrixSizePushButton_clicked();

    void on_fillRandomPushButton_clicked();

    void on_sortPushButton_clicked();

    void on_exitButton_clicked();

    void on_fillButton_clicked();



};

#endif // MAINWINDOW_H
