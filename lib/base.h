#include <GL/freeglut.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <time.h>

#define HALF_PI 1.57079632679489661923
#define PI 3.14159265358979323846
#define QUARTER_PI 0.7853982
#define TWO_PI 6.28318530717958647693
#define TAU TWO_PI
#define boolean bool
#define UP GLUT_UP
#define DOWN GLUT_DOWN
#define LEFT 37
#define RIGHT 39
#define CENTER 3
#define ALT 18
#define CONTROL 17
#define SHIFT 16
#define BACKSPACE 8
#define F1 112
#define F2 113
#define F3 114
#define F4 115
#define F5 116
#define F6 117
#define F7 118
#define F8 119
#define F9 120
#define F10 121
#define F11 122
#define F12 123
#define ENTER 10
#define SPACE 32
#define vertex glVertex
#define begin glBegin
#define end glEnd
#define null NULL

namespace Processing{

int mouseButton;
int mouseState;
int width, height;
int mouseX=0, mouseY=0,pmouseX=0,pmouseY=0;
bool mouseIsPressed,keyIsPressed;
unsigned char key;
std::string title = "sketch";
long frameCount=0;
int SR=0,SG=0,SB=0;
bool strokeEnable=true;
int FR=255,FG=255,FB=255;
bool fillEnable=true;


void setup();
void draw();
void mousePressed();
void mouseReleased();
void keyPressed();


//***********************************API*****************************************
void stroke(int R,int G,int B){
	SR=R; SG=G; SB=B;
	strokeEnable=true;
}
void noStroke(){strokeEnable=false;}
void fill(int R,int G,int B){
	FR=R; FG=G; FB=B;
	fillEnable=true;
}
void noFill(){fillEnable=false;}
/*
int year(){
	
}
int mounth(){
	
}
int weekDay(){
	
}
int day(){
	
}
int hour(){
	
}
int minute(){
	
}
int second(){
	
}
*/
void size(int w, int h) {
  width=w;
  height=h;
}

void line(float x, float y, float x1, float y1) {
	if(strokeEnable){
		glBegin(GL_LINES);
		glVertex2d(x, y);
		glVertex2d(x1, y1);
		glEnd();
	}	
}

void rect(float x, float y, float w, float h) {
	if(fillEnable){
		glColor3ub(FR,FG,FB);
		glRecti(x, y, w+x, y+h);
	}
	if(strokeEnable){
		glColor3ub(SR,SG,SB);
		line(x,y,x+w,y);
		line(x,y,x,y+h);
		line(x+w,y+h,x+w,y);
		line(x+w,y+h,x,y+h);
	}
}

void ellipse(float xCenter, float yCenter, float dx, float dy) {
	float rx=dx/2;
	float ry=dy/2;
	int pointCount = 360;
	if(strokeEnable){
		const float step = float(2 * M_PI / pointCount);
		begin(GL_LINE_STRIP);
		for (float angle = 0; angle < float(2 * M_PI); angle += step)
		{
			glColor3ub(SR,SG,SB);
			glBegin(GL_QUADS);
			const float dx = rx * cosf(angle);
			const float dy = ry * sinf(angle);
			glVertex2f(dx + xCenter, dy + yCenter);
		}
		end();
	}
	if(fillEnable){
		const float step = float(2 * M_PI) / pointCount;
		begin(GL_TRIANGLE_FAN);
		glVertex2f(xCenter, yCenter);
		for (float angle = 0; angle <= float(2 * M_PI); angle += step)
		{
			glColor3ub(FR,FG,FB);
			float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
			const float dx = rx * cosf(a);
			const float dy = ry * sinf(a);
			glVertex2f(dx + xCenter, dy + yCenter);
		}
		end();
	}
}

void triangle(float x, float y, float x1, float y1, float x2, float y2) {

      glBegin(GL_TRIANGLES);
      glVertex2d(x, y);
      glVertex2f(x1, y1);
      glVertex2d(x2, y2);
      glEnd();
}

void strokeWeight(float w) {
  glLineWidth(w);
}



  

void quad(float x, float y, float x1, float y1, float x2, float y2, float x3, float y3) {
  glBegin(GL_QUADS);
  glVertex2d(x, y);
  glVertex2d(x1, y1);
  glVertex2d(x2, y2);
  glVertex2d(x3, y3);
  glEnd();
}

void background(int r, int g, int b) {
  glColor3ub(r, g, b);
  rect(0,0,width,height);
}



float dist(float x2, float y2, float x1, float y1) {
  float x=x1-x2;
  float y=y1-y2;
  float d=sqrt(x*x+y*y);
  return d;
}




void randomSeed(int seed){
	srand(seed);
}

int random(int start = 0, int end = 1024){
	return rand()%(start-end)+start;
}

//***********************************API*****************************************



void display()
{
  draw();
  //glutSwapBuffers();
  frameCount++;
  pmouseX=mouseX;
  pmouseY=mouseY;
  glFlush();
  glEnd();
}

void mousePress(int button, int state, int x, int y) {
  mouseButton=button;
  mouseIsPressed=state==DOWN;
  if(mouseIsPressed){
    mousePressed();
  }else{
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

void setTitle(std::string title){
	glutSetWindowTitle(title.c_str());
}


}