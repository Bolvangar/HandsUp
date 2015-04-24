//
//  Character.h
//  openNiSample007
//
//  Created by Sharon Profita on 08/03/2015.
//
//
#ifndef _CHARACTER
#define _CHARACTER

#include "ofGraphics.h"
#include "ofMain.h"
#include <iostream>
#define MAX_DEVICES 2


class Character{

public:
    
    void setup();
	void head(ofImage, ofVec3f);
    void torso(ofImage, ofVec3f);
    void rightHand(ofImage, ofImage, ofVec3f, ofVec3f);
    void leftHand(ofImage, ofImage, ofVec3f, ofVec3f);
    void rightFoot(ofImage, ofImage, ofVec3f, ofVec3f);
    void leftFoot(ofImage, ofImage, ofVec3f, ofVec3f);
    void rightUpArm(ofImage, ofVec3f, ofVec3f);
    void leftUpArm(ofImage, ofVec3f, ofVec3f);
    void rightUpLeg(ofImage, ofVec3f, ofVec3f);
    void leftUpLeg(ofImage, ofVec3f, ofVec3f);

    
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);


    
    ofImage pin;


};

#endif /* defined(__openNiSample007__Character__) */