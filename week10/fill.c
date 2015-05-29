#include <stdlib.h>
#include <GL/glut.h>

	GLfloat colors[][3] = {{1.0,0.0,0.0},{0.0,1.0,0.0},
	{0.0,0.0,1.0}, {0.0,0.0,0.0}};
       
  	GLfloat M = 1.0;

void polygon(int a, int b, int c , int d)
{
 	glBegin(GL_POLYGON);
		glColor3fv(colors[a]);
		glVertex2f(0,M);
		glColor3fv(colors[b]);
		glVertex2f(-M,0);
		glColor3fv(colors[c]);
		glVertex2f(0,-2*M);
		glColor3fv(colors[d]);
		glVertex2f(2*M,0);
	glEnd();
																										}

void colorcube(void)
{
	polygon(0,3,2,1);
	polygon(2,3,7,6);
	polygon(0,4,7,3);
	polygon(1,2,6,5);
	polygon(4,5,6,7);
	polygon(0,1,5,4);
}

void display(void)
{
 glClearColor(1.0, 1.0, 1.0, 1.0);
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
 colorcube();
 glFlush();
	glutSwapBuffers();
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
            2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
            2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

int
main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("colorcube");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
	   glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
