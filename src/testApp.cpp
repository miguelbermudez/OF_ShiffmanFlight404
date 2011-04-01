#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
	ofBackground(20,20,20);
	
	//load particle image
	particleImg.loadImage("particle.png");
	particleImg.setAnchorPercent(0.5, 0.5);
	
	//load emitter image
	emitterImg.loadImage("emitter.png");
	emitterImg.setAnchorPercent(0.5, 0.5);
	emitterSize = 250;
	
	//load nebula image
	nebulaImg.loadImage("corona.png");
	nebulaImg.setAnchorPercent(0.5, 0.5);
	
}

//--------------------------------------------------------------
void testApp::update(){
	//holder vector for particles who are still alive
	vector<Particle> stillAlive;
	
	for (int i = 0; i < particles.size(); i++){
		if (!particles[i].isDead) {
			//particles[i].resetForce();
			//particles[i].addDampingForce();
			particles[i].update();
			stillAlive.push_back(particles[i]);
		} 
	}
	//replace particles with one that contains only "living" particles
	//this "kills" all dead particles in the process
	particles = stillAlive;

}

//--------------------------------------------------------------
void testApp::draw(){
	
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	
	//draw emitter
	emitterImg.draw(mouseX, mouseY, emitterSize, emitterSize);
	for (int i = 0; i < particles.size(); i++){
		particles[i].draw();
	}
	
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 50, 50);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	prevMouseX = x;
	prevMouseY = y;
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	float dx = x - prevMouseX;
	float dy = y - prevMouseY;
	
	float dampingScaler = 0.3;
	float velocityScaler = 0.35;
	
	int numOfParticles = 10;
	
	for (int i=0; i<numOfParticles; i++) {
		Particle myParticle;
		myParticle.setInitialCondition(x, y, dx*dampingScaler, dy*dampingScaler);	//why 0.3?
		
		ofxVec2f randomVector = ofxVec2f(ofRandomf(), ofRandomf());
		randomVector *= ofRandom(0, velocityScaler);
		myParticle.addForce(randomVector.x, randomVector.y);
		
		myParticle.particleImg = &particleImg;
		particles.push_back(myParticle);
	}
	
	prevMouseX = x;
	prevMouseY = y;
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	particles.clear();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

