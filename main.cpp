#include "multislider.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MultiSlider w;
    w.show();

    return a.exec();
}
