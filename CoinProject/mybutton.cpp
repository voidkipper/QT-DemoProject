#include "mybutton.h"
#include<QPropertyAnimation>
#include<QDebug>

MyButton::MyButton(QWidget *parent)
    : QPushButton{parent}//?????????
{

}

MyButton::MyButton(QString normalimg, QString pressimg){
    normalPath=normalimg;
    pressPath=pressimg;
    QPixmap pix;
    pix.load(normalimg);
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
}

void MyButton::zoom1(){
    QPropertyAnimation *an=new QPropertyAnimation(this,"geometry");
    an->setDuration(50);
    an->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    an->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    an->setEasingCurve(QEasingCurve::OutBounce);
    an->start();
}

void MyButton::zoom2(){
    QPropertyAnimation *an=new QPropertyAnimation(this,"geometry");
    an->setDuration(50);
    an->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    an->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    an->setEasingCurve(QEasingCurve::OutBounce);
    an->start();
}

//??????
void MyButton::mousePressEvent(QMouseEvent *e){
    if(pressPath!=""){
        QPixmap pix(pressPath);
        //? this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mousePressEvent(e);
}

void MyButton::mouseReleaseEvent(QMouseEvent *e){
    if(normalPath!=""){
        QPixmap pix(normalPath);
        //? this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}

