
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
	trailWidth		= 1;
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
void Particle::addForce(ofxVec2f aVector) {
	frc += aVector;
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
	
	if (vel.length() > 0.3) {
		ofxVec3f temp;
		temp.set(pos.x, pos.y, 0);	//we're not using z-cord yet
		loc.push_back(temp);
	} else {
		//if velocity has slowed down enough erase the trail
		if(loc.size() > 0) {
			loc.erase(loc.begin());
		}
	}
	//if the trail has grown too large, erase it
	if (loc.size() > 25) {
		loc.erase(loc.begin());
	}
}

//------------------------------------------------------------
void Particle::draw(){
    //ofCircle(pos.x, pos.y, 3);
	
	ofSetColor(255, 255, 255, particleAlpha);
	particleImg->draw(pos.x, pos.y, particleRadius, particleRadius);
	ofSetColor(255, 255, 255, 255);
	
}


//------------------------------------------------------------
//http://www.openframeworks.cc/forum/viewtopic.php?f=8&t=2527

void Particle::drawTrails(){

	float xp, yp, zp;
	float xOff, yOff, zOff;
	
	glBegin(GL_QUAD_STRIP);

	int tailLength = loc.size();
		for (int i=tailLength-1 ; i > 0; i--) {
			float per = 1.0 - (float)i/(float)(tailLength - 1);
			xp = loc[i].x;
			yp = loc[i].y;
			zp = loc[i].z;	//this is always 0
			
			if ( i < tailLength - 2 ) {
				
				ofxVec3f perp0 = loc[i] - loc[i + 1];
				
				//new technique
				perp0.normalize();
				ofxVec3f upAxis = ofxVec3f( 0, 1, 0 );
				ofxVec3f ya = ofxVec3f(upAxis);
				ofxVec3f v2 = ya.cross(perp0);
				ofxVec3f v3 = perp0.cross(v2).normalize();
				float w = trailWidth;
				float xOff   = v3.x * w;
				float yOff   = v3.y * w;
				float zOff   = v3.z * w;
				
				trailVerticies[ 0 ] = xp - xOff;
				trailVerticies[ 1 ] = yp - yOff;
				trailVerticies[ 2 ] = zp - zOff;
				trailVerticies[ 3 ] = xp + xOff;
				trailVerticies[ 4 ] = yp + yOff;
				trailVerticies[ 5 ] = zp + zOff;
				
				//glColor4f( per, per*.25, 1.0 - per, per * .125);
				glColor4f( per, per*.25, 1.0 - per, particleAlpha/255);
				glVertex3f( trailVerticies[0], trailVerticies[1], trailVerticies[2] );
				glVertex3f( trailVerticies[3], trailVerticies[4], trailVerticies[5] );	
			}
		}
	glEnd();
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


