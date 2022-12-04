#include "winnerwindow.h"
#include "ui_winnerwindow.h"

WinnerWindow::WinnerWindow(QVector<Ship *> shipList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinnerWindow)
{
    ui->setupUi(this);
    QString text;
    text += "Тройка победителей!";
    text += "\n 1. " + shipList[0]->getName();
    text += "\n 2. " + shipList[1]->getName();
    text += "\n 3. " + shipList[2]->getName();
    ui->label->setText(text);
}

WinnerWindow::~WinnerWindow()
{
    delete ui;
}
