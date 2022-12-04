#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include "game.h"
#include "shipname.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
      MainWindow(QWidget *parent = nullptr);
      ~MainWindow();

protected:
      virtual void resizeEvent(QResizeEvent *) override;

private slots:
      void on_fieldTable_cellClicked(int row, int column);

      void on_placeBut_clicked();

      void updateTimer();

      void initializeUI();

      void initializeFieldTable();

      void initializeCommandsTable();

      void initializeLayout();

      void initializeTimers();

      void initializePposkLogo();

      void on_shootBut_clicked();

      void on_timerBut_clicked();

      void updateCommandShip(Ship* ship);

      void updateDeadShip(Ship* ship);

      void on_commandsTable_cellClicked(int row, int column);

      QString convertCoordinates(std::tuple<int, int> pair);

      QPair<int, int> convertCoordinates(QString coordinates);

      QColor* getColor();

      void setNameQstring(QString);

      void setNameAndCoordinates(QString, QString);

      void on_addShipBut_clicked();

      void clearBackgroundFieldsTable();

      void calculateLifes();

private:
      void setShip(size_t row, size_t column, Ship *ship);

      Ship *getShip(size_t row, size_t column);

private:
      Ui::MainWindow *ui;
      Game* _game;
      QImage* _anchor;
      QPixmap* _pposkLogo;
      QTime* _time;
      QTimer* _timer;

      QString _shipNameString;

      QVector<Ship*> _ships;

      QVector<QPair<int, int>> _blackList;

      QVector<QColor*> _colorList;

      QString _coordinates;

      ShipName* _shipForm;

      int _amountOfShots;

      QSize defSize;


};
#endif // MAINWINDOW_H
