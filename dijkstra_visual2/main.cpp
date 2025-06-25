#include "graphwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    graphwidget w;
    w.show();
    return a.exec();
}
