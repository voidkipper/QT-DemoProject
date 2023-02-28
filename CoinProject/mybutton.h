#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = nullptr);
    MyButton(QString normalimg,QString pressimg="");
    QString normalPath;
    QString pressPath;
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void zoom1();
    void zoom2();
signals:

};

#endif // MYBUTTON_H
