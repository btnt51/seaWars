#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    anchor = new QPixmap("/Users/btnt51/seaWars/anchor.png");
    pposkLogo = new QPixmap("/Users/btnt51/seaWars/logo1.png");
    time = new QTime(0,0,0);
    timer = new QTimer();
    initializeUI();
    game = new Game(10, nullptr);
    _ships.fill(nullptr, 100);
    //connect(game, SIGNAL(sendUpdatedShipToTable(Ship*)), this, SLOT(updateCommandShip(Ship*)));
    if(game->getGameState() == EGameState::NOTSTARTED)
        game->setGameState(EGameState::START);
}

MainWindow::~MainWindow() {
    delete ui;
    delete game;
    delete anchor;
    delete pposkLogo;
    delete timer;
    delete time;
    ui = nullptr;
    game = nullptr;
    anchor = nullptr;
    pposkLogo = nullptr;
    timer = nullptr;
    time = nullptr;
    for(auto el : _ships) {
        delete el;
        el = nullptr;
    }
}


void MainWindow::on_fieldTable_cellClicked(int row, int column) {
    try {
        switch(game->getGameState()) {
            case QUESTION:
                break;
            case SHOT:
                break;
            case TIMER:
                break;
            case NOTSTARTED:
                break;
            case START:
                break;
            case PLACING_SHIPS:
                if(game->getField()->getCell(row, column) != ECell::SHIP) {
                    qDebug() << " ========== ";
                    qDebug() << "Placing ships";
                    QString name = "test";
                    QColor *color = new QColor(250, 250, 250);

                    Ship *ship = new Ship(name, row, column, color);
                    connect(ship, SIGNAL(updateShipInfo(Ship*)), this, SLOT(updateCommandShip(Ship*)));
                    connect(ship, SIGNAL(shipIsDead(Ship*)), this, SLOT(updateDeadShip(Ship*)));
                    setShip(row, column, ship);
                }
                break;
            case GAME:
                if(game->getField()->getCell(row, column) == ECell::SHIP && this->getShip(row, column)->getDeadStatus() != true) {
                    ui->fieldTable->item(row, column)->setBackground(Qt::transparent);
                    size_t n = column * 10 + row;
                    ui->commandsTable->selectRow(this->getShip(row, column)->getNumber());
                }
                break;
            case END:
                break;
        }
    } catch (std::exception &e){
        qDebug() << e.what();

    }
}


void MainWindow::on_placeBut_clicked() {
    if(game->getGameState() == EGameState::START) {
        game->setGameState(EGameState::PLACING_SHIPS);
        ui->placeBut->setText("Закончить расстановку");
        ui->addShipBut->setVisible(true);
        return;
    }
    if(game->getGameState() == EGameState::PLACING_SHIPS) {
        game->setGameState(EGameState::GAME);
        ui->placeBut->setVisible(false);
        ui->addShipBut->setVisible(false);
    }
}

void MainWindow::updateTimer() {
    *time = time->addSecs(-1);
    ui->timerLabel->setText("00:" + time->toString("ss"));
    if(time->toString("ss") == "00")
        timer->stop();
}

void MainWindow::initializeUI() {
    ui->addShipBut->setVisible(false);
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
    for(auto i = 0; i < 10; ++i) {
        for(auto j = 0; j < 10; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            ui->fieldTable->setItem(i, j, item);
        }
    }
    QString highlight = "yellow";
    QString stylesheet;
    stylesheet = "QTableView { gridline-color : green;}";
    stylesheet += "QHeaderView { border : none; border-bottom : 2px solid green; border-right : 2px solid green;}";
    stylesheet += "QHeaderView::section::selected { border : none; border-bottom : 2px solid yellow; border-right : 2px solid yellow;}";
    stylesheet +=  "QTableView {selection-background-color: " + highlight + ";";
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
    ui->timerLabel->setAlignment(Qt::AlignCenter);
}

void MainWindow::initializePposkLogo() {
    QPixmap logoImg = pposkLogo->scaled((pposkLogo->width() / this->width() * 100),
                                        (pposkLogo->height() / this->height() * 75),
                                        Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->imageLabel->setPixmap(logoImg);
    ui->imageLabel->setAlignment(Qt::AlignCenter);
}


void MainWindow::on_shootBut_clicked() {
    this->game->setGameState(EGameState::SHOT);
    for(int i = 0; i < 10; ++i) {
        int row = 0, column = 0;
        std::tie(row, column) = this->game->getRandomValueForXY(this->blacklist);
        this->ui->fieldTable->item(row, column)->setBackground(Qt::red);
        if(this->game->getField()->getCell(row, column) == ECell::SHIP) {
            this->getShip(row, column)->setHitStatus(true);
            this->getShip(row, column)->subLifes();
        }
    }
    ui->timerBut->setVisible(true);
    ui->timerLabel->setVisible(true);

}


void MainWindow::on_timerBut_clicked() {
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    timer->start(1000);
}

void MainWindow::updateCommandShip(Ship *ship) {
    //ui->commandsTable->item(ship->getNumber(), 1)->setText(ship->getName());
    ui->commandsTable->item(ship->getNumber(), 2)->setText(QString::number(ship->getAmountOfLifes()));
}

void MainWindow::updateDeadShip(Ship *ship) {
    bool lifeIsGifted = false;
    if(lifeIsGifted) {

    } else {
        for (int i = 0; i < 4; ++i) {
            Qt::ItemFlags itemFlags = ui->commandsTable->item(ship->getNumber(), i)->flags();
            ui->commandsTable->item(ship->getNumber(), i)->setBackground(Qt::gray);
            ui->commandsTable->item(ship->getNumber(), i)->setFlags(itemFlags ^ Qt::ItemIsSelectable);
        }

        auto itemFlags = ui->fieldTable->item(ship->getRow(), ship->getColumn())->flags();
        ui->fieldTable->item(ship->getRow(), ship->getColumn())->setBackground(Qt::gray);
        ui->fieldTable->item(ship->getRow(), ship->getColumn())->setFlags(itemFlags ^ Qt::ItemIsSelectable ^ Qt::ItemIsEnabled);
        this->blacklist.push_back(qMakePair(ship->getRow(), ship->getColumn()));
    }

}

QString MainWindow::convertCoordinates(std::tuple<int, int> pair) {
    int row = 0, column = 0;
    std::tie(row, column) = pair;
    QString result = QString::number(row+1);
    switch(column) {
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

QPair<int, int> MainWindow::convertCoordinates(QString coordinates) {
    int row = 0, column = 0;
    row = coordinates[0].digitValue() - 1;
    switch(coordinates[1].unicode()) {
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
    //TODO: realize converted
    return qMakePair(row, column);
}

void MainWindow::setShip(size_t row, size_t column, Ship *ship) {
    size_t n = column * 10 + row;
    if(field::checkDotsAnd(row, column) && n >= 0 && n < this->_ships.size()) {
      this->game->getField()->setCell(row, column, ECell::SHIP);
      this->_ships[n] = ship;
    }

    QPixmap resImg = anchor->scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QLabel *imgLabelCell = new QLabel();
    imgLabelCell->setPixmap(resImg);
    imgLabelCell->setAlignment(Qt::AlignCenter);
    ui->fieldTable->setCellWidget(row, column, imgLabelCell);
    ui->fieldTable->item(row, column)->setBackground(Qt::black);
    ui->commandsTable->insertRow(ui->commandsTable->rowCount());

    QString str[] = { QString::number(ship->getNumber()),
                      ship->getName(),
                      QString::number(ship->getAmountOfLifes()),
                      convertCoordinates(ship->getCoordinats()) };

    int rowComTab = ui->commandsTable->rowCount()-1;

    Qt::ItemFlags flags;

    for(int i = 0; i < 4; ++i) {
        ui->commandsTable->setItem(rowComTab, i, new QTableWidgetItem(str[i]));
        if(i != 2) {
            flags = ui->commandsTable->item(rowComTab, i)->flags();
            ui->commandsTable->item(rowComTab, i)->setFlags(flags ^ Qt::ItemIsEditable);
        }
    }

//    ui->commandsTable->setItem(ui->commandsTable->rowCount()-1, 0, new QTableWidgetItem(QString::number(ship->getNumber())));
//    ui->commandsTable->item(ui->commandsTable->rowCount()-1, 0)->setFlags(ui->commandsTable->item(ui->commandsTable->rowCount()-1, 0)->flags() ^ Qt::ItemIsEditable);
//    ui->commandsTable->setItem(ui->commandsTable->rowCount()-1, 1, new QTableWidgetItem(ship->getName()));
//    ui->commandsTable->item(ui->commandsTable->rowCount()-1, 1)->setFlags(ui->commandsTable->item(ui->commandsTable->rowCount()-1, 0)->flags());
//    ui->commandsTable->setItem(ui->commandsTable->rowCount()-1, 2, new QTableWidgetItem(QString::number(ship->getAmountOfLifes())));
//    ui->commandsTable->setItem(ui->commandsTable->rowCount()-1, 3, new QTableWidgetItem(convertCoordinates(ship->getCoordinats())));
//    ui->commandsTable->item(ui->commandsTable->rowCount()-1, 3)->setFlags(ui->commandsTable->item(ui->commandsTable->rowCount()-1, 0)->flags());


}

Ship *MainWindow::getShip(size_t row, size_t column) {
    size_t n = column * 10 + row;
    if(field::checkDotsOr(row, column)) {
      return nullptr;
    }
    if(n >= 0 && n < this->_ships.size()) {
      return this->_ships[n];
    }
    return nullptr;
}


void MainWindow::on_commandsTable_cellClicked(int row, int column) {
    int rowShip = 0, columnShip = 0;
    std::tie(rowShip, columnShip) = convertCoordinates(this->ui->commandsTable->item(row, 3)->text());
    qDebug() << rowShip << columnShip;
    if (this->getShip(rowShip, columnShip)->getDeadStatus() == false) {
        //TODO: highlight ship on fieldTable & realize cordinateCoverter
        ui->fieldTable->setCurrentCell(rowShip, columnShip);
    }
}

