#ifndef FIELD_H
#define FIELD_H

#include "ship.h"
#include <QObject>
#include <QDebug>

enum ECell {
  CLEAR,
  SHIP,
  DEAD_SHIP,
  SHIP_HITTED
};

class field : public QObject {
  Q_OBJECT
public:
  field();

  void setCell(size_t row, size_t column, ECell cell);

  ECell getCell(size_t row, size_t column);

  bool static checkDotsOr(size_t row, size_t column);

  bool static checkDotsAnd(size_t row, size_t column);


  QVector<ECell> getField();




private:
  void clear();

  QVector<ECell> _field;
};

#endif // FIELD_H
