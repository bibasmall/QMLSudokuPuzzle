#pragma once
#include <QAbstractListModel>
#include <QObject>
#include <algorithm>
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
        }
        ~Board() = default;
        
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
        
    public:
        bool checkBoard() const noexcept
        {
            for(int i = 0; i < 9; ++i)
            {
                if(std::accumulate(&board[i][0], &board[i][8], 0) != 45 || std::accumulate(&board[0][i], &board[8][i], 0) != 45)
                    return false;
                
                if((std::accumulate(&board[i / 3][i % 3], &board[i / 3][i % 3 + 2], 0)          +
                    std::accumulate(&board[i / 3 + 1][i % 3], &board[i / 3+1][i % 3 + 2], 0)    +
                    std::accumulate(&board[i / 3 + 2][i % 3], &board[i / 3+2][i % 3 + 2], 0)) != 45)
                    return false;
            }
            
            return true;
        }
        void solve()
        {
            std::function<bool(int)> solver;
            
            solver = [this, &solver](int count) {
                if (count == 81)
                    return true;
                
                int i = count / 9, j = count % 9;
                
                if (board[i][j] != 0)
                    return solver(count + 1);
                
                for (int d = 1; d <= 9; ++d)
                {
                    if (!checkDigit(i, j, d))
                        continue;
                    
                    board[i][j] = d;
                    if (solver(count + 1))
                        return true;
                    
                    board[i][j] = 0;
                }
                
                return false;
            };
            
            solver(0);
        }
        
        void start()
        {
            std::memset(&board, 0, sizeof(board));
            generate();
        }
        
    private:
        void generate() noexcept
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
    
    enum Role { value = Qt::UserRole + 1, count = Qt::UserRole + 2, valueFromBoard = Qt::UserRole + 3 };
    
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
    void onSolve();
    void onCheck() const;
    
signals:
    void boardChangedFromInside();
    
private:
    void start();
    void restart();
    
private:
    QVector<QString>        cells;
    std::unique_ptr<Board>  board;
    bool                    solved = false;
};
