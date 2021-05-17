#include "mainwindow.h"
#include "top.h"
#include "edge.h"
#include <QApplication>
#include <QLineEdit>
QString status="none";
int len=0;
int mem_x;
int mem_y;
int mem_num;
QVector <TOP> graph1;
QVector <EDGE> graph2;
QVector <QVector<int>> matrix;
QString statusBook[]={"top","edge1.1","edge2.1","move","del","none"};
QString text_for_arrows;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
