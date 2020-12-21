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
{
    text = ui->textEdit->toPlainText();
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
QVector<int> prefixFunction(QString pattern)
{
    int sz = pattern.length();
    QVector<int> prefix(sz);

    for (int i = 1; i < sz; ++i) {
        int j = prefix[i - 1];
        while (j > 0 && pattern[i] != pattern[j]){
            j = prefix[j - 1];
        }
        if (pattern[i] == pattern[j]){
            ++j;
        }
        prefix[i] = j;
    }

    return prefix;
}
void MainWindow::on_pushButton_4_clicked()// search
{
    QString output = "";

    textToFind = ui->line->text();
    if(textToFind[0] == '?' || textToFind[textToFind.size()-1] == '?'){
        QMessageBox msgBox;
                       msgBox.setIcon(QMessageBox::Warning);
                       msgBox.setText("sign '?' cant be in begin or in end the word");
                       msgBox.exec();
                       return;
    }
    auto prefix = prefixFunction(textToFind);
    output += "Prefix function table :\n";
    for(int p:prefix)
        output += QString::number(p)+" ";
    output += "\n";
     int size2 = text.length();
     int size1 = textToFind.length();
     //int k = 0;
     std::list<QString> l;
     int i = 0, j = 0;
     while(i < size2){
             if(j > 0 && ((textToFind[j] != text[i]) && (textToFind[j] != '?'))){

                 i -= prefix[j];
                 j = 0;
             }
             if(textToFind[j] == '?')
             {
                 j++;
             }
             if(textToFind[j] == text[i]){
                 j++;
             }
             if(!j) output += printStep(text,i,i);
             if(j == size1){
                 output += printStep(text,i-j+1,i);
                 output += "Word was found in position:"+QString::number(i - j + 1)+"\n";
                 l.push_back(QString::number(i - j + 1));
                 j = 0;
             }

             i++;
     }
     /*for (int i = 0; i <= size2-1; i++) {
         int j;
         for (j = 0; j < size1; j++) {

             if (text[i + j] != textToFind[j]) {
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
     }*/
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
