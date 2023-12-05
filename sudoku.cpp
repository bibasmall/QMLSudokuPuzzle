#include <QQmlProperty>
#include "assert.h"
#include "sudoku.h"


void Sudoku::Board::set(quint8 count, quint8 val)
{
    assert(val >= 0 && val <= BOARD_ROW && count < NUMBER_OF_CELLS);
    board[count / BOARD_ROW][count % BOARD_ROW] = val;
}

quint8 Sudoku::Board::get(quint8 count)
{
    assert(count < NUMBER_OF_CELLS);
    return board[count / BOARD_ROW][count % BOARD_ROW];
}

bool Sudoku::Board::checkBoard() const noexcept
{
    const int expectedSum = 45;
    const int last = BOARD_ROW - 1;
    
    for(int i = 0; i < BOARD_ROW; ++i)
    {
        auto rowSum = std::accumulate(&board[i][0], &board[i][last]+ 1, 0);
        if(rowSum != expectedSum)
            return false;
        
        unsigned row = (i / 3) * 3, col = (i % 3) * 3; 
        auto square3x3Sum = std::accumulate(&board[row][col], &board[row][col + 2] + 1, 0) +
                            std::accumulate(&board[row+1][col], &board[row+1][col + 2]+ 1, 0) +
                            std::accumulate(&board[row+2][col], &board[row+2][col + 2]+ 1, 0);
        
        if(square3x3Sum != expectedSum)
            return false;
        
        auto colSum = 0;
        for(int j = 0; j <= last; ++j)
            colSum+=board[j][i];
        if(colSum != expectedSum)
            return false;
    }
    
    return true;
}

void Sudoku::Board::solve()
{
    std::function<bool(int)> solver;
    
    solver = [this, &solver](int count) {
        if (count == NUMBER_OF_CELLS)
            return true;
        
        int i = count / BOARD_ROW, j = count % BOARD_ROW;
        
        if (board[i][j] != 0)
            return solver(count + 1);
        
        for (int d = 1; d <= BOARD_ROW; ++d)
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
    for (int i = 0; i < BOARD_ROW && result; ++i)
        result = !(board[row][i] == d || board[i][col] == d || board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == d);
    
    return result;
}

Sudoku::Sudoku(QObject *parent) : QAbstractListModel(parent), board(std::make_unique<Board>()), cells(Board::NUMBER_OF_CELLS, "")
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
    for(int i = 0; i < Board::BOARD_ROW; ++i)
    {
        for(int j = 0; j < Board::BOARD_ROW; ++j)
            if(cells.at(Board::BOARD_ROW * i + j).toInt() != board->get(Board::BOARD_ROW * i + j))
                setData(index(Board::BOARD_ROW*i + j), QString::number(board->get(Board::BOARD_ROW * i + j)), Role::valueFromBoard);
    }
    emit boardChangedFromInside();
}

void Sudoku::onCheck() const
{
    emit solved(board->checkBoard());
}

void Sudoku::start()
{
    board->start();
    for(int i = 0; i < Board::NUMBER_OF_CELLS; ++i)
        setData(index(i), board->get(i) ? QString::number(board->get(i)) : "", Role::valueFromBoard);
    
    emit boardChangedFromInside();
}

void Sudoku::restart()
{
    for(auto& e : cells)
        e = "";
    start();
}
