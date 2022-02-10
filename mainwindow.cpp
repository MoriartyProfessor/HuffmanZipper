#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qfiledialog.h>
#include <Functions.h>

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


void MainWindow::on_pushButton_clicked()
{
    QString fileName;
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    fileName=dialog.getOpenFileName();
    std::string str="";
    str=fileName.toStdString();
    if(str!="")
        encodeFile(str);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
        tr("Decode"), "D:/", tr("Huffman Zipped Files (*.hzip)"));
    std::string str="";
    str=fileName.toStdString();
    if(str!="")
        decodeFile(str);
}
