#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QString("Kektron"));
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}
