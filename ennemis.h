#ifndef ENNEMIS_H
#define ENNEMIS_H
#include <QSound>
#include <QLabel>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QtGui>
#include <QFile>
#include <QGraphicsView>
#include <math.h>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QStyleOption>
#include <QStringList>
#include <QList>
#include <QStyleOption>
#include <QWidget>
#include <QDebug>
#include <QTimer>


class Ennemis : public QObject, public QGraphicsItem
{
  Q_OBJECT

public:
    Ennemis();
    Ennemis(float,int,float,int,int);
    float taille;
    int mode;//mode de deplacement 0 rampant 1 volant 2 rampant et volant
    float vitesse;//case par seconde
    int hp;//vitalit¨Ĥ
    int resist;//resistance aux attaques

    QPixmap *pixmap;
    int casePrecedente;
    int img;
    QStringList way;
    void setway(QStringList *l);
    bool ralentir;


protected:
      QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QPixmap changeimage(int)=0;
public slots:
    virtual void advance(int);
    virtual void resetvitesse();
    virtual void smallvitesse();

};

class Cafards : public Ennemis{

      Q_OBJECT
public:
    Cafards(float);

protected:
    QPixmap changeimage(int);
public slots:
};


class Fourmis : public Ennemis       
{
      Q_OBJECT
public:
    bool acc;
    Fourmis(float);

protected:
   QPixmap changeimage(int);
public slots:
   void accelerer();

};



class Guepes : public Ennemis
{
      Q_OBJECT
public:
    Guepes(float);
    void die();
protected:
    QPixmap changeimage(int);

};


class Moustiques : public Ennemis
{
      Q_OBJECT
public:
    bool modevol;
    bool sol;
    Moustiques(float);
    void changemode();
    void cachersol();
    void moustiquestouche();
protected:
    QPixmap changeimage(int);

};

#endif // ENNEMIS_H