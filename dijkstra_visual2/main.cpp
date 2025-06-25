#include "graphwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    GraphWidget widget;
    widget.resize(800,600);
    widget.show();

    return a.exec();
}