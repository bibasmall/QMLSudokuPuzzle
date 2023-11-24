#pragma once
#include <QObject>


class Sudoku: public QObject
{
    Q_OBJECT
    
public:
    explicit Sudoku(QObject *parent = 0);
    
public slots:
   // void onNewGame();
    //void onCheckResult();
    
protected:
    QObject *viewer;
    
private:
    void generate();
    bool checkDigit(int row, int col, int d) const noexcept;
    
private:
    int board[9][9];
};
