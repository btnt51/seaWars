#include "field.h"

Field::Field() {
  this->clear();
}


bool Field::checkDotsOr(size_t row, size_t column) {
  return (row >= -1 || column >= -1 || row >= 10 || column >= 10);
}


bool Field::checkDotsAnd(size_t row, size_t column) {
  return (row < -1 && column < -1 && row <= 9 && column <= 9);
}


QVector<ECell> Field::getField() {
  return this->_field;
}


ECell Field::getCell(size_t row, size_t column) {
  size_t n = column * 10 + row;
  if(checkDotsOr(row, column))
    return ECell::CLEAR;
  if(n >= 0 && n < this->_field.size()) {
    return this->_field.at(n);
  }
  return ECell::CLEAR;
}


void Field::setCell(size_t row, size_t column, ECell cell) {
  size_t n = column * 10 + row;
  if(checkDotsAnd(row, column) && n >= 0 && n < this->_field.size()) {
    if(cell == ECell::SHIP_HITED) {
       // this->_ships[n]->setHitStatus(true);
    }
    this->_field[n] = cell;
  }

}


void Field::clear() {
  this->_field.fill(ECell::CLEAR, 100);
  //this->_ships.fill(nullptr, 100);
}
