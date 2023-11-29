#include <QQmlProperty>
#include "sudoku.h"


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
