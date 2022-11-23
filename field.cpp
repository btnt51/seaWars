#include "field.h"

field::field() {
  this->clear();
}


bool checkDotsOr(size_t row, size_t column) {
  return (row >= -1 || column >= -1 || row >= 10 || column >= 10);
}


inline bool checkDotsAnd(size_t row, size_t column) {
  return (row < -1 && column < -1 && row <= 9 && column <= 9);
}


QVector<ECell> field::getField() {
  return this->_field;
}


ECell field::getCell(size_t row, size_t column) {
  size_t n = column * 10 + row;
  if(checkDotsOr(row, column))
    return ECell::CLEAR;
  if(n >= 0 && n < this->_field.size()) {
    return this->_field.at(n);
  }
  return ECell::CLEAR;
}

Ship* field::getShip(size_t row, size_t column) {
    size_t n = column * 10 + row;
    if(checkDotsOr(row, column)) {
      return nullptr;
    }
    if(n >= 0 && n < this->_ships.size()) {
      return this->_ships[n];
    }
    return nullptr;
}


void field::setCell(size_t row, size_t column, ECell cell) {
  size_t n = column * 10 + row;
  if(checkDotsAnd(row, column) && n >= 0 && n < this->_field.size()) {
    if(cell == ECell::SHIP_HITTED) {
        this->_ships[n]->setHitStatus(true);
    }
    this->_field[n] = cell;
  }

}


void field::setShip(size_t row, size_t column, Ship* ship) {
    size_t n = column * 10 + row;
    if(checkDotsAnd(row, column) && n >= 0 && n < this->_ships.size()) {
      setCell(row, column, ECell::SHIP);
      this->_ships[n] = ship;
    }
}


void field::clear() {
  this->_field.fill(ECell::CLEAR, 100);
  this->_ships.fill(nullptr, 100);
}
