#include <QQmlProperty>
#include "sudoku.h"


Sudoku::Sudoku(QObject *parent) : QAbstractListModel(parent), board(std::make_unique<Board>())
{
    cells.reserve(81);
    for(int i = 0; i < 81; ++i)
        cells.push_back(board->get(i) ? QString::number(board->get(i)) : "");
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
    return roles;
}

bool Sudoku::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!hasIndex(index.row(), index.column(), index.parent()) || !value.isValid())
        return false;
    board->set(index.row(), value.toString().toInt());
    //emit dataChanged(index, index, { role } );
    return true;
}

void Sudoku::onNewGame()
{
    qDebug() << "New game pressed";
}

void Sudoku::onSolve()
{
    qDebug() << "Solve pressed";
    board->solve();
    
}

void Sudoku::onCheck() const
{
    if(board->checkBoard())
        qDebug() << "Well done";
    else
        qDebug() << "Wrong sudoku";
}
