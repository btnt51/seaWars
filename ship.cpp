#include "ship.h"
#include <QDebug>

int Ship::amountOfShips = 0;

Ship::Ship(QString name, int row, int column, QColor *clr) :
    _name(name), _row(row), _column(column)
{
    this->_number = amountOfShips;
    this->amountOfShips++;
    this->_isRightAnswer = false;
    this->_isDead = false;
    this->_isHited = false;
    this->_lifes = 5;
    if(clr)
        this->_color = clr;
    else
        assert((clr != nullptr) && "columnou must set collor");
}

Ship::~Ship() {
    delete _color;
    _color = nullptr;
}

void Ship::setName(QString name) {
    this->_name = name;
}

void Ship::setCoordinat(int row, int column) {
    this->_row = row;
    this->_column = column;
}

void Ship::setDeadStatus(bool isDead) {
    this->_isDead = isDead;
    if(isDead)
        emit shipIsDead(this);
}

void Ship::setAmmountOfLifes(unsigned int amountOfLifes) {
    this->_lifes = amountOfLifes;
    if(this->_lifes == 0) {
        this->setDeadStatus(true);
    }
}

void Ship::addLifes(unsigned int amountOfAddedLifes) {
    this->_lifes += amountOfAddedLifes;
    emit updateShipInfo(this);
}

void Ship::sendLife(Ship *deadShip) {
    this->subLifes(5);
    deadShip->addLifes(5);
}

void Ship::subLifes(int amountOfSubsLifes) {
    if(this->_lifes == 0)
        return;
    this->_lifes -= amountOfSubsLifes;
    emit updateShipInfo(this);
    if(this->_lifes == 0) {
        this->setDeadStatus(true);
    }
}

void Ship::setHitStatus(bool hitStatus) {

    this->_isHited = hitStatus;

}

void Ship::setAnswerStatus(bool answerStatus) {
    qDebug() << this->getName() << " old answer status" << this->getAnswerStatus();
    this->_isRightAnswer = answerStatus;
    qDebug() << this->getName() << " new answer status" << this->getAnswerStatus();
}

std::tuple<int, int> Ship::getCoordinats() {
    return std::make_tuple(this->_row, this->_column);
}

QString Ship::getName() {
    return this->_name;
}

unsigned int Ship::getAmountOfLifes() {
    return this->_lifes;
}

bool Ship::getDeadStatus() {
    return this->_isDead;
}

bool Ship::getHitStatus() {
    return this->_isHited;
}

bool Ship::getAnswerStatus() {
    return this->_isRightAnswer;
}

int Ship::getNumber() {
    return this->_number;
}

int Ship::getRow() {
    return this->_row;
}

int Ship::getColumn() {
    return this->_column;
}

QColor *Ship::getColor() {
    return this->_color;
}


