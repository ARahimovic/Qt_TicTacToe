#include "tictactoecell.h"

TicTacToeCell::TicTacToeCell(QWidget *parent):QLineEdit(parent){}
void TicTacToeCell::setPosition(int row, int col)
{
    this->row = row;
    this->col = col;
}

void TicTacToeCell::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e);
    emit cellSelected(row,col);
}
