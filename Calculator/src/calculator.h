#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
private slots:
    void add_digit();
    void add_dot();
    void unary();
    void binary();
    void equal();
    void clear();
};
#endif // CALCULATOR_H
