#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include"mybutton.h"
#include"choosewindow.h"
#include<QTimer>
#include<QtMultimedia/QSoundEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(390,570);
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    setWindowTitle("Test Programe");
    connect(ui->actionQuit,&QAction::triggered,[=](){
       this->close();
    });
    MyButton *StartBTN=new MyButton(":/res/MenuSceneStartButton.png");
    StartBTN->setParent(this);
    StartBTN->move(this->width()*0.5-StartBTN->width()*0.5,this->height()*0.7);

    choose=new chooseWindow();
    connect(StartBTN,&QPushButton::clicked,this,[=](){
        StartBTN->zoom1();
        StartBTN->zoom2();
        //Sound
        QSoundEffect *strat=new QSoundEffect(this);
        strat->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
        strat->setLoopCount(1);
        strat->setVolume(0.25f);
        strat->play();
        QTimer::singleShot(500,this,[=](){
            this->hide();
            choose->setGeometry(this->geometry());
            choose->show();
        });
    });
    //????
    connect(choose,&chooseWindow::Backmain,[=](){
        choose->hide();
        this->show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPixmap pix(":/res/PlayLevelSceneBg.png");
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    p.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
