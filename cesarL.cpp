
//Author / Modified by : Cesar Loya
// Date June 24, 2017
//cmps3350 - Source code

//*******************************************************************
//Progress
//June 24 - Mariachi appears on screen
//June 24 - general Enemy class ready
//June 24 - Mari class inherited from Enemy
//June 24 - OOP foundation ready

//*******************************************************************
//Responsabilities
//code object oriented Enemies
//proper animation
//walk in inervals
//animation for death 
//Enemies may have unique traits

//Week 4 goal - OO foundation and display one enemy

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
//#include "log.h"
#include "ppm.h"
#include "fonts.h"
#include "game.h"
using namespace std;


class my_time {
    public:
	double physicsRate;
	double oobillion;
	struct timespec timeStart, timeEnd, time_current;
	struct timespec walk_time;
	my_time() {
	    physicsRate = 1.0 / 30.0;
	    oobillion = 1.0 / 1e9;
	}
	double time_diff(struct timespec *start, struct timespec *end) {
	    return (double)(end->tv_sec - start->tv_sec ) +
		(double)(end->tv_nsec - start->tv_nsec) * oobillion;
	}
	void time_copy(struct timespec *dest, struct timespec *source) {
	    memcpy(dest, source, sizeof(struct timespec));
	}
	void record_time(struct timespec *t) {
	    clock_gettime(CLOCK_REALTIME, t);
	}

} time2;


void cesar_physics(void)
{  
    //use this for mariachi 
    time2.record_time(&time2.time_current);
    double tspan = time2.time_diff(&time2.walk_time, &time2.time_current);
    if (tspan > gl.cesar_delay) {
	++gl.cesar_walkframe;
	if (gl.cesar_walkframe >= 7) {
	    gl.cesar_walkframe -= 7;
	}
	time2.record_time(&time2.walk_time);
    }
}


Ppmimage* mari_image() 
{
    system("convert ./images/Enemy_Mariachi_3.gif ./images/Enemy_Mariachi_3.ppm");
    return ppm6GetImage("./images/Enemy_Mariachi_3.ppm");
}


Ppmimage* female_image() 
{
    system("convert ./images/female_fighter.png ./images/female_fighter.ppm");
    return ppm6GetImage("./images/female_fighter.ppm");
}


Ppmimage* obama_image()
{
    system("convert ./images/obama.gif ./images/obama.ppm");
    return ppm6GetImage("./images/obama.ppm");
}

Ppmimage* sun_image()
{
    system("convert ./images/sun.gif ./images/sun.ppm");
    return ppm6GetImage("./images/sun.ppm");
}




//first enemy
void show_mari() 
{
    if (gl.initDone == 0) {
	float x = gl.xres/1; 
	x = x-60; //x cord
    }
    mariEnemy.cy = 175; // y cord
    float ht = 100.0;//height of mari
    float w = ht*0.5; 

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.mari_Texture); 
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    int ax = 1;   
    int ay = 1;
    if (1 >= 1)
	ay = 0;
    float tx = (float)ax / 7.0;
    float ty = (float)ay / 1.0;
    glBegin(GL_QUADS);
    glTexCoord2f(tx,      ty+.6); glVertex2i(mariEnemy.cx+w, mariEnemy.cy-ht);
    glTexCoord2f(tx,      ty+0);    glVertex2i(mariEnemy.cx+w, mariEnemy.cy+ht);
    glTexCoord2f(tx+.14, ty+0);    glVertex2i(mariEnemy.cx-w, mariEnemy.cy+ht);
    glTexCoord2f(tx+.14, ty+.6); glVertex2i(mariEnemy.cx-w, mariEnemy.cy-ht);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}										

void show_female() 
{
    if (gl.initDone == 0) {
	float x = gl.xres/1; 
	x = x-60; //x cord
    }
    female.cy = 110; // y cord
    float ht = 50.0;//estatura de la mujer
    float w = ht*0.5; 

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.female_Texture); 
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    int ax = 1;   
    int ay = 1;
    if (1 >= 1)
	ay = 0;
    float tx = (float)ax / 8.0;
    float ty = (float)ay / 1.0;
    glBegin(GL_QUADS);
    glTexCoord2f(tx,      ty+ 1.0); glVertex2i(female.cx +w, female.cy-ht);
    glTexCoord2f(tx,      ty);    glVertex2i(female.cx +w, female.cy+ht);
    glTexCoord2f(tx+.08, ty);    glVertex2i(female.cx-w, female.cy+ht);
    glTexCoord2f(tx+.08, ty+1.0); glVertex2i(female.cx-w, female.cy-ht);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}

void show_obama()
{
    if (gl.initDone == 0) {
	float x = gl.xres/1;
	x = x-60; //x cord
    }
    //obama.cx = 200;	charceter.cx is to make him follow megaman
    obama.cy = 300; // y cord
    float ht = 75.0;//height of mari
    float w = ht*0.5;

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.obama_Texture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    int ax = 1;
    int ay = 1;
    if (1 >= 1)
	ay = 0;
    float tx = (float)ax / 7.0;
    float ty = (float)ay / 1.0;
    glBegin(GL_QUADS);
    glTexCoord2f(tx,      ty+1.0); glVertex2i(obama.cx+w, obama.cy-ht);
    glTexCoord2f(tx,      ty+0);    glVertex2i(obama.cx+w, obama.cy+ht);
    glTexCoord2f(tx+1.0, ty+0);    glVertex2i(obama.cx-w, obama.cy+ht);
    glTexCoord2f(tx+1.0, ty+1.0); glVertex2i(obama.cx-w, obama.cy-ht);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}

void show_sun()
{
    if (gl.initDone == 0) {
	float x = gl.xres/1;
	x = x-60; //x cord
    }
    sun.cx = 200;   //charceter.cx is to make him follow megaman
    sun.cy = 400; // y cord
    float ht = 75.0;//height of mari
    float w = ht*0.5;

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.sun_Texture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    int ax = 1;
    int ay = 1;
    if (1 >= 1)
	ay = 0;
    float tx = (float)ax / 7.0;
    float ty = (float)ay / 1.0;
    glBegin(GL_QUADS);
    glTexCoord2f(tx,      ty+1.0); glVertex2i(sun.cx+w, sun.cy-ht);
    glTexCoord2f(tx,      ty+0);    glVertex2i(sun.cx+w, sun.cy+ht);
    glTexCoord2f(tx+1.0, ty+0);    glVertex2i(sun.cx-w, sun.cy+ht);
    glTexCoord2f(tx+1.0, ty+1.0); glVertex2i(sun.cx-w, sun.cy-ht);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}






class Enemy {
    protected:
	string name;
	string type;
	int health_points;
	int attack;
	bool alive;
    public:
	Enemy();
	//mutators
	void SetName(string n);
	void SetType(string t);
	void SetHealth(int h);
	void SetAttack(int att);
	void SetAlive(bool a);
	//accessors
	string GetName();
	string GetType();
	int GetHealth();
	int GetAttack();
	bool GetAlive();
};

Enemy::Enemy() {
    name = "NO_NAME";
    type = "NO_TYPE";
    health_points = 0;
    attack = 0;
    alive = false; //must inherit to change
}

//first actual oo enemy
class Mari:public Enemy{
    private:
	int* soundwaves; //array of attacks (2nd move)
	int size;
    public:
	Mari();
	~Mari();
};

Mari::Mari(){
    name = "El Mariachi";
    type = "Fighter";
    health_points = 100;
    attack = 5;
    alive = true; //must inherit to change
    size = 10; 
    soundwaves = new int[size];
    // will build on this concept    
}

Mari::~Mari(){
    if(soundwaves != NULL){
	delete [] soundwaves;
	soundwaves = NULL;
    }
}

void Enemy::SetName(string n){
    name = n;
}

void Enemy::SetType(string t){
    type = t;
}

void Enemy::SetHealth(int h){
    health_points = h;
}

void Enemy::SetAttack(int att){
    attack = att;
}

void Enemy::SetAlive(bool a){
    alive = a;
}

string Enemy::GetName(){
    return name;
}

string Enemy::GetType(){
    return type;
}

int Enemy::GetHealth(){
    return health_points;
}

int Enemy::GetAttack(){
    return attack;
}

bool Enemy::GetAlive(){
    return alive;
}

