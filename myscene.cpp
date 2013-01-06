#include "Myscene.h"
#include <QPropertyAnimation>
Myscene::Myscene(QObject *parent) :
    QGraphicsScene(parent)
{
    initScene();
    readMap();
    maxEnnemis=31;
    ennemis = new Ennemis*[maxEnnemis];
    waveCounter=-1;
    EnnemisNumber=0;
    DefensesType=0;
    DefensesNumber=0;
    defenses = new Defenses*[30];
    nombreCredits=40;
    selectedDefenses = -1;
    selectedDefensesType = -1;


    t1 = new QTimer();
    t1->setSingleShot(false);
   // t1->start();
   // t1->stop();

    t2 = new QTimer();
    t2->setSingleShot(false);
   // t2->start(20);
    //t2->stop();


    createPistoletAEauTimer = new QTimer();
    createPistoletAEauTimer->start(300);
    createPistoletAEauTimer->stop();


    createLancePierreTimer = new QTimer;
    createLancePierreTimer->start(200);
    createLancePierreTimer->stop();

    createPaintBallTimer = new QTimer;   
    createPaintBallTimer->start(200);
    createPaintBallTimer->stop();

    deleteProjectileTimer=new QTimer;
    deleteProjectileTimer->start(200);
    deleteProjectileTimer->stop();


}

void Myscene::initScene(){
    QPixmap herbe;
    herbe.load(":/images/herbe.jpg",0,Qt::AutoColor);
    herbe = herbe.scaled(30,30,Qt::KeepAspectRatio);
    //scene->setSceneRect(480,480,480,480);

    for(int i=0;i<16;i++)
        for(int j=0;j<16;j++)
        {
            QGraphicsItem *background;
            background = this->addPixmap(herbe);
            background->setPos(i*30,j*30);
        }

}

void Myscene::readMap(){
  /******************************map***************************/
    QFile mapFile(":/txt/map.txt");
    if (mapFile.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        for(int i=0;i<16;i++)
        {
            mat[i]=mapFile.readLine();
            mat[i]=mat[i].simplified();
            list[i]=mat[i].split(" ",QString::SkipEmptyParts);

            l.append(list[i]);


        }
                mapFile.close();
    }



    QPixmap img0;
    img0.load(":/images/grass2.png", 0, Qt::AutoColor);
    img0=img0.scaled(30,30,Qt::KeepAspectRatio);


    QPixmap img1;
    img1.load(":/images/soil15.png", 0, Qt::AutoColor);
    img1=img1.scaled(30,30,Qt::KeepAspectRatio);

    QPixmap img2;
    img2.load(":/images/water3.png", 0, Qt::AutoColor);
    img2=img2.scaled(30,30,Qt::KeepAspectRatio);

    QPixmap img3;
    img3.load(":/images/fin.png", 0, Qt::AutoColor);
    img3=img3.scaled(30,30,Qt::KeepAspectRatio);

    for(int m=0;m<16;m++)
        for(int n=0;n<16;n++)
    {
        check[m][n]=0;
    }

    for (int i=0;i<16;i++)
    {
        for (int j=0;j<16;j++)
        {
            if (list[i][j]=="18" || list[i][j]=="2"|| list[i][j]=="11"  || list[i][j]=="6"||list[i][j]=="4"||list[i][j]=="10"||list[i][j]=="8"|| list[i][j]=="7")
            {
                QGraphicsItem *item1;
                item1 = this->addPixmap(img1);
                item1->setPos((j)*30,(i)*30);

            }
            if(list[i][j]=="0"){
                QGraphicsItem *item0;
                item0 = this->addPixmap(img0);
                item0->setPos((j)*30,(i)*30);
                check[j][i]=1;
            }
            if(list[i][j]=="64"){
                QGraphicsItem *item2;
                item2 = this->addPixmap(img2);
                item2->setPos((j)*30,(i)*30);
            }
            if(list[i][j]=="32"){
                QGraphicsItem *item3;
                item3 = this->addPixmap(img3);
                item3->setPos((j)*30,(i)*30);
            }
        }
    }



    /*********************wave Ennemis****************/
    QFile waveFile(":/txt/waves.txt");
    QString waveread;
    if(waveFile.open(QIODevice::ReadOnly| QIODevice::Text)){
            waveread=waveFile.readAll();
            waveFile.close();
    }
    else  waveread= "Impossible d'ouvrir le fichier !";
    QStringList wavelist = waveread.split('\n');
    nbvague=wavelist.count();//nb de vague totale
    for (int i=0;i<wavelist.count();i++)
    {
        QStringList partie1;
        QStringList partie2;
        partie1 = wavelist[i].split(';');
        tabWave[i].nb=partie1.count()-1; //renvoie le type d'ennemis dans une vague
        tabWave[i].intitule=partie1[0];

        for (int j=1;j<partie1.count();j++)
        {
            partie2 = partie1[j].split(':');
            tabWave[i].tab[j-1].t=partie2[0];
            tabWave[i].tab[j-1].s=partie2[1].toInt();
            tabWave[i].tab[j-1].n=partie2[2].toInt();
            tabWave[i].tab[j-1].i=partie2[3].toInt();
        }
    }

}


void Myscene::checkEnnemisSucceed(){
    QPointF b(405,465);
    for (int i=0;i<EnnemisNumber;i++){
        if (ennemis[i]!= 0){
            if (ennemis[i]->pos()==b){
                QSound::play("lose.wav");
                this->removeItem(ennemis[i]);
                delete ennemis[i];
                ennemis[i] = 0;
                deletedEnnemisNumber++;
                emit EnnemisSucceed(1);
                if (deletedEnnemisNumber == maxEnnemis+smallCafards)
                {
                    emit finishedWave();
                }
           }

        }
    }
}

void Myscene::killLeftItemsMysceneSlot(){
    for (int i=deletedEnnemisNumber;i<maxEnnemis;i++) {
        this->removeItem(ennemis[i]);
    }
}

void Myscene::dieGuepe(int focus){
   /* QRectF rectCentre(ennemis[focus]->pos().x(),ennemis[focus]->pos().y(),90,90);
    for (int i=0;i<EnnemisNumber;i++)
    {
        if (ennemis[i] != 0)
        {
            if (rectCentre.contains(ennemis[i]->pos()))
            {
                ennemis[i]->hp-=1;
                if (ennemis[i]->hp <= 0){
                if (dynamic_cast<Guepes*>(ennemis[i])){ dieGuepe(i);}
                if ((dynamic_cast<Cafards*>(ennemis[i])) && (ennemis[i]->taille>= 2)){ petitCafards(i);}
                this->removeItem(ennemis[i]);
                delete ennemis[i];
                ennemis[i] = 0;
                emit changeCredits(1);
                deletedEnnemisNumber++;}
                if (deletedEnnemisNumber==maxEnnemis+smallCafards){emit finishedWave();}

            }}}*/
};





void Myscene::petitCafards(int focus){
     for (int i=0;i<2;i++){
            ennemis[EnnemisNumber] = new Cafards(ennemis[focus]->taille-1);
            ennemis[EnnemisNumber]->setPos(ennemis[focus]->pos().x(),ennemis[focus]->pos().y());
            ennemis[EnnemisNumber]->setway(&l);
            this->addItem(ennemis[EnnemisNumber]);
            ennemis[EnnemisNumber]->setZValue(2);

            ennemis[EnnemisNumber]->casePrecedente = ennemis[focus]->casePrecedente;
            if (ennemis[focus]->casePrecedente == 6 || ennemis[focus]->casePrecedente == 4)
            {
                ennemis[EnnemisNumber]->setRotation(270);
            }
            if (ennemis[focus]->casePrecedente == 8)
            {
                ennemis[EnnemisNumber]->setRotation(90);
            }
            EnnemisNumber+=1;
            smallCafards++;
        }
    };







void Myscene::startWave () //lance une vague lorsqu'on clique sur le bouton correspondant
{
    smallCafards=0;
    waveCounter+=1;
    EnnemisNumber=0;
    deletedEnnemisNumber=0;
}

void Myscene::addEnnemis(){
    if (EnnemisNumber==0){
        maxEnnemis=0;
        for (int i=0;i<tabWave[waveCounter].nb;i++){
            maxEnnemis+=tabWave[waveCounter].tab[i].n;
       }
        typeNumber=0;
        EnnemisNumberType=0;
    }

    if (EnnemisNumber==maxEnnemis+smallCafards){

        return;}

    if (tabWave[waveCounter].tab[typeNumber].n==EnnemisNumberType){
        if (tabWave[waveCounter].nb==typeNumber)  return;
        typeNumber+=1;
        EnnemisNumberType=0;
    }
     if (tabWave[waveCounter].tab[typeNumber].t=="fourmi"){
        t1->start(50*tabWave[waveCounter].tab[typeNumber].i);
        ennemis[EnnemisNumber] = new Fourmis(tabWave[waveCounter].tab[typeNumber].s);
        EnnemisNumberType+=1;
        t2->start(6*ennemis[EnnemisNumber]->vitesse);
    }
    if (tabWave[waveCounter].tab[typeNumber].t=="guepe")
    {    t1->start(50*tabWave[waveCounter].tab[typeNumber].i);
        ennemis[EnnemisNumber] = new Guepes(tabWave[waveCounter].tab[typeNumber].s);
        EnnemisNumberType+=1;
        t2->start(6*ennemis[EnnemisNumber]->vitesse);
    }
    if (tabWave[waveCounter].tab[typeNumber].t=="cafard")
    {    t1->start(50*tabWave[waveCounter].tab[typeNumber].i);
        ennemis[EnnemisNumber] = new Cafards(tabWave[waveCounter].tab[typeNumber].s);
        EnnemisNumberType+=1;
        t2->start(6*ennemis[EnnemisNumber]->vitesse);
    }
    if (tabWave[waveCounter].tab[typeNumber].t=="moustique")
    {   t1->start(50*tabWave[waveCounter].tab[typeNumber].i);
        ennemis[EnnemisNumber] = new Moustiques(tabWave[waveCounter].tab[typeNumber].s);
        EnnemisNumberType+=1;
        t2->start(6*ennemis[EnnemisNumber]->vitesse);
    }

    ennemis[EnnemisNumber]->setPos((2)*30+15,(0)*30+15);
    ennemis[EnnemisNumber]->setway(&l);
    this->addItem(ennemis[EnnemisNumber]);
    ennemis[EnnemisNumber]->setZValue(2);
    EnnemisNumber++;
    emit changeProgressbar(EnnemisNumber);
};

void Myscene::upgradeDefenses(QPointF pt){
    int b=(pt.x())/30;
    int c=(pt.y())/30;
    int d=b+c*16;
    if(l[d]=="0") return;
    for(int i=0;i<DefensesNumber;i++){
;
        if(defenses[i]->position==QPointF(b,c)){
                switch(defenses[i]->niveau){
                case 1:
                    if(nombreCredits-defenses[i]->coutUnVersDeux>=0){
                        defenses[i]->setniveau(2);
                        nombreCredits-=defenses[i]->coutUnVersDeux;

                        qDebug()<<nombreCredits;
                        qDebug()<<i;
                        emit changeCredits(-defenses[i]->coutUnVersDeux);

                        emit typeTour(defenses[i]->typeName);
                        emit porteeTour(defenses[i]->rayonAction/30.0);
                        emit cadenceTour(defenses[i]->cadence);
                        emit degatsTour(defenses[i]->degat);
                        emit prixTour(defenses[i]->coutUnVersDeux);

                        return;
                    }

                case 2:
                     if(nombreCredits-defenses[i]->coutDeuxVersTrois>=0){
                        defenses[i]->setniveau(2);
                        nombreCredits-=defenses[i]->coutDeuxVersTrois;

                        emit changeCredits(-defenses[i]->coutDeuxVersTrois);
                        emit typeTour(defenses[i]->typeName);
                        emit porteeTour(defenses[i]->rayonAction/30.0);
                        emit cadenceTour(defenses[i]->cadence);
                        emit degatsTour(defenses[i]->degat);
                        emit prixTour(defenses[i]->coutDeuxVersTrois);

                        return;
                    }

                case 3:break;
                default: return;
             }
        }
    }

};

void Myscene::DefensesTypePistoletAEau(){
    DefensesType=1;
};
void Myscene::DefensesTypeLancePierre(){
    DefensesType=2;
};
void Myscene::DefensesTypePaintBall(){
    DefensesType=3;
};
void Myscene::DefensesTypePetanque(){
    DefensesType=4;
};

void Myscene::createDefenses(QPointF pt){
    int b=(pt.x())/30;
    int c=(pt.y())/30;
    int d=b+c*16;
    if (DefensesType!=0){
        if (l[d]=="0"){
            switch(DefensesType){
            case 1:
                 defenses[DefensesNumber] = new PistoletAEauDefenses();
                 infoPanel();
                 l[d]="1";
                 break;
            case 2:
                 defenses[DefensesNumber] = new LancePierreDefenses();
                 infoPanel();
                 l[d]="2";
                 break;
            case 3:
                 defenses[DefensesNumber] = new PaintBallDefenses();
                 infoPanel();
                 l[d]="3";
                 break;
            case 4:
                 defenses[DefensesNumber] = new PetanqueDefenses();
                 infoPanel();
                 l[d]="4";
                 break;
            default: break;
            }
            if ((nombreCredits - defenses[DefensesNumber]->coutDeBase) >= 0){
                    defenses[DefensesNumber]->setPos(b*30+15,c*30+15);
                    defenses[DefensesNumber]->position = QPointF(b,c);
                    this->addItem(defenses[DefensesNumber]);
                    emit changeCredits(-defenses[DefensesNumber]->coutDeBase);

                    DefensesType=0;
                    nombreCredits-=defenses[DefensesNumber]->coutDeBase;
                    DefensesNumber++;

                    emit cleanConstruireTour(" ");
                     qDebug()<<"okokhihihihihi"<<DefensesNumber;
            }
            else{ qDebug()<<"impossiblehihihihihi";
                    emit impossibleDeConstruireTour("Pas assez de credits !");
                    delete defenses[DefensesNumber];
                    l[d]="0";
                    DefensesType=0;
                }
            }
    else if (l[d] == "1" || l[d] == "2" || l[d] == "3"){  qDebug()<<"hihihihihi";upgradeDefenses(pt);
   }
    }

};

void Myscene::infoPanel()
{
    emit typeTour(defenses[DefensesNumber]->typeName);
    emit porteeTour(defenses[DefensesNumber]->rayonAction/30.0);
    emit cadenceTour(defenses[DefensesNumber]->cadence);
    emit degatsTour(defenses[DefensesNumber]->degat);
    emit prixTour(defenses[DefensesNumber]->coutDeBase);
}

void Myscene::createPistoletAEauProjectile(){
    for (int i=0;i<DefensesNumber;i++){
        if (defenses[i]->type == 1){
            if (defenses[i]->focusNumber == -1){ //Recherche une cible
                for (int j=0;j<EnnemisNumber;j++){
                    if (ennemis[j]!=0){
                        QPointF vecteur = ennemis[j]->pos() - defenses[i]->pos();
                        float distance = sqrt( ( vecteur.x() * vecteur.x() ) + ( vecteur.y() * vecteur.y()) );
                        if (distance < defenses[i]->rayonAction){
                            defenses[i]->focusNumber = j;
                         }
                    }
                }
            }
            else  {//On a d'une cible
            if (ennemis[defenses[i]->focusNumber] != 0){
                    QPointF cible= ennemis[defenses[i]->focusNumber]->pos();
                    QPointF vecteur =cible - defenses[i]->pos();
                    float distance = sqrt( ( vecteur.x() * vecteur.x() ) + ( vecteur.y() * vecteur.y()) );
                    if (distance < defenses[i]->rayonAction){
                                if(defenses[i]->nbProjectiles==20) defenses[i]->nbProjectiles=0;
                                defenses[i]->projectile[defenses[i]->nbProjectiles] = new EauProjectiles(QPointF(defenses[i]->pos().x()-15,defenses[i]->pos().y()-15),2);
                                defenses[i]->projectile[defenses[i]->nbProjectiles]->target = defenses[i]->focusNumber;
                                this->addItem(defenses[i]->projectile[defenses[i]->nbProjectiles]);
                                defenses[i]->projectile[defenses[i]->nbProjectiles]->launch(QPointF(cible.x()+10,cible.y()-10));
                                defenses[i]->nbProjectiles++;
                                QTimer::singleShot(200,this, SLOT(deleteProjectile()));
                   }
                    else{
                        defenses[i]->focusNumber = -1;
                    }
                }
                else
                {
                    defenses[i]->focusNumber = -1;

                }
            }
        }
    }
};



void Myscene::deleteProjectile(){
    for (int i=0;i<DefensesNumber;i++){
            for (int j=0;j<defenses[i]->nbProjectiles;j++){
                if (defenses[i]->projectile[j] != 0){
                    QSound::play("collision.wav");
                    if (ennemis[defenses[i]->projectile[j]->target] != 0){
                        int focus = defenses[i]->projectile[j]->target;                        
                        if (Fourmis *pt = dynamic_cast<Fourmis*>(ennemis[focus])){
                            if (pt->acc==false) pt->accelerer();
                            QTimer::singleShot(5000,ennemis[focus],SLOT(accelerer()));
                        }
                        ennemis[focus]->hp-=1;
                        defenses[i]->projectile[j]->destroy();
                        delete defenses[i]->projectile[j];
                        defenses[i]->projectile[j] = 0;

                        if (ennemis[focus]->hp <= 0){                                                                                  
                            if (dynamic_cast<Guepes*>(ennemis[focus])){ dieGuepe(focus);}
                            if ((dynamic_cast<Cafards*>(ennemis[focus])) && (ennemis[focus]->taille>= 2)){  petitCafards(focus);}

                            this->removeItem(ennemis[focus]);
                            delete ennemis[focus];
                            ennemis[focus] = 0;
                            emit changeCredits(1);
                            deletedEnnemisNumber++;}
                            if (deletedEnnemisNumber==maxEnnemis+smallCafards){emit finishedWave();}}
                    else
                    {
                        defenses[i]->projectile[j]->target = -1;
                        defenses[i]->projectile[j]->destroy();
                        delete defenses[i]->projectile[j];
                        defenses[i]->projectile[j] = 0;
                    }
             }}}};

void Myscene::createLancePierreProjectile(){
    for (int i=0;i<DefensesNumber;i++){
        if (defenses[i]->type == 2){
            if (defenses[i]->focusNumber == -1){ //Recherche une cible
                for (int j=0;j<EnnemisNumber;j++){
                    if (ennemis[j]!=0){
                        QPointF vecteur = ennemis[j]->pos() - defenses[i]->pos();
                        float distance = sqrt( ( vecteur.x() * vecteur.x() ) + ( vecteur.y() * vecteur.y()) );
                        if (distance < defenses[i]->rayonAction){
                            defenses[i]->focusNumber = j;
                         }
                    }
                }
            }
            else  {//On a d'une cible
            if (ennemis[defenses[i]->focusNumber] != 0){
                    QPointF cible= ennemis[defenses[i]->focusNumber]->pos();
                    QPointF vecteur =cible - defenses[i]->pos();
                    float distance = sqrt( ( vecteur.x() * vecteur.x() ) + ( vecteur.y() * vecteur.y()) );
                    if (distance < defenses[i]->rayonAction){
                                if(defenses[i]->nbProjectiles==20) defenses[i]->nbProjectiles=0;
                                defenses[i]->projectile[defenses[i]->nbProjectiles] = new PierreProjectiles(QPointF(defenses[i]->pos().x()-15,defenses[i]->pos().y()-15),2);
                                defenses[i]->projectile[defenses[i]->nbProjectiles]->target = defenses[i]->focusNumber;
                                this->addItem(defenses[i]->projectile[defenses[i]->nbProjectiles]);
                                defenses[i]->projectile[defenses[i]->nbProjectiles]->launch(QPointF(cible.x()+10,cible.y()-10));
                                defenses[i]->nbProjectiles++;
                                QTimer::singleShot(200,this, SLOT(deleteProjectile()));
                   }
                    else{
                        defenses[i]->focusNumber = -1;
                    }
                }
                else
                {
                    defenses[i]->focusNumber = -1;
                }
            }
        }
    }
};

void Myscene::createPaintBallProjectile(){
    for (int i=0;i<DefensesNumber;i++){
        if (defenses[i]->type == 3){
            if (defenses[i]->focusNumber == -1){ //Recherche une cible
                for (int j=0;j<EnnemisNumber;j++){
                    if (ennemis[j]!=0){
                        QPointF vecteur = ennemis[j]->pos() - defenses[i]->pos();
                        float distance = sqrt( ( vecteur.x() * vecteur.x() ) + ( vecteur.y() * vecteur.y()) );
                        if (distance < defenses[i]->rayonAction){
                            defenses[i]->focusNumber = j;
                         }
                    }
                }
            }
            else  {//On a d'une cible
            if (ennemis[defenses[i]->focusNumber] != 0){
                    QPointF cible= ennemis[defenses[i]->focusNumber]->pos();
                    QPointF vecteur =cible - defenses[i]->pos();
                    float distance = sqrt( ( vecteur.x() * vecteur.x() ) + ( vecteur.y() * vecteur.y()) );
                    if (distance < defenses[i]->rayonAction){
                                if(defenses[i]->nbProjectiles==20) defenses[i]->nbProjectiles=0;
                                defenses[i]->projectile[defenses[i]->nbProjectiles] = new PaintBallProjectiles(QPointF(defenses[i]->pos().x()-15,defenses[i]->pos().y()-15),2);
                                defenses[i]->projectile[defenses[i]->nbProjectiles]->target = defenses[i]->focusNumber;
                                this->addItem(defenses[i]->projectile[defenses[i]->nbProjectiles]);
                                defenses[i]->projectile[defenses[i]->nbProjectiles]->launch(QPointF(cible.x()+10,cible.y()-10));
                                defenses[i]->nbProjectiles++;
                                QTimer::singleShot(200,this, SLOT(deleteProjectile()));

                   }
                    else{
                        defenses[i]->focusNumber = -1;

                    }
                }
                else
                {
                    defenses[i]->focusNumber = -1;

                }
            }
        }
    }
};