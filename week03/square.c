/* This program illustrates the use of the glut library for
interfacing with a Window System */

/* The program opens a window, clears it to black,
then draws a box at the location of the mouse each time the
left button is clicked. The right button exits the program

The program also reacts correctly when the window is
moved or resized by clearing the new window to black*/

#include <GL/glut.h>
#include <stdlib.h>

/* globals */
int b;
GLsizei wh = 500, ww = 500; /* initial window size */
GLfloat size = 3.0;   /* half side length of square */


void drawSquare(int x, int y)
{
  y=wh-y;
  glColor3ub( (char) rand()%256, (char) rand()%256, (char) rand()%256);
  glBegin(GL_POLYGON);
  if(b == 1){
  glVertex2f(x+2, y+2);
  glVertex2f(x-2, y+2);
  glVertex2f(x-2, y-2);
  glVertex2f(x+2, y-2);
  }
  if(b == 2){
  glVertex2f(x+6, y+6);
  glVertex2f(x-6, y+6);
  glVertex2f(x-6, y-6);
  glVertex2f(x+6, y-6);
  }
  if(b == 3){
  glVertex2f(x+10, y+10);
  glVertex2f(x-10, y+10);
  glVertex2f(x-10, y-10);
  glVertex2f(x+10, y-10);
  }
  glEnd();
  glFlush();
  glutSwapBuffers();
}


/* rehaping routine called whenever window is resized
or moved */

void myReshape(GLsizei w, GLsizei h)
{

  /* adjust clipping box */

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); 
  glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity(); 

  /* adjust viewport and clear */

  glViewport(0,0,w,h);
  glClearColor (0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
  glutSwapBuffers();

  /* set global size for use by drawing routine */

  ww = w;
  wh = h; 
}

void myinit(void)
{

  glViewport(0,0,ww,wh);

  /* Pick 2D clipping window to match size of screen window 
     This choice avoids having to scale object coordinates
     each time window is resized */

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); 
  glOrtho(0.0, (GLdouble) ww , 0.0, (GLdouble) wh , -1.0, 1.0);

  /* set clear color to black and clear window */

  glClearColor (0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();

  /* callback routine for reshape event */

  glutReshapeFunc(myReshape);

}

void mouse(int btn, int state, int x, int y)
{
   if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
   	 b= 1;
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    	b= 2;
    if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)
    	b= 3;
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_UP)   exit(0);
}
 void quit(unsigned char key, int x, int y)
{
  if (key == 'q' || key == 'Q')
    exit(0);
}
/* display callback required by GLUT 3.0 */

void display(void)
{}

int main(int argc, char** argv)
{

  glutInit(&argc,argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutCreateWindow("square");
  myinit ();

  glutReshapeFunc (myReshape);
  glutMouseFunc (mouse);
  glutMotionFunc(drawSquare);
  glutDisplayFunc(display);
  glutKeyboardFunc(quit);       // set keyboard callback function

  glutMainLoop();

}
