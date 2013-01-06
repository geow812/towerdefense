#include "widget.h"

Myview::Myview(Myscene *scene, QWidget *parent) :
    QGraphicsView(scene, parent){
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)

{
    QSound *begin=new QSound("begin1.wav",this);
    begin->play();
    scene = new Myscene;
    view = new Myview(scene,parent);

    //=====================bloc 1
    btnLancer = new QPushButton("Begin");
    btnLancer->setEnabled(true);
    btnArreter = new QPushButton("Pause");
    btnArreter->setEnabled(false);
    etatBtn=0;
    btnQuitter = new QPushButton("Exit");
    group1 = new QHBoxLayout;
    group1->addWidget(btnLancer,0,Qt::AlignCenter);
    group1->addWidget(btnArreter,0,Qt::AlignCenter);
    group1->addWidget(btnQuitter,0,Qt::AlignCenter);

    //======================bloc 2
    credit = new QLabel("Credit");
    nbCredit = new QLCDNumber(4);
    vie = new QLabel("Vie");
    nbVie = new QLCDNumber(4);
    box = new QGridLayout;
    box->addWidget(credit,0,0,Qt::AlignCenter);
    box->addWidget(nbCredit,0,1,Qt::AlignCenter);
    box->addWidget(vie,1,0,Qt::AlignCenter);
    box->addWidget(nbVie,1,1,Qt::AlignCenter);
    group2 = new QGroupBox;
    group2->setLayout(box);

    //========================bloc 3
    group3 = new QProgressBar;
    group3->setRange(0,15);
    group3->setTextVisible(true);
    group3->setValue(0);

    //========================bloc 4
    btnEau = new QPushButton("Eau");
    btnPierre = new QPushButton("Pierre");
    btnPaintBall = new QPushButton("Paint-Ball");
    btnPetanque = new QPushButton("Petanque");
    btnMusicien = new QPushButton("Musicien");
    layout3 = new QGridLayout;
    layout3->addWidget(btnEau,0,0,Qt::AlignCenter);
    layout3->addWidget(btnPierre,0,1,Qt::AlignCenter);
    layout3->addWidget(btnPaintBall,1,0,Qt::AlignCenter);
    layout3->addWidget(btnPetanque,1,1,Qt::AlignCenter);
    layout3->addWidget(btnMusicien,2,0,Qt::AlignCenter);
    group4 = new QGroupBox;
    group4->setTitle("Type de defenses");
    group4->setLayout(layout3);

    //=========================bloc 5
    typeTourLabel = new QLabel(tr("Type de tour : "));
    porteeTourLabel = new QLabel(tr("Portée de Tour : "));
    cadenceTourLabel = new QLabel(tr("Cadence de Tour : "));
    degatsTourLabel = new QLabel(tr("Dégats de Tour : "));
    coutTourLabel = new QLabel(tr("Coût amélioration de Tour : "));

    btnAmeliorer = new QPushButton("Ameliorer");
    btnDetruire = new QPushButton("Detruire");
    btnAmeliorer->setFixedWidth(70);
    btnDetruire->setFixedWidth(70);
    bloc4 = new QVBoxLayout;
    bloc4->addWidget(typeTourLabel,0,Qt::AlignLeft);
    bloc4->addWidget(porteeTourLabel,0,Qt::AlignLeft);
    bloc4->addWidget(cadenceTourLabel,0,Qt::AlignLeft);
    bloc4->addWidget(degatsTourLabel,0,Qt::AlignLeft);
    bloc4->addWidget(coutTourLabel,0,Qt::AlignLeft);

    bloc4->addWidget(btnAmeliorer,0,Qt::AlignCenter);
    bloc4->addWidget(btnDetruire,0,Qt::AlignCenter);
    group5 = new QGroupBox;
    group5->setLayout(bloc4);
    group5->setTitle("Information de Defenses");

    //======================regrouper tous les blocs a droite
    rightLayout = new QVBoxLayout;
    rightLayout->addLayout(group1);
    rightLayout->addWidget(group2);
    rightLayout->addWidget(group3);
    rightLayout->addWidget(group4);
    rightLayout->addWidget(group5);

    //======================layout global
    layout = new QGridLayout;
    layout->setColumnMinimumWidth(0,30);
    layout->setColumnStretch(0,1);
    layout->addWidget(view,0,1,Qt::AlignCenter);
    layout->setColumnMinimumWidth(2,40);
    layout->setColumnStretch(2,0);
    layout->addLayout(rightLayout,0,3,Qt::AlignCenter);
    layout->setColumnMinimumWidth(5,30);
    layout->setColumnStretch(5,1);

    this->setLayout(layout);

    QWidget::connect(btnQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));

    connect(btnLancer,SIGNAL(clicked()),scene,SLOT(startWave()));
    connect(btnLancer,SIGNAL(clicked()),scene->t1,SLOT(start()));
    connect(btnLancer,SIGNAL(clicked()),scene->t2,SLOT(start()));
    connect(scene->t2,SIGNAL(timeout()),scene,SLOT(advance()));
    connect(scene->t1,SIGNAL(timeout()),scene,SLOT(addEnnemis()));
    connect(btnLancer,SIGNAL(clicked()),this,SLOT(buttons()));
    connect(btnArreter,SIGNAL(clicked()),this,SLOT(buttons()));

    connect(scene,SIGNAL(finishedWave()),scene->t1,SLOT(stop()));
    connect(scene,SIGNAL(finishedWave()),this,SLOT(buttons()));
    //connect(scene,SIGNAL(finishedWave()),scene->t2,SLOT(stop()));

    connect(btnLancer,SIGNAL(clicked()),scene->createPistoletAEauTimer,SLOT(start()));
    connect(btnLancer,SIGNAL(clicked()),scene->createLancePierreTimer,SLOT(start()));
    connect(btnLancer,SIGNAL(clicked()),scene->createPaintBallTimer,SLOT(start()));


    connect(btnEau,SIGNAL(clicked()),scene,SLOT(DefensesTypePistoletAEau()));
    connect(btnPierre,SIGNAL(clicked()),scene,SLOT(DefensesTypeLancePierre()));
    connect(btnPaintBall,SIGNAL(clicked()),scene,SLOT(DefensesTypePaintBall()));
    connect(btnPetanque,SIGNAL(clicked()),scene,SLOT(DefensesTypePetanque()));


    connect(view,SIGNAL(mouseScenePress(QPointF)),scene,SLOT(upgradeDefenses(QPointF)));
    connect(view,SIGNAL(mouseScenePress(QPointF)),scene,SLOT(createDefenses(QPointF)));

    connect(scene,SIGNAL(projectileCreer()),scene,SLOT(deleteProjectile()));
    connect(scene->createPistoletAEauTimer,SIGNAL(timeout()),scene,SLOT(createPistoletAEauProjectile()));
    connect(scene->createLancePierreTimer,SIGNAL(timeout()),scene,SLOT(createLancePierreProjectile()));
    connect(scene->createPaintBallTimer,SIGNAL(timeout()),scene,SLOT(createPaintBallProjectile()));

    nbCredit->display("40");
    nbVie->display("10");

    connect(scene,SIGNAL(EnnemisSucceed(int)),this,SLOT(vieLCD(int)));
    connect(scene->t2,SIGNAL(timeout()),scene,SLOT(checkEnnemisSucceed()));
    connect(this, SIGNAL(gameover()), qApp, SLOT(quit()));

    connect(scene, SIGNAL(changeProgressbar(int)), this, SLOT(avanceProgressbar(int)));
    connect(scene,SIGNAL(changeCredits(int)),this,SLOT(creditLCD(int)));


    connect(scene,SIGNAL(typeTour(QString)),this->typeTourLabel,SLOT(setText(QString)));
    connect(scene,SIGNAL(porteeTour(int)),this->typeTourLabel,SLOT(setNum(int)));
    connect(scene,SIGNAL(cadenceTour(int)),this->cadenceTourLabel,SLOT(setNum(int)));
    connect(scene,SIGNAL(degatsTour(int)),this->degatsTourLabel,SLOT(setNum(int)));
    connect(scene,SIGNAL(prixTour(int)),this->coutTourLabel,SLOT(setNum(int)));

  /*  connect(scene,SIGNAL(creditsTower(int)),this,SLOT(creditsLeft(int)));
    connect(scene,SIGNAL(showCreditsLeft(int)),nbCredit,SLOT(display(int)));
    connect(nbVie,SIGNAL(displayViesRestantes(int)),nbVie,SLOT(display(int)));
    connect(nbVie,SIGNAL(stopTimers()),t1,SLOT(stop()));
    connect(nbVie,SIGNAL(stopTimers()),t2,SLOT(stop()));*/
   // connect(nbVie,SIGNAL(stopTimers()),panel,SLOT(buttonsDisabled()));//stopTimers <=> il ne reste plus de vie, on arrete donc la vague

}

Widget::~Widget(){

}