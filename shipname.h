#ifndef SHIPNAME_H
#define SHIPNAME_H

#include <QDialog>

namespace Ui {
    class ShipName;
    }

class ShipName : public QDialog
{
    Q_OBJECT

public:
    explicit ShipName(bool withCoordinates = false, QWidget *parent = nullptr);
    ~ShipName();

signals:
    void sendShipName(QString);

    void sendShipWithCoordinates(QString, QString);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ShipName *ui;
    bool _withCordinates;
};

#endif // SHIPNAME_H