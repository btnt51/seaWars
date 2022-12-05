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
  QUESTION,
  SHOT,
  TIMER, //When starting timer
  END
};

class Game : public QObject
{
  Q_OBJECT
public:
  Game();

  void placeShip(Ship *ship);

  Field *getField();

  void StartingTimer();

  std::tuple<int, int> getRandomValueForXY(QVector<QPair<int, int> > blackList);

  std::tuple<int, int> getRandomValueForXY();

  void setGameState(EGameState gameState);

  EGameState getGameState();

  void clearThisRoundShots();

signals:
  void sendUpdatedShipToTable(Ship *ship);

public slots:
  void getUpdatedShip(Ship *ship);

  void getDeadShip(Ship *ship);


private:
  Field *_field;

  EGameState _currentState;

  QVector<QPair<int, int> > thisRoundShots;

};

#endif // GAME_H
