#include "sudoku.h"


Sudoku::Sudoku(QObject *parent)
{
    std::memset(&board, 0, sizeof(board));
    generate();
}

void Sudoku::generate()
{   
    for(int clues = (rand() % 4) + 17; clues; --clues)
    {
        int i = 0;
        int j = 0;
        
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

bool Sudoku::checkDigit(int row, int col, int d) const noexcept
{
    bool result = true;
    for (int i = 0; i < 9 && result; ++i)
        result = !(board[row][i] == d || board[i][col] == d || board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == d);
    
    return result;
}
