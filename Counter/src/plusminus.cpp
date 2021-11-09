#include "plusminus.h"
#include <QGridLayout>

PlusMinus::PlusMinus(QWidget *parent)
    : QWidget(parent) {

  QPushButton *plsBtn = new QPushButton("+", this);
  QPushButton *minBtn = new QPushButton("-", this);
  QPushButton *twinBtn = new QPushButton("*2", this);
  QPushButton *halfBtn = new QPushButton(":2", this);
  lbl = new QLabel("0", this);

  QGridLayout *grid = new QGridLayout(this);
  grid->addWidget(plsBtn, 0, 0);
  grid->addWidget(minBtn, 0, 1);
  grid->addWidget(twinBtn, 1, 0);
  grid->addWidget(halfBtn, 1, 1);
  grid->addWidget(lbl, 2, 1);

  setLayout(grid);

  connect(plsBtn, &QPushButton::clicked, this, &PlusMinus::OnPlus);
  connect(minBtn, &QPushButton::clicked, this, &PlusMinus::OnMinus);
  connect(twinBtn, &QPushButton::clicked, this, &PlusMinus::Twice);
  connect(halfBtn, &QPushButton::clicked, this, &PlusMinus::Half);
}

void PlusMinus::OnPlus() {

  int val = lbl->text().toInt();
  val++;
  lbl->setText(QString::number(val));
}

void PlusMinus::OnMinus() {

  int val = lbl->text().toInt();
  val--;
  lbl->setText(QString::number(val));
}

void PlusMinus::Twice() {
  int val = lbl->text().toInt();
  val = val*2;
  lbl->setText(QString::number(val));
}

void PlusMinus::Half() {
  int val = lbl->text().toInt();
  val = val/2;
  lbl->setText(QString::number(val));
}
