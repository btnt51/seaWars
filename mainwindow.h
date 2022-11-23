#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
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
//  void on_fieldTable_cellDoubleClicked(int row, int column);

//  void on_fieldTable_cellActivated(int row, int column);

  void on_fieldTable_cellClicked(int row, int column);

  void on_placeBut_clicked();

private:
  Ui::MainWindow *ui;
  Game *game;
  QPixmap *anchor;
};
#endif // MAINWINDOW_H
