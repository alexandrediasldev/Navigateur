#include "fenprincipale.h"

FenPrincipale::FenPrincipale()
{
    creerBarreEtat();
    creerMenus();
    creerActions();
    creerBarresOutils();
    onglets = new QTabWidget;

    onglets->addTab(creerOnglet("http://www.google.com"),"Nouvelle page");
    connect(onglets, SIGNAL(currentChanged(int)), this, SLOT(changementOnglet(int)));
    setCentralWidget(onglets);





}
void FenPrincipale::creerActions()
{
    //quitter
    actionQuitter = new QAction("&Quitter",this);
    menuFichier->addAction(actionQuitter);

    QObject::connect(actionQuitter,SIGNAL(triggered()),qApp ,SLOT(quit()));

    //?
    actionApropos = new QAction ("&A propos...",this);
    menuInterrogation->addAction(actionApropos);
    connect(actionApropos,SIGNAL(triggered()),this,SLOT(aPropos()));
    actionAproposQt = new QAction ("A propos Qt...",this);
    menuInterrogation->addAction(actionAproposQt);
    connect(actionAproposQt,SIGNAL(triggered()),qApp,SLOT(aboutQt()));

    //ouvrironglet dans le menu Fichier
    actionOuvrirOnglet =new QAction ("Ouvrir onglet",this);
    menuFichier->addAction(actionOuvrirOnglet);
    connect(actionOuvrirOnglet,SIGNAL(triggered()),this,SLOT(nouvelleOnglet()));

    //fermeronglet dans le menu fichier
    actionFermerOnglet=new QAction("Fermer onglet",this);
    menuFichier->addAction(actionFermerOnglet);
    connect(actionFermerOnglet,SIGNAL(triggered()),this,SLOT(fermerOnglet()));

    //retour en a la page d'avant
    actionPrecedente =new QAction ("Page Precédente",this);
    actionPrecedente->setIcon(QIcon("prec.png"));
    menuNavigation->addAction(actionPrecedente);
    connect(actionPrecedente,SIGNAL(triggered(bool)),this,SLOT(retourArriere()));

    //retour en a la page d'après
    actionSuivante=new QAction ("Page Suivante",this);
    actionSuivante->setIcon(QIcon("suiv.png"));
    menuNavigation->addAction(actionSuivante);
    connect(actionSuivante,SIGNAL(triggered(bool)),this,SLOT(retourAvant()));

    //retour à google
    actionHome = new QAction("Google",this);
    actionHome->setIcon(QIcon("home.png"));
    menuNavigation->addAction(actionHome);
    connect(actionHome,SIGNAL(triggered()),this,SLOT(retourHome()));

    //actualiser
    actionActualiser = new QAction("Actualiser",this);
    actionActualiser->setIcon(QIcon("actu.png"));
    menuNavigation->addAction(actionActualiser);
    connect(actionActualiser,SIGNAL(triggered()),this,SLOT(actualiser()));

    //arreter chargement
    actionStop = new QAction("Arreter le chargement",this);
    actionStop->setIcon(QIcon("stop.png"));
    menuNavigation->addAction(actionStop);
    connect(actionStop,SIGNAL(triggered()),this,SLOT(stop()));

    //recher site
    actionRecherche = new QAction("Rechercher",this);
    actionRecherche->setIcon(QIcon("go.png"));
    menuNavigation->addAction(actionRecherche);
    connect(actionRecherche,SIGNAL(triggered()),this,SLOT(recherche()));


}
void FenPrincipale::creerMenus()
{
menuFichier = menuBar()->addMenu("&Fichier");
menuNavigation = menuBar()->addMenu("&Navigation");
menuInterrogation = menuBar()->addMenu("&?");
}
void FenPrincipale::creerBarresOutils()
{
    champAdresse = new QLineEdit;
    connect(champAdresse, SIGNAL(returnPressed()), this, SLOT(recherche()));

    toolBar =addToolBar("ToolBar");
    toolBar->addAction(actionPrecedente);
    toolBar->addAction(actionSuivante);
    toolBar->addAction(actionHome);
    toolBar->addAction(actionActualiser);
    toolBar->addAction(actionStop);
    toolBar->addWidget(champAdresse);
    toolBar->addAction(actionRecherche);



}
void FenPrincipale::aPropos()
{
    QMessageBox::information(this,"A propos","Ce navigateur web a été crée par alexandre dias");
}

QWidget *FenPrincipale::creerOnglet(QString url)
{
    QWebView *pageWeb = new QWebView;
    QWidget *pageOnglet = new QWidget;

    QVBoxLayout *layout =new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);


    layout->addWidget(pageWeb);
    pageOnglet->setLayout(layout);


    if (url.isEmpty())
      {
          pageWeb->load(QUrl(tr("html/page_blanche.html")));
      }
      else
      {
          if (url.left(7) != "http://")
          {
              url = "http://" + url;
          }
          pageWeb->load(QUrl(url));
      }

    connect(pageWeb, SIGNAL(titleChanged(QString)), this, SLOT(changementTitre(QString)));
    connect(pageWeb, SIGNAL(urlChanged(QUrl)), this, SLOT(changementUrl(QUrl)));
    connect(pageWeb, SIGNAL(loadStarted()), this, SLOT(chargementDebut()));
    connect(pageWeb, SIGNAL(loadProgress(int)), this, SLOT(chargementEnCours(int)));
    connect(pageWeb, SIGNAL(loadFinished(bool)), this, SLOT(chargementTermine(bool)));


    return pageOnglet;
}
void FenPrincipale::nouvelleOnglet()
{


    int indexNouvelleOnglet = onglets->addTab(creerOnglet("http://www.google.com"),"Nouvelle page");
    onglets->setCurrentIndex(indexNouvelleOnglet);

}
void FenPrincipale::fermerOnglet()
{

    onglets->removeTab(onglets->currentIndex());
    if(onglets->count() < 1)
    {
    nouvelleOnglet();
    }
}

QWebView *FenPrincipale::pageActuelle()
{
    return onglets->currentWidget()->findChild<QWebView *>();
}
void FenPrincipale::retourArriere()
{
    pageActuelle()->back();
}
void FenPrincipale::retourAvant()
{
     pageActuelle()->forward();
}
void FenPrincipale::retourHome()
{
    pageActuelle()->load(QUrl("http://google.com"));
}
void FenPrincipale::actualiser()
{
    pageActuelle()->reload();
}
void FenPrincipale::stop()
{
    pageActuelle()->stop();
}
void FenPrincipale::changementOnglet(int index)
{
    changementTitre(pageActuelle()->title());
    changementUrl(pageActuelle()->url());
}
void FenPrincipale::changementTitre(const QString &titreComplet)
{
    QString titreCourt = titreComplet;
    if (titreComplet.size() > 40)
    {
        titreCourt = titreComplet.left(40) +"...";
    }
    setWindowTitle(titreCourt);
    onglets->setTabText(onglets->currentIndex(),titreCourt);
}
void FenPrincipale::changementUrl(const QUrl &url)
{
    if (url.toString() != tr("html/page_blanche.html"))
        {
            champAdresse->setText(url.toString());
        }

}
void FenPrincipale::creerBarreEtat()
{
    progression = new QProgressBar(this);
    progression->setVisible(false);
    progression->setMaximumHeight(14);
    statusBar()->addWidget(progression, 1);
}
void FenPrincipale::chargementDebut()
{
    progression->setVisible(true);
}

void FenPrincipale::chargementEnCours(int pourcentage)
{
    progression->setValue(pourcentage);
}

void FenPrincipale::chargementTermine(bool ok)
{
    progression->setVisible(false);
    statusBar()->showMessage(tr("Prêt"), 2000);
}
void FenPrincipale::recherche()
{
    QString url = champAdresse->text();

        // On rajoute le "http://" s'il n'est pas déjà dans l'adresse
        if (url.left(7) != "http://")
        {
            url = "http://" + url;
            champAdresse->setText(url);
        }

        pageActuelle()->load(QUrl(url));
}
