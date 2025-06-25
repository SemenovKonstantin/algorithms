#include "graphwidget.h"
#include "ui_graphwidget.h"

graphwidget::graphwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::graphwidget)
{
    ui->setupUi(this);
}

graphwidget::~graphwidget()
{
    delete ui;
}
