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
    
    int newFly;
    
//--------------screens variables
    ofImage beanstalk;
    ofImage nubes;
    ofImage intro;
    ofImage mayorscreen;
    ofImage jungle;
    ofImage pandora [5];
  
//--------------swimming gesture
    bool wasLeftArmUp, wasRightArmUp;
    int swimCount;
    
//---------------audio
 
    ofSoundPlayer firstscreen;
    ofSoundPlayer agent1;
    ofSoundPlayer agent2;
    ofSoundPlayer agent3;
    ofSoundPlayer mayor;
    ofSoundPlayer main;
    ofSoundPlayer fireflies;
  
    
// ----------------------------- JAVERIYAH: ANIMATION VARIABLES ------------------ //
    
////---------------Mayor Pandora Sequence:---------------////
// using ofTexture is faster than using ofImage, less lag the better.
    vector<ofTexture> pandoraSeq;
    ofDirectory pandaDir;
    int p = pandaDir.listDir("pandora");
    
////-----------Forest Sequence:---------------////
    
    vector<ofTexture> owlSeq;
    ofDirectory owlDir;
    int oo = owlDir.listDir("owl");
    
    vector<ofTexture> birdSeq;
    ofDirectory birdDir;
    int bi = birdDir.listDir("bird");
    
    vector<ofTexture> bunnySeq;
    ofDirectory bunnyDir;
    int bu = bunnyDir.listDir("bunny");
    
    vector<ofTexture> bearSeq;
    ofDirectory bearDir;
    int be = bearDir.listDir("bear");
    
////---------------Tutorial Sequence:---------------////
    
////---------------Beanstalk Tutorial---------------////
    vector<ofTexture> beanTipSeq;
    ofDirectory beanTipDir;
    int beans = beanTipDir.listDir("beanTip");
    
////---------------Fireflies & Forest Tutorial---------------////
    vector<ofTexture> fireflyTipSeq;
    ofDirectory fireflyTipDir;
    int flyTip = fireflyTipDir.listDir("fireflyTip");
};

#endif
