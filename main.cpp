#include <QApplication>
#include <QWidget>
#include "fenprincipale.h"
#include <QtWebKitWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    FenPrincipale fenetre;
    fenetre.show();



    return app.exec();
}
