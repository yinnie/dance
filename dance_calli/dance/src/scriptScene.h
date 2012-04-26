#pragma once
#include "ofxBvh.h"


class scriptScene
{
public:
	
	const ofxBvhJoint *joint;
	deque<ofVec3f> points;
	int scriptLength;
	vector<ofMesh> meshes;
	deque<ofVec3f> pointsLong;
		
	void setup(const ofxBvhJoint *o){
		joint = o;
		scriptLength = 200;
	}
	
	void setScriptLength(int trackerLen) {
		scriptLength = trackerLen;
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
			
			for (int i = 0; i < points.size() - 1; i++){
				points[i].y+=0.6;
			}
			
			if (points.size() > scriptLength){
				points.pop_back();
			}
		}
		
		//points for drawing individual characters
		if(pointsLong.empty()) {
			pointsLong.push_front(joint->getPosition());
		}
		else {
			if (p.distance(pointsLong.front()) > 1) 
				pointsLong.push_front(joint->getPosition());
			
			for (int i = 0; i < pointsLong.size() - 1; i++){
				pointsLong[i].y+=1;
			}
			
			int length = scriptLength*0.5; //this determines the size of the individual 'character' drawn
			
		    if (pointsLong.size()%length==0) {
				//make a mesh from the points and save it into an array of meshes
				ofMesh mesh;
				mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
				//glPointSize(4);
				
				for(int i = 1; i < length; i++){
					
					//find this point and the next point
					ofVec3f thisPoint = points[i];
					ofVec3f nextPoint = points[i+1];
					
					//get the direction from one to the next. 
					//the ribbon should fan out from this direction
					ofVec3f direction = (nextPoint - thisPoint);
					
					//get the distance from one point to the next
					float distance = direction.length();
					
					//get the normalized direction. normalized vectors always have a length of one
					//and are really useful for representing directions as opposed to something with length
					ofVec3f unitDirection = direction.normalized();
					
					//find both directions to the left and to the right 
					ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0,0,1));
					ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0,0,1));
					
					//use the map function to determine the distance.
					//the longer the distance, the narrower the line. 
					//this makes it look a bit like brush strokes
					float thickness = ofMap(distance, 0, 8, 3, 0.2, true);
					
					//calculate the points to the left and to the right
					//by extending the current point in the direction of left/right by the length
					ofVec3f leftPoint = thisPoint+toTheLeft*thickness;
					ofVec3f rightPoint = thisPoint+toTheRight*thickness;
					
					//add these points to the triangle strip
					mesh.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
					mesh.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
				}
				
				meshes.push_back(mesh);
				
			}
		}
		
	}
	void draw1() {
		//draw the individual characters
		if (meshes.empty()) return;
		
		ofSetColor(0);
		//draw vertically
			if (meshes.size() > 2 && meshes.size() < 20) {
				
				for (int i=3; i< meshes.size(); i++) {
					ofPushMatrix();
					ofTranslate(-150,400-i*30);
					ofRotate(0, 0, 1, 0);
					ofScale(0.35, 0.35, 0.35);
					meshes[i].draw();
					ofPopMatrix();
				}
			}
			if (meshes.size() > 19 ) {
				for (int i=3; i< 19; i++) {
					ofPushMatrix();
					ofTranslate(-150,400-i*30);
					ofRotate(0, 0, 1, 0);
					ofScale(0.35, 0.35, 0.35);
					meshes[i].draw();
					ofPopMatrix();
				}			
				for (int i=20; i<meshes.size(); i++) {
					ofPushMatrix();
					ofTranslate(-120,400-(i-9)*30);
					ofRotate(0, 0, 1, 0);
					ofScale(0.35, 0.35, 0.35);
					meshes[i].draw();
					ofPopMatrix();
				}
		  }
				
	}
	void draw2() {
		//draw the individual characters
		ofSetColor(0);
		
		if (meshes.empty()) return;
		if (meshes.size() > 2 && meshes.size() < 13) {
			for (int i = 3; i<meshes.size(); i++) {
				ofPushMatrix();
				ofTranslate(-150,400-i*30);
				ofRotate(0, 0, 1, 0);
				ofScale(0.35, 0.35, 0.35);
				meshes[i].draw();
				ofPopMatrix();
			}
		}
		if (meshes.size() > 12 ) {
			for (int i = 13; i<meshes.size(); i++) {
				ofPushMatrix();
				ofTranslate(-100,400-i*30);
				ofRotate(0, 0, 1, 0);
				ofScale(0.35, 0.35, 0.35);
				meshes[i].draw();
				ofPopMatrix();
			}
		}
		
				
	}
	void clear() {
		points.clear();
	}
};