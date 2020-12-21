#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void CreateTable();
    ~MainWindow();

private slots:
    void on_pushButton_generate_clicked();

    void on_pushButton_sort_clicked();

    void on_pushButton_showDiagram_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
