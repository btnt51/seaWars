#include "winnerwindow.h"
#include "ui_winnerwindow.h"
#include <QDebug>

WinnerWindow::WinnerWindow(QVector<Ship *> shipList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinnerWindow)
{
    ui->setupUi(this);
    QStringList headerName = {"Позиция", "Номер судна", "Название судна", "Количество жизней"};
    ui->resTable->setHorizontalHeaderLabels(headerName);
    ui->resTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->resTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->buttonBox->setCenterButtons(true);
    int k = 1;
    for(auto *ship : shipList) {
        ui->resTable->insertRow(ui->resTable->rowCount());

        QString str[] = { QString::number(ship->getNumber() + 1),
                          ship->getName(),
                          QString::number(ship->getAmountOfLifes())};

        int rowComTab = ui->resTable->rowCount()-1;
        qDebug() << rowComTab;
        Qt::ItemFlags flags;
        ui->resTable->setItem(rowComTab, 0, new QTableWidgetItem(QString::number(k)));
        flags = ui->resTable->item(rowComTab, 0)->flags();
        ui->resTable->item(rowComTab, 0)->setFlags(flags ^ Qt::ItemIsEditable);

        for (int i = 0; i < 3; ++i) {
            ui->resTable->setItem(rowComTab, i+1, new QTableWidgetItem(str[i]));
            flags = ui->resTable->item(rowComTab, i+1)->flags();
            ui->resTable->item(rowComTab, i+1)->setFlags(flags ^ Qt::ItemIsEditable);
        }
        k++;
    }
}

WinnerWindow::~WinnerWindow()
{
    delete ui;
}
