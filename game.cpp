#include "game.h"

Game::Game() {
    this->_field = new Field();

    this->_currentState = EGameState::NOTSTARTED;
}


void Game::placeShip(Ship *ship) {
    int row = 0;
    int column = 0;
}


Field* Game::getField() {
  return this->_field;
}


void Game::StartingTimer() {

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

void Game::clearThisRoundShots() {
    this->thisRoundShots.clear();
}

void Game::getUpdatedShip(Ship *ship) {
    emit sendUpdatedShipToTable(ship);
}

void Game::getDeadShip(Ship *ship) {

}
