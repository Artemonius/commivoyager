#include "myglwidget.h"
#include "mypainter.h"
#include <QPainter>
#include <top.h>
#include <edge.h>
#include <QMouseEvent>
myGLWidget::myGLWidget(QWidget *parent)
    :QOpenGLWidget(parent)
{
    mypainter=new myPainter;
}
void myGLWidget::redraw()
{
    //mypainter->back.setColor((QColor(255,0,0)));
    this->update();
}
void myGLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    mypainter->draw(&painter,event);
    painter.end();
}
void myGLWidget::mousePressEvent(QMouseEvent *event)
{
    extern QVector<TOP> graph1;
    extern QVector<EDGE> graph2;
    extern QVector <QVector<int>> matrix;
    extern int len;
    extern int mem_x;
    extern int mem_y;
    extern int mem_num;
    extern QString status;
    extern QString text_for_arrows;
    int m=text_for_arrows.toInt();
    if (status=="top")
    {
        TOP a(event->x(),event->y());
        graph1.push_back(a);
        len++;
        //matrix
        QVector <int> row(len);
        row.fill(0);
        matrix.append(row);
        for (int i=0;i<len-1;i++) matrix[i].append(0);
    }
    else if (status=="edge1.1" || status=="edge2.1")
    {
        for (int i=0;i<len;i++)
        {
            int x1=event->x();
            int y1=event->y();
            int x2=graph1[i].x;
            int y2=graph1[i].y;
            if ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<1600)
            {
                mem_x=x2;
                mem_y=y2;
                mem_num=i;
                status=(status=="edge1.1")? "edge1.2":"edge2.2";
                break;
            }
        }
    }
    else if (status=="edge1.2" || status=="edge2.2")
    {
        for (int i=0;i<len;i++)
        {
            int x1=event->x();
            int y1=event->y();
            int x2=graph1[i].x;
            int y2=graph1[i].y;
            if ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<1600)
            {
                if (status=="edge1.2")
                {
                    EDGE a(mem_x,mem_y,x2,y2,1,m);
                    graph2.push_back(a);
                    //matrix
                    matrix[mem_num][i]=m;

                }
                else
                {
                    EDGE a(mem_x,mem_y,x2,y2,2,m);
                    graph2.push_back(a);
                    //matrix
                    matrix[mem_num][i]=m;
                    matrix[i][mem_num]=m;
                }
                status=(status=="edge1.2")? "edge1.1":"edge2.1";
                break;
            }
        }
    }
    else if (status=="move")
    {
        for (int i=0;i<len;i++)
        {
            int x1=event->x();
            int y1=event->y();
            int x2=graph1[i].x;
            int y2=graph1[i].y;
            if ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<1600)
            {
                graph1[i].mark=true;
                break;
            }
        }
    }
    else if (status=="del")
    {
        for (int i=0;i<len;i++)
        {
            int x1=event->x();
            int y1=event->y();
            int x2=graph1[i].x;
            int y2=graph1[i].y;
            if ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<1600)
            {
                QVector<EDGE> graph2_new;
                for (int j=0;j<graph2.size();j++)
                {
                    if (!(graph2[j].x1==graph1[i].x && graph2[j].y1==graph1[i].y)
                       && !(graph2[j].x2==graph1[i].x && graph2[j].y2==graph1[i].y))
                    {
                        graph2_new.push_back(graph2[j]);
                    }
                }
                graph2=graph2_new;
                graph1.erase(graph1.begin()+i);
                len--;
                //matrix
                for (int j=0;j<len;j++) matrix[j].erase(matrix[j].begin()+i);
                matrix.erase(matrix.begin()+i);
                break;
            }
        }
    }
    update();
}
void myGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    extern QVector<TOP> graph1;
    extern int len;
    extern QString status;
    if (status=="move") for (int i=0;i<len;i++) graph1[i].mark=false;
    update();
}
void myGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    extern QVector<TOP> graph1;
    extern QVector<EDGE> graph2;
    extern int len;
    extern QString status;
    if (status=="move")
    {
        for (int i=0;i<len;i++)
        {
            if (graph1[i].mark)
            {
                for (int j=0;j<graph2.size();j++)
                {
                    if (graph2[j].x1==graph1[i].x && graph2[j].y1==graph1[i].y)
                    {
                        graph2[j].x1=event->x();
                        graph2[j].y1=event->y();
                    }
                    if (graph2[j].x2==graph1[i].x && graph2[j].y2==graph1[i].y)
                    {
                        graph2[j].x2=event->x();
                        graph2[j].y2=event->y();
                    }
                }
                graph1[i].x=event->x();
                graph1[i].y=event->y();
                break;
            }
        }
    }
    update();
}
