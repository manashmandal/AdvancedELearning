#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen *splash = new QSplashScreen;

    splash->setPixmap(QPixmap(":/images/atel.pnh.png"));

    splash->show();


    splash->showMessage(QObject::tr("Setting up the main window"));
    //QTest::qWait(3000);


    MainWindow w;

    w.setWindowTitle("Advanced Technological & e-Learning (Ver: Ki@teL B01)");

    w.show();
    splash->finish(&w);
    delete splash;
    return a.exec();
}
