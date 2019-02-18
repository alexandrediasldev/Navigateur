#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QWebView>
#include <QProgressBar>
#include <QLineEdit>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QStatusBar>

#include <QtWebKitWidgets>

class FenPrincipale : public QMainWindow
{
        Q_OBJECT
        public:
        FenPrincipale();
        void creerActions();
        void creerMenus();
        void creerBarresOutils();
        QWidget *creerOnglet(QString url);
        QWebView *pageActuelle();
        void creerBarreEtat();

        private:
        QTabWidget *onglets;
        QMenu *menuFichier;
        QMenu *menuInterrogation;
        QMenu *menuNavigation;
        QAction *actionQuitter;
        QAction *actionApropos;
        QAction *actionAproposQt;
        QAction *actionOuvrirOnglet;
        QAction *actionFermerOnglet;
        QAction *actionPrecedente;
        QAction *actionSuivante;
        QAction *actionHome;
        QAction *actionActualiser;
        QAction *actionStop;
        QAction *actionRecherche;
        QToolBar *toolBar;

        QProgressBar *progression;
        QLineEdit *champAdresse;

private slots:
        void aPropos();
        void nouvelleOnglet();
        void fermerOnglet();
        void retourArriere();
        void retourAvant();
        void retourHome();
        void actualiser();
        void stop();
        void changementOnglet(int index);
        void changementTitre(const QString & titreComplet);
        void changementUrl(const QUrl & url);
        void chargementDebut();
        void chargementEnCours(int pourcentage);
        void chargementTermine(bool ok);
        void recherche();



};
#endif // FENPRINCIPALE_H
