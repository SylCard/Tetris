#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stddef.h>
#include <iostream>
#include <string>
#include "tetrimino.hpp"
#include "tetris.hpp"


#define COLUMNS 18
#define ROWS 22
int fps = 2 ;


bool isGameOver;
// Tetrimino definitions
Tetrimino tetrimino;

// start position of current piece
int currentx = 6 ,currenty = 21 ;


void reset(){
    tetrimino.reset(currentx,currenty);
    isGameOver = false;
}

void init(){
    //set background colour
    glClearColor(0.137255f, 0.137255f,0.556863f, 1.0f );

}

void reshape(int w,int h) {
   // the reshape function will allow the viewport to dynamically resize to always fit the display
   glViewport(0,0,(GLsizei)w,(GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);
   glMatrixMode(GL_MODELVIEW);
}

void displayScore(){
  glRasterPos2f(12.5, 17);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'S');
  glRasterPos2f(13.2, 17);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'C');
  glRasterPos2f(13.9, 17);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'O');
  glRasterPos2f(14.7, 17);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'R');
  glRasterPos2f(15.4, 17);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');

  int score = tetrimino.getScore();
  std::string s = std::to_string(score);

  glRasterPos2f(13.7, 16);

  for (int x = 0; x < s.length() ; x++) {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,s[x]);
  }

}

void displayNextPiece(){

  glRasterPos2f(12.5, 14);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'N');
  glRasterPos2f(13.2, 14);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
  glRasterPos2f(13.7, 14);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'X');
  glRasterPos2f(14.2, 14);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'T');
  glRasterPos2f(15.2, 14);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'P');
  glRasterPos2f(15.7, 14);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'I');
  glRasterPos2f(16.0, 14);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
  glRasterPos2f(16.5, 14);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'C');
  glRasterPos2f(17.2, 14);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');

  //draw next piece from y = 12 x = 14
  tetrimino.drawNextPiece();

}


void drawGrid(){
  glLineWidth(1.0f);
  glColor3f(1.0f,0.5f,1.0f);
  for (int x = 2 ; x < 12; x++) {
    for (int y = 0; y < 20; y++) {
        glBegin(GL_LINE_LOOP);
          glVertex2f(x,y);
          glVertex2f(x+1,y);
          glVertex2f(x+1,y+1);
          glVertex2f(x,y+1);
        glEnd();
    }
  }
}

void keyboard(unsigned char key, int, int){
	std::cerr << "\t you pressed the " << key << " key" << std::endl;

	switch (key)
	{
		case 'q': exit(1); // quit!

    case 'h': fps = 8 ; break;  // hard mode

    case 'e': fps = 2 ; break; // exit hard mode

    case 'n': tetrimino.newGame() ; break;     //new game

	}

	glutPostRedisplay(); // force a redraw
}

void directions(int key, int,int){
  //this method will handle the direction of the current block
  // handles direction keys
	switch (key)
	{
		case GLUT_KEY_LEFT:
          tetrimino.move(1) ;
          break;
    case GLUT_KEY_RIGHT:
          tetrimino.move(-1) ;
          break;
		case GLUT_KEY_DOWN:
          tetrimino.move(0);
          break;
          // rotate piece
    case GLUT_KEY_UP: tetrimino.rotate() ; break;
	}

	glutPostRedisplay(); // force a redraw
}

void timer(int){
  glutPostRedisplay();
  //to redisplay 10 frames a second we know there are 1000ms in a second => 100ms per frame
  //approximately 10fps due to overhead added by the swap buffers and CPU/GPU performance
  glutTimerFunc(1000/fps,timer,0);

}

void displayGame(){
  if (tetrimino.gameOver()) {


    glRasterPos2f(5.0, 12);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'G');
    glRasterPos2f(5.7, 12);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'A');
    glRasterPos2f(6.3, 12);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'M');
    glRasterPos2f(7.0, 12);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');

    glRasterPos2f(7.7, 12);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'O');
    glRasterPos2f(8.4, 12);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'V');
    glRasterPos2f(9.0, 12);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
    glRasterPos2f(9.5, 12);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'R');
  }
  else{
    // draw the background
    drawGrid();
    // display score
    displayScore();
    // display next piece
    displayNextPiece();
    if (!tetrimino.hasLanded()) { //if the piece has not landed keep drawing it
      tetrimino.draw();
    }
    else {
      // piece has landed therefore we store it in our board
        tetrimino.store();
      //then generate a new piece
        tetrimino.reset(currentx,currenty);
    }
  }
}

void display(){
      glClear(GL_COLOR_BUFFER_BIT);
      displayGame();
      glutSwapBuffers();
}

int main(int argc, char **argv){

  glutInit(&argc, argv);
  //GLUT Double specifies that we are using double buffering
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
  glutInitWindowSize(360, 600);
  glutCreateWindow("TETRIS");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutTimerFunc(0,timer,0);
  //glut special will handle keyboard inputs for which there are predefined functions e.g. special
  glutSpecialFunc(directions);
  glutKeyboardFunc(keyboard);

  reset();

  init();
  glutMainLoop();
  return 0;
}
