#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "tictactoecell.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <utility>

class ticTacToe : public QMainWindow
{
    Q_OBJECT

public:
    ticTacToe(QWidget *parent = nullptr);
    ~ticTacToe();

private slots :
    void handleCellSelected(int row, int col);
private:
    bool checkWin(int row, int col);
    bool checkDraw();
    std::pair<int,int> findEmptyCell();

    TicTacToeCell* cells[3][3];
    QString cellStyleSheet = "border:0; border-right:2px solid grey; border-bottom:2px solid grey;";
    QLabel* player1;
    QLabel* player2;
    bool isPlayer1 = true;
};
#endif // TICTACTOE_H
