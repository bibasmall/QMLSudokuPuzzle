#pragma once
#include <QAbstractListModel>
#include <QObject>
#include "assert.h"
#include <memory>


class Sudoku : public QAbstractListModel
{
    Q_OBJECT
    
    class Board
    {
    public:
        Board()
        {
            std::memset(&board, 0, sizeof(board));
            generate();
        }
        
        void set(quint8 count, quint8 val)
        {
            assert(val >= 0 && val <= 9 && count < 81);
            board[count / 9][count % 9] = val;
        }
        quint8 get(quint8 count)
        {
            assert(count < 81);
            return board[count / 9][count % 9];
        }
        
    private:
        void generate()
        {
            for(int clues = (rand() % 4) + 17; clues; --clues)
            {
                quint8 i = 0;
                quint8 j = 0;
                
                while(board[i][j] != 0)
                {
                    i = rand() % 8;
                    j = rand() % 8;
                }
                
                for(auto d = rand() % 8 + 1; ; d = rand() % 8 + 1)
                {
                    if(checkDigit(i, j, d))
                    {
                        board[i][j] = d;
                        break;
                    }
                }
            }
        }
        bool checkDigit(quint8 row, quint8 col, quint8 d) const noexcept
        {
            bool result = true;
            for (int i = 0; i < 9 && result; ++i)
                result = !(board[row][i] == d || board[i][col] == d || board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == d);
            
            return result;
        }
        
    private:
        quint8 board[9][9];
    };
    
public:
    explicit Sudoku(QObject *parent = 0);
    
    ~Sudoku() = default;
    Sudoku(const Sudoku&) = delete;
    const Sudoku& operator=(const Sudoku&) = delete;
    Sudoku(Sudoku&&) = delete;
    Sudoku& operator=(Sudoku&&) = delete;
    
public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    
public:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    
public slots:
    void onNewGame();
    void onCheck() const;
    
private:
    QList<QString>          cells;
    std::unique_ptr<Board>  board;
};
