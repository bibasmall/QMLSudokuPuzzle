#include <QQmlProperty>
#include "sudoku.h"


void Sudoku::Board::set(quint8 count, quint8 val)
{
    assert(val >= 0 && val <= 9 && count < 81);
    board[count / 9][count % 9] = val;
}

quint8 Sudoku::Board::get(quint8 count)
{
    assert(count < 81);
    return board[count / 9][count % 9];
}

bool Sudoku::Board::checkBoard() const noexcept
{
    for(int i = 0; i < 9; ++i)
    {
        auto rowSum = std::accumulate(&board[i][0], &board[i][8]+1, 0);
        if(rowSum != 45)
            return false;
        
        unsigned row = (i / 3) * 3, col = (i % 3) * 3; 
        auto square3x3Sum = std::accumulate(&board[row][col], &board[row][col + 2]+1, 0) +
                            std::accumulate(&board[row+1][col], &board[row+1][col + 2]+1, 0) +
                            std::accumulate(&board[row+2][col], &board[row+2][col + 2]+1, 0);
        if(square3x3Sum != 45)
            return false;
        
        auto colSum = 0;
        for(int j = 0; j <= 8; ++j)
            colSum+=board[j][i];
        if(colSum != 45)
            return false;
    }
    
    return true;
}

void Sudoku::Board::solve()
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

void Sudoku::Board::start()
{
    std::memset(&board, 0, sizeof(board));
    generate();
}

void Sudoku::Board::generate() noexcept
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

bool Sudoku::Board::checkDigit(quint8 row, quint8 col, quint8 d) const noexcept
{
    bool result = true;
    for (int i = 0; i < 9 && result; ++i)
        result = !(board[row][i] == d || board[i][col] == d || board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == d);
    
    return result;
}

Sudoku::Sudoku(QObject *parent) : QAbstractListModel(parent), board(std::make_unique<Board>()), cells(81, "")
{
    srand(time(NULL));
    start();
}

int Sudoku::rowCount(const QModelIndex& parent) const
{
    return cells.count();
}

QVariant Sudoku::data(const QModelIndex& index, int role) const
{
    if ( !index.isValid() || index.row() < 0 || index.row() >= rowCount() )
        return {};
    
    QVariant res{};
    if(role == Qt::UserRole + 1)
        res = cells[index.row()];
    if(role == Qt::UserRole + 2)
        res = index.row();
    
    return res;
}

QHash<int, QByteArray> Sudoku::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole + 1] = "Value";
    roles[Qt::UserRole + 2] = "Count";
    roles[Qt::UserRole + 3] = "ValueFromBoard";
    return roles;
}

bool Sudoku::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!hasIndex(index.row(), index.column(), index.parent()) || !value.isValid())
        return false;
    
    if(role == Role::value)
        board->set(index.row(), value.toString().toInt());
    else if(role == Role::valueFromBoard)
    {
        cells[index.row()] = value.toString();
        emit dataChanged(index, index, { Role::value } );
    }
    
    return true;
}

void Sudoku::onNewGame()
{
    start();
}

void Sudoku::onSolve()
{
    qDebug() << "Solve pressed";
    board->solve();
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
            if(cells.at(9*i + j).toInt() != board->get(9*i + j))
                setData(index(9*i + j), QString::number(board->get(9*i + j)), Role::valueFromBoard);
    }
    emit boardChangedFromInside();
}

void Sudoku::onCheck() const
{
    if(board->checkBoard())
        qDebug() << "Well done";
    else
        qDebug() << "Wrong sudoku";
}

void Sudoku::start()
{
    board->start();
    for(int i = 0; i < 81; ++i)
        setData(index(i), board->get(i) ? QString::number(board->get(i)) : "", Role::valueFromBoard);
    
    emit boardChangedFromInside();
}

void Sudoku::restart()
{
    for(auto& e : cells)
        e = "";
    start();
}
