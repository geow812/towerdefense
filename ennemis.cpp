#include "ennemis.h"
Ennemis::Ennemis(){
    taille = 1;
    ralentir = false;
};

Ennemis::Ennemis(float t,int m,float v,int vitalite,int resistance):taille(t),mode(m),vitesse(v),hp(vitalite),resist(resistance)
{
    ralentir = false;
};

QRectF Ennemis::boundingRect() const{
   return QRect (-30/2,-30/2,30,30);
}

void Ennemis::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QRectF r(boundingRect());
   painter->drawPixmap(-30/2,-15/2,*pixmap);
}

void Ennemis::setway(QStringList *l){
    way = QStringList(*l);
    img = 0;
}

void Ennemis::advance(int phase){
    if (!phase)
    return;
    img++;
    *pixmap = changeimage(img);
    QPointF a(this->scenePos());
    int b=(a.x()-15)/pixmap->width();
    int c=(a.y()-15)/pixmap->height();
    qreal m=c*16+b;
    if((way[m]=="18") && (QPoint(b*30+15,c*30+15)==this->scenePos())){
        casePrecedente=18;
        this->moveBy(0,1);
        return;
    }
    if((way[m]=="2") && (QPoint(b*30+15,c*30+15)==this->scenePos())){
        casePrecedente=2;
        this->moveBy(0,1);
        return;
    }
    if((way[m]=="6") && (QPoint(b*30+15,c*30+15)==this->scenePos())){
        casePrecedente=6;
        this->setRotation(270);
        this->moveBy(1,0);
    return;
}
if((way[m]=="4") && (QPoint(b*30+15,c*30+15)==this->scenePos())){
    casePrecedente=4;
    this->moveBy(1,0);
    return;
}
if((way[m]=="7") && (QPoint(b*30+15,c*30+15)==this->scenePos())){
    casePrecedente=7;
    this->setRotation(0);
    this->moveBy(0,1);
    return;
}
if((way[m]=="10") && (QPoint(b*30+15,c*30+15)==this->scenePos())){
    casePrecedente=10;
    this->setRotation(90);
    this->moveBy(-1,0);
    return;
}
if((way[m]=="8") && (QPoint(b*30+15,c*30+15)==this->scenePos())){
    casePrecedente=8;
    this->setRotation(90);
    this->moveBy(-1,0);
    return;
}
if((way[m]=="11") && (QPoint(b*30+15,c*30+15)==this->scenePos())){
    casePrecedente=11;
    this->setRotation(0);
    this->moveBy(0,1);
    return;
}
if((way[m]=="32") && (QPoint(b*30+15,c*30+15)==this->scenePos())){

    casePrecedente=32;
    this->setRotation(0);
    this->moveBy(0,0);
    return;
}

if (casePrecedente==18){
    this->moveBy(0,1);
    return;
}
if (casePrecedente==2){
    this->moveBy(0,1);
    return;
}
if (casePrecedente==6){
    this->moveBy(1,0);
    return;
}
if (casePrecedente==4){
    this->moveBy(1,0);
    return;
}
if (casePrecedente==7){
    this->moveBy(0,1);
    return;
}
if (casePrecedente==10){
    this->moveBy(-1,0);
    return;
}
if (casePrecedente==8){
    this->moveBy(-1,0);
    return;
}
if (casePrecedente==11){
    this->moveBy(0,1);
    return;
}}

void Ennemis::resetvitesse(){
    if(ralentir==true){
        vitesse=2*vitesse;
        ralentir=false;
    }
    else return;
}
void Ennemis::smallvitesse(){
    if(ralentir==false){
            ralentir=true;
            vitesse=0.5*vitesse;}
    else return;
}


Cafards::Cafards(float t):Ennemis(t,0,2,10*t*t,5*t*t){
    pixmap = new QPixmap(":/images/cafard1.png");
    *pixmap=pixmap->scaled(30,30,Qt::IgnoreAspectRatio);
    casePrecedente=18;
    img=0;
}

QPixmap Cafards::changeimage(int img){
    if (img%15==0)
    {
        pixmap = new QPixmap(":/images/cafard1.png");
        *pixmap=pixmap->scaled(30,30,Qt::KeepAspectRatio);
    }
    else if (img%10==0)
    {
        pixmap = new QPixmap(":/images/cafard3.png");
        *pixmap=pixmap->scaled(30,30,Qt::KeepAspectRatio);
    }
    else if (img%5==0)
    {
        pixmap = new QPixmap(":/images/cafard2.png");
        *pixmap=pixmap->scaled(30,30,Qt::KeepAspectRatio);

    }
return *pixmap;
}




Fourmis::Fourmis(float t):Ennemis(t,0,(2+t/2),5*t*t,t*t){
    pixmap = new QPixmap(":/images/fourmi1.png");
    *pixmap=pixmap->scaled(30,30,Qt::IgnoreAspectRatio);
    casePrecedente=18;
    img=0;

    acc=false;
}

QPixmap Fourmis::changeimage(int img){
    img++;
    if (img%15==0){
        pixmap = new QPixmap(":/images/fourmi1.png");
        *pixmap=pixmap->scaled(30,30,Qt::KeepAspectRatio);
        img=0;
    }
    else if (img%10==0){
        pixmap = new QPixmap(":/images/fourmi3.png");
        *pixmap=pixmap->scaled(30,30,Qt::KeepAspectRatio);
    }
    else if (img%5==0){
        pixmap = new QPixmap(":/images/fourmi2.png");
        *pixmap=pixmap->scaled(30,30,Qt::KeepAspectRatio);

    }
    return *pixmap;
}

void Fourmis::accelerer(){
    if(acc==false) {vitesse*=1.5;
                    acc=true;
                    }
    else {vitesse/=1.5;
         acc=true;}
};

Guepes::Guepes(float t):Ennemis(t,1,3,7*t*t,4*t*t){
    pixmap = new QPixmap(":/images/guepe1.png");
    *pixmap=pixmap->scaled(30,30,Qt::IgnoreAspectRatio);
    casePrecedente=18;
    img=0;
}

QPixmap Guepes::changeimage(int img){

    img++;
    if (img%10==0){
        pixmap = new QPixmap(":/images/guepe2.png");
        *pixmap=pixmap->scaled(30,30,Qt::KeepAspectRatio);
        img=0;
    }
    else if (img%5==0){
        pixmap = new QPixmap(":/images/guepe1.png");
        *pixmap=pixmap->scaled(30,30,Qt::KeepAspectRatio);

    }
    return *pixmap;
}

void Guepes::die(){
};

Moustiques::Moustiques(float t):Ennemis(t,2,(1+t/2),6*t*t,15*t*t){
    pixmap = new QPixmap(":/images/moustiquevolant1.png");
    *pixmap=pixmap->scaled(30,30,Qt::IgnoreAspectRatio);
    casePrecedente=18;
    img=0;
    modevol=true;
    sol=false;
}

QPixmap Moustiques::changeimage(int img){
    img++;

    if (img%10==0){
        pixmap = new QPixmap(":/images/moustiquevolant2.png");
        *pixmap=pixmap->scaled(30,30,Qt::KeepAspectRatio);
    }
    else if (img%5==0){
        pixmap = new QPixmap(":/images/moustiquevolant1.png");
        *pixmap=pixmap->scaled(30,30,Qt::KeepAspectRatio);

    }
return *pixmap;
}


void Moustiques::changemode(){

};
void Moustiques::cachersol(){
    if(sol) {
        resist=15*taille*taille;
        sol=false;    }
    else {resist=100*taille*taille;
        sol=true;}

};
void Moustiques::moustiquestouche(){

//touche au vol se posent pendant 3 seconds
};