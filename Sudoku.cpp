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
    
    return cells[index.row()];
}

QHash<int, QByteArray> Sudoku::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole + 1] = "Value";
    return roles;
}

void Sudoku::onNewGame()
{
    qDebug() << "New game pressed";
}
