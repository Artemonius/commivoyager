#include "mypainter.h"
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <QtCore/qmath.h>
#include "top.h"
#include "edge.h"
double pi=3.1415;
double angle=pi/8;//угол раствора стрелки
int ls=30;        //длина кончика стрелки
myPainter::myPainter()
{
    front=QBrush(QColor(255,193,199));
    back=QBrush(QColor(200,200,200));
    textPen=QPen(QColor(33,33,33));
    glFont.setPixelSize(30);
}
void myPainter::draw_top(int x, int y, QString text,QPainter *painter)
{
    int c1=x-20;
    int c2=y-15;
    int c3=40;
    int c4=30;
    painter->drawEllipse(QRectF(x-40,y-40,80,80));
    painter->drawText(QRect(c1,c2,c3,c4),Qt::AlignCenter,text);
}
void myPainter::draw_edge(int x1, int y1, int x2, int y2, int type,QPainter *painter,QString text)
{
    double l=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    int xl1=(x2-x1)/l*40+x1;
    int yl1=(y2-y1)/l*40+y1;
    int xl2=x2-(x2-x1)/l*40;
    int yl2=y2-(y2-y1)/l*40;
    painter->drawLine(xl1,yl1,xl2,yl2);
    if (type==1)
    {
        double b;
        if      (x2==xl2 && yl2<y2) b=pi*3/2;
        else if (y2==yl2 && xl2<x2) b=pi;
        else if (x2==xl2 && yl2>y2) b=pi/2;
        else if (y2==yl2 && xl2>x2) b=0;
        else if (xl2>x2 && yl2<y2)  b=2*pi+atan(1.0*(y2-yl2)/(x2-xl2));
        else if (xl2<x2 && yl2<y2)  b=atan(1.0*(y2-yl2)/(x2-xl2))+pi;
        else if (xl2<x2 && yl2>y2)  b=atan(1.0*(y2-yl2)/(x2-xl2))+pi;
        else if (xl2>x2 && yl2>y2)  b=atan(1.0*(y2-yl2)/(x2-xl2));
        int xs1=cos(b+angle)*ls+xl2;
        int ys1=sin(b+angle)*ls+yl2;
        int xs2=cos(b-angle)*ls+xl2;
        int ys2=sin(b-angle)*ls+yl2;
        painter->drawLine(xl2,yl2,xs1,ys1);
        painter->drawLine(xl2,yl2,xs2,ys2);
    }
    //текст
    int c1=(xl2+xl1)/2-20;
    int c2=(yl2+yl1)/2-15;
    int c3=40;
    int c4=30;
    painter->drawText(QRect(c1,c2,c3,c4),Qt::AlignCenter,text);
}
void myPainter::draw(QPainter *painter, QPaintEvent *event)
{
    painter->fillRect(event->rect(),back);
    painter->setBrush(front);
    painter->setPen(textPen);
    painter->setFont(glFont);
    textPen.setWidth(4);
    extern QVector<TOP> graph1;
    extern QVector<EDGE> graph2;
    for (int i=0;i<graph1.size();i++)
    {
        draw_top(graph1[i].x,
                 graph1[i].y,
                 QString::number(i),
                 painter);
    }
    for (int i=0;i<graph2.size();i++)
    {
        draw_edge(graph2[i].x1,
                  graph2[i].y1,
                  graph2[i].x2,
                  graph2[i].y2,
                  graph2[i].type,
                  painter,
                  QString::number(graph2[i].mass));
    }
}

