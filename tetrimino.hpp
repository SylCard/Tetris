//
//  tetrimino.hpp
//  Tetris
//
//  Created by Sylvester Cardorelle on 13/12/2017.
//  Copyright © 2017 Sylvester Cardorelle. All rights reserved.
//

#ifndef tetrimino_hpp
#define tetrimino_hpp

#include <stdio.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <ctime>

#include "board.hpp"

class Tetrimino {
private:
  int level ;
  int currentPiece ;
  int nextPiece ;
  int noOfRotations;
  int shapes[7][4][4] ;
  bool blocks[4][4];
  int curX ;
  int curY ;
  Board board ;
public:
  Tetrimino();
  void draw();
  void reset(int x, int y);
  void rotate();
  void rotateCcw();
  void rotateBack();
  void move(int direction);
  bool leftCollision();
  bool rightCollision();
  bool bottomCollision();
  bool rotationCollision(bool newBlocks[][4]);
  bool tetriminoCollision(int x, int y);
  bool hasLanded();
  void store();
  bool gameOver();
  void newGame();
  int  getScore();
  void drawNextPiece();
};

#endif /* tetrimino_hpp */
