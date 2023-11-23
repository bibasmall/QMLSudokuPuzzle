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
    
private:
    int matrix[9][9];
};
