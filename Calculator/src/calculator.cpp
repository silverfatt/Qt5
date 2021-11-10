#include "calculator.h"
#include "ui_calculator.h"
double first_number = 0;
QString last_operand = "";
QString expression = "";

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    connect(ui->pushButton_0,SIGNAL(clicked()), this, SLOT(add_digit()));       //0
    connect(ui->pushButton_1,SIGNAL(clicked()), this, SLOT(add_digit()));       //1
    connect(ui->pushButton_2,SIGNAL(clicked()), this, SLOT(add_digit()));       //2
    connect(ui->pushButton_3,SIGNAL(clicked()), this, SLOT(add_digit()));       //3
    connect(ui->pushButton_4,SIGNAL(clicked()), this, SLOT(add_digit()));       //4
    connect(ui->pushButton_5,SIGNAL(clicked()), this, SLOT(add_digit()));       //5
    connect(ui->pushButton_6,SIGNAL(clicked()), this, SLOT(add_digit()));       //6
    connect(ui->pushButton_7,SIGNAL(clicked()), this, SLOT(add_digit()));       //7
    connect(ui->pushButton_8,SIGNAL(clicked()), this, SLOT(add_digit()));       //8
    connect(ui->pushButton_9,SIGNAL(clicked()), this, SLOT(add_digit()));       //9
    connect(ui->pushButton_dot,SIGNAL(clicked()), this, SLOT(add_dot()));       //.

    connect(ui->pushButton_cng,SIGNAL(clicked()), this, SLOT(unary()));         //+/-
    connect(ui->pushButton_percent,SIGNAL(clicked()), this, SLOT(unary()));     //%
    connect(ui->pushButton_down,SIGNAL(clicked()), this, SLOT(unary()));        //1/x
    connect(ui->pushButton_sqr,SIGNAL(clicked()), this, SLOT(unary()));         //x*x
    connect(ui->pushButton_sqrt,SIGNAL(clicked()), this, SLOT(unary()));         //x*x

    connect(ui->pushButton_ce,SIGNAL(clicked()), this, SLOT(clear()));          //CE
    connect(ui->pushButton_c,SIGNAL(clicked()), this, SLOT(clear()));           //C
    connect(ui->pushButton_back,SIGNAL(clicked()), this, SLOT(clear()));        //<-

    connect(ui->pushButton_plus,SIGNAL(clicked()), this, SLOT(binary()));       //+
    connect(ui->pushButton_min,SIGNAL(clicked()), this, SLOT(binary()));        //-
    connect(ui->pushButton_div,SIGNAL(clicked()), this, SLOT(binary()));        //:
    connect(ui->pushButton_mult,SIGNAL(clicked()), this, SLOT(binary()));       //x
    connect(ui->pushButton_eq,SIGNAL(clicked()), this, SLOT(equal()));          //=

    //ui->pushButton_min->setCheckable(true);
    //ui->pushButton_plus->setCheckable(true);
    //ui->pushButton_div->setCheckable(true);
    //ui->pushButton_mult->setCheckable(true);
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::clear(){
    QPushButton* btn = (QPushButton *)sender();
    if (btn->text() == "CE"){
        ui->lbl->setText("0");
    } else if(btn->text() == "C"){
        first_number = 0;
        expression = "";
        last_operand = "";
        ui->label->setText(expression);
        ui->lbl->setText("0");
    } else if(btn->text() == "<-"){
        QString str = ui->lbl->text();
        str.chop(1);
        ui->lbl->setText(str);
    }

}

void Calculator::add_digit(){
    QPushButton* btn = (QPushButton *)sender();
    double oldnumber;
    QString newnumber;
    oldnumber = (ui->lbl->text() + btn->text()).toDouble();
    newnumber = QString::number(oldnumber, 'g', 15);
    ui->lbl->setText(newnumber);

}
void Calculator::add_dot(){
    //QPushButton* btn = (QPushButton *)sender();
    if(!(ui->lbl->text().contains('.'))) ui->lbl->setText(ui->lbl->text() + ".");
}
void Calculator::unary(){
    QPushButton* btn = (QPushButton *)sender();
    if (btn->text() == "+/-"){
        double oldnumber;
        QString newnumber;
        oldnumber = ui->lbl->text().toDouble();
        oldnumber = -1 * oldnumber;
        newnumber = QString::number(oldnumber, 'g', 15);
        ui->lbl->setText(newnumber);
    } else if (btn->text() == "%"){
        double oldnumber;
        QString newnumber;
        oldnumber = ui->lbl->text().toDouble();
        oldnumber = 0.01 * oldnumber;
        newnumber = QString::number(oldnumber, 'g', 15);
        ui->lbl->setText(newnumber);
    } else if (btn->text() == "x*x"){
        double oldnumber;
        QString newnumber;
        oldnumber = ui->lbl->text().toDouble();
        oldnumber = oldnumber * oldnumber;
        newnumber = QString::number(oldnumber, 'g', 15);
        ui->lbl->setText(newnumber);
    } else if (btn->text() == "1/x"){
        double oldnumber;
        QString newnumber;
        oldnumber = ui->lbl->text().toDouble();
        oldnumber = 1/oldnumber;
        newnumber = QString::number(oldnumber, 'g', 15);
        ui->lbl->setText(newnumber);
    } else if (btn->text() == "sqrt(x)"){
        double oldnumber;
        QString newnumber;
        oldnumber = ui->lbl->text().toDouble();
        oldnumber = sqrt(oldnumber);
        newnumber = QString::number(oldnumber, 'g', 15);
        ui->lbl->setText(newnumber);
    }

}

void Calculator::binary(){
    QPushButton* btn = (QPushButton *)sender();
    if (last_operand == "") {
        ui->label->setText(" ");
        last_operand = btn->text();
        first_number = first_number + ui->lbl->text().toDouble();
        expression.append(ui->lbl->text());
        expression.append(last_operand);
        ui->lbl->setText("0");
    }else if(last_operand == "+"){
        first_number = first_number + ui->lbl->text().toDouble();
        expression.append(ui->lbl->text());
        if((last_operand = btn->text()) == "x" || last_operand == "/") expression.prepend("(").append(")").append(last_operand);
        else expression.append(last_operand);
        ui->lbl->setText("0");
        ui->label->setText(expression);
    }else if(last_operand == "-"){
        first_number = first_number - ui->lbl->text().toDouble();
        expression.append(ui->lbl->text());
        if((last_operand = btn->text()) == "x" || last_operand == "/") expression.prepend("(").append(")").append(last_operand);
        else expression.append(last_operand);
        ui->lbl->setText("0");
        ui->label->setText(expression);
    }else if(last_operand == "x"){
        last_operand = btn->text();
        first_number = first_number * ui->lbl->text().toDouble();
        expression.append(ui->lbl->text());
        expression.append(last_operand);
        ui->lbl->setText("0");
        ui->label->setText(expression);
    }else if(last_operand == "/"){
        last_operand = btn->text();
        first_number = first_number / ui->lbl->text().toDouble();
        expression.append(ui->lbl->text());
        expression.append(last_operand);
        ui->lbl->setText("0");
        ui->label->setText(expression);
    }
}

void Calculator::equal(){
    QString solutionstr;

    if(last_operand == "+"){
        first_number = first_number+ui->lbl->text().toDouble();
        solutionstr = QString::number(first_number, 'g', 15);
        ui->label->setText(expression.append(ui->lbl->text()));
        ui->lbl->setText(solutionstr);
        first_number = 0;
        expression = "";
        last_operand = "";
    } else if(last_operand == "-"){
        first_number = first_number-ui->lbl->text().toDouble();
        solutionstr = QString::number(first_number, 'g', 15);
        ui->label->setText(expression.append(ui->lbl->text()));
        ui->lbl->setText(solutionstr);
        first_number = 0;
        expression = "";
        last_operand = "";
    } else if(last_operand == "x"){
        first_number = first_number*ui->lbl->text().toDouble();
        solutionstr = QString::number(first_number, 'g', 15);
        ui->label->setText(expression.append(ui->lbl->text()));
        ui->lbl->setText(solutionstr);
        first_number = 0;
        expression = "";
        last_operand = "";
    } else if(last_operand == "/"){
        first_number = first_number/ui->lbl->text().toDouble();
        solutionstr = QString::number(first_number, 'g', 15);
        ui->label->setText(expression.append(ui->lbl->text()));
        ui->lbl->setText(solutionstr);
        first_number = 0;
        expression = "";
        last_operand = "";
    }
}




