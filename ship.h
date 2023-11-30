/**
 * @file ship.h
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief файл содержащий класс, отвечающий за работу и обработку сущности судна
 * @version 0.1
 * @date 2023-02-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SHIPS_H
#define SHIPS_H

#include <QObject>
#include <QColor>
#include <tuple>

/// @brief класс, отвечающий за работу и обработку сущности судна
class Ship : public QObject
{
    Q_OBJECT
public:
    /// @brief конструктор судна 
    /// @param name название судна
    /// @param row ряд судно
    /// @param column столбец судна
    /// @param clr указатель на цвет судна
    Ship(QString name, int row, int column, QColor *clr = nullptr);

    /// @brief деструктор судна
    ~Ship();

    /// @brief функция-сеттер нового название судна
    /// @param name новое название судна
    void setName(QString name);

    /// @brief функция-сеттер новых координат судна
    /// @param row новый ряд судна
    /// @param column новый столбец судна
    void setCoordinat(int row, int column);

    /// @brief функция-сеттер статуса уничтожения судна 
    /// @param isDead новый статус уничтожения судна true - унчитожен, false - живой
    void setDeadStatus(bool isDead);

    /// @brief функция-сеттер количества жизней судна
    /// @param amountOfLifes новое количество жизней судна
    void setAmmountOfLifes(unsigned int amountOfLifes);

    /// @brief функция добавления жизней судну
    /// @param amountOfAddedLifes количество добавляемых жизней
    void addLifes(unsigned int amountOfAddedLifes = 1);

    /// @brief функция отправки жизней уничтоженному судну (
    ///        отнимает 5 жизни у отпровителя и добавляет 5 жизней уничтоженному судну)
    /// @param deadShip указатель на уничтоженное судно
    void sendLife(Ship* deadShip);

    /// @brief функция отнимания жизней у судна
    /// @param amountOfSubsLifes количество отнимаемых жизней у судна
    void subLifes(int amountOfSubsLifes = 1);

    /// @brief функция-сеттер статуса раненния судна 
    /// @param hitStatus новый статус ранения судна: true - ранен, false - неранен
    void setHitStatus(bool hitStatus);

    /// @brief функция-сеттер статуса данного правильного ответа судном
    /// @param answerStatus новый статус данного правильного ответа судном: true - правильный, false - неправильный
    void setAnswerStatus(bool answerStatus);

    /// @brief функция-геттер коориданат судна
    /// @return кортеж кооридант судна, первое Х, второе Y
    std::tuple<int, int> getCoordinats();

    /// @brief функция-геттер названия судна
    /// @return название судна
    QString getName();

    /// @brief функция-геттер количества жизней судна
    /// @return количество жизней судна
    unsigned int getAmountOfLifes();

    /// @brief функция-геттер статуса уничтожения судна
    /// @return статус уничтожения судна true - унчитожен, false - живой
    bool getDeadStatus();

    /// @brief функция-геттер статуса ранения судна
    /// @return статус ранения судна: true - ранен, false - неранен
    bool getHitStatus();

    /// @brief функция-геттер статуса данного правильного ответа судном
    /// @return статус данного правильного ответа судном: true - правильный, false - неправильный
    bool getAnswerStatus();

    /// @brief функция-геттер порядкового номера судна
    /// @return порядковый номер судна
    int getNumber();

    /// @brief функция-геттер ряда судна
    /// @return ряд судна
    int getRow();

    /// @brief функция-геттер столбца судна
    /// @return столбец судна
    int getColumn();

    /// @brief функция-геттер цвета судна
    /// @return цвет судна
    QColor *getColor();

signals:
    /// @brief сигнал о том что судно уничтожено
    /// @param ship указатель на уничтоженное судно
    void shipIsDead(Ship *ship);

    /// @brief сигнал обновления судна
    /// @param ship указатель на обновленное судно
    void updateShipInfo(Ship *ship);

private:
    /// @brief название судна
    QString _name;

    /// @brief ряд судна
    int _row;

    /// @brief столбец судна
    int _column;

    /// @brief статус уничтожения судна
    bool _isDead;

    /// @brief количество жизней судна
    unsigned int _lifes;

    /// @brief статус данного правильного ответа судна
    bool _isRightAnswer;

    /// @brief статус ранения судна
    bool _isHited;

    /// @brief порядковый номер судна
    int _number;

    /// @brief статическое суммарное колчество судов
    static int amountOfShips;

    /// @brief указатель на цвет судна
    QColor* _color;
};

#endif // SHIPS_H
