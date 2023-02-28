#ifndef GAMECOIN_H
#define GAMECOIN_H

#include <QWidget>
#include <QPushButton>

class GameCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit GameCoin(QWidget *parent = nullptr);
   GameCoin(QString butImg);
   int posX;
   int posY;
   bool flag;
   bool isWin;
   void changeFlag();
   QTimer *timer1;
   QTimer *timer2;
   int min;
   int max;
   bool isAnimation;
   void mousePressEvent(QMouseEvent *e);
signals:

};

#endif // GAMECOIN_H
