#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(255);
		
	rotate = 0;
	
	// setup bvh
	bvh[0].load("bvhfiles/kashiyuka.bvh");
	bvh[1].load("bvhfiles/nocchi.bvh");
	bvh[2].load("bvhfiles/aachan.bvh");
	
	for (int i = 0; i < 3; i++)	{
		bvh[i].play();
	}
	// setup tracker
	for (int i = 0; i < 3; i++)
	{
		ofxBvh &b = bvh[i];  
		
		const ofxBvhJoint *o = b.getJoint("RightWrist");
		Tracker *t = new Tracker;
		t->setup(o);
		t->setStartY(120);
		t->setStartX(-100);
		trackers.push_back(t); //because trackers is a vector array of type <Tracker *> , here we can pushback on t instead of *t
		
		const ofxBvhJoint *m = b.getJoint("LeftWrist");
		Tracker *q = new Tracker;
		q->setup(m);
		q->setStartY(150);
		q->setStartX(50);
		trackers2.push_back(q);
			
		for (int n = 0; n < b.getNumJoints(); n++) {
		  const ofxBvhJoint *l = b.getJoint(n);
		  Tracker *s = new Tracker;
		  s->setup(l);
		  trackersAll.push_back(s);   //adding to array of all joints
		}
	}
	
	camera.setFov(45);
	camera.setDistance(500);
	camera.disableMouseInput();	
	
	mode =0;	
}

//--------------------------------------------------------------
void testApp::update()
{   
		//for (int i=0; i<3; i++) {
//		bvh[i].update();
//	}
	
	
	bvh[1].update();
	
	for (int i=0; i<trackers.size(); i++) {
		if(trackers[i] == NULL) {cout << "Not init\n";}
		trackers[i]->update();  //use '->' becoz trackers is a vector of pointers
	}
	for (int i=0; i<trackers2.size(); i++) {
		trackers2[i]->update();
	}
	for (int i=0; i<trackersAll.size(); i++) {
		trackersAll[i]->update();
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	//glEnable(GL_DEPTH_TEST);
	
	ofSetColor(0);
	camera.begin();
	
	if (mode == 0) {   //dancing mode

	ofPushMatrix();
		ofTranslate(-220, -150);
		ofRotate(rotate, 0, 1, 0);
		ofScale(1, 1, 1);		
		//bvh[1].draw();
	for (int i = 1; i < trackersAll.size()-1; i++){
		const ofVec3f &p = trackersAll[i-1]->joint->getPosition();
		const ofVec3f &q = trackersAll[i]->joint->getPosition();
		ofSetLineWidth(1.4);
		ofLine(p.x, p.y, q.x, q.y);
	}
	ofPopMatrix();
	
	ofPushMatrix();
		ofTranslate(-30, -150);
		ofRotate(rotate, 0, 1, 0);
		ofScale(0.85, 0.85, 0.85);
		for (int i = 0; i < trackers.size(); i++){
			trackers[i]->draw();
			trackers[i]->drawLast(80,-60);
		}
    ofPopMatrix();
	
	ofPushMatrix();
	ofTranslate(165, -40);
	ofRotate(rotate, 0, 1, 0);
	ofScale(0.85, 0.85, 0.85);
	for (int i = 0; i < trackers2.size(); i++){
		trackers2[i]->draw();
		trackers2[i]->drawLast(70,-175);
	}	
    ofPopMatrix();
		
		ofNoFill();
		ofRect(-20, -155, 100, 100);
		ofRect(170, -155, 100, 100);
	
	}  
	
	
	if (mode == 1) {   //script mode
		
		ofPushMatrix();
		ofTranslate(80, 210);
		ofRotate(rotate, 0, 1, 0);
		ofScale(1, 1, 1);
		for (int i = 0; i < trackers.size(); i++){
			trackers[i]->draw1();
		}	
		ofPopMatrix();
		
		
		ofPushMatrix();
		ofTranslate(410, 240);
		ofRotate(rotate, 0, 1, 0);
		ofScale(1, 1, 1);
	    for (int i = 0; i < trackers2.size(); i++){
			trackers2[i]->draw2();
		}	
		ofPopMatrix();
	}

	camera.end();
}

void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	if (key == ' ') {
		mode++;
	}
}


