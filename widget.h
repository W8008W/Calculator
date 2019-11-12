#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnResult_clicked();

private:
    Ui::Widget *ui;


    QString BasicCalculate(QString str);
};

#endif // WIDGET_H
