/**
 * @file game.h
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief Файл который содержит перечисление EGameState и класс Game, отвечающий за контроль и управление игрой.
 * @version 0.1
 * @date 2023-02-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QTimer>
#include <QRandomGenerator>
#include "field.h"

/// @brief перечисление отвечающее за состоянии/стадии игры. Может принимать значения:
///        NOTSTARTED - игра еще не стартовала, START - начало игры, 
///        PLACING_SHIPS - стадия растоновки игры, GAME - стадия игры, 
///        QUESTION - стадия задания вопроса, SHOT - стадия выстрела, 
///        TIMER - стадия работы таймера, END - конец игры.
enum EGameState {
  NOTSTARTED,
  START,
  PLACING_SHIPS,
  GAME,
  QUESTION,
  SHOT,
  TIMER, 
  END
};

/// @brief класс отвечающий за состояние и управление ходом игры
class Game : public QObject
{
  Q_OBJECT
public:
  /// @brief конструктор контролера игры
  Game();

  /// @brief функция-геттер игрового поля
  /// @return указатель на игровое поле
  Field *getField();

  /// @brief функция генерации кортежа координат
  /// @return кортеж коориднат, первое - Х, второе - Y
  std::tuple<int, int> getRandomValueForXY();

  /// @brief функция генерации коориданат для выстрелов
  /// @param blackList массив координат, по которым нельзя стрелять
  /// @return кортеж коориднат, первое - Х, второе - Y
  std::tuple<int, int> getRandomValueForXY(QVector<QPair<int, int> > blackList);

  /// @brief функция-сеттер текущего состояния/стадии игры
  /// @param gameState новое состояние/стадии игры
  void setGameState(EGameState gameState);

  /// @brief функция-геттер текущего состояния/стадии игры
  /// @return текущее состояние игры
  EGameState getGameState();

  /// @brief вспомогательная функция очистики массива координат выстрелов в текущем раунде
  void clearThisRoundShots();

signals:
  /// @brief сигнал обновления судна 
  void sendUpdatedShipToTable(Ship *ship);

public slots:
  /// @brief функция пересылки сигнала обновления судна
  void getUpdatedShip(Ship *ship);



private:
  /// @brief указатель на игровое поле
  Field *_field;

  /// @brief текущее состояние игры
  EGameState _currentState;

  /// @brief массив координат выстрелов в текущем раунде
  QVector<QPair<int, int> > thisRoundShots;

};

#endif // GAME_H
