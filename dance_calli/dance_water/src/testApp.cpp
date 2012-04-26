#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup() {
	ofSetFrameRate(60);
	ofEnableAlphaBlending();
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
    //track.play();
    //track.setLoop(true);
	
	// setup tracker
	for (int i = 0; i < 3; i++)
	{
		ofxBvh &b = bvh[i];  //why use '&' here???		
		//for (int n = 0; n < b.getNumJoints(); n++) {
		//	const ofxBvhJoint *o = b.getJoint(n);
		
	    const ofxBvhJoint *o = b.getJoint("RightWrist");
			Tracker *t = new Tracker;
			t->setup(o);
		    t->setStartY(-58);
		    t->setStartX(-250);
			trackers.push_back(t);  //because trackers is a vector array of type <Tracker *> , here we can pushback on t instead of *t
		
		
		const ofxBvhJoint *m = b.getJoint("LeftWrist");
		Tracker *q = new Tracker;
		q->setup(m);
		q->setStartY(22);
		q->setStartX(-500);
		trackers2.push_back(q);
	}
	
	camera.setFov(45);
	camera.setDistance(360);
	camera.disableMouseInput();	
	
	//fluid shader-----------------------------------------------------------
	image.loadImage("background.jpeg");
    // Initial Allocation
    fluid.allocate(1280, 800, 0.5);
    // Seting the gravity set up & injecting the background image
    fluid.setGravity(ofVec2f(0.0,0.0098));
    fluid.setTexture(image.getTextureReference());
    
    // Adding constant forces
    //fluid.addConstantForce(ofVec2f(640*0.5,480*0.85), ofVec2f(0,-3), ofFloatColor(0.5,0.0,0.0), 6.f);
    //fluid.addConstantForce(ofVec2f(640*0.5,480*0.85), ofVec2f(0,-1), ofFloatColor(0.0,0.3,0.0), 3.f);
    
    bPaint = true;
    bObstacle = false;
    bBounding = true;
    bClear = true;

}

//--------------------------------------------------------------
void testApp::update()
{   
		//for (int i=0; i<3; i++) {
//		bvh[i].update();
//	}
	
	bvh[1].update();
	
	for (int i=0; i<trackers.size(); i++) {
		trackers[i]->update();  //use '->' becoz trackers is a vector of pointers
	}
	for (int i=0; i<trackers2.size(); i++) {
		trackers2[i]->update();
	}
	
	//fluid---------------------------------------------
	for (int i=0; i<trackers.size(); i++) {
		ofVec2f m = ofVec2f(trackers[i]->joint->getPosition().x, trackers[i]->joint->getPosition().y);
	

    if (bPaint){
        ofVec2f center = ofVec2f(ofGetWidth()*0.5, ofGetHeight()*0.5);
        ofVec2f d = m - oldM;
        ofVec2f c = center - m;
        d *= 2.0;
        c.normalize();
        
        // Adding temporal Force
        fluid.addTemporalForce(m, d, ofFloatColor(c.x,c.y,0.5),3.0f);
    } 
	
    // Updating the obstacle texture if not using obstacles you have to call update()
    fluid.begin();
    if (bClear) ofClear(0);
    
    if (bObstacle){
        ofFill();
        ofColor(255,0,0);
        ofCircle(m.x, m.y, 5);
    } 
    
    if (bBounding){
        ofNoFill();
        ofSetColor(200);
        ofRect(2, 2, ofGetWidth()-2, ofGetHeight()-2);
    }
    fluid.end();
    
    fluid.update();
    
    // Storing the mouse position in order to get the velocity of it and pass it to the fluid
    oldM = m;
    
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
		ofTranslate(-100, -100);
		ofRotate(rotate, 0, 1, 0);
		ofScale(0.85, 0.85, 0.85);
		//ofSetColor(ofColor::white, 80);
		for (int i = 0; i < trackers.size(); i++){
			trackers[i]->draw();
		}
	   
    ofPopMatrix();
	
	ofPushMatrix();
	ofTranslate(100, -130);
	ofRotate(rotate, 0, 1, 0);
	ofScale(0.85, 0.85, 0.85);
	//ofSetColor(ofColor::white, 80);
	for (int i = 0; i < trackers2.size(); i++){
		trackers2[i]->draw();
	}
	
    ofPopMatrix();

	camera.end();

	
	fluid.draw();
}

void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == 'f') {
		ofToggleFullscreen();
	}
}


