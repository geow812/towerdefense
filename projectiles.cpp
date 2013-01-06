#include "projectiles.h"

#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>


void Projectiles::destroy(){
this->deleteLater();
};

Projectiles::Projectiles(QPointF point,int t):p(point),vitesse(t){

    setPos(p.x()-15,p.y()-15);
    setZValue(2);
    this->scale(0.10,0.10);
};

void Projectiles::launch(QPointF d){

    QParallelAnimationGroup *group=new QParallelAnimationGroup;
    QPropertyAnimation *anim1=new QPropertyAnimation(this, "pos");
    anim1->setDuration(200*vitesse);
    anim1->setStartValue(p);
    anim1->setEndValue(d);
    //anim1->setEasingCurve(QEasingCurve::OutBounce);
    anim1->start();
    group->addAnimation(anim1);
};

EauProjectiles::EauProjectiles(QPointF point,int t):Projectiles(point,t){
    QPixmap *bird=new QPixmap;
    bird->load(":/images/ball7.png");
    setPixmap(*bird);

};

PierreProjectiles::PierreProjectiles(QPointF point,int t):Projectiles(point,t){
    QPixmap *bird=new QPixmap;
    bird->load(":/images/ball8.png");
    setPixmap(*bird);

};


PaintBallProjectiles::PaintBallProjectiles(QPointF point,int t):Projectiles(point,t){
    QPixmap *bird=new QPixmap;
    bird->load(":/images/ball4.png");
    setPixmap(*bird);

};