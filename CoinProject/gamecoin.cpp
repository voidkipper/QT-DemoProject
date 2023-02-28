#include "gamecoin.h"
#include <QTimer>

GameCoin::GameCoin(QWidget *parent)
    : QPushButton{parent}
{

}

GameCoin::GameCoin(QString butImg){
    max=8;
    min=1;
    isAnimation=false;
    QPixmap pix(butImg);
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    timer1=new QTimer(this);
    timer2=new QTimer(this);
    //suveilance timer1sing
    connect(timer1,&QTimer::timeout,[=](){
       QPixmap pix;
       QString str=QString(":/res/Coin000%1.png").arg(this->min++);
       pix.load(str);
       this->setFixedSize(pix.width(),pix.height());
       setStyleSheet("QPushButton{border:0px;}");
       setIcon(pix);
       setIconSize(QSize(pix.width(),pix.height()));
       if(this->min>this->max){
           this->min=1;
           timer1->stop();
           //stop an;
           this->isAnimation=false;
       }
    });
    connect(timer2,&QTimer::timeout,[=](){
       QPixmap pix;
       QString str=QString(":/res/Coin000%1.png").arg(this->max--);
       pix.load(str);
       this->setFixedSize(pix.width(),pix.height());
       setStyleSheet("QPushButton{border:0px;}");
       setIcon(pix);
       setIconSize(QSize(pix.width(),pix.height()));
       if(this->max<this->min){
           this->max=8;
           timer2->stop();
           this->isAnimation=false;
       }
    });
}
//time shot annima
void GameCoin::changeFlag()
{
    if(this->flag){
        timer1->start(30);
        this->isAnimation=true;
        this->flag=false;
    }
    else{
        timer2->start(30);
        this->isAnimation=true;
        this->flag=true;
    }

}
//mouser PressEevnt
void GameCoin::mousePressEvent(QMouseEvent *e){
    if(this->isAnimation||isWin==true){return;}
    else return QPushButton::mousePressEvent(e);
}
