#include "mainwindow.h"
#include <QApplication>
#include <pqxx/pqxx>
using namespace pqxx;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
