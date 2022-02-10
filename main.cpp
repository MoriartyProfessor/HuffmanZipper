#include "mainwindow.h"
#include <heap.cpp>
#include <node.h>
#include <QApplication>
#include <QFileDialog>
#include <Functions.h>
#include <huffmantree.h>
#include <cstdlib>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
