#ifndef EDITCOMTABLEWINDOW_H
#define EDITCOMTABLEWINDOW_H


#include <QDialog>
#include <QVector>
#include <QStandardItemModel>

#include "ship.h"


namespace Ui {
class EditComTableWindow;
}

class EditComTableWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditComTableWindow(QVector<Ship*> shiplist, QWidget *parent = nullptr);
    ~EditComTableWindow();

    void addItem(Ship *);

    Ship* getShip();

protected:
    void keyPressEvent(QKeyEvent *evt);


private slots:
    void on_aliveShipsBox_currentIndexChanged(int index);

    void on_nameLineEdit_returnPressed();

    void on_nameLineEdit_editingFinished();

    void updateLifeLineEdit(Ship*);

    void on_lifeLineEdit_editingFinished();

    void on_lifeLineEdit_returnPressed();

    void on_addLifeBut_clicked();

    void on_subLifeBut_clicked();


    void updateDisplayName(QString name);
private:
    Ui::EditComTableWindow *ui;
    QVector<Ship *> _ships;
};

#endif // EDITCOMTABLEWINDOW_H
