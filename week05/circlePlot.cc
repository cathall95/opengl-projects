#include <GL/glut.h>

class scrPt {
public:
  GLint x, y;
};

void setPixel (GLint x, GLint y)
{
  glBegin (GL_POINTS);
  glVertex2i (x, y);
  glEnd ( );
}

void circleMidpoint (scrPt circCtr, GLint radius)
{
  scrPt circPt;

  GLint p = 1 - radius;         // Initial value of midpoint parameter.

  circPt.x = 0;             // Set coordinates for top point of circle.
  circPt.y = radius;

  void circlePlotPoints (scrPt, scrPt);

  /* Plot the initial point in each circle quadrant. */
  circlePlotPoints (circCtr, circPt);

  /* Calculate next points and plot in each octant. */
  while (circPt.x < circPt.y) {
    circPt.x++;
    if (p < 0)
      p += 2 * circPt.x + 1;
    else {
      circPt.y--;
      p += 2 * (circPt.x - circPt.y) + 1;
    }
    circlePlotPoints (circCtr, circPt);
  }
}

void circlePlotPoints (scrPt circCtr, scrPt circPt)
{
  setPixel (circCtr.x + circPt.x, circCtr.y + circPt.y);
  setPixel (circCtr.x - circPt.x, circCtr.y + circPt.y);
  setPixel (circCtr.x + circPt.x, circCtr.y - circPt.y);
  setPixel (circCtr.x - circPt.x, circCtr.y - circPt.y);
  setPixel (circCtr.x + circPt.y, circCtr.y + circPt.x);
  setPixel (circCtr.x - circPt.y, circCtr.y + circPt.x);
  setPixel (circCtr.x + circPt.y, circCtr.y - circPt.x);
  setPixel (circCtr.x - circPt.y, circCtr.y - circPt.x);
}

