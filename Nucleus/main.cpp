#include "mainwindow.h"

#include <QApplication>
#include<QSplashScreen>
#include<QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen *splash=new QSplashScreen();
    splash->setPixmap(QPixmap(":/img/splash/spl1.jpeg"));
    splash->show();
    QTimer::singleShot(10000,splash,SLOT(close()));
    QTimer::singleShot(10000,new MainWindow,SLOT(show()));
    return a.exec();
}
