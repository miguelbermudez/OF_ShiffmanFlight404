
#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"
#include "ofxVec2f.h"
#include "ofxVec3f.h"

class Particle 
{
	public:
		ofxVec2f pos;
		ofxVec2f vel;
		ofxVec2f frc;
		
		ofImage *particleImg;
		vector<ofxVec3f> loc;			//vector of particle's postions

		float trailVerticies[6];
		float damping;
		float particleRadius;
		float trailWidth;
		float age;
		float particleAlpha;
		float lifespan;
		
		bool isDead;
		
	
		Particle();
		
		virtual ~Particle(){};
		
		void resetForce();
		void addForce(float x, float y);
		void addForce(ofxVec2f aVector);
		void addRepulsionForce(float x, float y, float radius, float scale);
		void addAttractionForce(float x, float y, float radius, float scale);
		
		void addRepulsionForce(Particle &p, float radius, float scale);
		void addAttractionForce(Particle &p, float radius, float scale);
		
		void addDampingForce();
		
		void setInitialCondition(float px, float py, float vx, float vy);
		void update();	
		void draw();
		void drawTrails();
		void bounceOffWalls();
		
		float heading2D(ofxVec2f vt);
	
	
};

#endif //PARTICLE_H