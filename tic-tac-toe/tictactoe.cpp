#include "tictactoe.h"
#include <QGridLayout>
#include <QWidget>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QDebug>

ticTacToe::ticTacToe(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug() << "Hello I am working";
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* centralLayout = new QHBoxLayout(centralWidget);
    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);
    centralWidget->setFocus();

    //want to create a grid and 2 qlabel
    QGridLayout* myGrid = new QGridLayout();
    for(int row =0; row <3; row++)
    {
        for(int col =0; col <3; col++)
        {
            TicTacToeCell* cell = new TicTacToeCell(this);
            cell->setMaxLength(1);
            cell->setAlignment(Qt::AlignCenter);
            cell->setFixedHeight(100);
            cell->setFixedWidth(100);
            cell->setStyleSheet(cellStyleSheet);
            cell->setPosition(row,col);
            myGrid->addWidget(cell, row, col);
            cells[row][col] = cell;

            connect(cell, &TicTacToeCell::cellSelected, this, &ticTacToe::handleCellSelected);
        }

    }
    //might need to add vertical spacer at the botton to make the gird stick togetehr

    QSpacerItem* vSpacer = new QSpacerItem(20,20,QSizePolicy::Minimum, QSizePolicy::Expanding);
    myGrid->addItem(vSpacer,3,0,1,3);
    myGrid->setHorizontalSpacing(0); // Space between columns
    myGrid->setVerticalSpacing(0);

    QVBoxLayout *leftColumn = new QVBoxLayout();
    leftColumn->addStretch();
    leftColumn->addLayout(myGrid);
    leftColumn->addStretch();
    //want to add 2 qlabel
    //create a vertical alyout
    QVBoxLayout *rightColumn = new QVBoxLayout();

    player1 = new QLabel("Player 1");
    player1->setAlignment(Qt::AlignCenter);
    player1->setStyleSheet("border:2px solid black; background-color:green;");
    player1->setFixedHeight(100);
    player1->setFixedWidth(150);

    player2 = new QLabel("Player 2");
    player2->setAlignment(Qt::AlignCenter);
    player2->setStyleSheet("border:2px solid black; background:blue;");
    player2->setFixedHeight(100);
    player2->setFixedWidth(150);


    rightColumn->addWidget(player1);
    rightColumn->addWidget(player2);
    rightColumn->setSpacing(0);
    rightColumn->setContentsMargins(0, 0, 0, 0); // Remove margins around the layout


    centralLayout->addLayout(leftColumn);
    centralLayout->addLayout(rightColumn);



    setWindowTitle("Tic-Tac-Toe");
    setFixedSize(500, 500);

}

void ticTacToe::handleCellSelected(int row, int col)
{
    TicTacToeCell *cell = qobject_cast<TicTacToeCell*>(sender());
    if(cell)
    {
        if(cell->text().isEmpty())
        {
            if(isPlayer1)
            {
                cell->setText("X");
                cell->setStyleSheet(cellStyleSheet + "color : blue;");
            }

            else
            {
                cell->setText("O");
                cell->setStyleSheet(cellStyleSheet + "color : orange;");
            }
            cell->clearFocus();
            cell->setReadOnly(true);
            isPlayer1 = !isPlayer1;

            if(checkWin(row,col))
            {
                qDebug()<< "you Won";
            }
            else if(checkDraw())
            {
                qDebug()<< "Draw";
            }

        }

        qDebug() << "cell selected : " << row << " col : " << col;
    }
}

std::pair<int,int> ticTacToe::findEmptyCell()
{
    for(int i =0; i < 3; i++)
    {
        for(int j =0; j <3; j++)
        {
            if(cells[i][j]->text().isEmpty())
                return std::make_pair(i,j);
        }
    }

    return std::make_pair(-1,-1);
}
bool ticTacToe::checkDraw()
{
    auto empty = findEmptyCell();
    if(empty.first == -1 and empty.second == -1)
    {
        qDebug() << "it is a Draw";
        return true;
    }
    return false;
}

bool ticTacToe::checkWin(int row, int col)
{
    QString cellText = cells[row][col]->text();
    qDebug() << "We checking this value" << cellText;

    //check main diagonal
    if(row==col)
    {
        for(int i =0; i < 3; i++)
        {
            if(cells[i][i]->text() != cellText)
                break;
            if(i == 2)
                return true;
        }
    }

    //check anti diagonal
    if(row+col == 2)
    {
        for(int i =0; i < 3; i++)
        {
            if(cells[i][2-i]->text() != cellText)
                break;
            if(i == 2)
                return true;
        }
    }

    //check entire row
    for(int i = 0; i < 3 ; i++)
    {
        if(cells[row][i]->text() != cellText)
            break;

        if(i == 2)
            return true;
    }

    //check entire column
    for(int i = 0; i < 3 ; i++)
    {
        if(cells[i][col]->text() != cellText)
            break;
        if(i == 2)
            return true;
    }

    //no win condition met
    return false;
}
ticTacToe::~ticTacToe() {}
