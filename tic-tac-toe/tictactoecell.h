#ifndef TICTACTOECELL_H
#define TICTACTOECELL_H

#include <QLineEdit>
#include <QFocusEvent>

class TicTacToeCell : public QLineEdit
{
Q_OBJECT
public:
    explicit TicTacToeCell(QWidget *parent =nullptr);
    void setPosition(int row, int col);

protected:
    void focusInEvent(QFocusEvent *e) override;

private:
    int row;
    int col;

signals :
    void cellSelected(int row, int col);

};

#endif // TICTACTOECELL_H
