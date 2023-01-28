#include "base.h"

namespace Processing{
	
int a=1,b=3;

int lab[5][5]={
1,1,1,1,1,
1,0,0,0,1,
1,0,1,0,1,
1,0,1,0,1,
1,1,1,1,1,	
};

void igrok();
	
void setup(){
	size(500,500);
}
void draw(){
	noStroke();
	for(int i = 0; i<5; i++){
		for(int j = 0; j<5; j++){
			if(lab[i][j]){
				fill(255,0,0);
				rect(j*100,i*100,100,100);
			}else{
				fill(0,255,0);
				rect(j*100,i*100,100,100);
			}
		}
	}
	igrok();
	rect(mouseX,mouseY,20,20);
	
}

void keyPressed(){
	if(key=='w' && !lab[b-1][a]){
		b--;
	}
	if(key=='s' && !lab[b+1][a]){
		b++;
	}
	if(key=='a' && !lab[b][a-1]){
		a--;
	}
	if(key=='d' && !lab[b][a+1]){
		a++;
	}	
}

void mousePressed(){}
void mouseReleased(){}


void igrok(){
	fill(0,0,255);
	rect(a*100,b*100,100,100);
	fill(255,255,0);
	rect(a*100+20,b*100+20,20,10);
	rect(a*100+80,b*100+20,20,10);
	rect(a*100+20,b*100+80,60,10);	
}

}