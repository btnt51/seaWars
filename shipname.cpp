#include "shipname.h"
#include "ui_shipname.h"
#include <QDebug>

ShipName::ShipName(bool withCoordinates, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShipName)
{
    ui->setupUi(this);
    this->_withCoordinates = withCoordinates;
    this->setWindowTitle("Расстановка судов");
    this->resize(320, 131);
    //^([1-9]|10)$
    ui->rowShipLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^([1-9]|10)$"), this));
    ui->columnShipLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^[а-кА-К]{0,1}$"), this));
    if (!withCoordinates) {
        this->resize(320, 111);
        ui->rowShipLineEdit->setVisible(false);
        ui->rowShipLabel->setVisible(false);
        //ui->rowShipLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^[10]"), this));
        ui->columnShipLineEdit->setVisible(false);
    }
}

ShipName::~ShipName() {
    delete ui;
}

void ShipName::on_buttonBox_accepted() {
    if (this->_withCoordinates) {
        emit sendShipWithCoordinates(ui->nameShipLineEdit->text(),
                      ui->rowShipLineEdit->text() + ui->columnShipLineEdit->text());
    } else {
        emit sendShipName(ui->nameShipLineEdit->text());
    }
    ui->nameShipLineEdit->clear();
    ui->rowShipLineEdit->clear();
    ui->columnShipLineEdit->clear();
}

