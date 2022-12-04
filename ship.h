#ifndef SHIPS_H
#define SHIPS_H

#include <QObject>
#include <QColor>
#include <tuple>

class Ship : public QObject
{
    Q_OBJECT
public:
    Ship(QString name, int row, int column, QColor *clr = nullptr);

    ~Ship();

    void setName(QString name);

    void setCoordinat(int row, int column);

    void setDeadStatus(bool isDead);

    void setAmmountOfLifes(unsigned int amountOfLifes);

    void addLifes(unsigned int amountOfAddedLifes = 1);

    void sendLife(Ship* deadShip);

    void subLifes(int amountOfSubsLifes = 1);

    void setHitStatus(bool hitStatus);

    void setAnswerStatus(bool answerStatus);

    std::tuple<int, int> getCoordinats();

    QString getName();

    unsigned int getAmountOfLifes();

    bool getDeadStatus();

    bool getHitStatus();

    bool getAnswerStatus();

    int getNumber();

    int getRow();

    int getColumn();

    QColor *getColor();

signals:
    void shipIsDead(Ship *ship);

    void updateShipInfo(Ship *ship);

private:
    QString _name;
    int _row;
    int _column;
    bool _isDead;
    unsigned int _lifes;
    bool _isRightAnswer;
    bool _isHited;
    int _number;
    static int amountOfShips;
    QColor* _color;
};

#endif // SHIPS_H
