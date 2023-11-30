/**
 * @file mainwindow.h
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief Файл который содержит класс, отвечающий за главный экран приложения
 * @version 0.1
 * @date 2023-02-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QResizeEvent>


#include "game.h"
#include "shipname.h"
#include "deadshipwindow.h"
#include "winnerwindow.h"
#include "editcomtablewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/// @brief класс, отвечающий за главный экран приложения
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
      /// @brief конструктор главного экрана
      /// @param parent указатель на родительский виджет (окно), 
      ///               используется для управления памятью и контроле в модальных окнах
      MainWindow(QWidget *parent = nullptr);

      /// @brief деструктор главного экрана
      ~MainWindow();

protected:
      /// @brief перегруженная функция изменения окна
      /// @param event событие изменения экрана
      virtual void resizeEvent(QResizeEvent *event) override;

private slots:
      /// @brief функция обработка нажатия на таблицу
      /// @param row ряд клетки
      /// @param column столбец клетки
      void on_fieldTable_cellClicked(int row, int column);

      /// @brief функция обраобки нажатия на кнопку добавления судна на таблицу
      void on_placeBut_clicked();

      /// @brief функция обновления таймера
      void updateTimer();

      /// @brief вспомогательная функция инициализации графического интерфейса пользователя
      void initializeUI();

      /// @brief вспомогательная функция инциализации таблицы игрового поля
      void initializeFieldTable();

      /// @brief вспомогталельная функция инциализации таблицы команд-участников
      void initializeCommandsTable();

      /// @brief вспомогательная функция инициализации макета
      void initializeLayout();

      /// @brief вспомогательная функция инициализации таймера
      void initializeTimers();

      /// @brief вспомогтаельная функции иницилзации изображения-логотипа ППОСК
      void initializePposkLogo();

      /// @brief функция обработки нажатия на кнопку выстрела
      void on_shootBut_clicked();

      /// @brief функция обработки нажатия на кнопку таймера
      void on_timerBut_clicked();

      /// @brief функция обновления судна
      /// @param ship указатель на судно, которое необходимо обновить
      void updateCommandShip(Ship* ship);

      /// @brief функция обновления уничтоженного судна
      /// @param ship указатель на уничтоженное судно, которое необходимо обновить
      void updateDeadShip(Ship* ship);

      /// @brief функция обработки нажатия на клетку в таблице комманд
      /// @param row ряд клетки
      /// @param column столбец клетки
      void on_commandsTable_cellClicked(int row, int column);

      /// @brief вспомогательная функция конвертации координат из кортежа с целыми числами в строку
      /// @param pair кортеж координат, первое - Х, второе - Y
      /// @return координаты в формате строки
      QString convertCoordinates(std::tuple<int, int> pair);

      /// @brief вспомогательная функция конвертации координат из строки в кортеж с целыми числами 
      /// @param coordinates строка содержащая координаты
      /// @return кортеж координат, первое - Х, второе - Y
      std::tuple<int, int> convertCoordinates(QString coordinates);

      /// @brief функция генерации цвета
      /// @return указатель на цвет
      QColor* getColor();

      /// @brief вспомогтаельная функция для получения названия судна
      /// @param name название судна
      void setNameQstring(QString name);

      /// @brief вспомогтаельная функция для получения названия и координат судна
      /// @param name название судна
      /// @param coordinates координаты судна
      void setNameAndCoordinates(QString name, QString coordinates);

      /// @brief функция обработки нажаия на кнопку добавления судна
      void on_addShipBut_clicked();

      /// @brief вспомогательная функция очистки заднего фона клеток таблиц игрового поля
      void clearBackgroundFieldsTable();

      /// @brief функция подсчета жизней
      void calculateLifes();

      /// @brief функция обработки нажатия на кнопку редактирования судов
      void on_editShipsBut_clicked();

      /// @brief функция обработки нажатия на кнопку конца игры
      void on_endBut_clicked();

private:
      /// @brief функция добавления судна на таблицу игрового поля
      /// @param row ряд судна
      /// @param column столбец судна
      /// @param ship указатель на добавляемое судно
      void setShip(size_t row, size_t column, Ship *ship);

      /// @brief функция получения указателя на судно 
      /// @param row ряд судна
      /// @param column столбец судна
      /// @return указатель на судно
      Ship *getShip(size_t row, size_t column);

private:

      /// @brief указатель на графический интерфейс
      Ui::MainWindow *ui;

      /// @brief указатель на контроллер игры
      Game* _game;

      /// @brief указатель на изображение судна в виде якоря
      QImage* _anchor;

      /// @brief указатель на изображение логотипа ППОСК
      QPixmap* _pposkLogo;

      /// @brief указатель на 
      QTime* _time;

      /// @brief указатель на таймер
      QTimer* _timer;

      /// @brief вспомогательная переменная для получения названия судна из окна добавления судна
      QString _shipNameString;

      /// @brief массив судов
      QVector<Ship*> _ships;

      /// @brief массив координата по которым нельзя стрелять
      QVector<QPair<int, int>> _blackList;

      /// @brief массив используемых цветов
      QVector<QColor*> _colorList;

      /// @brief вспомогателдья переменная для получения координат судна из окна добавления судна
      QString _coordinates;

      /// @brief указатель на окно добавления судна
      ShipName* _shipForm;

      /// @brief количество выстрелов за раунд
      int _amountOfShots;

      /// @brief стандартный размер онка при запуске
      QSize defSize;

      /// @brief функция инициализации кнопок графического интерфейса
      void initializeButtons();

      /// @brief функция установки темной темы графического интерфейса
      void setDarkTheme();
};
#endif // MAINWINDOW_H
