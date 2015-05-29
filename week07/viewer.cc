/* Simple geometry viewer:  Left mouse: rotate;  Middle mouse:  zoom;  Right mouse:   menu;  ESC to quit 
 The function InitGeometry() initializes  the geometry that will be displayed. */
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

#define MAX_TRIANGLES (10)

struct Point {float x[3];   float n[3]; };
struct Triangle {   Point v[3];  };

Triangle triangleList[MAX_TRIANGLES];
int triangleCount = 0;
void InitGeometry();
 
/* Viewer state */
float sphi=90.0, stheta=45.0;
float sdepth = 10;
float zNear=1.0, zFar=100.0;
float aspect = 5.0/4.0;
float xcam = 0, ycam = 0;
long xsize, ysize;
int downX, downY;
bool leftButton = false, middleButton = false;

int i,j;
GLfloat light0Position[] = { 0, 1, 0, 1.0}; 
int displayMenu, mainMenu;
enum {WIREFRAME, HIDDENLINE, FLATSHADED, SMOOTHSHADED};
int displayMode = WIREFRAME;
 
void MyIdleFunc(void) { glutPostRedisplay();} /* things to do while idle */
void RunIdleFunc(void) {   glutIdleFunc(MyIdleFunc); }
void PauseIdleFunc(void) {   glutIdleFunc(NULL); }
 
void DrawSmoothShaded(void)
{
  int i;
  assert( triangleCount < MAX_TRIANGLES );
  glColor3f(0.8f, 0.2f, 0.8f);
  glBegin ( GL_TRIANGLES ) ;
  for ( i = 0; i < triangleCount; ++i ) {
    glNormal3fv( triangleList[i].v[0].n );
    glVertex3fv( triangleList[i].v[0].x );
    glNormal3fv( triangleList[i].v[1].n );
    glVertex3fv( triangleList[i].v[1].x );
    glNormal3fv( triangleList[i].v[2].n );
    glVertex3fv( triangleList[i].v[2].x ); }
  glEnd ( ) ;
}
 
void DrawWireframe(void)
{
  int i;
  glColor3f(1.0, 1.0, 1.0);
  for ( i = 0; i < triangleCount; ++i ) {
    glBegin(GL_LINE_STRIP);
    glVertex3fv( triangleList[i].v[0].x );
    glVertex3fv( triangleList[i].v[1].x );
    glVertex3fv( triangleList[i].v[2].x );
    glVertex3fv( triangleList[i].v[0].x );
    glEnd();
  }
}
 
void DrawFlatShaded(void)
{
  int i;
  glEnable(GL_POLYGON_OFFSET_FILL);
  glColor3f(0.8f, 0.2f, 0.8f);
  glBegin ( GL_TRIANGLES ) ;
  for ( i = 0; i < triangleCount; ++i ) {
    glVertex3fv( triangleList[i].v[0].x );
    glVertex3fv( triangleList[i].v[1].x );
    glVertex3fv( triangleList[i].v[2].x );   }
  glEnd ( ) ;
  glDisable(GL_POLYGON_OFFSET_FILL);
}
 
void DrawHiddenLine(void)
{
  glEnable(GL_POLYGON_OFFSET_FILL);
  glColor3f(0,0,0);
  glBegin ( GL_TRIANGLES ) ;
  for ( i = 0; i < triangleCount; ++i ) {
    glVertex3fv( triangleList[i].v[0].x );
    glVertex3fv( triangleList[i].v[1].x );
    glVertex3fv( triangleList[i].v[2].x );   }
  glEnd ( ) ;
  glDisable(GL_POLYGON_OFFSET_FILL);
  glColor3f(1.0,1.0,1.0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin ( GL_TRIANGLES ) ;
  for ( i = 0; i < triangleCount; ++i ) {
    glVertex3fv( triangleList[i].v[0].x );
    glVertex3fv( triangleList[i].v[1].x );
    glVertex3fv( triangleList[i].v[2].x );   }
  glEnd ( ) ;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
 
void ReshapeCallback(int width, int height)
{
  xsize = width; 
  ysize = height;
  aspect = (float)xsize/(float)ysize;
  glViewport(0, 0, xsize, ysize);

  glutPostRedisplay();
}
 
void SetDisplayMenu(int value)
{
  displayMode = value;
  switch(value) {
    case WIREFRAME:
	glShadeModel(GL_FLAT); glDisable(GL_LIGHTING);
       	break;
    case HIDDENLINE:
       glShadeModel(GL_FLAT); glDisable(GL_LIGHTING);
       break;
    case FLATSHADED:
      glShadeModel(GL_FLAT); glEnable(GL_LIGHTING);
      break;
    case SMOOTHSHADED:
     glShadeModel(GL_SMOOTH); glEnable(GL_LIGHTING);
     break;
  }
  glutPostRedisplay();
}
 
void SetMainMenu(int value)
{
  switch(value)
  {
  case 99:
    exit(0);
    break;
  }
}
 
void DisplayCallback(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(64.0, aspect, zNear, zFar);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity(); 
  glTranslatef(0.0,0.0,-sdepth);
  glRotatef(-stheta, 1.0, 0.0, 0.0);
  glRotatef(sphi, 0.0, 0.0, 1.0);
  switch (displayMode) {
    case WIREFRAME: DrawWireframe();     break;
    case HIDDENLINE: DrawHiddenLine();     break;
    case FLATSHADED: DrawFlatShaded();     break;
    case SMOOTHSHADED: DrawSmoothShaded();     break;   }
  glutSwapBuffers();
}
 
void KeyboardCallback(unsigned char ch, int x, int y)
{
  switch (ch) {
  case 27:
    exit(0);
    break;
  }
  glutPostRedisplay();
}
 
void MouseCallback(int button, int state, int x, int y)
{
  downX = x; downY = y;
  leftButton = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));
  middleButton = ((button == GLUT_MIDDLE_BUTTON) &&  (state == GLUT_DOWN));
  glutPostRedisplay();
}
 
void MotionCallback(int x, int y)
{
  if (leftButton){sphi+=(float)(x-downX)/4.0;stheta+=(float)(downY-y)/4.0;} // rotate
  if (middleButton){sdepth += (float)(downY - y) / 10.0;  } // scale
  downX = x;   downY = y; 
  glutPostRedisplay();
}
 
void InitGL()
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutCreateWindow("CS4815 Triangle Viewer");
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glPolygonOffset(1.0, 1.0);
  glDisable(GL_CULL_FACE);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_DIFFUSE);
  glLightfv (GL_LIGHT0, GL_POSITION, light0Position);
  glEnable(GL_LIGHT0);
  glutReshapeFunc(ReshapeCallback);
  glutDisplayFunc(DisplayCallback);
  glutKeyboardFunc(KeyboardCallback);
  glutMouseFunc(MouseCallback);
  glutMotionFunc(MotionCallback);
}
 
void InitMenu()
{
  displayMenu = glutCreateMenu(SetDisplayMenu);
  glutAddMenuEntry("Wireframe", WIREFRAME);
  glutAddMenuEntry("Hidden Line", HIDDENLINE);
  glutAddMenuEntry("Flat Shaded", FLATSHADED);
  glutAddMenuEntry("Smooth Shaded", SMOOTHSHADED);
  mainMenu = glutCreateMenu(SetMainMenu);
  glutAddSubMenu("Display", displayMenu);
  glutAddMenuEntry("Exit", 99);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}
 
void InitGeometry()
{
  triangleCount = 2;
  /* coordinates */
  triangleList[0].v[0].x[0] = 0;   triangleList[0].v[0].x[1] = 0;   triangleList[0].v[0].x[2] = 0;
  triangleList[0].v[1].x[0] = 0;   triangleList[0].v[1].x[1] = 1;   triangleList[0].v[1].x[2] = 0;
  triangleList[0].v[2].x[0] = 1;   triangleList[0].v[2].x[1] = 0;   triangleList[0].v[2].x[2] = 0;
  triangleList[1].v[0].x[0] = 0;   triangleList[1].v[0].x[1] = 0;   triangleList[1].v[0].x[2] = 0;
  triangleList[1].v[1].x[0] = 0;   triangleList[1].v[1].x[1] = 0;   triangleList[1].v[1].x[2] = 1;
  triangleList[1].v[2].x[0] = 0;   triangleList[1].v[2].x[1] = 1;   triangleList[1].v[2].x[2] = 0;
  /* normals */
  triangleList[0].v[0].n[0] = 0.7;   triangleList[0].v[0].n[1] = 0;   triangleList[0].v[0].n[2] = 0.7;
  triangleList[0].v[1].n[0] = 0.7;   triangleList[0].v[1].n[1] = 0;   triangleList[0].v[1].n[2] = 0.7;
  triangleList[0].v[2].n[0] = 0;   triangleList[0].v[2].n[1] = 0;   triangleList[0].v[2].n[2] = 1;
  triangleList[1].v[0].n[0] = 0.7;   triangleList[1].v[0].n[1] = 0;   triangleList[1].v[0].n[2] = 0.7;
  triangleList[1].v[1].n[0] = 1;   triangleList[1].v[1].n[1] = 0;   triangleList[1].v[1].n[2] = 0;
  triangleList[1].v[2].n[0] = 0.7;    triangleList[1].v[2].n[1] = 0;   triangleList[1].v[2].n[2] = 0.7;
}
 
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  InitGL();
  InitMenu();
  InitGeometry();
  glutMainLoop();
}
 
