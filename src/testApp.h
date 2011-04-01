#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "Particle.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
	
		float prevMouseX;
		float prevMouseY;
	
		ofxVec2f gravity;
		
		ofImage particleImg;
		vector<Particle> particles;
		
		ofImage emitterImg;
		int emitterSize;
		
		ofImage nebulaImg;
		int nebulaSize;
	
		bool ALLOWTRAILS;
		bool ALLOWGRAVITY;
		

};

#endif
