#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
      ui->setupUi(this);
      QStringList headerName = {"А", "Б", "В", "Г", "Д", "Е", "Ж", "З", "И", "К"};
      anchor = new QPixmap("/Users/btnt51/seaWars/anchor.png");
      ui->fieldTable->setHorizontalHeaderLabels(headerName);
      QWidget *centralLayout = new QWidget();
      centralLayout->setLayout(ui->layout);
      this->setCentralWidget(centralLayout);

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

//      ui->fieldTable->setStyleSheet("QTableView { gridline-color : green;}"
//                                 "QHeaderView { border : none; border-bottom : 2px solid green; border-right : 2px solid green;}");
    ui->fieldTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->commandsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->commandsTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->fieldTable->item(0,0)->setIcon(QIcon("~/anchor.png"));

//  ui->fieldTable->cellWidget(0, 0)->setBackgroundColor(Qt::blue);
//  ui->fieldTable->setItem(0, 0, item);
//  ui->fieldTable->item(0, 0)->setBackground(Qt::blue);
//  ui->fieldTable->item(9, 9)->setBackground(Qt::blue);
    game = new Game(10, nullptr);
    if(game->getGameState() == EGameState::NOTSTARTED)
        game->setGameState(EGameState::START);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
    delete anchor;
}


void MainWindow::on_fieldTable_cellClicked(int row, int column)
{
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
                    game->getField()->setShip(row, column, new Ship(name, row, column, color));
                    game->getField()->setCell(row, column, ECell::SHIP);
                    QPixmap resImg = anchor->scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                    QLabel *lbltest = new QLabel();
                    lbltest->setPixmap(resImg);
                    lbltest->setAlignment(Qt::AlignCenter);
                    ui->fieldTable->setCellWidget(row, column, lbltest);
                    ui->fieldTable->item(row, column)->setBackground(Qt::black);
                    //ui->fieldTable->cellWidget(row, column)->resize();
                }
                break;
            case GAME:
                //if(game->getField()->getCell(row, column))
                if(game->getField()->getCell(row, column) == ECell::SHIP) {
                    qDebug() << " ========== ";
                    qDebug() << "getting ship";
                    int x = 0, y = 0;
                    ui->fieldTable->item(row, column)->setBackground(Qt::transparent);
                    std::tie(x, y) = game->getField()->getShip(row, column)->getCoordinats();
                    qDebug() << game->getField()->getShip(row, column)->getName() << "\t (" << x << ":" << y << ")\n";
                }
                break;
            case PAUSE:
                break;
            case END:
                break;
        }
    } catch (std::exception &e){
        qDebug() << e.what();

    }
}


void MainWindow::on_placeBut_clicked()
{
    if(game->getGameState() == EGameState::START) {
        game->setGameState(EGameState::PLACING_SHIPS);
        ui->placeBut->setText("Закончить расстановку");
        return;
    }
    if(game->getGameState() == EGameState::PLACING_SHIPS) {
        game->setGameState(EGameState::GAME);
        ui->placeBut->setVisible(false);
    }
}

