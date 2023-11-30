/**
 * @file editcomtablewindow.h
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief Файл который содержит класс, отвечающий за окно редактирования информации участников в процессе игры в ручном режиме
 * @version 0.1
 * @date 2023-02-02
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef EDITCOMTABLEWINDOW_H
#define EDITCOMTABLEWINDOW_H


#include <QStandardItemModel>
#include <QKeyEvent>
#include <QDialog>
#include <QVector>


#include "ship.h"


namespace Ui {
class EditComTableWindow;
}

/// @brief класс, отвечающий за окно редактирования информации участников в процессе игры в ручном режиме
class EditComTableWindow : public QDialog {
    Q_OBJECT

public:
    /// @brief конструктор окна
    /// @param shiplist список живых судов
    /// @param parent указатель на родительский виджет (окно), 
    ///               используется для управления памятью и контроле в модальных окнах
    explicit EditComTableWindow(QVector<Ship*> shiplist, QWidget *parent = nullptr);
    
    ~EditComTableWindow();

    /// @brief вспомогательная функция, использующаяся для заполнения QComboBox живых судов
    /// @param ship указатель на судно, которое будет помещено в QComboBox живых судов
    void addItem(Ship *ship);

    /// @brief вспомогательная функция, использующаяся для получения выбраного судна в QComboBox живых судов 
    /// @return указатель на судно, которое было выбрано в QComboBox
    Ship* getShip();

protected:
    /// @brief функция обработки нажатия на клавиши, пока окно активно
    /// @param evt указтаель на событие нажатие на клавиши
    void keyPressEvent(QKeyEvent *evt);


private slots:
    /// @brief впомогательная функция обновления графического интерфейса пользователя,
    ///        при выборе другого судна в QComboBox живых судов
    void on_aliveShipsBox_currentIndexChanged(int index);

    /// @brief функция обработки нажатия на кнопку "Возврата" (Return) однострочного текстового блока,
    ///        отвечающее за названия судна
    void on_nameLineEdit_returnPressed();

    /// @brief функция обработки окончания однострочного текстового блока,
    ///        отвечающее за названия судна
    void on_nameLineEdit_editingFinished();

    /// @brief функция обновления однострочного текстового блока, отвечающее за количество жизней у судна
    /// @param указатель на судно, у которой обновилось количество жизней
    void updateLifeLineEdit(Ship* ship);

    /// @brief функция обработки окончания однострочного текстового блока,
    ///        отвечающее за количество жизней судна 
    void on_lifeLineEdit_editingFinished();

    /// @brief функция обработки нажатия на кнопку "Возврата" (Return) однострочного текстового блока,
    ///        отвечающее за количество жизней судна
    void on_lifeLineEdit_returnPressed();

    /// @brief функция обработки нажатия на графическую кнопку добавления одной жизни судну
    void on_addLifeBut_clicked();
    
    /// @brief функция обработки нажатия на графическую кнопку удаление одной жизни судну
    void on_subLifeBut_clicked();

    /// @brief функция обновления отображаемого имени судна в QComboBox
    /// @param name новое имя
    void updateDisplayName(QString name);

private:
    /// @brief указатель на графический интерфейс
    Ui::EditComTableWindow *ui;

    /// @brief список живых судов
    QVector<Ship *> _ships;
};

#endif // EDITCOMTABLEWINDOW_H
