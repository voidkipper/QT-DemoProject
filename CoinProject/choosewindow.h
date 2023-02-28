#ifndef CHOOSEWINDOW_H
#define CHOOSEWINDOW_H
#include "mybutton.h"
#include <QMainWindow>
#include "playwindows.h"

class chooseWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooseWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    MyButton *reBtn;
    PlayWindows *playlevel=NULL;
signals:
    void Backmain();
};

#endif // CHOOSEWINDOW_H
