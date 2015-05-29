#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/*  Set initial size of the display window.  */
GLsizei winWidth = 600, winHeight = 600;  
bool leftButton = false;
float zoom = 1.0;
int whichpoint = 10;
GLint nCtrlPts = 6;
float downX, downY,downX2, downY2;
/*  Set size of world-coordinate clipping window.  */
GLfloat xwcMin, xwcMax;
GLfloat ywcMin, ywcMax;

class wcPt3D {
   public:
      GLfloat x, y, z;
};
wcPt3D ctrlPts [6] = { {-40.0, -40.0, 0.0}, {-10.0, 100.0, 0.0},
                 {10.0, -100.0, 0.0}, {40.0, 40.0, 0.0}, {40.0, 60.0, 0.0} , {30.0, 50.0, 0.0}};
void init (void)
{
   /*  Set color of display window to white.  */
   glClearColor (1.0, 1.0, 1.0, 0.0);
}

void clippingwindow(void)
{
float xval [6];
float yval [6];
int i;
for(i = 0;i<6;i++)
{
xval[i] = ctrlPts[i].x;
}
for(i = 0;i<6;i++)
{
yval[i] = ctrlPts[i].y;
}
xwcMin = xval[0];
xwcMax = xval[0];
ywcMin = yval[0];
ywcMax = yval[0];
for(i = 1;i<6;i++)
{
if(xwcMin > xval[i])
xwcMin = xval[i];
if(xwcMax < xval[i])
xwcMax = xval[i];
if(ywcMin > yval[i])
ywcMin = yval[i];
if(ywcMax < yval[i])
ywcMax = yval[i];
}
}

void plotPoint (wcPt3D bezCurvePt)
{
    glBegin (GL_POINTS);
        glVertex2f (bezCurvePt.x, bezCurvePt.y);
    glEnd ( );
}

/*  Compute binomial coefficients C for given value of n.  */
void binomialCoeffs (GLint n, GLint * C)
{
   GLint k, j;

   for (k = 0;  k <= n;  k++) {
      /*  Compute n!/(k!(n - k)!).  */
      C [k] = 1;
      for (j = n;  j >= k + 1;  j--)
        C [k] *= j;
      for (j = n - k;  j >= 2;  j--)
        C [k] /= j;
   }
}

void computeBezPt (GLfloat t, wcPt3D * bezPt, GLint nCtrlPts,
                    wcPt3D * ctrlPts, GLint * C)
{
   GLint k, n = nCtrlPts - 1;
   GLfloat bezBlendFcn;

   bezPt->x = bezPt->y = bezPt->z = 0.0;

   /*  Compute blending functions and blend control points. */
   for (k = 0; k < nCtrlPts; k++) {
      bezBlendFcn = C [k] * pow (t, k) * pow (1 - t, n - k);
      bezPt->x += ctrlPts [k].x * bezBlendFcn;
      bezPt->y += ctrlPts [k].y * bezBlendFcn;
      bezPt->z += ctrlPts [k].z * bezBlendFcn;
   }
}

void bezier (wcPt3D * ctrlPts, GLint nCtrlPts, GLint nBezCurvePts)
{
   wcPt3D bezCurvePt;
   GLfloat t;
   GLint *C;

   /*  Allocate space for binomial coefficients  */
   C = new GLint [nCtrlPts];

   binomialCoeffs (nCtrlPts - 1, C);
   for (int i = 0;  i <= nBezCurvePts;  i++) {
      t = GLfloat (i) / GLfloat (nBezCurvePts);
      computeBezPt (t, &bezCurvePt, nCtrlPts, ctrlPts, C);
      plotPoint (bezCurvePt);
   }
   delete [ ] C;
}

void displayFcn (void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //  Clear display window.

   /*  Set example number of control points and number of
    *  curve positions to be plotted along the Bezier curve.
    */
  glColor3f (0.0, 0.0, 1.0);
  glBegin(GL_LINES);
    glVertex2f(ctrlPts[0].x, ctrlPts[0].y);
        glVertex2f(ctrlPts[1].x, ctrlPts[1].y);
        glVertex2f(ctrlPts[1].x, ctrlPts[1].y);
	glVertex2f(ctrlPts[2].x, ctrlPts[2].y);
	glVertex2f(ctrlPts[2].x, ctrlPts[2].y);
	glVertex2f(ctrlPts[3].x, ctrlPts[3].y);
	glVertex2f(ctrlPts[3].x, ctrlPts[3].y);
	glVertex2f(ctrlPts[4].x, ctrlPts[4].y);
	glVertex2f(ctrlPts[4].x, ctrlPts[4].y);
	glVertex2f(ctrlPts[5].x, ctrlPts[5].y);
  glEnd();
  glFlush();
   GLint nBezCurvePts = 1000;
   glPointSize (4);
   glColor3f (1.0, 0.0, 0.0);   
glMatrixMode (GL_PROJECTION);
   glLoadIdentity ( );

   gluOrtho2D (xwcMin, xwcMax, ywcMin, ywcMax);

   glutPostRedisplay();   //  Set point color to red.
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ( );
   glTranslatef(downX2,downY2,0.0);
   bezier (ctrlPts, nCtrlPts, nBezCurvePts);
   glutSwapBuffers();
   glutPostRedisplay();
}

void winReshapeFcn (GLint newWidth, GLint newHeight)
{
   /*  Maintain an aspect ratio of 1.0.  */
   glViewport (0, 0, newHeight, newHeight);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ( );

   gluOrtho2D (xwcMin, xwcMax, ywcMin, ywcMax);

   glutPostRedisplay();
}

void MouseCallback(int button, int state, int x, int y)
{
  leftButton = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));
  downX = x; downY = y;
  int i = 0;
  whichpoint = 10;
  float tempx = 0,tempy = 0;
  float tempx2 = 0,tempy2 = 0;
  tempx =(float)x;
  tempy =(float)winHeight - y;
  float distancex,distancey;
  for(;i<nCtrlPts;i++)
  {
  tempx2 = (float)winWidth -ctrlPts[i].x;
  tempy2 = (float)winHeight - ctrlPts[i].y;
  distancex = (float)tempx2 / tempx;
  distancey = (float) tempy2 / tempy;
  if(distancex <= 1.3 && distancey <= 1.3)
  whichpoint = i;
}
  glutPostRedisplay();
}
 
void MotionCallback(int x, int y)
{
  if (leftButton)
  {
  if(whichpoint == 10)
  {
  downX2 = x - downX;
  downY2 = downY - y;
   }
  else
  {
  ctrlPts[whichpoint].x = (float)x;
  ctrlPts[whichpoint].y = (float)winHeight - y;
  glutPostRedisplay();
  }
  }
}

void keyboard(unsigned char key, int x, int y)
{
if (key == 'z'){
    xwcMin += 5;
    ywcMin += 5; 
	}
  if (key == 'Z'){
    xwcMin -= 5;
    ywcMin -= 5; 
	}
}

int main (int argc, char** argv)
{
   clippingwindow();
   glutInit (&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowPosition (50, 50);
   glutInitWindowSize (winWidth, winHeight);
   glutCreateWindow ("Bezier Curve");
   glutMouseFunc(MouseCallback);
   glutMotionFunc(MotionCallback);
   glutKeyboardFunc(keyboard);
   init ( );
   glutDisplayFunc (displayFcn);
   glutReshapeFunc (winReshapeFcn);
   glutMainLoop ( );
}
