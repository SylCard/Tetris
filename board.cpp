//
//  board.cpp
//  Tetris
//
//  Created by Sylvester Cardorelle on 18/12/2017.
//  Copyright © 2017 Sylvester Cardorelle. All rights reserved.
//

#include "board.hpp"

Board::Board(){
  this->score  = 0;
}

void Board::draw(){
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 12; j++) {
        if (board[i][j] == 1) {

            glRectd(j+1, 20-i, j, 19 -i);
        }
      }
  }
}

void Board::storePiece(bool block[][4],int curX,int curY){
    //store new tetrimino piece into the board
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
          if (block[i][j] == 1) {
              board[20-(curY - i)][(curX + j)-1]=1;
          }
        }
    }
    //check for a full row
    // check full row
    for (int y = 0; y < 20; ++y) {
        bool full = true;
        for (int x = 2; x < 12; ++x) {
            if (board[y][x] == 0) {
                full = false;
                break;
            }
        }

        if (full) {
            // increase score  by 1
            score++;

            for (int i = y; i > 0; --i) {
                for (int x = 0; x < 10; ++x) {
                    board[i][x] = board[i - 1][x];
                }
            }
            for (int i = 0; i < 10; ++i) {
                board[0][i] = 0;
            }

        }
    }



}

void Board::print() {
  for (int i = 0; i < 20; ++i)
   {
       for (int j = 0; j < 12; ++j)
       {
           std::cout << board[i][j] << ' ';
       }
       std::cout << std::endl;
   }
}

bool Board::isBoardCollision(bool block[][4],int curX,int curY){
      //check whether tetrimino is about to collide with a tetrimino on the board
      for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            if (block[x][y] == 1) {
                if (board[20-(curY - x)][(curX + y)-1] == 1 ) {
                  return true;
                }
            }
        }
      }

      return false;
}

bool Board::hasReachedTop(){
      //if the top layer of the board is fill then it is GAME OVER
      int y = 0 ;
        for (int x = 2 ; x < 12; x++) {
          if(board[y][x] == 1){
            return true;
          }
        }

      return false;

}

void Board::reset(){
  //clear board for new game
  for (size_t y = 0; y < 20; y++) {
    for (size_t x = 0; x < 12; x++) {
      board[y][x] = 0;
    }
  }
}
