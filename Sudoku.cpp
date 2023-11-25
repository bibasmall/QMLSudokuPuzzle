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
    qDebug() << "Oh yes we got here";
    return true;
}

void Sudoku::onNewGame()
{
    qDebug() << "New game pressed";
}

void Sudoku::onCheck() const
{
    qDebug() << "Check pressed";
}
