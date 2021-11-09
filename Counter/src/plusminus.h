#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>

class PlusMinus : public QWidget {

  Q_OBJECT // этот макрос должен включаться в классы, которые объявляют свои собственные сигналы и слоты

  public:
    PlusMinus(QWidget *parent = 0);

  private slots:
    void OnPlus();
    void OnMinus();
    void Twice();
    void Half();

  private:
    QLabel *lbl;

};
