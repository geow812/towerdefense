#include "defenses.h"

Defenses::Defenses()
{ 
    rayonAction = 120;
    focus = 0;
    focusNumber = -1;
    niveau = 1;
    nbProjectiles = 0;
    type = 0;
    projectile = new Projectiles*[20];


}

QRectF Defenses::boundingRect() const{
   return QRect (-15,-15,30,30);
}

void Defenses::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   painter->drawPixmap(-15, -15, *pixmap);
}

PistoletAEauDefenses::PistoletAEauDefenses() : Defenses(){
    typeName = "Pistolet A Eau";

    type = 1;
    pixmap = new QPixmap(":/images/blue_monster.png");
    *pixmap=pixmap->scaled(30,30,Qt::KeepAspectRatio);
    niveau = 1;
    rayonAction = 60 + (niveau/2.0)*30.0;
    degat = ( 5 * (pow(niveau,1.5)) );
    coutDeBase = 8;
    coutUnVersDeux = 20;
    coutDeuxVersTrois = 45;
    cadence = 4;
}

LancePierreDefenses::LancePierreDefenses() : Defenses(){
    typeName = "Lance Pierre";

    pixmap = new QPixmap(":/images/yellow_monster.png");
    *pixmap=pixmap->scaled(30,30,Qt::KeepAspectRatio);
    type = 2;
    niveau = 1;
    rayonAction = 90 + (niveau/2.0)*30.0;
    degat = ( 10 * (pow(niveau,1.5)) );
    coutDeBase = 12;
    coutUnVersDeux = 25;
    coutDeuxVersTrois = 60;
    cadence = 1;
}


PaintBallDefenses::PaintBallDefenses(){
    typeName = "Paint-ball";
    type=3;
    pixmap = new QPixmap(":/images/green_monster.png");
    *pixmap=pixmap->scaled(30,30,Qt::KeepAspectRatio);
    niveau = 1;
    rayonAction = 120 + (niveau/2.0)*30.0;
    degat = ( 4 * (pow(niveau,1.5)) );
    coutDeBase = 12;
    coutUnVersDeux = 25;
    coutDeuxVersTrois = 60;
    cadence = 2;
}

PetanqueDefenses :: PetanqueDefenses()  {
    typeName = "Joueuer de pétanque";
    type=4;
    pixmap = new QPixmap(":/images/red_monster.png");
    *pixmap=pixmap->scaled(30,30,Qt::KeepAspectRatio);
    niveau = 1;
    rayonAction = 120 + (niveau/2.0)*30.0;
    degat = ( 4 * (pow(niveau,1.5)) );
    coutDeBase = 15;
    coutUnVersDeux = 40;
    coutDeuxVersTrois = 80;
    cadence = 2;
}

