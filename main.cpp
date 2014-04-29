#include "fluushoption.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    FluushOption w;
    //w.show();

    return a.exec();
}
