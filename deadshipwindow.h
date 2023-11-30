/**
 * @file deadshipwindow.h
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief Файл который содержит класс, отвечающий за окно-уведомление о том,
 *        что участник выбывает из игры с возможностью возвращаения в игру при помощи других игроков
 * @version 0.1
 * @date 2023-02-02
 *  
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef DEADSHIPWINDOW_H
#define DEADSHIPWINDOW_H

#include "ship.h"

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
    class deadShipWindow;
    }

/// @brief класс, отвечающий за окно-уведомление о том,
///        что участник выбывает из игры с возможностью возвращаения в игру при помощи других игроков
class deadShipWindow : public QDialog
{
    Q_OBJECT

public:
    /// @brief  Конструктор окна
    /// @param shipList список живых судов
    /// @param deadShip указатель на судно выбывшего участника
    /// @param parent указатель на родительский виджет (окно), 
    ///               используется для управления памятью и контроле в модальных окнах
    explicit deadShipWindow(QVector<Ship *> shipList, Ship *deadShip = nullptr, QWidget *parent = nullptr);

    /// 
    ~deadShipWindow();

private slots:
    /// @brief функция обработки нажатия на кнопку "OK"
    void on_buttonBox_accepted();
    
    /// @brief вспомогательная функция, использующаяся для заполнения QComboBox живых судов
    /// @param ship указатель на судно, которое будет помещено в QComboBox живых судов
    void addItem(Ship *ship);

    /// @brief вспомогательная функция, использующаяся для получения выбраного судна в QComboBox живых судов 
    /// @return указатель на судно, которое было выбрано в QComboBox
    Ship* getShip();

private:
    /// @brief указатель на графический интерфейс
    Ui::deadShipWindow *ui;
    /// @brief список живых судов
    QVector<Ship* > _shipsList;
    /// @brief указатель на судно выбывшего участника
    Ship* _deadShip;
};

#endif // DEADSHIPWINDOW_H
