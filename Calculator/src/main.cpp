#include "calculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;
    w.setFixedSize(371,638);
    w.show();
    return a.exec();
}
