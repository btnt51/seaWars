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
}


void MainWindow::on_fieldTable_cellClicked(int row, int column) {
    try {
        switch(game->getGameState()) {
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
                    //game->getField()->setShip(row, column, ship);
                    size_t n = column * 10 + row;
                    this->_ships[n] = ship;


                    game->getField()->setCell(row, column, ECell::SHIP);
                    QPixmap resImg = anchor->scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                    QLabel *lbltest = new QLabel();
                    lbltest->setPixmap(resImg);
                    lbltest->setAlignment(Qt::AlignCenter);
                    ui->fieldTable->setCellWidget(row, column, lbltest);
                    ui->fieldTable->item(row, column)->setBackground(Qt::black);
                    ui->commandsTable->insertRow(ui->commandsTable->rowCount());
                    ui->commandsTable->setItem(ui->commandsTable->rowCount()-1, 0, new QTableWidgetItem(QString::number(ship->getNumber())));
                    ui->commandsTable->setItem(ui->commandsTable->rowCount()-1, 1, new QTableWidgetItem(ship->getName()));
                    ui->commandsTable->setItem(ui->commandsTable->rowCount()-1, 2, new QTableWidgetItem(QString::number(ship->getAmountOfLifes())));

                }
                break;
            case GAME:
                if(game->getField()->getCell(row, column) == ECell::SHIP) {
                    qDebug() << " ========== ";
                    qDebug() << "getting ship";
                   // int x = 0, y = 0;
                    ui->fieldTable->item(row, column)->setBackground(Qt::transparent);
                 //   std::tie(x, y) = game->getField()->getShip(row, column)->getCoordinats();
                   // qDebug() << game->getField()->getShip(row, column)->getName() << "\t (" << x << ":" << y << ")";
                    size_t n = column * 10 + row;
                    this->_ships[n]->subLifes();
                    //game->getField()->getShip(row, column)->subLifes();
                    qDebug() << "Ship number: " << this->_ships[n]->getNumber();
                    qDebug() << "Amount of lifes: " << this->_ships[n]->getAmountOfLifes();
                }
                break;
//            case PAUSE:
//                break;
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
    ui->timerBut->setVisible(true);
    ui->timerLabel->setVisible(true);
}


void MainWindow::on_timerBut_clicked() {
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    timer->start(1000);
}

void MainWindow::updateCommandShip(Ship *ship) {
    //ui->commandsTable->findItems(ship->getName(), Qt::MatchFixedString);
    ui->commandsTable->item(ship->getNumber(), 1)->setText(ship->getName());
    ui->commandsTable->item(ship->getNumber(), 2)->setText(QString::number(ship->getAmountOfLifes()));
}

void MainWindow::setShip(size_t row, size_t column, Ship *ship) {
    size_t n = column * 10 + row;
    if(field::checkDotsAnd(row, column) && n >= 0 && n < this->_ships.size()) {
      this->game->getField()->setCell(row, column, ECell::SHIP);
      this->_ships[n] = ship;
    }
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

