#include <iostream>
#include <QApplication>
#include "MyMainWindow.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //window
    MyMainWindow win;
    win.showNormal();

    return app.exec();
}