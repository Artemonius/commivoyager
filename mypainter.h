#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>

class myPainter
{
public:
    myPainter();
public:
    void draw(QPainter *painter, QPaintEvent *event);
    void draw_edge(int x1,int y1,int x2,int y2, int type,QPainter *painter,QString text);
    void draw_top(int x,int y,QString text,QPainter *painter );
    QBrush front;
private:
    QBrush back;
    QFont glFont;
    QPen textPen;
};

#endif //MYPAINTER_H
