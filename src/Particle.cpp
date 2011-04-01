
#include "Particle.h"

Particle::Particle() {
	setInitialCondition(0, 0, 0, 0);

	particleRadius	= (ofRandom( 5, 60 )) * 2;

	//particle's life
	age				= 0;
	lifespan		= (int)ofRandom(30, 90);
	isDead			= false;
	particleAlpha	= 255;
	damping			= 0.13f;	
}


//------------------------------------------------------------
void Particle::resetForce(){
    // we reset the forces every frame
    frc.set(0,0);
}

//------------------------------------------------------------
void Particle::addForce(float x, float y) {
	// add in a force in X and Y for this frame.
	frc.x = frc.x + x;
	frc.y = frc.y + y;
}


//------------------------------------------------------------
void Particle::addRepulsionForce(float x, float y, float radius, float scale) {
	
	
	//make a vector of where this postion is:
	ofxVec2f posOfForce;
	posOfForce.set(x, y);
	
	//calculate the difference & length
	ofxVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	//check close enough
	bool isCloseEnough = true;
	if (radius > 0) {
		if (length > radius) {
			isCloseEnough = false;
		}
	}
	
	//if so, update force
	if (isCloseEnough) {
		float pct = 1- (length / radius);		//stronger on the inside
		diff.normalize();						//why do we have to do this?
		frc.x = frc.x + diff.x * scale * pct;
		frc.y = frc.y + diff.y * scale * pct;
	}
}

//------------------------------------------------------------



//------------------------------------------------------------
void Particle::addDampingForce() {
	frc.x = frc.x - vel.x * damping;
	frc.y = frc.y - vel.y * damping;
	
}

//------------------------------------------------------------
void Particle::setInitialCondition(float px, float py, float vx, float vy){
    pos.set(px,py);
	vel.set(vx,vy);
}

//------------------------------------------------------------
void Particle::update(){	
	vel = vel + frc;
	pos = pos + vel;
	
	age++;
	particleAlpha = ofMap(age, 0, lifespan, 255, 0);
	if(age > lifespan)
		isDead = true;
}

//------------------------------------------------------------
void Particle::draw(){
    //ofCircle(pos.x, pos.y, 3);
	
	ofSetColor(255, 255, 255, particleAlpha);
	particleImg->draw(pos.x, pos.y, particleRadius, particleRadius);
	ofSetColor(255, 255, 255, 255);
	
}

//------------------------------------------------------------
void Particle::bounceOffWalls() {
	bool isDampedOnCollision = true;
	bool isDidICollide = false;
	
	//what are the walls
	float minx = 0;
	float miny = 0;
	float maxx = ofGetWidth();
	float maxy = ofGetHeight();
	
	if (pos.x > maxx) {
		pos.x = maxx;	// move to the edge
		vel.x *= -1;	//reverse direction
		isDidICollide = true;
	} else if (pos.x < minx) {
		pos.x = minx;	//move to the edge
		vel.x *= -1;	//reverse direction
		isDidICollide = true;
	}
	
	if (pos.y > maxy){
		pos.y = maxy; //move to the edge
		vel.y *= -1;  //reverse direction
		isDidICollide = true;
	} else if (pos.y < miny){
		pos.y = miny; //move to the edge
		vel.y *= -1;  //reverse direction
		isDidICollide = true;
	}
	
	if (isDidICollide == true && isDampedOnCollision == true){
		vel *= 0.3;
	}
	
}

