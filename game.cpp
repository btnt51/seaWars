#include "game.h"

Game::Game(int shots, QTimer *timer) {
    this->_Field = new field();
    if(shots == 0) {
        this->_shots = 10;
    } else {
        this->_shots = shots;
    }

    if(timer == nullptr) {
        this->_timer = new QTimer();
    } else {
        this->_timer = timer;
    }
    this->_currentState = EGameState::NOTSTARTED;
}


void Game::placeShip(Ship *ship) {
    int x = 0;
    int y = 0;
    std::tie(x, y) = ship->getCoordinats();
    this->_Field->setShip(x, y, ship);
}


field* Game::getField() {
  return this->_Field;
}


void Game::StartingTimer() {

}


std::tuple<int, int> Game::getRandomValueForXY() {
    int x = static_cast<int>(QRandomGenerator::global()->bounded(1,11));
    int y = static_cast<int>(QRandomGenerator::global()->bounded(1,11));
    while(true) {
        if(this->_Field->getCell(x, y) != ECell::SHIP_HITTED) {
           break;
        }
        x = static_cast<int>(QRandomGenerator::global()->bounded(1,11));
        y = static_cast<int>(QRandomGenerator::global()->bounded(1,11));
    }
    return std::make_tuple(x, y);
}


void Game::RandomShot() {
    for(int i = 0; i < this->_shots; ++i) {
        int x = 0, y = 0;
        std::tie(x, y) = getRandomValueForXY();
        if(this->_Field->getCell(x, y) == ECell::CLEAR || this->_Field->getCell(x, y) == ECell::SHIP) {
            if(this->_Field->getCell(x, y) == ECell::SHIP) {
                //this->_Field->setCell(x, y, ECell::FIRED);
                this->_Field->getShip(x, y)->setHitStatus(true);
                //this->
            }
        }
    }
}


void Game::setGameState(EGameState gameState) {
    this->_currentState = gameState;
}


EGameState Game::getGameState() {
    return this->_currentState;
}
