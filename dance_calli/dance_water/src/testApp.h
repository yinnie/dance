#pragma once

#include "ofMain.h"
#include "ofxBvh.h"
#include "Tracker.h"
#include "ofxFX.h"


class testApp : public ofBaseApp{

  public:
	void setup();
	void update();
	void draw();
	void exit();
	void keyPressed(int key);

	ofSoundPlayer track;
	ofxBvh bvh[3];
	
	float rotate;
	float play_rate, play_rate_t;
	
	ofEasyCam camera;
	
	vector<Tracker*> trackers;
	vector<Tracker*> trackers2;
	
	vector<ofMesh> meshes;
	
	//fluid shader
	ofxFluid fluid;
	ofVec2f oldM;
    bool    bPaint, bObstacle, bBounding, bClear;
	ofImage image;
		
};
