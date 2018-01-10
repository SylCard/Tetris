//
//  tetrimino.cpp
//  Tetris
//
//  Created by Sylvester Cardorelle on 13/12/2017.
//  Copyright © 2017 Sylvester Cardorelle. All rights reserved.
//
#include "tetrimino.hpp"

void Tetrimino::reset(int x, int y){
  //draw game board
  board.draw();

  noOfRotations = 0;
  //set piece coordinates
  curX = x ;
  curY = y ;
  // using time as seed for random piece generator
  srand(time(0));
    // if the game has just begun, lets initialise the next Piece
  if (level == 0 ) {

    int dump1 = rand() % 7;
    int dump2 = rand() % 7;
    int shape = rand() % 7;
    nextPiece = shape ;
  }


  currentPiece = nextPiece;
  for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 4; y++) {
          blocks[x][y] = shapes[currentPiece][x][y];
      }
  }

  // generate new piece

  int dump1 = rand() % 7;
  int dump2 = rand() % 7;
  int shape = rand() % 7;
  nextPiece = shape ;

  //increase game level
  level++;
}

void Tetrimino::draw(){
    board.draw();



    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
          if (blocks[i][j] == 1) {

              glRectd(curX + j, curY - i, curX - 1 + j, curY - 1 - i);
          }
        }
     }

     // move piece down over time
     move(0);

}

bool Tetrimino::gameOver(){
    if (board.hasReachedTop()) {
        board.score = 0 ;
        level = 0 ;
      return true ;
    }

    return false;
}

void Tetrimino::rotate(){


    noOfRotations ++;
    if (currentPiece == 0 /* O piece*/ ) {
        ;
    }
     else if (currentPiece == 1 /* I piece */ || currentPiece == 2 /*S piece */  || currentPiece == 3 /* Z piece */) {
        if (noOfRotations % 2 == 0) {
            rotateBack();
        }
        else {
            rotateCcw();
        }
    }
    else if (currentPiece == 4 /* L piece */ || currentPiece == 5 /* J Piece */ || currentPiece == 6 /* T piece */) {
          rotateCcw();
        }


}

void Tetrimino::rotateCcw(){
    // pivot is [1][2]
    bool new_blocks[4][4] = {{0}};
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (blocks[y][x]) {
                int new_y = 1 - (x - 2);
                int new_x = 2 + (y - 1);
                if (0 <= new_y && new_y < 4 &&
                    0 <= new_x && new_x < 4) {
                    new_blocks[new_y][new_x] = 1;
                }
            }
        }
    }

    if (!rotationCollision(new_blocks)) {
        for (int y = 0; y < 4; ++y) {
            for (int x = 0; x < 4; ++x) {
                blocks[y][x] = new_blocks[y][x];
            }
        }
    }
    else {
       noOfRotations -= 1;
    }
}

void Tetrimino::rotateBack(){
    bool new_blocks[4][4] = {{0}};
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            new_blocks[y][x] = shapes[currentPiece][y][x];
        }
    }

    if (!rotationCollision(new_blocks)) {
        //memcpy(blocks, new_blocks, 4 * 4);
        for (int y = 0; y < 4; ++y) {
            for (int x = 0; x < 4; ++x) {
                blocks[y][x] = new_blocks[y][x];
            }
        }
    }
    else {
       noOfRotations -= 1;
    }
}

void Tetrimino::move(int direction){

  switch (direction) {
    case 0: //move down
        // if there is no collision
        if (!bottomCollision() && !tetriminoCollision(curX,curY - 1) ) {
        curY--;
        }; break ;
    case 1: //move left
      if (!leftCollision() && !tetriminoCollision(curX -1,curY)) {
        // if there is no collision
        curX--;
      } ; break ;
    case -1: //move right
    if (!rightCollision()&& !tetriminoCollision(curX +1 ,curY)) {
        // if there is no collision
        curX++;
    } ; break ;

  }
}

bool Tetrimino::rotationCollision(bool newBlocks[][4]){
    //check for left collision
    int predictedX = (curX - 1)  ;
    for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 4; y++) {
        if (newBlocks[x][y]==1) {
          if (predictedX+y < 2) {
            return true ;
          }
        }
      }
    }
    //check for right collision
    predictedX = (curX + 1)  ;
    for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 4; y++) {
        if (newBlocks[x][y]==1) {
          if (predictedX+y > 13) {
            return true ;
          }
        }
      }
    }
    //check for piece collision
    if (board.isBoardCollision(newBlocks,curX,curY)) {
      return true ;
    }

    return false;
}

bool Tetrimino::leftCollision(){
  //calculate block positions and if any are outside the game boundaries -> collision detected

  //check for left wall collision
  int predX = (curX - 1)  ;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (this->blocks[x][y]==1) {
        if (predX+y == 2) {
          return true ;
        }
      }
    }
  }


  return false;
}

bool Tetrimino::rightCollision(){
  //calculate block positions and if any are outside the game boundaries -> collision detected

  //check for right wall collision
  int predictedX = (curX + 1)  ;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (this->blocks[x][y]==1) {
        if (predictedX+y == 13) {
          return true ;
        }
      }
    }
  }
  return false;
}

bool Tetrimino::bottomCollision(){
  //calculate block positions and if any are outside the game boundaries -> collision detected

  //check for bottom wall collision
  int predY = (curY - 1)  ;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (this->blocks[x][y]==1) {
        if (predY-x == 0) {
          return true ;
        }
      }
    }
  }


  return false;
}

bool Tetrimino::tetriminoCollision(int x, int y){
      if (board.isBoardCollision(this->blocks,x,y)) {
        return true;
      }
      return false;
}

bool Tetrimino::hasLanded(){

  //a tetrimino has landed when it can no longer move down
  if ( bottomCollision() || tetriminoCollision(curX,curY - 1)) {
    return true;
  }
  return false ;
}

void Tetrimino::store(){
  board.storePiece(blocks,curX,curY);
  //redraw game board
  board.draw();

  board.print();
}

void Tetrimino::newGame(){
  board.reset();
  reset(6,21);
}

int Tetrimino::getScore(){
  return board.score ;
}

void Tetrimino::drawNextPiece(){


      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shapes[nextPiece][i][j] == 1) {
                glRectd(14+ j, 14 - i, 14 - 1 + j, 14 - 1 - i);
            }
          }
       }



}
