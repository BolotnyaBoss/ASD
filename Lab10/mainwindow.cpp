#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{// click on enter(change text)
 QStringList list = text.split(QRegExp("\n"), QString::SkipEmptyParts);
 QString temp1 = list[ui->i_number->text().toInt()-1];
 list[ui->i_number->text().toInt()-1] = list[ui->n_number->text().toInt()-2];
 list[ui->n_number->text().toInt()-2] = temp1;
 text = list.join("\n");
 ui->textEdit->clear();
 ui->textEdit->setText(text);
}

QString printStep(QString text, int a, int b){
    QString res = "";
    if(a == b){
        for(int i = 0; i < text.size(); i++)
        {
            if(i == a) res += "|" + text[i] + "|";
            else  res += text[i] ;

        }}
    else{
    for(int i = 0; i < text.size(); i++)
    {
        if(i == a) res += "|" + text[i];
        else if (i == b) res += text[i] + "|";
        else  res += text[i] ;

    }}
    res+="\n";
    return res;
}
void MainWindow::on_pushButton_4_clicked()// search
{
    QString output = "";
    QString word = ui->line->text();
     int size2 = text.length();
     int size1 = word.length();
     //int k = 0;
     std::list<QString> l;
     for (int i = 0; i <= size2-1; i++) {
         int j;
         for (j = 0; j < size1; j++) {

             if (text[i + j] != word[j]) {
                 output += printStep(text,i,i);
                 break;
             }
             output += printStep(text,i,i+j);
         }
         if (j == size1) {
             output += "Word was found in position:"+QString::number(i)+"\n";
             //output += "Step:"+QString::number(k)+"\n";
             // output += printStep(text,i,i+size1);
             l.push_back(QString::number(i));
         }
     }
     if(l.empty()){
         QMessageBox msgBox;
                        msgBox.setIcon(QMessageBox::Information);
                        msgBox.setText("Not found entered substring");
                        msgBox.exec();
                        return;
        }
     QString str = output;
     str += "\nIndexes entering the substrate:\n";
     int lsize = l.size();
     for(int i = 0; i < lsize; ++i){
        str+= l.front() +" ";
        l.pop_front();
     }
     ui->BS->setText(str);

}

void MainWindow::on_pushButton_5_clicked()
{ // click on exit
    close();
}

void MainWindow::on_pushButton_clicked()//read from file
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open some file");
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
       {
        QMessageBox msgBox;
                       msgBox.setIcon(QMessageBox::Critical);
                       msgBox.setText("Cannot read from file");
                       msgBox.exec();
                       return;
       }
    QTextStream in(&file);
    text = in.readAll();
            ui->textEdit->setText(text);
}
