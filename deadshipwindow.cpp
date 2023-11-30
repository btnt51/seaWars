#include "deadshipwindow.h"
#include "ui_deadshipwindow.h"

#include <QStandardItemModel>

deadShipWindow::deadShipWindow(QVector<Ship *> shipList, Ship *deadShip,
                   QWidget *parent) :
    QDialog(parent),
    _shipsList(shipList), _deadShip(deadShip),
    ui(new Ui::deadShipWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Последний шанс");
    QString text = "Команда " + this->_deadShip->getName() + " терпит крушение,"
                                                             "\nкто-нибудь хочет им помочь?";
    ui->msg->setText(text);
    for(auto &el :_shipsList)
        addItem(el);
}

deadShipWindow::~deadShipWindow()
{
    delete ui;
}

void deadShipWindow::on_buttonBox_accepted() {
    getShip()->sendLife(this->_deadShip);
}

void deadShipWindow::addItem(Ship *ship) {
    QStandardItemModel *model = qobject_cast< QStandardItemModel * >( ui->aliveShipsBox->model() );
    QStandardItem *newItem = new QStandardItem();
    newItem->setData(ship->getName(), Qt::DisplayRole );
    newItem->setData(QVariant::fromValue(ship), Qt::UserRole+1);
    model->appendRow( newItem );
}

Ship *deadShipWindow::getShip() {
    int index = ui->aliveShipsBox->currentIndex();
    QStandardItemModel *model = qobject_cast< QStandardItemModel * >(ui->aliveShipsBox->model() );
    QStandardItem *item = model->item( index );
   // name = item ->data( name, Qt::DisplayRole ).toString();
   // userData = item ->data( Qt::UserRole ).toString();
    return item->data(Qt::UserRole+1).value<Ship*>();
}

