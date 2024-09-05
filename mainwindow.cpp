#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QGridLayout>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    field.resize(rows, std::vector<QLabel*>(cols, nullptr));
    fieldInt.resize(rows, std::vector<int>(cols, -1));
    columnCount.resize(cols, 0);
    buttons.resize(cols, nullptr);

    red = QPixmap("../VierGewinnt/red.png");
    yellow= QPixmap("../VierGewinnt/yellow.png");
    white= QPixmap("../VierGewinnt/white.png");

    QGridLayout* gridlayout = new QGridLayout(ui->centralwidget);

    float labelHeight = this->height() / (rows+1);
    float labelWidth= this->width() / (cols+1);

    for(int r=0; r< rows; r++)    {
        for(int c=0; c< cols; c++)    {
            auto* l = new QLabel(ui->centralwidget);
            l->setPixmap(white);
            l->setScaledContents(true);
            float min = std::min(labelWidth, labelHeight);
            l->setMaximumSize(min, min);
            l->setMinimumSize(20,20);

            field.at(r).at(c) = l;
            gridlayout->addWidget(l, r, c);
        }
    }

    for(int i=0; i< cols; i++){
        buttons.at(i) = new NumberButton(i, ui->centralwidget);
        connect(buttons.at(i), &NumberButton::numberButtonClicked, this, &MainWindow::numberButtonClickedSlot);
        buttons.at(i)->setMinimumSize(40, 20);
        gridlayout->addWidget(buttons.at(i) , 7, i);

    }
    ui->statusbar->showMessage("Spieler 1 (rot) an der Reihe.");

}

MainWindow::~MainWindow()
{
    for(auto e : buttons)
        delete e;
    for(auto& v : field)
        for(auto e: v)
            delete e;
    delete ui;
}

void MainWindow::numberButtonClickedSlot(int number)
{
    if(columnCount.at(number) >= rows ){

        QMessageBox msgBox;
        msgBox.setText(QString("Diese Reihe ist bereits voll!"));
        msgBox.exec();
        return ;
    }
    if(currentPlayer == 0){
        field.at(rows-1-columnCount.at(number)).at(number)->setPixmap(red);
        fieldInt.at(rows-1-columnCount.at(number)).at(number) = 0;
        ui->statusbar->showMessage("Spieler 2 (gelb) an der Reihe.");
    }else{
        field.at(rows-1-columnCount.at(number)).at(number)->setPixmap(yellow);
        fieldInt.at(rows-1-columnCount.at(number)).at(number) = 1;
        ui->statusbar->showMessage("Spieler 1 (rot) an der Reihe.");
    }

    columnCount.at(number)++;

    if(gameWon()){
        QMessageBox msgBox;
        msgBox.setText(QString("Spieler "+ QString::number(currentPlayer+1) + " hat das Spiel gewonnen!"));
        msgBox.exec();
        newGame();
        return;
    }
    currentPlayer = (currentPlayer + 1) % 2;
}

bool MainWindow::gameWon()
{
    for(int i=0 ; i< cols; i++){
        if(checkColumn(i))
            return true;
    }
    for(int i=0 ; i< rows; i++){
        if(checkRow(i))
            return true;
    }
    return false;
}

bool MainWindow::checkColumn(int column)
{
    if(columnCount.at(column) < 4)
        return false;

    int tmp = fieldInt.at(rows-1).at(column);
    int r = rows -2;
    int cnt = 1;
    while(r >= 0 && fieldInt.at(r).at(column) != -1){
        if(fieldInt.at(r).at(column) == tmp){
            cnt++;
        }else{
            tmp = fieldInt.at(r).at(column);
            cnt = 1;
        }
        if(cnt >= 4)
            return true;
        r--;
    }
    return false;
}

bool MainWindow::checkRow(int row)
{
    int tmp = -1;
    int cnt = 0;
    for( int c = 0; c < cols ; c++){
        if(fieldInt.at(row).at(c) == -1){
            tmp = 0;
            cnt = 0;
            continue;
        }
        if(fieldInt.at(row).at(c) == tmp ) {
            cnt++;
            if(cnt >= 4)
                return true;
        }
        else if(fieldInt.at(row).at(c) != tmp){
            cnt = 1;
            tmp = fieldInt.at(row).at(c);
        }

    }
    return false;
}

void MainWindow::newGame()
{
    for(int r=0; r< rows; r++)    {
        for(int c=0; c< cols; c++)    {
           field.at(r).at(c)->setPixmap(white);
        }
    }
    fieldInt.clear();
    fieldInt.resize(rows, std::vector<int>(cols, -1));
    columnCount.clear();
    columnCount.resize(cols, 0);

    currentPlayer = 0;
    ui->statusbar->showMessage("Spieler 1 (rot) an der Reihe.");
}

void MainWindow::resizeEvent(QResizeEvent *event)
{

    QMainWindow::resizeEvent(event);
    float labelHeight = event->size().height() / (rows+1);
    float labelWidth = event->size().width() /  (cols+1);

    for(int r=0; r< rows; r++)    {
        for(int c=0; c< cols; c++)    {
            auto l = field.at(r).at(c);
            float min = std::min(labelWidth, labelHeight);
            l->setMaximumSize(min, min);
        }
    }
}



