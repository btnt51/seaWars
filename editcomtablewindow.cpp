#include "editcomtablewindow.h"
#include "ui_editcomtablewindow.h"



EditComTableWindow::EditComTableWindow(QVector<Ship*> shiplist, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditComTableWindow), _ships(shiplist)
{
    ui->setupUi(this);
    for(auto & el : _ships) {
        connect(el, SIGNAL(updateShipInfo(Ship*)), this, SLOT(updateLifeLineEdit(Ship*)));
        addItem(el);
    }
    this->setWindowTitle("Редактирование таблицы");
}

EditComTableWindow::~EditComTableWindow() {
    delete ui;
}

void EditComTableWindow::addItem(Ship *ship) {
    QStandardItemModel *model = qobject_cast< QStandardItemModel * >( ui->aliveShipsBox->model() );
    QStandardItem *newItem = new QStandardItem();
    newItem->setData(ship->getName(), Qt::DisplayRole );
    newItem->setData(QVariant::fromValue(ship), Qt::UserRole+1);
    model->appendRow( newItem );

}

Ship *EditComTableWindow::getShip() {
    int index = ui->aliveShipsBox->currentIndex();
    QStandardItemModel *model = qobject_cast< QStandardItemModel * >(ui->aliveShipsBox->model() );
    QStandardItem *item = model->item( index );
   // name = item ->data( name, Qt::DisplayRole ).toString();
   // userData = item ->data( Qt::UserRole ).toString();
    return item->data(Qt::UserRole+1).value<Ship*>();
}

void EditComTableWindow::keyPressEvent(QKeyEvent *evt) {
    if(evt->key() == Qt::Key_Enter || evt->key() == Qt::Key_Return)
        return;
    QDialog::keyPressEvent(evt);
}


void EditComTableWindow::on_aliveShipsBox_currentIndexChanged(int index) {
    QStandardItemModel *model = qobject_cast< QStandardItemModel * >(ui->aliveShipsBox->model() );
    QStandardItem *item = model->item( index );
    auto * ship = item->data(Qt::UserRole+1).value<Ship*>();
    ui->nameLineEdit->setText(ship->getName());
    ui->lifeLineEdit->setText(QString::number(ship->getAmountOfLifes()));
}


void EditComTableWindow::on_nameLineEdit_returnPressed() {
    updateDisplayName(ui->nameLineEdit->text());
    this->getShip()->setName(ui->nameLineEdit->text());
}


void EditComTableWindow::on_nameLineEdit_editingFinished() {
    updateDisplayName(ui->nameLineEdit->text());
    this->getShip()->setName(ui->nameLineEdit->text());
}

void EditComTableWindow::updateLifeLineEdit(Ship *ship) {
    if(ui->aliveShipsBox->currentText() == ship->getName()) {
        ui->lifeLineEdit->setText(QString::number(ship->getAmountOfLifes()));
    }
}


void EditComTableWindow::on_lifeLineEdit_editingFinished() {
    this->getShip()->setAmmountOfLifes(ui->lifeLineEdit->text().toInt());
}


void EditComTableWindow::on_lifeLineEdit_returnPressed() {
    this->getShip()->setAmmountOfLifes(ui->lifeLineEdit->text().toInt());
}


void EditComTableWindow::on_addLifeBut_clicked() {
    this->getShip()->addLifes();
}


void EditComTableWindow::on_subLifeBut_clicked() {
    this->getShip()->subLifes();
}

void EditComTableWindow::updateDisplayName(QString name) {
    int index = ui->aliveShipsBox->currentIndex();
    QStandardItemModel *model = qobject_cast< QStandardItemModel * >(ui->aliveShipsBox->model() );
    QStandardItem *item = model->item( index );
    item->setData(name, Qt::DisplayRole);
}

