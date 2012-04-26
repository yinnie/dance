#pragma once

#include "ofxBvh.h"


class Body
{
public:
	
	const ofxBvhJoint *joint;
	deque<ofVec3f> points;
	int trackerLength;
		
	void setup(const ofxBvhJoint *o){
		joint = o;
		trackerLength = 200;
	}
	
	void update() {
		const ofVec3f &p = joint->getPosition();
		//points for drawing the vertical calligraphy
		if(points.empty()) {
			points.push_front(joint->getPosition());
		}
		else {
			if (p.distance(points.front()) > 1) 
				points.push_front(joint->getPosition());
			
			if (points.size() > trackerLength){
				points.pop_back();
			}
		}
	}
	void draw()	{
			
		if (points.empty()) return;
	    
	    	
	void clear() {
		points.clear();
	}
};

