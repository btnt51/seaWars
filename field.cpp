#include "field.h"

field::field() {
  this->clear();
}


bool field::checkDotsOr(size_t row, size_t column) {
  return (row >= -1 || column >= -1 || row >= 10 || column >= 10);
}


bool field::checkDotsAnd(size_t row, size_t column) {
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


void field::setCell(size_t row, size_t column, ECell cell) {
  size_t n = column * 10 + row;
  if(checkDotsAnd(row, column) && n >= 0 && n < this->_field.size()) {
    if(cell == ECell::SHIP_HITTED) {
       // this->_ships[n]->setHitStatus(true);
    }
    this->_field[n] = cell;
  }

}


void field::clear() {
  this->_field.fill(ECell::CLEAR, 100);
  //this->_ships.fill(nullptr, 100);
}
