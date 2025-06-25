#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class graphwidget;
}
QT_END_NAMESPACE

class graphwidget : public QWidget
{
    Q_OBJECT

public:
    graphwidget(QWidget *parent = nullptr);
    ~graphwidget();

private:
    Ui::graphwidget *ui;
};
#endif // GRAPHWIDGET_H
