#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

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

  void updateCommandShip(Ship *ship);

private:
  void setShip(size_t row, size_t column, Ship *ship);

  Ship *getShip(size_t row, size_t column);

private:
  Ui::MainWindow *ui;
  Game *game;
  QPixmap *anchor;
  QPixmap *pposkLogo;
  QTime *time;
  QTimer *timer;

  QVector<Ship*> _ships;
};
#endif // MAINWINDOW_H
