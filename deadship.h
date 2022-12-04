#ifndef DEADSHIP_H
#define DEADSHIP_H

#include "ship.h"

#include <QDialog>

namespace Ui {
    class deadShip;
    }

class deadShip : public QDialog
{
    Q_OBJECT

public:
    explicit deadShip(QVector<Ship *> shipList, Ship *deadShip = nullptr, QWidget *parent = nullptr);
    ~deadShip();

private slots:
    void on_buttonBox_accepted();

    void addItem(Ship *);

    Ship* getShip();

private:
    Ui::deadShip *ui;
    QVector<Ship* > _shipsList;
    Ship* _deadShip;
};

#endif // DEADSHIP_H
