#ifndef PROJECTILES_H
#define PROJECTILES_H
#include "ennemis.h"

class Projectiles : public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
  Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    QPointF p;
    int vitesse;
    Projectiles(QPointF p,int);
    virtual void launch(QPointF d);
    int target;
public slots:
    virtual void destroy();
};

class EauProjectiles:public Projectiles{
public:
    EauProjectiles(QPointF p,int);

};

class PierreProjectiles:public Projectiles{
public:
    PierreProjectiles(QPointF p,int);

};

class PaintBallProjectiles:public Projectiles{
public:
    PaintBallProjectiles(QPointF p,int);

};


#endif // PROJECTILES_H


