#include "fluushoption.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString trans = QLocale::system().name().section("_", 0, 0);

    QTranslator translator(&a);
    translator.load(":/translation/fluush_" + trans);
    a.installTranslator(&translator);

    a.setQuitOnLastWindowClosed(false);
    FluushOption w;
    //w.show();

    return a.exec();
}
