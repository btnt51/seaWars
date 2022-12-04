#ifndef WINNERWINDOW_H
#define WINNERWINDOW_H

#include "ship.h"

#include <QDialog>

namespace Ui {
    class WinnerWindow;
    }

class WinnerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WinnerWindow(QVector<Ship *> shipList, QWidget *parent = nullptr);
    ~WinnerWindow();

private:
    Ui::WinnerWindow *ui;
};

#endif // WINNERWINDOW_H
