#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    defSize = this->size();

    this->setWindowTitle("Главное окно");

    ui->fieldTable->setSizeAdjustPolicy(
                QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
     this->_shipForm = nullptr;
    _anchor = new QImage(":/img/ship.png");
    _anchor->invertPixels();
    _pposkLogo = new QPixmap(":/img/logo2.png");
    _time = new QTime(0,0,0);
    _timer = new QTimer();
    initializeUI();
    _game = new Game();
    _ships.fill(nullptr, 100);
    _amountOfShots = 0;
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    if(_game->getGameState() == EGameState::NOTSTARTED) {
        _game->setGameState(EGameState::START);
    }
}

MainWindow::~MainWindow() {
    delete ui;
    delete _game;
    delete _anchor;
    delete _pposkLogo;
    delete _timer;
    delete _time;
    if(_shipForm != nullptr) {
        delete _shipForm;
        _shipForm = nullptr;
    }
    ui = nullptr;
    _game = nullptr;
    _anchor = nullptr;
    _pposkLogo = nullptr;
    _timer = nullptr;
    _time = nullptr;
    for (auto el : _ships) {
        delete el;
        el = nullptr;
    }
}

void MainWindow::resizeEvent(QResizeEvent *e) {
    QMainWindow::resizeEvent(e);

    qDebug() << e->size();
    qDebug() << "Cell size " << ui->fieldTable->rowHeight(0) << " x " << ui->fieldTable->columnWidth(0);
    for(int row = 0; row < 10; ++row) {
        for(int column = 0; column < 10; ++column) {
            Ship* ship = getShip(row, column);
            if(ship != nullptr) {
                QImage resImg;
                ui->fieldTable->setCellWidget(row, column, nullptr);

                if(defSize == e->size())
                    resImg = _anchor->scaled(ui->fieldTable->columnWidth(0)-8, ui->fieldTable->rowHeight(0), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                else
                    resImg = _anchor->scaled(ui->fieldTable->columnWidth(0), ui->fieldTable->rowHeight(0), Qt::KeepAspectRatio, Qt::SmoothTransformation);


                QLabel *imgLabelCell = new QLabel();


                QPainter *p = new QPainter(&resImg);

                if(ui->fieldTable->rowHeight(0) > 100)
                    p->setFont(QFont("Arial", 20));

                else
                    p->setFont(QFont("Arial", 13));


                p->setPen(const_cast<const QColor &>(*ship->getColor()));

                if(ui->fieldTable->rowHeight(0) > 100)
                    p->drawText(10, 20, QString::number(ship->getNumber() + 1));
                else
                    p->drawText(5, 10, QString::number(ship->getNumber() + 1));

                imgLabelCell->setPixmap(QPixmap::fromImage(resImg));

                ui->fieldTable->setCellWidget(row, column, imgLabelCell);
                imgLabelCell->setAlignment(Qt::AlignCenter);
                delete p;
            }
        }
    }
}

void MainWindow::on_fieldTable_cellClicked(int row, int column) {
    try {
        switch (_game->getGameState()) {
            case QUESTION:
                if (_game->getField()->getCell(row, column) == ECell::SHIP
                        && this->getShip(row, column)->getDeadStatus() != true) {
                    if(this->getShip(row, column)->getAnswerStatus() == false) {
                        this->getShip(row, column)->setAnswerStatus(true);
#if (QT_VERSION < QT_VERSION_CHECK(6, 2, 0))
                            ui->fieldTable->item(row, column)->setBackgroundColor(Qt::green);
#else
                            ui->fieldTable->item(row, column)->setBackground(Qt::green);
#endif
                    } else {
                        this->getShip(row, column)->setAnswerStatus(false);
                        if(this->getShip(row, column)->getHitStatus() == true) {
#if (QT_VERSION < QT_VERSION_CHECK(6, 2, 0))
                            ui->fieldTable->item(row, column)->setBackgroundColor(Qt::red);
#else
                            ui->fieldTable->item(row, column)->setBackground(Qt::red);
#endif
                        } else {
#if (QT_VERSION < QT_VERSION_CHECK(6, 2, 0))
                            ui->fieldTable->item(row, column)->setBackgroundColor(Qt::transparent);
#else
                            ui->fieldTable->item(row, column)->setBackground(Qt::transparent);
#endif
                        }
                    }
                    ui->commandsTable->selectRow(this->getShip(row, column)->getNumber());
                }
                break;
            case SHOT:
                break;
            case TIMER:
                break;
            case NOTSTARTED:
                if (_game->getField()->getCell(row, column) == ECell::SHIP && this->getShip(row, column)->getDeadStatus() != true) {
                    this->getShip(row, column)->setDeadStatus(true);
                }
                break;
            case START:
                break;
            case PLACING_SHIPS:
                if (_game->getField()->getCell(row, column) != ECell::SHIP) {
                    this->_shipForm = new ShipName(false, nullptr);
                    connect(this->_shipForm, SIGNAL(sendShipName(QString)), this, SLOT(setNameQstring(QString)));
                    if(this->_shipForm->exec() == QDialog::Accepted){
                        Ship *ship = new Ship(this->_shipNameString, row, column, this->getColor());
                        connect(ship, SIGNAL(updateShipInfo(Ship*)), this, SLOT(updateCommandShip(Ship*)));
                        connect(ship, SIGNAL(shipIsDead(Ship*)), this, SLOT(updateDeadShip(Ship*)));
                        setShip(row, column, ship);
                    }
                    delete this->_shipForm;
                    this->_shipForm = nullptr;

                }
                break;
            case GAME:
                if ((_game->getField()->getCell(row, column) == ECell::SHIP || _game->getField()->getCell(row, column) == ECell::SHIP_HITED)
                        && this->getShip(row, column)->getDeadStatus() != true) {
                    ui->commandsTable->selectRow(this->getShip(row, column)->getNumber());
                }
                break;
            case END:
                break;
        }
    } catch (std::exception &e) {
        qDebug() << e.what();

    }
}

void MainWindow::on_placeBut_clicked() {
    if(_game->getGameState() == EGameState::NOTSTARTED) {
        Ship* ship1 = new Ship("Test 1", 0, 0, this->getColor());
        this->setShip(0, 0, ship1);
        connect(ship1, SIGNAL(updateShipInfo(Ship*)), this, SLOT(updateCommandShip(Ship*)));
        connect(ship1, SIGNAL(shipIsDead(Ship*)), this, SLOT(updateDeadShip(Ship*)));
        this->getShip(0,0)->addLifes(15);
        Ship* ship2 =  new Ship("Test 2", 1, 1, this->getColor());
        this->setShip(1,1, ship2);
        connect(ship2, SIGNAL(updateShipInfo(Ship*)), this, SLOT(updateCommandShip(Ship*)));
        connect(ship2, SIGNAL(shipIsDead(Ship*)), this, SLOT(updateDeadShip(Ship*)));

        Ship* ship3 =  new Ship("Test 3", 2, 2, this->getColor());
        this->setShip(2, 2, ship3);
        connect(ship3, SIGNAL(updateShipInfo(Ship*)), this, SLOT(updateCommandShip(Ship*)));
        connect(ship3, SIGNAL(shipIsDead(Ship*)), this, SLOT(updateDeadShip(Ship*)));
        this->getShip(2, 2)->addLifes(2);
        Ship* ship4 =  new Ship("Test 4", 3, 3, this->getColor());
        this->setShip(3, 3, ship4);
        connect(ship4, SIGNAL(updateShipInfo(Ship*)), this, SLOT(updateCommandShip(Ship*)));
        connect(ship4, SIGNAL(shipIsDead(Ship*)), this, SLOT(updateDeadShip(Ship*)));

        this->getShip(1, 1)->subLifes(5);

        this->getShip(3,3)->subLifes(5);

        QVector<Ship *> t;
        for(auto &el : this->_ships) {
            if(el != nullptr) {
                if(el->getDeadStatus() != true) {
                    t.push_back(el);
                }
            }
        }
        std::sort(t.begin(), t.end(), [](Ship * a, Ship * b){
            return a->getAmountOfLifes() > b->getAmountOfLifes();
        });
        WinnerWindow *ww = new WinnerWindow(t, nullptr);
        ww->exec();
    }

    if (_game->getGameState() == EGameState::START) {
        _game->setGameState(EGameState::PLACING_SHIPS);
        ui->placeBut->setText("Закончить расстановку");
        ui->addShipBut->setVisible(true);
        return;
    }

    if (_game->getGameState() == EGameState::PLACING_SHIPS) {
        _game->setGameState(EGameState::SHOT);
        ui->shootBut->setVisible(true);
        ui->placeBut->setVisible(false);
        ui->addShipBut->setVisible(false);
        ui->editShipsBut->setVisible(true);
    }
}

void MainWindow::updateTimer() {
    if(_game->getGameState() == EGameState::END) {
        return;
    }
    *_time = _time->addSecs(-1);
    ui->timerLabel->setText("00:" + _time->toString("ss"));
    if (_time->toString("ss") == "00") {
        _timer->stop();
        this->_game->setGameState(EGameState::QUESTION);
        ui->shootBut->setText("Посчитать жизни");
        ui->shootBut->setVisible(true);
    }
}

void MainWindow::initializeButtons()
{
    ui->addShipBut->setVisible(false);
    ui->shootBut->setVisible(false);
    ui->editShipsBut->setVisible(false);
    ui->endBut->setVisible(false);
}

void MainWindow::setDarkTheme()
{
    QPalette darkPalette;
    //QColor(ARGB 1, 0.196078, 0.196078, 0.196078));

    QColor color;
    color.setRgbF(0.196078, 0.196078, 0.196078,1);
    // Настраиваем палитру для цветовых ролей элементов интерфейса
    darkPalette.setColor(QPalette::Window, color);
    color.setRgbF(1, 1, 1, 0.847059);
    darkPalette.setColor(QPalette::WindowText, color);
    color.setRgbF(0.0895094, 0.0895094, 0.0895094, 1);
    darkPalette.setColor(QPalette::Base, color);
    color.setRgbF(0.596078, 0.596078, 0.596078, 1);
    darkPalette.setColor(QPalette::AlternateBase, color);
    color.setRgbF(1, 1, 1, 0.247059);
    darkPalette.setColor(QPalette::ToolTipBase, color);
    color.setRgbF(0, 0, 0, 1);
    darkPalette.setColor(QPalette::ToolTipText, color);
    color.setRgbF(1, 1, 1, 0.847059);
    darkPalette.setColor(QPalette::Text, color);
    color.setRgbF(1, 1, 1, 0.847059);
    darkPalette.setColor(QPalette::Button, color);
    color.setRgbF(0.596078, 0.596078, 0.596078, 1);
    darkPalette.setColor(QPalette::ButtonText, color);
    color.setRgbF(0.215686, 0.215686, 0.215686, 1);
    darkPalette.setColor(QPalette::BrightText, color);
    color.setRgbF(0.206485, 0.526543, 0.998535, 1);
    darkPalette.setColor(QPalette::Link, color);
    color.setRgbF(0.449516, 0.16849, 0.414496, 1);
    darkPalette.setColor(QPalette::Highlight, color);
    color.setRgbF(1, 1, 1, 0.847059);
    darkPalette.setColor(QPalette::HighlightedText, color);
    color.setRgbF(1, 1, 1, 0.247059);
    darkPalette.setColor(QPalette::PlaceholderText, color);
    color.setRgbF(0.140047, 0.140047, 0.140047, 1);
    darkPalette.setColor(QPalette::Mid, color);
    color.setRgbF(0.196078, 0.196078, 0.196078, 1);
    darkPalette.setColor(QPalette::Button, color);
    color.setRgbF(0.74902, 0.74902, 0.74902, 1);
    darkPalette.setColor(QPalette::Dark, color);
    color.setRgbF(0.215686, 0.215686, 0.215686, 1);
    darkPalette.setColor(QPalette::Light, color);
    color.setRgbF(0, 0, 0, 1);
    darkPalette.setColor(QPalette::NoRole, color);
    color.setRgbF(0.203922, 0.203922, 0.203922, 1);
    darkPalette.setColor(QPalette::Midlight, color);
    color.setRgbF(0, 0, 0, 1);
    darkPalette.setColor(QPalette::Shadow, color);

    qApp->setPalette(darkPalette);
}

void MainWindow::initializeUI() {
    setDarkTheme();
    initializeButtons();
    initializeLayout();
    initializePposkLogo();
    initializeTimers();
    initializeFieldTable();
    initializeCommandsTable();
}

void MainWindow::initializeFieldTable() {
    QStringList headerName = {"А", "Б", "В", "Г", "Д", "Е", "Ж", "З", "И", "К"};
    ui->fieldTable->setHorizontalHeaderLabels(headerName);
    ui->fieldTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->fieldTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (auto i = 0; i < 10; ++i) {
        for (auto j = 0; j < 10; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            ui->fieldTable->setItem(i, j, item);
        }
    }
    QString highlight = "rgb(95, 158, 160)";
    QString stylesheet;
    stylesheet = "QTableView { gridline-color : rgb(68, 148, 74);}";
    stylesheet += "QHeaderView { border : none; border-bottom : 2px solid rgb(68, 148, 74); border-right : 2px solid rgb(68, 148, 74);}";
    stylesheet += "QHeaderView::section::selected { border : none; border-bottom : 2px solid yellow; border-right : 2px solid yellow;}";
    stylesheet += "QTableView {selection-background-color: " + highlight + ";";
    stylesheet +=     "selection-color: white; show-decoration-selected: 10}\n";
    stylesheet += "QTableView::item:focus{border: 1px solid yellow;";
    stylesheet +=     "background-color:" + highlight +"}";

    ui->fieldTable->setStyleSheet(stylesheet);
    ui->fieldTable->setSelectionMode(QAbstractItemView::SingleSelection);
}

void MainWindow::initializeCommandsTable() {
    ui->commandsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->commandsTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->commandsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::initializeLayout() {
    QWidget *centralLayout = new QWidget();
    centralLayout->setLayout(ui->layout);
    this->setCentralWidget(centralLayout);
}

void MainWindow::initializeTimers() {
    ui->timerBut->setVisible(false);
    ui->timerLabel->setVisible(false);
    ui->timerLabel->setText("00:60");
    ui->timerLabel->setAlignment(Qt::AlignCenter);
}

void MainWindow::initializePposkLogo() {
    QPixmap logoImg = _pposkLogo->scaled((_pposkLogo->width() / this->width() * 100),
                                        (_pposkLogo->height() / this->height() * 75),
                                        Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->imageLabel->setPixmap(logoImg);
    ui->imageLabel->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_shootBut_clicked() {
    if (this->_game->getGameState() == EGameState::SHOT) {
        _amountOfShots++;
        if(_amountOfShots == 1)
            ui->endBut->setVisible(true);
        if(_amountOfShots > 50) {
            QVector<Ship *> t;
            for(auto &el : this->_ships) {
                if(el != nullptr) {
                    t.push_back(el);
                }
            }
            std::sort(t.begin(), t.end(), [](Ship * a, Ship * b){
                return a->getAmountOfLifes() > b->getAmountOfLifes();
            });
            WinnerWindow *ww = new WinnerWindow(t, nullptr);
            ww->exec();
            delete ww;
            ww = nullptr;
        } else {
            for (int i = 0; i < 10; ++i) {
                int row = 0, column = 0;
                std::tie(row, column) = this->_game->getRandomValueForXY(this->_blackList);
                this->ui->fieldTable->item(row, column)->setBackground(Qt::red);

                if (this->_game->getField()->getCell(row, column) == ECell::SHIP) {
                    this->getShip(row, column)->setHitStatus(true);
                }
            }
            ui->timerBut->setVisible(true);
            ui->timerLabel->setVisible(true);
            ui->shootBut->setVisible(false);

            this->_game->clearThisRoundShots();
        }
        return;
    }

    if (this->_game->getGameState() == EGameState::QUESTION) {
        //time = new QTime(0,0,0);
        qDebug() << "Atter seting timer: " << _time->toString("ss");
        ui->timerLabel->setText("00:60");
        this->calculateLifes();
        this->clearBackgroundFieldsTable();
        ui->shootBut->setText("Выстрелить");
        ui->timerBut->setVisible(false);
        this->_game->setGameState(EGameState::SHOT);
    }
}

void MainWindow::on_timerBut_clicked() {
    _timer->start(1000);
    ui->timerBut->setVisible(false);
}

void MainWindow::updateCommandShip(Ship *ship) {
    ui->commandsTable->item(ship->getNumber(), 1)->setText(ship->getName());
    ui->commandsTable->item(ship->getNumber(), 2)->setText(QString::number(ship->getAmountOfLifes()));
}

void MainWindow::updateDeadShip(Ship *ship) {
    QVector<Ship *> t;
    for(auto &el : this->_ships) {
        if(el != nullptr && el != ship) {
            if(el->getDeadStatus() != true && (el->getAmountOfLifes() - 5) > 0) {
                t.push_back(el);
            }
        }
    }

    deadShipWindow *deadShipDialog = new deadShipWindow (t, ship,nullptr);
    if (deadShipDialog->exec() != QDialog::Accepted) {
        for (int i = 0; i < 4; ++i) {
            Qt::ItemFlags itemFlags = ui->commandsTable->item(ship->getNumber(), i)->flags();
            ui->commandsTable->item(ship->getNumber(), i)->setBackground(Qt::gray);
            ui->commandsTable->item(ship->getNumber(), i)->setFlags(itemFlags ^ Qt::ItemIsSelectable);
        }

        auto itemFlags = ui->fieldTable->item(ship->getRow(), ship->getColumn())->flags();
        ui->fieldTable->item(ship->getRow(), ship->getColumn())->setBackground(Qt::gray);
        ui->fieldTable->item(ship->getRow(), ship->getColumn())->setFlags(itemFlags ^ Qt::ItemIsSelectable ^ Qt::ItemIsEnabled);
        this->_blackList.push_back(qMakePair(ship->getRow(), ship->getColumn()));
    } else {
        ship->setDeadStatus(false);
    }

    delete deadShipDialog;
    deadShipDialog = nullptr;
}

QString MainWindow::convertCoordinates(std::tuple<int, int> pair) {
    int row = 0, column = 0;
    std::tie(row, column) = pair;
    QString result = QString::number(row+1);
    switch (column) {
        case 0:
            result += "А";
        break;
        case 1:
            result += "Б";
        break;
        case 2:
            result += "В";
        break;
        case 3:
            result += "Г";
        break;
        case 4:
            result += "Д";
        break;
        case 5:
            result += "Е";
        break;
        case 6:
            result += "Ж";
        break;
        case 7:
            result += "З";
        break;
        case 8:
            result += "И";
        break;
        case 9:
            result += "К";
        break;
    }
    return result;
}


std::tuple<int, int> MainWindow::convertCoordinates(QString coordinates) {
    int row = 0, column = 0;
    if (!coordinates.isEmpty()) {
        if(coordinates.size() == 3)
            row = coordinates.mid(0, 2).toInt() - 1;
        if (coordinates.size() == 2)
            row = coordinates.mid(0, 1).toInt() - 1;
        switch (coordinates.back().toUpper().unicode()) {
            case u'А':
                column = 0;
            break;
            case u'Б':
                column = 1;
            break;
            case u'В':
                column = 2;
            break;
            case u'Г':
                column = 3;
            break;
            case u'Д':
                column = 4;
            break;
            case u'Е':
                column = 5;
            break;
            case u'Ж':
                column = 6;
            break;
            case u'З':
                column = 7;
            break;
            case u'И':
                column = 8;
            break;
            case u'К':
                column = 9;
            break;
        }
        return std::make_tuple(row, column);
    } else {
        return this->_game->getRandomValueForXY();
    }
}

bool checkColor(QVector<QColor*> blackList, QColor* clr) {
    bool res = true;
    for(auto el : blackList) {
        if(el == clr) {
            res = false;
            break;
        }
    }
    return res;
}

QColor* MainWindow::getColor() {
    int r = static_cast<int>(QRandomGenerator::global()->bounded(0, 256));
    int g = static_cast<int>(QRandomGenerator::global()->bounded(0, 256));
    int b = static_cast<int>(QRandomGenerator::global()->bounded(0, 256));
    while(true) {
        if(checkColor(this->_colorList, new QColor(r, g, b))) {
           break;
        }

        r = static_cast<int>(QRandomGenerator::global()->bounded(0, 256));
        g = static_cast<int>(QRandomGenerator::global()->bounded(0, 256));
        b = static_cast<int>(QRandomGenerator::global()->bounded(0, 256));
    }
    _colorList.push_back(new QColor(r, g, b));
    return _colorList.back();
}

void MainWindow::setNameQstring(QString name) {
    this->_shipNameString = name;
}

void MainWindow::setNameAndCoordinates(QString name, QString coordinates) {
    this->_shipNameString = name;
    this->_coordinates = coordinates;
}

void MainWindow::setShip(size_t row, size_t column, Ship *ship) {

    size_t n = column * 10 + row;
    if (Field::checkDotsAnd(row, column) && n >= 0 && n < this->_ships.size()) {
      this->_game->getField()->setCell(row, column, ECell::SHIP);
      this->_ships[n] = ship;
    }

    auto tempSize = defSize;
    tempSize.setHeight(tempSize.height()+28);
    QImage resImg;
    qDebug() << "Cell size " << ui->fieldTable->rowHeight(0) << " x " << ui->fieldTable->columnWidth(0);
//    if(this->size() == defSize || this->size()  == tempSize)
//        resImg = _anchor->scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//    else
//        resImg = _anchor->scaled(50*2, 50*2, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    resImg = _anchor->scaled(ui->fieldTable->columnWidth(0), ui->fieldTable->rowHeight(0), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QLabel *imgLabelCell = new QLabel();


    QPainter *p = new QPainter(&resImg);

    if(ui->fieldTable->rowHeight(0) < 100)
        p->setFont(QFont("Arial", 12));
    else
        p->setFont(QFont("Arial", 20));

    p->setPen(const_cast<const QColor &>(*ship->getColor()));

    if(ui->fieldTable->rowHeight(0) < 100)
        p->drawText(5, 10, QString::number(ship->getNumber()+1));
    else
        p->drawText(10, 20, QString::number(ship->getNumber()+1));

    imgLabelCell->setPixmap(QPixmap::fromImage(resImg));
    ui->fieldTable->setCellWidget(row, column, imgLabelCell);
    imgLabelCell->setAlignment(Qt::AlignCenter);

    ui->commandsTable->insertRow(ui->commandsTable->rowCount());

    QString str[] = { QString::number(ship->getNumber() + 1),
                      ship->getName(),
                      QString::number(ship->getAmountOfLifes()),
                      convertCoordinates(ship->getCoordinats()) };

    int rowComTab = ui->commandsTable->rowCount()-1;

    Qt::ItemFlags flags;

    for (int i = 0; i < 4; ++i) {
        ui->commandsTable->setItem(rowComTab, i, new QTableWidgetItem(str[i]));
        flags = ui->commandsTable->item(rowComTab, i)->flags();
        ui->commandsTable->item(rowComTab, i)->setFlags(flags ^ Qt::ItemIsEditable);
    }
    delete p;
}

Ship *MainWindow::getShip(size_t row, size_t column) {
    size_t n = column * 10 + row;
    if (Field::checkDotsOr(row, column)) {
        return nullptr;
    }
    if (n >= 0 && n < this->_ships.size()) {
        return this->_ships[n];
    }
    return nullptr;
}

void MainWindow::on_commandsTable_cellClicked(int row, int column) {
    int rowShip = 0, columnShip = 0;
    std::tie(rowShip, columnShip) = convertCoordinates(this->ui->commandsTable->item(row, 3)->text());

    if (this->getShip(rowShip, columnShip)->getDeadStatus() == false) {
        ui->fieldTable->setCurrentCell(rowShip, columnShip);
    }
}

void MainWindow::on_addShipBut_clicked() {
    this->_shipForm = new ShipName(true, nullptr);
    connect(this->_shipForm, &ShipName::sendShipWithCoordinates, this, &MainWindow::setNameAndCoordinates);
    if(this->_shipForm->exec() ==  QDialog::Accepted) {
        int row = 0, column = 0;
        std::tie(row, column) = convertCoordinates(this->_coordinates);
        Ship *ship = new Ship(this->_shipNameString, row, column, this->getColor());
        connect(ship, SIGNAL(updateShipInfo(Ship*)), this, SLOT(updateCommandShip(Ship*)));
        connect(ship, SIGNAL(shipIsDead(Ship*)), this, SLOT(updateDeadShip(Ship*)));
        setShip(row, column, ship);
    }
    delete this->_shipForm;
    this->_shipForm = nullptr;
}

void MainWindow::clearBackgroundFieldsTable() {
    for (int row = 0; row < ui->fieldTable->rowCount(); ++row) {
        for (int column = 0; column < ui->fieldTable->columnCount(); ++column) {
            if (this->_game->getField()->getCell(row, column) != ECell::DEAD_SHIP) {
                ui->fieldTable->item(row, column)->setBackground(Qt::transparent);
            }
        }
    }
}

void MainWindow::calculateLifes() {
    for (int row = 0; row < ui->fieldTable->rowCount(); ++row) {
        for (int column = 0; column < ui->fieldTable->columnCount(); ++column) {
            if (this->_game->getField()->getCell(row, column) != ECell::DEAD_SHIP &&
                    this->_game->getField()->getCell(row, column) == ECell::SHIP) {
                auto ship = this->getShip(row, column);
                if ((ship->getAnswerStatus() && ship->getHitStatus()) ||
                        (!ship->getAnswerStatus() && ship->getDeadStatus())) {
                    ship->setAnswerStatus(false);
                    ship->setHitStatus(false);
                    continue;
                } else if (ship->getAnswerStatus() && !ship->getHitStatus()) {
                    ship->setAnswerStatus(false);
                    ship->setHitStatus(false);
                    ship->addLifes();
                } else if (!ship->getAnswerStatus() && ship->getHitStatus()){
                    ship->setAnswerStatus(false);
                    ship->setHitStatus(false);
                    ship->subLifes();
                }
            }
        }
    }
    this->_game->setGameState(EGameState::SHOT);
}

void MainWindow::on_editShipsBut_clicked(){
    QVector<Ship *> temp;
    for(int row = 0; row < 10; ++row) {
        for(int column = 0; column < 10; ++column) {
            if(this->getShip(row, column) != nullptr && this->getShip(row, column)->getDeadStatus() == false) {
                temp.push_back(this->getShip(row, column));
            }
        }
    }
    EditComTableWindow *ectw = new EditComTableWindow(temp, nullptr);
    ectw->exec();
    delete ectw;
    ectw = nullptr;
}

void MainWindow::on_endBut_clicked() {
    this->_game->setGameState(EGameState::END);
    QVector<Ship *> t;
    for(auto &el : this->_ships) {
        if(el != nullptr) {
            t.push_back(el);
        }
    }
    std::sort(t.begin(), t.end(), [](Ship * a, Ship * b){
        return a->getAmountOfLifes() > b->getAmountOfLifes();
    });
    WinnerWindow *ww = new WinnerWindow(t, nullptr);
    ww->exec();
    delete ww;
    ww = nullptr;
}

