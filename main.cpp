#include "mainwindow.h"
#include "qbase.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTest>
#include "qbaseoperations.h"
#include <QWidget>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen *splash = new QSplashScreen;

    splash->setPixmap(QPixmap(":/images/atelsplash_2.png"));


    MainWindow w;
    w.setWindowIcon(QIcon(":/images/app_icon.svg"));
    splash->show();
     splash->showMessage(QObject::tr("Setting up the main window"));
QTest::qWait(3000);
    w.setWindowTitle("Advanced Technological & e-Learning Systems [Beta-0.01]");

    w.show();
    splash->finish(&w);
    delete splash;
// QApplication a(argc, argv);
//    QBaseOperations *op = new QBaseOperations;
//    op->show();
    return a.exec();

//    QBase base;

//    qDebug() << "r;s comp : " <<  base.calcRMinusOneComplement(8, "2450.011");
//    qDebug() << base.grayToBinary("");


}
