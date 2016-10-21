#include "TicTacToeView.h"

using namespace std;

// Method to print a human-understandable TicTacToe Board
void TicTacToeView::PrintBoard(ostream &out) const {

   // Labeling of the columns on top
   out << " -  0  1  2  " << endl;

   for (int row = 0; row < BOARD_SIZE_T; row++) {

      // Labeling of rows on left side
      out << " " << row << " ";

      for (int col = 0; col < BOARD_SIZE_T; col++) {

         // Replace 0, 1, -1 w/ game markers
         if (mTicTacToeBoard->mBoard[row][col] == TicTacToeBoard::Player::X)
            out << " X ";
         else if (mTicTacToeBoard->mBoard[row][col] == TicTacToeBoard::Player::O)
            out << " O ";
         else
            out << " . ";
      }

      // Make it look better
      out << endl;
   }
}