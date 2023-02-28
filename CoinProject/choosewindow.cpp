#include "choosewindow.h"
#include<QMenuBar>
#include<QMenu>
#include<QPainter>
#include"mybutton.h"
#include<QTimer>
#include<QLabel>

chooseWindow::chooseWindow(QWidget *parent)
    : QMainWindow{parent}
{
    this->setFixedSize(390,570);
    this->setWindowIcon(QIcon(QPixmap(":/res/Coin0001.png")));
    this->setWindowTitle("????");

    QMenuBar *Bar=new QMenuBar(this);
    this->setMenuBar(Bar);
    QMenu *start=Bar->addMenu("Star");
    QAction *quiteAction=start->addAction("Quit");
    connect(quiteAction,&QAction::triggered,[=](){
        this->close();
    });
    //B
    reBtn=new MyButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    reBtn->setParent(this);
    reBtn->move(this->width()-reBtn->width(),this->height()-reBtn->height());
    //??
    connect(reBtn,&QPushButton::clicked,this,[=](){
        QTimer::singleShot(500,this,[=](){
            this->hide();
            emit this->Backmain();
        });
    });
    //??
    for(int i=0;i<20;i++){
        MyButton *level=new MyButton(":/res/LevelIcon.png");

        level->setParent(this);
        level->move(25+(i%4)*70,130+(i/4)*70);
        //????
        QLabel *lab=new QLabel();
        lab->setParent(this);
        lab->setFixedSize(level->width(),level->height());
        lab->setText(QString::number(i+1));
        lab->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);
        lab->move(25+(i%4)*70,130+(i/4)*70);
        lab->setAttribute(Qt::WA_TransparentForMouseEvents,true);
        //×¢ÊÍÂÒÂë
        connect(level,&QPushButton::clicked,this,[=](){
            this->hide();
            if(playlevel==NULL){
                this->hide();
                playlevel=new PlayWindows(i+1);
                playlevel->setGeometry(this->geometry());
                playlevel->show();        //????????
                connect(playlevel,&PlayWindows::back,this,[=](){
                    this->show();
                    delete playlevel;
                    playlevel=NULL;
                });
            }
        });

    }

}

void chooseWindow::paintEvent(QPaintEvent *event){
    QPainter P(this);
    QPixmap pix(":/res/OtherSceneBg.png");
    P.drawPixmap(0,0,pix);
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    P.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
