#include "mainview.h"
#include <QApplication>
#include "randomgenerator.h"

int main(int argc, char *argv[])
{
    RandomGenerator::pickSeed();

    QApplication a(argc, argv);
    MainView w;
    w.show();

    return a.exec();
}
