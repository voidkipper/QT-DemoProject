#ifndef PLAYWINDOWS_H
#define PLAYWINDOWS_H

#include <QMainWindow>
#include "gamecoin.h"
#include <QLabel>

class PlayWindows : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayWindows(QWidget *parent = nullptr);
    PlayWindows(int index);
    int levelcode;
    void paintEvent(QPaintEvent *event);
    int gameArr[4][4];
    GameCoin *coinmap[4][4];
    bool isWin=true;
    QLabel* winlaber;
signals:
    void back();
};

#endif // PLAYWINDOWS_H
