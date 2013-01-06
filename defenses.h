#ifndef DEFENSES_H
#define DEFENSES_H
#include "ennemis.h"
#include "projectiles.h"

class Defenses : public QGraphicsItem
{
public:
    Defenses();
    QPixmap *pixmap;
    Ennemis *focus;
    int focusNumber;
    float rayonAction;
    Projectiles **projectile;
    int nbProjectiles;
    int type;
    int niveau;
    float degat;
    int coutDeBase;
    int coutUnVersDeux;
    int coutDeuxVersTrois;
    int cadence;
    QPointF position;
    virtual void setniveau(int n) {niveau=n;}

    QString typeName;

public slots :

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class PistoletAEauDefenses : public Defenses
{
public :
    PistoletAEauDefenses();

};

class LancePierreDefenses : public Defenses{
public :
    LancePierreDefenses();

};

class PaintBallDefenses : public Defenses//paintBall
{
public :
    PaintBallDefenses();

};

class PetanqueDefenses : public Defenses//paintBall
{
public :
    PetanqueDefenses();

};


#endif // Defenses_H