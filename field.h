/**
 * @file field.h
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief Файл который содержит перечисление ECell и класс Field, отвечающий за игровое поле.
 * @version 0.1
 * @date 2023-02-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef FIELD_H
#define FIELD_H

#include "ship.h"
#include <QObject>
#include <QDebug>

/// @brief Перечисление отвечающее за тип клетки. Может принимать значения,
///        CLEAR - пустая клетка, SHIP - в клетке судно, 
///        DEAD_SHIP - в клетке уничтоженное судно, SHIP_HITED - в клетке подбитое судно
enum ECell {
  CLEAR,
  SHIP,
  DEAD_SHIP,
  SHIP_HITED
};

/// @brief класс-обёртка над массивом клеток игрового поля
class Field : public QObject {
  Q_OBJECT
public:
  /// @brief конструктор поля 
  Field();

  /// @brief функция-сеттер типа клетки
  /// @param row ряд клетки
  /// @param column столбец клетки
  /// @param cell новое значение клетки
  void setCell(size_t row, size_t column, ECell cell);

  /// @brief функция-геттер типа клетки
  /// @param row ряд клетки
  /// @param column столбец клетки
  /// @return тип клетки
  ECell getCell(size_t row, size_t column);

  /// @brief вспомогательная функция проверки клетки с использованием логического "ИЛИ"
  /// @param row ряд клетки
  /// @param column столбец клетки
  /// @return true, если клетка в пределах игрового поля иначе false
  bool static checkDotsOr(size_t row, size_t column);

  /// @brief вспомогательная функция проверки клетки с использованием логического "И"
  /// @param row ряд клетки
  /// @param column столбец клетки
  /// @return true, если клетка в пределах игрового поля иначе false
  bool static checkDotsAnd(size_t row, size_t column);

  /// @brief функция-геттер массива клеток
  /// @return массив клеток
  QVector<ECell> getField();


private:
  /// @brief вспомогательная функция очистки массива клеток
  void clear();

  /// @brief массив клеток
  QVector<ECell> _field;
};

#endif // FIELD_H
