//
//  board.hpp
//  Tetris
//
//  Created by Sylvester Cardorelle on 18/12/2017.
//  Copyright © 2017 Sylvester Cardorelle. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include <stdio.h>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Board {
private:
  bool board[20][12];

public:
  Board();
  void storePiece(bool block[][4],int curX, int curY);
  void draw();
  void print();
  bool isBoardCollision(bool block[][4],int curX,int curY);
  bool hasReachedTop();
  void reset();
  int score ;
};

#endif /* board_hpp */
