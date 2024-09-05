#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include "numberbutton.h"
#include <QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void numberButtonClickedSlot(int number);
private:
    Ui::MainWindow *ui;
    const int rows = 6;
    const int cols = 7;
    int numberPlayers = 2;
    int currentPlayer = 0;
    std::vector< std::vector<QLabel*>> field;
    std::vector< std::vector<int>> fieldInt;
    std::vector<NumberButton*> buttons;
    std::vector<int> columnCount;

    QPixmap red, yellow, white;

    bool gameWon();
    bool checkColumn(int column);
    bool checkRow(int row);
    void newGame();

    void resizeEvent(QResizeEvent* event);
};
#endif // MAINWINDOW_H
