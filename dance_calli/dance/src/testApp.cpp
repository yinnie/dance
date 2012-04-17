#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup() {
	//ofSetFrameRate(60);
	ofSetVerticalSync(true);
		
	rotate = 0;
	
	// setup bvh
	bvh[0].load("bvhfiles/kashiyuka.bvh");
	bvh[1].load("bvhfiles/nocchi.bvh");
	bvh[2].load("bvhfiles/aachan.bvh");
	
	for (int i = 0; i < 3; i++)	{
		bvh[i].play();
	}
	
	//track.loadSound("Perfume_globalsite_sound.wav");
//   track.play();
//   track.setLoop(true);
	
	// setup tracker
	for (int i = 0; i < 3; i++)
	{
		ofxBvh &b = bvh[i];
		
		//for (int n = 0; n < b.getNumJoints(); n++) {
		//	const ofxBvhJoint *o = b.getJoint(n);
	    const ofxBvhJoint *o = b.getJoint("RightWrist");

			Tracker *t = new Tracker;
			t->setup(o);
			//t->setTrackerLength(trackerLength);
		trackers.push_back(t);
		/*
		const ofxBvhJoint *m = b.getJoint("Head");
		Tracker *q = new Tracker;
		q->setup(m);
		q->setTrackerLength(trackerLength);
			trackers.push_back(q);
		 */
		//}
	}
	
	camera.setFov(45);
	camera.setDistance(360);
	camera.disableMouseInput();
	
	//background.loadImage("background.png");
	
}

//--------------------------------------------------------------
void testApp::update()
{   
		//for (int i=0; i<3; i++) {
//		bvh[i].update();
//	}
	
	bvh[1].update();
	for (int i=0; i<trackers.size(); i++) {
		trackers[i]->update();
	}
	 
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackgroundHex(0x000000);
	//ofSetHexColor(0xffffff);
	//background.draw(0,0,ofGetWidth(),ofGetHeight());
	
	glEnable(GL_DEPTH_TEST);
	
	camera.begin();
	ofPushMatrix();
		ofTranslate(0, -80);
		ofRotate(rotate, 0, 1, 0);
		ofScale(1, 1, 1);
		// draw bvh
		glDisable(GL_DEPTH_TEST);
		ofEnableBlendMode(OF_BLENDMODE_ADD);		
		//for (int i=0; i<3; i++) {
//			bvh[0].draw();
//		}		
		bvh[1].draw();
	ofPopMatrix();
	
	ofPushMatrix();
		ofTranslate(-100, -130);
		ofRotate(rotate, 0, 1, 0);
		ofScale(0.85, 0.85, 0.85);
		//ofSetColor(ofColor::white, 80);
		for (int i = 0; i < trackers.size(); i++){
			trackers[i]->draw();
		}
    ofPopMatrix();
	
	camera.end();

}

void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == 'f') {
		ofToggleFullscreen();
	}
}


