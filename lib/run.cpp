#include "sketch.h"



int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  Processing::setup();
  glutInitWindowSize(Processing::width, Processing::height);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(200, 200);
  glutCreateWindow(Processing::title.c_str());
  glLoadIdentity();
  glOrtho(0, Processing::width, Processing::height, 0, 0, 0);
  srand(time(NULL));
  glutDisplayFunc(Processing::display);
  glutKeyboardFunc(Processing::keyPress);
  glutMouseFunc(Processing::mousePress);
  glutMotionFunc(Processing::mouseCoordinate);
  glutPassiveMotionFunc(Processing::mouseCoordinate);
  glViewport(0, 0, Processing::width, Processing::height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, Processing::width, Processing::height,0, 0, 1);
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT);
  glutMainLoop();
}