#include "base.h"

namespace Processing{
	
	int a=100;
	
	
void setup(){
	size(500,500);
}
void draw(){
	background(0,0,0);
	stroke(0,255,0);
	fill(250,250,0);
	line(0,0,width,height);
	ellipse(mouseX,mouseY,a,a);
}

void keyPressed(){
		a++;
}

void mousePressed(){}
void mouseReleased(){}
}