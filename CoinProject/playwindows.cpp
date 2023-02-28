#include "playwindows.h"
#include <QMenuBar>
#include <QPainter>
#include <mybutton.h>
#include <QLabel>
#include "gamecoin.h"
#include "dataconfig.h"
#include <QTimer>
#include <QPropertyAnimation>

PlayWindows::PlayWindows(QWidget *parent)
    : QMainWindow{parent}
{

}
//??windows????
PlayWindows::PlayWindows(int index){
    //preper win laber
    winlaber=new QLabel;
    QPixmap tmpPix(":/res/LevelCompletedDialogBg.png");
    winlaber->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winlaber->setPixmap(tmpPix);
    winlaber->setParent(this);
    winlaber->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());


    this->levelcode=index;
    this->setFixedSize(390,570);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("???");
    QMenuBar *bar=this->menuBar();
    this->setMenuBar(bar);
    QMenu *startMenu=bar->addMenu("??");
    QAction *quitAction=startMenu->addAction("??");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //??????
    MyButton *btnback=new MyButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    btnback->setParent(this);
    btnback->move(this->width()-btnback->width(),this->height()-btnback->height());
    connect(btnback,&QPushButton::clicked,this,[=](){
        this->hide();
        emit this->back();//??????
    });
    //????
    QLabel *label=new QLabel(this);
    QFont font;
    font.setFamily("????");
    font.setPointSize(20);
    label->setFont(font);
    QString str=QString("level:%1").arg(this->levelcode);
    label->setText(str);
    label->setGeometry(QRect(30,this->height()-50,120,50));
    //data set
    dataConfig config;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            gameArr[i][j]=config.mData[this->levelcode][i][j];
        }
    }
    //?????
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            QLabel *lab=new QLabel;
            lab->setGeometry(0,0,50,50);
            lab->setPixmap(QPixmap(":/res/BoardNode.png"));
            lab->setParent(this);
            lab->move(57+i*50,200+j*50);
            //coin set
            QString img;
            if(gameArr[i][j]==1){
                img=":/res/Coin0001.png";
            }
            else img=":/res/Coin0008.png";
            GameCoin *coin=new GameCoin(img);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            coin->posX=i;
            coin->posY=j;
            coin->flag=gameArr[i][j];
            coinmap[i][j]=coin;
            connect(coin,&QPushButton::clicked,[=](){
                coin->changeFlag();
                gameArr[i][j]=gameArr[i][j]==0?1:0;
                //change neber coin;
                QTimer::singleShot(300,this,[=](){
                    if(coin->posX+1<=3){
                        coinmap[coin->posX+1][coin->posY]->changeFlag();
                        gameArr[coin->posX+1][coin->posY]=gameArr[coin->posX+1][coin->posY]==0?1:0;
                    }
                    if(coin->posX-1>=0){
                        coinmap[coin->posX-1][coin->posY]->changeFlag();
                        gameArr[coin->posX-1][coin->posY]=gameArr[coin->posX-1][coin->posY]==0?1:0;
                    }
                    if(coin->posY+1<=3){
                        coinmap[coin->posX][coin->posY+1]->changeFlag();
                        gameArr[coin->posX][coin->posY+1]=gameArr[coin->posX][coin->posY+1]==0?1:0;
                    }
                    if(coin->posY-1>=0){
                        coinmap[coin->posX][coin->posY-1]->changeFlag();
                        gameArr[coin->posX][coin->posY-1]=gameArr[coin->posX][coin->posY-1]==0?1:0;
                    }
                    //win check
                    this->isWin=true;
                    for(int i=0;i<4;i++){
                        for(int j=0;j<4;j++){
                            if(coinmap[i][j]->flag==false){
                                this->isWin=false;
                                break;
                            }
                        }
                    }

                    //win annimation
                    if(this->isWin)
                    {
                        qDebug()<<"WIN!";
                        QPropertyAnimation *annimation1=new QPropertyAnimation(winlaber,"geometry");
                        annimation1->setDuration(1000);
                        annimation1->setStartValue(QRect(winlaber->x(),winlaber->y(),winlaber->width(),winlaber->height()));
                        annimation1->setEndValue(QRect(winlaber->x(),winlaber->y()+114,winlaber->width(),winlaber->height()));
                        annimation1->setEasingCurve(QEasingCurve::OutBounce);
                        annimation1->start();
                        //ban all click
                        for(int i=0;i<4;i++){
                            for(int j=0;j<4;j++){
                                coinmap[i][j]->isWin=true;
                            }
                        }
                    }
                });
            });
        }
    }
    //data set
}

void PlayWindows::paintEvent(QPaintEvent *event){
    QPainter p(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    p.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    p.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
