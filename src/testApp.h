#ifndef _TEST_APP
#define _TEST_APP

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "Character.h"
#include "ofFirefly.h"
#include "math.h"
#include "ofSoundPlayer.h"
#include <iostream>

#define NFLIES 10
#define MAX_DEVICES 2




class testApp : public ofBaseApp{

public:
    
	void setup();
	void update();
	void draw();
    void states();
    void exit();
    
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
    
    ofTrueTypeFont verdana;

//-------------openNi variables
    int numDevices;
        ofxOpenNI openNIDevices[MAX_DEVICES];
    
   
    void userEvent(ofxOpenNIUserEvent & event);

//-------------character variables
    ofImage smile;
    ofImage lHand;
    ofImage rHand;
    ofImage rFoot;
    ofImage lFoot;
    ofImage arm;
    ofImage leg;
    ofImage torso;
    
    Character kid;

//-------------fireflies variables
   
   
  //  ofRectangle lantern;
    ofImage net;
    ofImage lantern;
    
    ofFirefly fly[NFLIES];
    vector<ofFirefly> mFlies;
    int numOfAliveFlies;
    int targetTime;
    
    ofImage catcher;
    ofPoint cursor;
    
    //bool xB = false;
    //bool yB = false;
    int newFly;
    
//--------------screens variables
    ofImage beanstalk;
    ofImage nubes;
    ofImage intro;
    ofImage mayorscreen;
    ofImage jungle;
	ofImage forest;
  
//--------------swimming gesture
    bool wasLeftArmUp, wasRightArmUp;
    int swimCount;
    
//---------------audio
 
    //int playNum = 0;
    ofSoundPlayer firstscreen;
    ofSoundPlayer agent1;
    ofSoundPlayer agent2;
    ofSoundPlayer agent3;
    ofSoundPlayer mayor;
    ofSoundPlayer main;
    ofSoundPlayer fireflies;
  
};

#endif
