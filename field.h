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

  void setShip(size_t row, size_t column, Ship *ship);

  QVector<ECell> getField();

  Ship *getShip(size_t row, size_t column);


private:
  void clear();

  QVector<ECell> _field;

  QVector<Ship*> _ships;

};

#endif // FIELD_H
