#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    srand(time(0));

}

MainWindow::~MainWindow()
{
    delete ui;
}
QString ArrToStr(const std::vector<std::vector<double>> &arr)
{
    QString res;

    for(int i = 0; (double)i < arr[0].size(); ++i)
    {
        for(int j = 0; (double)j < arr.size(); ++j)
        {
            res += QString::number(arr[j][i]) + " ";
        }
        res.chop(1);
        res += '\n';
    }

    return res;
}
void MainWindow::FillTable(QTableWidget* table, const std::vector<std::vector<double>> &matr)
{
    int rows = matr[0].size();
    int  cols= matr.size();

    table->clear();

    table->setRowCount(rows);
    table->setColumnCount(cols);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            table->setItem(i, j, new QTableWidgetItem(QString::number(matr[j][i])));
        }
    }
}

void MainWindow::on_setMatrixSizePushButton_clicked()
{

    int rows = ui->rowsCountSpinBox->value();
    int cols = ui->colsCountSpinBox->value();

    matrix.resize(rows);

    for (int i = 0; i < rows; ++i)
    {
        matrix[i].resize(cols, 0.0);
    }

    FillTable(ui->startMatrixTableWidget, matrix);
    N = ui->rowsCountSpinBox->value();
    M = ui->colsCountSpinBox->value();
}

void MainWindow::on_fillRandomPushButton_clicked()
{
    if(matrix.size() == 0)
    {
        return;
    }

    const int rows = matrix.size();
    const int cols = matrix[0].size();
    const int maxAbs = 100;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            matrix[i][j] = (rand() % ((maxAbs + 1) * 100));
        }
    }

    FillTable(ui->startMatrixTableWidget, matrix);
}



void MainWindow::on_exitButton_clicked()
{
    close();
}

void MainWindow::on_fillButton_clicked()
{
    if(matrix.size() == 0)
    {
        return;
    }

    const int rows = matrix.size();
    const int cols = matrix[0].size();

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            QTableWidgetItem *item1(ui->startMatrixTableWidget->item(i,j));
            matrix[i][j] = ui->startMatrixTableWidget->item(i, j)->text().toDouble();;
        }
    }

    FillTable(ui->startMatrixTableWidget, matrix);
}
std::vector<std::vector<double>> merge(std::vector<std::vector<double>> left, std::vector<std::vector<double>> right,QTextBrowser* info)
{
    const int n = left.size();
    const int m = right.size();
    int i = 0;
    int j = 0;
    int iter = 0;

    info->append("Left Part:");
    info->append(ArrToStr(left));
    info->append("Right Part:");
    info->append(ArrToStr(right));

    std::vector<std::vector<double>> answer(n + m);

    while (i < n && j < m)
    {
        double lsum = 0.0, rsum = 0.0;
        for(int s = 0; s < n; s++)
        {
           lsum += left[i][s];
        }
        for(int s = 0; s < m; s++)
        {
        rsum += right[j][s];
        }

                if(lsum < rsum) answer[iter++] = left[i++];
        else    answer[iter++] = right[j++];
    }
    while (i < n)   answer[iter++] = left[i++];
    while (j < m)   answer[iter++] = right[j++];

    info->append("Merged:");
    info->append(ArrToStr(answer));

    return answer;
}
std::vector<std::vector<double>> mergesort(std::vector<std::vector<double>> arr, int left, int right,QTextBrowser* info)
{
    int length = right - left + 1;
    if (length < 2) return std::vector<std::vector<double>>(arr.begin() + left, arr.begin() + right + 1);

    const int middle = (right + left) / 2;

    return merge(mergesort(arr, left, middle,info), mergesort(arr, middle + 1, right,info),info);
}
void MainWindow::on_sortPushButton_clicked()
{
    const auto begin = std::chrono::high_resolution_clock::now();
    ui->infoTextBrowser->clear();
    ui->infoTextBrowser->append("Merge Sort:");
    ui->infoTextBrowser->append("");
    ui->infoTextBrowser->append("Initial Matrix:");
    ui->infoTextBrowser->append(ArrToStr(matrix));

    auto res = mergesort(matrix, 0, N-1,ui->infoTextBrowser);

    ui->infoTextBrowser->append("Result:");
    ui->infoTextBrowser->append(ArrToStr(res));

    FillTable(ui->resultMatrixTableWidget, res);
    auto end = std::chrono::high_resolution_clock::now() - begin;
    ui->time_1->setText(QString::number(std::chrono::duration<double, std::milli>(end).count()));
}
