#include <GL/freeglut.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <time.h>
#include <ctime>

#define HALF_PI 1.57079632679489661923
#define PI 3.14159265358979323846
#define QUARTER_PI 0.7853982
#define TWO_PI 6.28318530717958647693
#define TAU TWO_PI
#define boolean bool
#define UP (unsigned char)GLUT_UP
#define DOWN (unsigned char)GLUT_DOWN
#define LEFT (unsigned char)37
#define RIGHT (unsigned char)39
#define CENTER (unsigned char)3
#define ALT (unsigned char)18
#define CONTROL (unsigned char)17
#define SHIFT (unsigned char)16
#define BACKSPACE (unsigned char)8
#define F1 (unsigned char)112
#define F2 (unsigned char)113
#define F3 (unsigned char)114
#define F4 (unsigned char)115
#define F5 (unsigned char)116
#define F6 (unsigned char)117
#define F7 (unsigned char)118
#define F8 (unsigned char)119
#define F9 (unsigned char)120
#define F10 (unsigned char)121
#define F11 (unsigned char)122
#define F12 (unsigned char)123
#define ENTER (unsigned char)10
#define SPACE (unsigned char)32
#define vertex glVertex
#define begin glBegin
#define end glEnd
#define null NULL

namespace Processing {

  int mouseButton;
  int mouseState;
  int width, height;
  int mouseX=0, mouseY=0, pmouseX=0, pmouseY=0;
  bool mouseIsPressed, keyIsPressed;
  unsigned char key;
  std::string title = "sketch";
  long frameCount=0;
  int SR=0, SG=0, SB=0;
  bool strokeEnable=true;
  int FR=255, FG=255, FB=255;
  bool fillEnable=true;

  void setup();
  void draw();
  void mousePressed();
  void mouseReleased();
  void keyPressed();


  //***********************************API*****************************************
  void stroke(int R, int G, int B) {
    SR=R; 
    SG=G; 
    SB=B;
    strokeEnable=true;
  }
  void noStroke() {
    strokeEnable=false;
  }
  void fill(int R, int G, int B) {
    FR=R; 
    FG=G; 
    FB=B;
    fillEnable=true;
  }
  void noFill() {
    fillEnable=false;
  }

  int year() {
    const long long int T = time(NULL);
    return localtime (&T)->tm_year;
  }
  int mounth() {
    const long long int T = time(NULL);
    return localtime (&T)->tm_mon;
  }
  int weekDay() {
    const long long int T = time(NULL);
    return localtime (&T)->tm_wday;
  }
  int day() {
    const long long int T = time(NULL);
    return localtime (&T)->tm_mday;
  }
  int hour() {
    const long long int T = time(NULL);
    return localtime (&T)->tm_hour;
  }
  int minute() {
    const long long int T = time(NULL);
    return localtime (&T)->tm_min;
  }
  int second() {
    const long long int T = time(NULL);
    return localtime (&T)->tm_sec;
  }

  void size(int w, int h) {
    width=w;
    height=h;
  }

  void line(float x, float y, float x1, float y1) {
    if (strokeEnable) {
      glColor3ub(SR, SG, SB);
      glBegin(GL_LINES);
      glVertex2d(x, y);
      glVertex2d(x1, y1);
      glEnd();
    }
  }

  void rect(float x, float y, float w, float h) {
    if (fillEnable) {
      glColor3ub(FR, FG, FB);
      glRecti(x, y, w+x, y+h);
    }
    if (strokeEnable) {
      glColor3ub(SR, SG, SB);
      line(x, y, x+w, y);
      line(x, y, x, y+h);
      line(x+w, y+h, x+w, y);
      line(x+w, y+h, x, y+h);
    }
  }


  void triangle(float x, float y, float x1, float y1, float x2, float y2) {
    if (fillEnable) {
      glColor3ub(FR, FG, FB);
      glBegin(GL_TRIANGLES);
      glVertex2d(x, y);
      glVertex2f(x1, y1);
      glVertex2d(x2, y2);
      glEnd();
    }
    if (strokeEnable) {
      line(x, y, x1, y1);
      line(x1, y1, x2, y2);
      line(x2, y2, x, y);
    }
  }


  void ellipse(float xCenter, float yCenter, float dx, float dy) {
    float rx=dx/2;
    float ry=dy/2;
    int pointCount = 360;
	if (fillEnable) {
	  strokeEnable=false;	
	  const float step = float(2 * M_PI / pointCount);
      for (float angle = 0; angle < float(2 * M_PI); angle += step)
      {
        const float ddx = rx * cosf(angle)+xCenter;
        const float ddy = ry * sinf(angle)+yCenter;
        const float ddx2 = rx * cosf(angle+step)+xCenter;
        const float ddy2 = ry * sinf(angle+step)+yCenter;
        triangle(ddx, ddy, ddx2, ddy2,xCenter,yCenter);
      }
      strokeEnable=true;
    }
    if (strokeEnable) {
      const float step = float(2 * M_PI / pointCount);
      for (float angle = 0; angle < float(2 * M_PI); angle += step)
      {
        const float ddx = rx * cosf(angle)+xCenter;
        const float ddy = ry * sinf(angle)+yCenter;
        const float ddx2 = rx * cosf(angle+step)+xCenter;
        const float ddy2 = ry * sinf(angle+step)+yCenter;
        line(ddx, ddy, ddx2, ddy2);
      }
    }
    
  }

  

  void strokeWeight(float w) {
    glLineWidth(w);
  }





  void quad(float x, float y, float x1, float y1, float x2, float y2, float x3, float y3) {
    if (fillEnable) {
      glColor3ub(FR, FG, FB);
      glBegin(GL_QUADS);
      glVertex2d(x, y);
      glVertex2d(x1, y1);
      glVertex2d(x2, y2);
      glVertex2d(x3, y3);
      glEnd();
    }
    if (strokeEnable) {
      line(x, y, x1, y1);
      line(x1, y1, x2, y2);
      line(x2, y2, x3, y3);
      line(x, y, x3, y3);
    }
  }

  void background(int r, int g, int b) {
    fill(r, g, b);
    rect(-25, -25, width+50, height+50);
  }



  float dist(float x2, float y2, float x1, float y1) {
    float x=x1-x2;
    float y=y1-y2;
    float d=sqrt(x*x+y*y);
    return d;
  }




  void randomSeed(int seed) {
    srand(seed);
  }

  int random(int start = 0, int end = 1024) {
    return rand()%(start-end)+start;
  }

  //***********************************API*****************************************



  void display()
  {
    draw();
    //glutSwapBuffers();
	glutPostRedisplay();
    frameCount++;
    pmouseX=mouseX;
    pmouseY=mouseY;
    glFlush();
    glEnd();
  }

  void mousePress(int button, int state, int x, int y) {
    mouseButton=button;
    mouseIsPressed=state==DOWN;
    if (mouseIsPressed) {
      mousePressed();
    } else {
      mouseReleased();
    }
    glutPostRedisplay();
  }



  void mouseCoordinate(int x, int y)
  {
    mouseX=x;
    mouseY=y;
    glutPostRedisplay();
  }  


  void keyPress(unsigned char k, int x, int y)
  {
    key = k;
    keyPressed();
  }

  void setTitle(std::string title) {
    glutSetWindowTitle(title.c_str());
  }
}
