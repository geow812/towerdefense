#ifndef WIDGET_H
#define WIDGET_H

#include <QApplication>
#include <QtGui/QWidget>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QFile>
#include <QGroupBox>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QProgressBar>
#include <QTextEdit>
#include <QMouseEvent>
#include "myscene.h"

class Myview : public QGraphicsView
{
    Q_OBJECT
public:
    Myview(Myscene *scene, QWidget *parent = 0);
    QPointF mousePoint;
    void mousePressEvent(QMouseEvent * mouseEvent )
    {
        mousePoint = mouseEvent->pos();
        emit mouseScenePress(mousePoint);
    }
signals:
    void mouseScenePress(QPointF);
public slots:

};


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();



private:
    Myscene* scene;
    QGraphicsView* view;
    QGridLayout *layout;

    //=====================bloc 1
    int etatBtn;
    QPushButton *btnLancer;
    QPushButton *btnArreter;
    QPushButton *btnQuitter ;
    QHBoxLayout *group1;

    //======================bloc 2
    QLabel* credit;
    QLCDNumber* nbCredit;
    QLabel* vie;
    QLCDNumber* nbVie;
    QGridLayout *box;
    QGroupBox* group2;

    //========================bloc 3
    QProgressBar* group3;


    //========================bloc 4
    QPushButton *btnEau;
    QPushButton *btnPierre;
    QPushButton *btnPaintBall;
    QPushButton *btnPetanque;
    QPushButton *btnMusicien;
    QGridLayout *layout3;
    QGroupBox* group4 ;

    //=========================bloc 5

    QLabel*typeTourLabel;
    QLabel*porteeTourLabel;
    QLabel*cadenceTourLabel;
    QLabel*degatsTourLabel;
    QLabel*coutTourLabel;

    QPushButton *btnAmeliorer;
    QPushButton *btnDetruire;
    QVBoxLayout *bloc4;
    QGroupBox* group5;
    //======================regrouper tous les blocs a droite
    QVBoxLayout *rightLayout;

signals:
    void gameover();

public slots:
    void vieLCD(int i){
        int vie=nbVie->intValue()-i;
        if (vie>0){
            nbVie->display(vie);}
        else emit gameover();
    }
    void creditLCD(int i){
        int credits=nbCredit->intValue()+i;
        if (credits>0){
            nbCredit->display(credits);}
        //else emit gameover();
    }

    void avanceProgressbar(int i){
        group3->setValue(i);;
    }

    void buttons(){
          if (etatBtn==0){
                btnLancer->setEnabled(false);
                btnArreter->setEnabled(true);
                etatBtn=1;}
          else{
                btnLancer->setEnabled(true);
                btnArreter->setEnabled(false);
                etatBtn=0;
           }
    }

};

#endif // WIDGET_H