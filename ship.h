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

    void setDeadCondition(bool isDead);

    void setAmmountOfLifes(unsigned int amountOfLifes);

    void addLifes(unsigned int amountOfAddedLifes = 1);

    void sendLife(Ship* deadShip);

    void subLifes(int amountOfSubsLifes = 1);

    void setHitStatus(bool hitStatus);

    std::tuple<int, int> getCoordinats();

    QString getName();

    unsigned int getAmountOfLifes();

    bool getAliveStatus();

    bool getHitStatus();

    int getNumber();

signals:
    void shipIsDead(Ship *ship);

    void updateShipInfo(Ship *ship);

private:
    QString _name;
    int _row;
    int _column;
    bool _isDead;
    unsigned int _lifes;
    bool _isHitted;
    int _number;
    static int amountOfShips;
    QColor *_color;

};

#endif // SHIPS_H
