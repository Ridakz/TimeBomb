#include "customwidget.h"
#include <QMouseEvent>
#include <QDebug>

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{

}

void CustomWidget::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << "mouse : " << event->pos().x()  << " " << event->pos().y() ;
}

