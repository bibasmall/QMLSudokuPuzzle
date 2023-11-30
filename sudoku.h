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
        Board() = default;
        ~Board() = default;
        
        void set(quint8 count, quint8 val);
        quint8 get(quint8 count);
        
    public:
        bool checkBoard() const noexcept;
        void solve();
        void start();
        
    private:
        void generate() noexcept;
        bool checkDigit(quint8 row, quint8 col, quint8 d) const noexcept;
        
    private:
        std::array<std::array<qint8, 9>, 9> board{};
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
};
