#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>


class CustomWidget : public QWidget
{
    Q_OBJECT
public:

    CustomWidget(QWidget *parent = nullptr);
//    void paintEvent(QPaintEvent *);
//    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    virtual ~CustomWidget() {}
};

#endif // CUSTOMWIDGET_H
