/**
 * @file shipname.h
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief файл содержащий класс, отвечающий за окно добавления нового судна
 * @version 0.1
 * @date 2023-02-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SHIPNAME_H
#define SHIPNAME_H

#include <QDialog>
#include <QIntValidator>

namespace Ui {
    class ShipName;
    }

/// @brief класс, отвечающий за окно добавления нового судна
class ShipName : public QDialog
{
    Q_OBJECT

public:
    /// @brief конструктор окна добавления нового судна
    /// @param withCoordinates тип окна true - с координатами, false - без координат
    /// @param parent указатель на родительский виджет (окно), 
    ///               используется для управления памятью и контроле в модальных окнах
    explicit ShipName(bool withCoordinates = false, QWidget *parent = nullptr);

    /// @brief деструкторк окна добавления нового судна
    ~ShipName();

signals:
    
    /// @brief сигнал добавления судна 
    /// @param name название судна
    void sendShipName(QString name);

    /// @brief сигнал добавления судна 
    /// @param name название судна
    /// @param coordinates коориднаты судна
    void sendShipWithCoordinates(QString name, QString coordinates);

private slots:
    /// @brief функция обработки нажатия на кнопку 
    void on_buttonBox_accepted();

private:
    /// @brief указатель на графический интерфейс
    Ui::ShipName *ui;

    /// @brief тип окна true - с координатами, false - без координат
    bool _withCoordinates;
};

#endif // SHIPNAME_H
