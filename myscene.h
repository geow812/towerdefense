#ifndef MYSCENE_H
#define MYSCENE_H
#include "ennemis.h"
#include "defenses.h"
#include "projectiles.h"
#include <QGraphicsScene>
#include <QApplication>
#include <QtGui/QWidget>
#include <QWidget>
#include <QGraphicsItem>
#include <QPixmap>
#include <QFile>
#include <QMouseEvent>

struct structWave
{
    QString t;//type
    qreal s;//size
    qreal n;//nombre
    qreal i;//interval
};

struct wave{
        QString intitule; // Intitulde la vague
        structWave tab[10]; // une vague,possible different type d'ennemis
        qreal nb; // Nombre de type d'ennemis
};

class Myscene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Myscene(QObject *parent = 0);
    void initScene();
    void readMap();
    int check[16][16];

    Ennemis **ennemis;
    wave tabWave[10];//on suppose max dix vague
    int maxWave; // Nombre max de vague (=5) //REFAIRE EN PRENANT LE NOMBRE DE VAGUE COMME ARGUMENT DU CONSTRUCTEUR MYSCENE
    int maxEnnemis; // Nombre max de Ennemis par vague (=30) // DE MEME EN PASSANT LE NB D'ENNEMI MAX COMME ARG
    int EnnemisNumber; //Nombre de Ennemis
    int waveCounter ; //num de la vague actuelle
    int typeNumber; //numero actuel du type de Ennemis de la vague
    int EnnemisNumberType; //nombre actuel de Ennemis d'un certain type dans une vague
    int deletedEnnemisNumber; //nombre de Ennemis supprimer pour une vage donne
    int nbvague;//nb de vague totale
    int smallCafards;
    void dieGuepe(int);
    void petitCafards(int);

    Defenses **defenses;
    int DefensesNumber;
    int DefensesType;
    int nombreCredits;
    int selectedDefenses;
    int selectedDefensesType;

    void infoPanel();

    QTimer *t1;
    QTimer *t2;
    QTimer *createPistoletAEauTimer; 
    QTimer *createLancePierreTimer;   
    QTimer *createPaintBallTimer;
    QTimer *deleteProjectileTimer;


private:
    QString mat[16];
    QStringList list[16];
    QStringList l;

signals:

    void clicked(int,int);
    void EnnemisSucceed(int);
    void finishedWave();
    void ouvrirInfoTour(int);

    //signal pr les affichages dans le label
    void typeTour(QString);
    void porteeTour(int);
    void cadenceTour(int);
    void degatsTour(int);
    void prixTour(int);
    void impossibleDeConstruireTour(QString);

    void cleanConstruireTour(QString);
    void projectileCreer();
    void changeCredits(int);
    void changeProgressbar(int);





public slots:

    void checkEnnemisSucceed();
    void killLeftItemsMysceneSlot();
    void startWave (); //lance une vague lorsqu'on clique sur le bouton correspondant
    void addEnnemis();


    void DefensesTypePistoletAEau();
    void DefensesTypeLancePierre();
    void DefensesTypePaintBall();
    void DefensesTypePetanque();

    void createDefenses(QPointF pt);
    void createPistoletAEauProjectile();
    void deleteProjectile();
    void createLancePierreProjectile();
    void createPaintBallProjectile();
    void upgradeDefenses(QPointF qt);

protected:


};

#endif // MYSCENE_H