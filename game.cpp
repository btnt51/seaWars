#include "game.h"

Game::Game() {
    this->_field = new Field();

    this->_currentState = EGameState::NOTSTARTED;
}


Field* Game::getField() {
  return this->_field;
}


bool checkPair(QVector<QPair<int, int>> blackList, QPair<int, int> pair) {
    bool res = true;
    for(auto el : blackList) {
        if(el == pair) {
            res = false;
            break;
        }
    }
    return res;
}


std::tuple<int, int> Game::getRandomValueForXY() {
    int x = static_cast<int>(QRandomGenerator::global()->bounded(0, 10));
    int y = static_cast<int>(QRandomGenerator::global()->bounded(0, 10));
    while(true) {
        if(this->_field->getCell(x, y) != ECell::SHIP && checkPair(thisRoundShots, qMakePair(x, y))) {
           break;
        }

        x = static_cast<int>(QRandomGenerator::global()->bounded(0, 10));
        y = static_cast<int>(QRandomGenerator::global()->bounded(0, 10));
    }
    thisRoundShots.push_back(qMakePair(x, y));
    return std::make_tuple(x, y);
}



std::tuple<int, int> Game::getRandomValueForXY(QVector<QPair<int, int> > blackList) {
    int x = static_cast<int>(QRandomGenerator::global()->bounded(0, 10));
    int y = static_cast<int>(QRandomGenerator::global()->bounded(0, 10));
    while(true) {
        if (this->_field->getCell(x, y) != ECell::SHIP_HITED && checkPair(blackList, qMakePair(x, y))
                && checkPair(thisRoundShots, qMakePair(x, y))) {
           break;
        }

        x = static_cast<int>(QRandomGenerator::global()->bounded(0, 10));
        y = static_cast<int>(QRandomGenerator::global()->bounded(0, 10));
    }
    thisRoundShots.push_back(qMakePair(x, y));
    return std::make_tuple(x, y);
}


void Game::setGameState(EGameState gameState) {
    this->_currentState = gameState;
}


EGameState Game::getGameState() {
    return this->_currentState;
}


void Game::clearThisRoundShots() {
    this->thisRoundShots.clear();
}


void Game::getUpdatedShip(Ship *ship) {
    emit sendUpdatedShipToTable(ship);
}
