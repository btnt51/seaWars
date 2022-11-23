#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QTimer>
#include <QRandomGenerator>
#include "field.h"

enum EGameState {
  NOTSTARTED,
  START,
  PLACING_SHIPS,
  GAME,
  PAUSE, //When starting timer
  END
};

class Game : public QObject
{
  Q_OBJECT
public:
  Game(int shots = 10, QTimer *timer = nullptr);

  void placeShip(Ship *ship);

  field *getField();

  void StartingTimer();

  void RandomShot();

  void setGameState(EGameState gameState);

  EGameState getGameState();

private:
  field *_Field;

  EGameState _currentState;

  QTimer *_timer;

  int _shots;

  std::tuple<int, int> getRandomValueForXY();

  QVector<QPair<int, int> > blackListOfCordinates;
};

#endif // GAME_H