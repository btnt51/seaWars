#include "game.h"

Game::Game() {
    this->_field = new Field();

    this->_currentState = EGameState::NOTSTARTED;
}


void Game::placeShip(Ship *ship) {
    int row = 0;
    int column = 0;
    //std::tie(row, column) = ship->getCoordinats();
    //this->_Field->setShip(row, column, ship);
    //connect(ship, SIGNAL(updateShipInfo(Ship*)), this, SLOT(getUpdatedShip(Ship *ship)));
    //ship->subLifes();
}


Field* Game::getField() {
  return this->_field;
}


void Game::StartingTimer() {

}

QPair<int, int> Game::getRandomValueForXY() {
    int x = static_cast<int>(QRandomGenerator::global()->bounded(0, 10));
    int y = static_cast<int>(QRandomGenerator::global()->bounded(0, 10));
    while(true) {
        if(this->_field->getCell(x, y) != ECell::SHIP) {
           break;
        }

        x = static_cast<int>(QRandomGenerator::global()->bounded(0, 10));
        y = static_cast<int>(QRandomGenerator::global()->bounded(0, 10));
    }
    return qMakePair(x, y);
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

QPair<int, int> Game::getRandomValueForXY(QVector<QPair<int, int> > blackList) {
    int x = static_cast<int>(QRandomGenerator::global()->bounded(0, 10));
    int y = static_cast<int>(QRandomGenerator::global()->bounded(0, 10));
    while(true) {
        if(this->_field->getCell(x, y) != ECell::SHIP_HITED && checkPair(blackList, qMakePair(x, y))) {
           break;
        }

        x = static_cast<int>(QRandomGenerator::global()->bounded(0, 10));
        y = static_cast<int>(QRandomGenerator::global()->bounded(0, 10));
    }
    return qMakePair(x, y);
}


//void Game::RandomShot() {
//    for(int i = 0; i < this->_shots; ++i) {
//        int x = 0, y = 0;
//        std::tie(x, y) = getRandomValueForXY();
//        if(this->_Field->getCell(x, y) == ECell::CLEAR || this->_Field->getCell(x, y) == ECell::SHIP) {
//            if(this->_Field->getCell(x, y) == ECell::SHIP) {
//                //this->_Field->setCell(x, y, ECell::FIRED);
//                //this->_Field->getShip(x, y)->setHitStatus(true);
//                //this->
//            }
//        }
//    }
//}


void Game::setGameState(EGameState gameState) {
    this->_currentState = gameState;
}


EGameState Game::getGameState() {
    return this->_currentState;
}

void Game::getUpdatedShip(Ship *ship) {
    emit sendUpdatedShipToTable(ship);
}

void Game::getDeadShip(Ship *ship) {

}
