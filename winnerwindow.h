/**
 * @file winnerwindow.h
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief файл содержащий класс, отвечающий за окно с итоговой таблицей судов
 * @version 0.1
 * @date 2023-02-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef WINNERWINDOW_H
#define WINNERWINDOW_H

#include "ship.h"

#include <QDialog>

namespace Ui {
    class WinnerWindow;
    }

/// @brief класс, отвечающий за окно с итоговой таблицей судов
class WinnerWindow : public QDialog
{
    Q_OBJECT

public:
    /// @brief конструктор окна с итоговой таблицей судов
    /// @param shipList список судов
    /// @param parent указатель на родительский виджет (окно), 
    ///               используется для управления памятью и контроле в модальных окнах
    explicit WinnerWindow(QVector<Ship *> shipList, QWidget *parent = nullptr);

    /// @brief деструктор окна с истоговой таблицей судов
    ~WinnerWindow();

private:
    /// @brief указатель на графический интерфейс
    Ui::WinnerWindow *ui;
};

#endif // WINNERWINDOW_H
