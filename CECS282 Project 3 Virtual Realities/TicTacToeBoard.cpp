#include "GameBoard.h"
#include "TicTacToeBoard.h"

// Initialize the game board
TicTacToeBoard::TicTacToeBoard() : GameBoard() {
   for (int i = 0; i < BOARD_SIZE_T; i++)
      for (int j = 0; j < BOARD_SIZE_T; j++)
         mBoard[i][j] = EMPTY;
}

// Obtain possible moves, which are all the empty spaces
void TicTacToeBoard::GetPossibleMoves(std::vector<GameMove *> *list) const {
   for (int row = 0; row < BOARD_SIZE_T; row++) {
      for (int col = 0; col < BOARD_SIZE_T; col++) {
         if (mBoard[row][col] == EMPTY) {
            TicTacToeMove* tMove = new TicTacToeMove(row, col);
            list->push_back(tMove);
         }
      }
   }
}

// Place player marker onto board
void TicTacToeBoard::ApplyMove(GameMove *move) {

   // Save in history
   mHistory.push_back(move);

   // Cast GameMove to TicTacToeMove
   TicTacToeMove *tMove = dynamic_cast<TicTacToeMove*>(move);

   // If GameMove was pointing at a non-TicTacToeMove, throw exception
   if (tMove == nullptr)
      throw TicTacToeException("TicTacToeMove pointer is null.");

   // Place player marker at spot
   mBoard[tMove->mRow][tMove->mCol] = mNextPlayer;

   // If there is a winner, change the value to the value of the current player
   if (CheckWinner())
      mValue = mNextPlayer;

   // Increment turns and switch player
   mTurns++;
   mNextPlayer = -mNextPlayer;
}

// Remove player marker from board
void TicTacToeBoard::UndoLastMove() {

   // Get the most recent move (the one that will be undone)
   TicTacToeMove *undoMove = dynamic_cast<TicTacToeMove*>(mHistory.back());

   // If GameMove was pointing at a non-TicTacToeMove, throw exception
   if (undoMove == nullptr)
      throw TicTacToeException("OthelloMove pointer is null.");

   // Remove marker from board
   mBoard[undoMove->mRow][undoMove->mCol] = EMPTY;

   // free memory
   delete undoMove;

   mHistory.pop_back();

   // Decrement turns and switch player
   mTurns--;
   mNextPlayer = -mNextPlayer;
}

// FIX
bool TicTacToeBoard::CheckWinner() const {

   for (int row = 0; row < BOARD_SIZE_T; row++) {
      for (int col = 0; col < BOARD_SIZE_T; col++) {

         if (mBoard[row][col] == mNextPlayer) {

            // Delta's allow for 8-directional check
            for (int rowDelta = -1; rowDelta <= 1; rowDelta++) {
               for (int colDelta = -1; colDelta <= 1; colDelta++) {

                  // Move over to the next spot
                  // Resets value of i and j on future checks
                  // k = number of checks needed to find 3 in a row
                  int i = row + rowDelta;
                  int j = col + colDelta;
                  int k = 1;

                  while (mBoard[i][j] == mNextPlayer && InBounds(i, j) &&
                     !(rowDelta == 0 && colDelta == 0) && k < 3) {
                     i += rowDelta;
                     j += colDelta;
                     k++;
                  }

                  // There is a winner if 3 pieces are in a row
                  if (k == 3)
                     return true;
               }
            }
         }
      }
   }
   
   // Else, return false
   return false;
}