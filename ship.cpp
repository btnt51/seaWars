#include "ship.h"
#include <QDebug>

Ship::Ship(QString name, int row, int column, QColor *clr) :
    _name(name), _row(row), _column(column)
{
    _lifes = 5;
    if(clr)
        _color = clr;
    else
        assert((clr != nullptr) && "columnou must set collor");
}

Ship::~Ship()
{
    delete _color;
    _color = nullptr;
}

void Ship::setName(QString name)
{

}

void Ship::setCoordinat(int row, int column)
{

}

void Ship::setDeadCondition(bool isDead)
{

}

void Ship::setAmmountOfLifes(unsigned int amountOfLifes)
{

}

void Ship::addLifes()
{

}

void Ship::sendLife()
{

}

void Ship::subLifes(int amountOfSubsLifes)
{

}

void Ship::setHitStatus(bool hitStatus)
{

}

std::tuple<int, int> Ship::getCoordinats()
{
    qDebug() << this;
    return std::make_tuple(this->_row, this->_column);
}

QString Ship::getName()
{
    return this->_name;
}

unsigned int Ship::getAmountOfLifes()
{
    return this->_lifes;
}

bool Ship::getAliveStatus()
{
    return this->_isDead;
}

bool Ship::getHitStatus()
{
    return this->_isHitted;
}


