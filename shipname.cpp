#include "shipname.h"
#include "ui_shipname.h"
#include <QDebug>

ShipName::ShipName(bool withCoordinates, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShipName)
{
    ui->setupUi(this);
    this->_withCordinates = withCoordinates;
    if (!withCoordinates) {
        ui->rowShipLineEdit->setVisible(false);
        ui->rowShipLabel->setVisible(false);
        ui->columnShipLineEdit->setVisible(false);
        ui->columnShipLabel->setVisible(false);
    }
}

ShipName::~ShipName() {
    delete ui;
}

void ShipName::on_buttonBox_accepted() {
    if (this->_withCordinates) {
        emit sendShipWithCoordinates(ui->nameShipLineEdit->text(),
                      ui->rowShipLineEdit->text() + ui->columnShipLineEdit->text());
    } else {
        qDebug() << "I was here";
        emit sendShipName(ui->nameShipLineEdit->text());
    }
    ui->nameShipLineEdit->clear();
    ui->rowShipLineEdit->clear();
    ui->columnShipLineEdit->clear();
}

