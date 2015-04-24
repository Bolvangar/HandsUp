#include "testApp.h"
#include "ofGraphics.h"
#include <character.h>
#include <iostream>

float mPosX;
float mPosY;
int state = 0;
bool start = false;
bool screen1 = false;
bool screen2 = false;
bool screen3 = false;
bool screen4 = false;
bool screen5 = false;
bool screen6 = false;

bool xB = false;
bool yB = false;
int counter = 0;
int playNum = 0;

/*******************************
 STATES:
 state 0 = intro screen (logo + hands)
 state 1 = mayor pandora animation
 state 2 = beanstalk
 state 3 = fireflies
 state 4 = jungle
 state 5 = bear
 *******************************/

//--------------------------------------------------------------

void testApp::setup() {
    
    //-------------------------------------audio setup
    
    firstscreen.loadSound("intro.wav");
    agent1.loadSound("Agent 1.wav");
    agent2.loadSound("Agent 2.wav");
    agent3.loadSound("Agent 3.wav");
    mayor.loadSound("Mayor 2.wav");
    main.loadSound("mainLoop.wav");
    fireflies.loadSound("fireFliesLoop.wav");
    // main.setLoop(true);
    main.setVolume(0.2);
    fireflies.setVolume(0.3);
    roar.loadSound("roar.wav");
    roar.setVolume(0.2);
    
    //-------------------------------------character setup
    smile.loadImage("head.png");
    rHand.loadImage("rhand.png");
    lHand.loadImage("lhand.png");
    rFoot.loadImage("rfoot.gif");
    lFoot.loadImage("lfoot.gif");
    arm.loadImage("arm.png");
    leg.loadImage("leg.png");
    torso.loadImage("torso.png");
    
    //----------------------------------------firefly setup
    catcher.loadImage("splash.png");
    net.loadImage("net.gif");
    
    fly[0].SetAlive(true);
    numOfAliveFlies = 0;
    targetTime = ofGetElapsedTimeMillis() + 5000;
    
    
    //-----------------------------------------screens setup
    beanstalk.loadImage("beanstalk.png");
    nubes.loadImage("nubes.png");
    intro.loadImage("intro.png");
    mayorscreen.loadImage("mayor.png");
    forest.loadImage("forest.png");
    lantern.loadImage("lantern.png");
    layer1.loadImage("layer1.png");
    layer2.loadImage("layer2.png");
    layer3.loadImage("layer3.png");
    key.loadImage("key.png");
    credits.loadImage("credits.png");
    
    //----------------------------------------lantern setup
    
    
    bCount=0;
    
    keyX= ofRandom(0,1000);
    keyY= ofRandom(700);
    
    speedx = ofRandom(0, 1.5);
    speedy = ofRandom(0, 1.5);
    
    
    
    // ------------------------------------ JAVERIYAH: ANIMATIONS SETUP
	//// Mayor Pandora Sequence ////
    pandoraSeq.resize(p);
    for(int i = 0; i < p; i++) {
        string pandora = pandaDir.getPath(i);
        ofLoadImage(pandoraSeq[i], pandora);
    }
    
	//// Forest Sequence ////
    owlSeq.resize(oo);
    for(int i = 0; i < oo; i++) {
        string owl = owlDir.getPath(i);
        ofLoadImage(owlSeq[i], owl);
    }
    
    birdSeq.resize(bi);
    for(int i = 0; i < bi; i++) {
        string bird = birdDir.getPath(i);
        ofLoadImage(birdSeq[i], bird);
    }
    
    bunnySeq.resize(bu);
    for(int i = 0; i < bu; i++) {
        string bunny = bunnyDir.getPath(i);
        ofLoadImage(bunnySeq[i], bunny);
    }
    
	//// Bear Sequence ////
    bearSeq.resize(be);
    for(int i = 0; i < be; i++) {
        string bear = bearDir.getPath(i);
        ofLoadImage(bearSeq[i], bear);
    }
    
	//// Beanstalk Tutorial Sequence ////
    beanTipSeq.resize(beans);
    for(int i = 0; i < beans; i++) {
        string bTu = beanTipDir.getPath(i);
        ofLoadImage(beanTipSeq[i], bTu);
    }
    
	//// Firefly Tutorial Sequence ////
    fireflyTipSeq.resize(flyTip);
    for(int i = 0; i < flyTip; i++) {
        string wave = fireflyTipDir.getPath(i);
        ofLoadImage(fireflyTipSeq[i], wave);
    }
    
    
    //-------------------------------------OpenNi setup
    ofSetLogLevel(OF_LOG_NOTICE);
    
    numDevices = openNIDevices[0].getNumDevices();
    
    for (int deviceID = 0; deviceID < numDevices; deviceID++){
        //openNIDevices[deviceID].setLogLevel(OF_LOG_VERBOSE); // ofxOpenNI defaults to ofLogLevel, but you can force to any level
        openNIDevices[deviceID].setup();
        openNIDevices[deviceID].addDepthGenerator();
        openNIDevices[deviceID].addImageGenerator();
        openNIDevices[deviceID].addUserGenerator();
        openNIDevices[deviceID].setRegister(true);
        openNIDevices[deviceID].setMirror(true);
		openNIDevices[deviceID].start();
        
    }
    
    openNIDevices[0].setMaxNumUsers(1); // defualt is 4
    ofAddListener(openNIDevices[0].userEvent, this, &testApp::userEvent);
    
    ofxOpenNIUser user;
    
    user.setUseMaskTexture(true);
    user.setUsePointCloud(true);
    user.setPointCloudDrawSize(2); // this is the size of the glPoint that will be drawn for the point cloud
    user.setPointCloudResolution(2); // this is the step size between points for the cloud -> eg., this sets it to every second point
    openNIDevices[0].setBaseUserClass(user);
    
    
    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);
    
}

//--------------------------------------------------------------
void testApp::update(){
    ofBackground(0, 0, 0);
    
    
    //--------------------------------------openni update
    for (int deviceID = 0; deviceID < numDevices; deviceID++){
        openNIDevices[deviceID].update();
    }
    
    //--------------------------------------firefly update
    
    for(int i=0; i<NFLIES; i++)
    {
        if(fly[i].GetAlive())fly[i].update();
        fly[i].caughtX = mouseX;
        fly[i].caughtY = mouseY;
    }
    
    
    
    if(numOfAliveFlies < 7){
        if(ofGetElapsedTimeMillis() >  targetTime){
            numOfAliveFlies++;
            fly[numOfAliveFlies].SetAlive(true);
            targetTime = ofGetElapsedTimeMillis() + 5000;
        }
    }
    
    //--------------------------------------lantern update

    // this is the speed of key
    keyX +=speedx;
    keyY +=speedy;
    
    // counts to compare how many times key has been taken, made it 3 times so its a bit more time.
    int count= bCount;
    
    if (keyX<0 || keyX > ofGetWidth()) {
        keyX=ofRandom(5,10);
    }
    
    if (keyY<0 || keyY > ofGetHeight()) {
        keyY=ofRandom(5,10);
    }
}

//--------------------------------------------------------------
void testApp::states(){
    
    
    if (state == 0){
        start = true;
    }
    
    if (state == 1){
        
        firstscreen.unloadSound();
        start = false;
        screen1 = true;
        
    } else if (state == 2){
        
        screen1 = false;
        screen2 = true;
        
    } else if (state == 3){
        
        screen2 = false;
        screen3 = true;
        
        
    } else if (state == 4){
        
        screen3 = false;
		screen4 = true;
        
    } else if (state == 5){
        
        agent3.unloadSound();
        main.unloadSound();
        screen5 = true;
    } else if (state == 6){
        screen6 = true;
    }
    
    cout<<state<<endl;
    
}

//--------------------------------------------------------------
void testApp::draw(){
	
    ofSetColor(255, 255, 255);
    main.setLoop(true);
    
    // do some drawing of user clouds and masks
    ofPushMatrix();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    int numUsers = openNIDevices[0].getNumTrackedUsers();
    for (int nID = 0; nID < numUsers; nID++){
        ofxOpenNIUser & user = openNIDevices[0].getTrackedUser(nID);
        // user.drawMask();
    
    //-----------------------------------------------------------------character's joint positions
    //********************* CHARACTER SHOULD BE CALLED IN EVERY INTERACTION SCREEN, AND JUST DRAWINGS ON ANIMATION SCREEN ************//
    
    ///////////////////retrieving joints positions from skeleton data
    
    ofxOpenNIJoint & head = user.getJoint(JOINT_HEAD);
    ofVec3f headPos = head.getProjectivePosition();
    
    ofxOpenNIJoint & righthand = user.getJoint(JOINT_LEFT_HAND);
    ofVec3f righthandPos = righthand.getProjectivePosition();
    
    ofxOpenNIJoint & lefthand = user.getJoint(JOINT_RIGHT_HAND);
    ofVec3f lefthandPos = lefthand.getProjectivePosition();
    
    ofxOpenNIJoint & lknee = user.getJoint(JOINT_RIGHT_KNEE);
    ofVec3f lkneePos = lknee.getProjectivePosition();
    
    ofxOpenNIJoint & rknee = user.getJoint(JOINT_LEFT_KNEE);
    ofVec3f rkneePos = rknee.getProjectivePosition();
    
    ofxOpenNIJoint & leftfoot = user.getJoint(JOINT_RIGHT_FOOT);
    ofVec3f leftfootPos = leftfoot.getProjectivePosition();
    
    ofxOpenNIJoint & rightfoot = user.getJoint(JOINT_LEFT_FOOT);
    ofVec3f rightfootPos = rightfoot.getProjectivePosition();
    
    ofxOpenNIJoint & rightarm = user.getJoint(JOINT_LEFT_SHOULDER);
    ofVec3f rightarmPos = rightarm.getProjectivePosition();
    
    ofxOpenNIJoint & leftarm = user.getJoint(JOINT_RIGHT_SHOULDER);
    ofVec3f leftarmPos = leftarm.getProjectivePosition();
    
    ofxOpenNIJoint & rightelb = user.getJoint(JOINT_LEFT_ELBOW);
    ofVec3f rightelbPos = rightelb.getProjectivePosition();
    
    ofxOpenNIJoint & leftelb = user.getJoint(JOINT_RIGHT_ELBOW);
    ofVec3f leftelbPos = leftelb.getProjectivePosition();
    
    ofxOpenNIJoint & rightHip = user.getJoint(JOINT_RIGHT_HIP);
    ofVec3f rightHipPos = rightHip.getProjectivePosition();
    
    ofxOpenNIJoint & leftHip = user.getJoint(JOINT_LEFT_HIP);
    ofVec3f leftHipPos = leftHip.getProjectivePosition();
    

    if(playNum == 0){
        main.play();
        playNum += 1;
    }
    
    states();
    
    if (start) {
        if(playNum == 1){
            firstscreen.play();
            playNum += 1;
        }
        intro.draw(0, 0);
        
    }
    
    //-----------------------------------------------openni draw
    ofPushMatrix();
    
    for (int deviceID = 0; deviceID < numDevices; deviceID++){
        ofTranslate(0, deviceID * 960);
        //   openNIDevices[deviceID].drawDebug(); // debug draw does the equivalent of the commented methods below
        //   openNIDevices[deviceID].drawDepth(0, 0, 640, 480);
        // openNIDevices[deviceID].drawImage(640, 0, 640, 480);
        //   openNIDevices[deviceID].drawSkeletons(0, 0, 640, 480);
        //openNIDevices[deviceID].drawHands(640, 0, 640, 480);
        
    }
 
    //------------------------------------------------mayor animation
        if (user.isFound() && righthandPos.y < headPos.y && lefthandPos.y < headPos.y && state == 0){
            state = 1;
        }
        if (screen1){
            
            mayor.setLoop(false);
            if(playNum == 2){
                
                mayor.play();
                playNum += 1;
                
            }
            mayorscreen.draw(0, 0);
            
            ////	JAVERIYAH : Mayor Pandora Animation		////
			int p = pandoraSeq.size();
			float pTime = ofGetElapsedTimef();
			float pDur = p/12.0;
			float pPos = fmodf(pTime, pDur);
			int i = int(pPos / pDur * p);
			pandoraSeq[i].draw(300, 0, 370, 370);
            
            // When audio stops, stop animation.
			if(!mayor.getIsPlaying()) {
				pandoraSeq[0].draw(300, 30, 370, 370);
				state = 2;
			}
            

            if (mayor.getIsPlaying() == false) state = 2;
        }
        
        
        
//--------------------------------------------------------------beanstalk screen
//*************************** STATE N.2 *****************************************//
        if (screen2){
            
            agent1.setLoop(false);
            if(playNum == 3){
                agent1.play();
                playNum +=1;
            }
            
            //---------------background features (beanstalk)
            nubes.draw(150, 150);
            beanstalk.draw(400,swimCount-400);
            
            // Only draw Beanstalk tutorial while audio is playing
			if(agent1.getIsPlaying()) {
                
                ////	JAVERIYAH : Beanstalk Tutorial Animation		////
				int beans = beanTipSeq.size();
				float beanTime = ofGetElapsedTimef();
				float beanDur = beans/6.0;
				float beanPos = fmodf(beanTime, beanDur);
				int beanIndex = int(beanPos / beanDur * beans);
				beanTipSeq[beanIndex].draw(770, 300, 300, 400);
			}
            
            int tTime = 2000;

//--------------------climbing gesture
            
            if(righthandPos.y < rightarmPos.y && wasRightArmUp){
                swimCount += 20;
            }else if(righthandPos.y > rightarmPos.y && !wasRightArmUp){
                swimCount += 20;
            }
            
            wasRightArmUp = righthandPos.y > rightarmPos.y; // this returns true or false ... it's just a shortcut instead of using and if
            
            
            if(lefthandPos.y < leftarmPos.y && wasLeftArmUp){
                swimCount += 20;
            }else if(lefthandPos.y > leftarmPos.y && !wasLeftArmUp){
                swimCount += 20;
            }
            
            wasLeftArmUp = lefthandPos.y > leftarmPos.y; // this returns true or false ... it's just a shortcut instead of using an if
            
//--------------------------------------character drawing
            ofPushMatrix();
            ofTranslate(200, 250);
            ofScale(0.8, 0.8);
            kid.leftHand(lHand, arm, leftelbPos, lefthandPos);
            kid.leftUpArm(arm, leftarmPos, leftelbPos);
            kid.rightHand(rHand, arm, rightelbPos, righthandPos);
            kid.rightUpArm(arm, rightarmPos, rightelbPos);
           // kid.leftFoot(lFoot, leg, lkneePos, leftfootPos);
            //kid.leftUpLeg(leg, leftHipPos, lkneePos);
            //kid.rightFoot(rFoot, leg, rkneePos, rightfootPos);
           // kid.rightUpLeg(leg, rightHipPos, rkneePos);
            
            ofPushMatrix();
            kid.torso(torso, headPos);
            kid.head(smile, headPos);
            ofPopMatrix();
            ofPopMatrix();
            
            if (swimCount - 400 > 600 && agent1.getIsPlaying() == false) state = 3;
            
        }
        
//--------------------------------------------------------------fireflies screen
//*************************** STATE N.3 *******************************///
        
        if (screen3) {
           
            agent2.setLoop(false);
            fireflies.setLoop(true);
            
            if(playNum == 4){
                agent2.play();
                playNum += 1;
            }
            
//--------------------------------------------draw user---------------------------------------------->>
            
            ofPushMatrix();
            ofTranslate(200, 250);
            ofScale(0.8, 0.8);
            kid.leftHand(lHand, arm, leftelbPos, lefthandPos);
            kid.leftUpArm(arm, leftarmPos, leftelbPos);
            kid.rightHand(rHand, arm, rightelbPos, righthandPos);
            kid.rightUpArm(arm, rightarmPos, rightelbPos);
           // kid.leftFoot(lFoot, leg, lkneePos, leftfootPos);
           // kid.leftUpLeg(leg, leftHipPos, lkneePos);
           // kid.rightFoot(rFoot, leg, rkneePos, rightfootPos);
            //kid.rightUpLeg(leg, rightHipPos, rkneePos);
            
            ofPushMatrix();
            kid.torso(torso, headPos);
            kid.head(smile, headPos);
            ofPopMatrix();
            ofPopMatrix();
            
            
//--------- Only draw Firefly tutorial while audio is playing
			if(agent2.getIsPlaying()) {
                
////	JAVERIYAH : Firefly Tutorial Animation		////
				int flyTip = fireflyTipSeq.size();
				float fTime = ofGetElapsedTimef();
				float fDur = flyTip/15.0;
				float fPos = fmodf(fTime, fDur);
				int fIndex = int(fPos / fDur * flyTip);
				fireflyTipSeq[fIndex].draw(770, 300, 300, 400);
			}

  //----------------------------------fireflies
            for(int i=0; i<NFLIES; i++)
            {
                if(fly[i].GetAlive())fly[i].draw();
               // else state = 4;
            }
            
            mPosX = righthandPos.x - 50;
            mPosY = righthandPos.y;
            
            int lanternX = 0;
            int lanternY = 300;
            
            ofPushMatrix();
            ofPushStyle();
            
            ofTranslate(200, 250);
            ofNoFill();
            net.draw(mPosX, mPosY + 20, 400, 450);
    
            //Collision
            
            for(int i=0; i<NFLIES; i++){
                
                if(fly[i].GetAlive()){
                    if(fly[i].x > (mPosX + 200) && fly[i].x < (mPosX + 200 + 25)){
                        xB = true;
                    } else {
                        xB = false;
                    }
                    
                    if(fly[i].y > (mPosY + 150 - 35) && fly[i].y < (mPosY + 150 + 35)){
                        yB = true;
                    } else {
                        yB = false;
                    }
                    
                    if(xB == true && yB == true){
                            fly[i].inNet = true;
                            fly[i].keepFlying = false;
                            fly[i].caught(0, 0);
                            fly[i].speedX = 0;
                            fly[i].speedY = 0;
                            numOfAliveFlies--;

                    }
                    if (numOfAliveFlies <= 1 && !agent2.getIsPlaying()) state = 4;
                    cout<<"fireflies =                                 "<<numOfAliveFlies<<endl;

                }
            }
            
            ofPopStyle();
            ofPopMatrix();
        }
//---------------------------forest screen
            if (screen4) {
                agent3.setLoop(false);
                if(playNum == 5){
                    agent3.play();
                    playNum += 1;
                }
                forest.draw(500, 350);
                
                ////	JAVERIYAH : Owl Animation	////
                int oo = owlSeq.size();
                float oTime = ofGetElapsedTimef();
                float oDur = oo/10.0;
                float oPos = fmodf(oTime, oDur);
                int j = int(oPos / oDur * oo);
                
                
                ////	JAVERIYAH :	Bird Animation	////
                int bi = birdSeq.size();
                float biTime = ofGetElapsedTimef();
                float biDur = bi/7.0;
                float biPos = fmodf(biTime, biDur);
                int k = int(biPos / biDur * bi);
                
                
                ////	JAVERIYAH :	Bunny Animation	////
                int bu = bunnySeq.size();
                float buTime = ofGetElapsedTimef();
                float buDur = bi/9.0;
                float buPos = fmodf(buTime, buDur);
                int l = int(buPos / buDur * bu);


                if (righthandPos.x+300 > 250 && righthandPos.x+300 < 250+260 && righthandPos.y+270 > 275 && righthandPos.y+270 < 275+220) {
                    owlSeq[j].draw(250, 375, 260, 420);
                } else {
                    // Only displays still image
                    owlSeq[0].draw(250, 375, 260, 420);
                }
                 if (righthandPos.x+300 > 540 && righthandPos.x+300 < 540+210 && righthandPos.y+270 > 320 && righthandPos.y+270 < 320+205) {
                    birdSeq[k].draw(640, 320, 210, 470);
                } else {
                    // Only displays still image
                    birdSeq[0].draw(640, 320, 210, 470);
                }
                if (righthandPos.x+300 > 400 && righthandPos.x+300 < 400+200 && righthandPos.y+270 > 500 && righthandPos.y+270 < 500+205) {
                     bunnySeq[l].draw(400, 500, 100, 205);
                } else {
                    // Only displays still image
                     bunnySeq[0].draw(400, 500, 100, 205);
                }
                
               
                ofPushMatrix();
                ofTranslate(350, 250);
                ofScale(0.8, 0.8);
                kid.leftHand(lHand, arm, leftelbPos, lefthandPos);
                kid.leftUpArm(arm, leftarmPos, leftelbPos);
                kid.rightHand(rHand, arm, rightelbPos, righthandPos);
                kid.rightUpArm(arm, rightarmPos, rightelbPos);
               // kid.leftFoot(lFoot, leg, lkneePos, leftfootPos);
                //kid.leftUpLeg(leg, leftHipPos, lkneePos);
               // kid.rightFoot(rFoot, leg, rkneePos, rightfootPos);
               // kid.rightUpLeg(leg, rightHipPos, rkneePos);
                
                ofPushMatrix();
                kid.torso(torso, headPos);
                kid.head(smile, headPos);
                ofPopMatrix();
                ofPopMatrix();
                
                lantern.draw(righthandPos.x+300, righthandPos.y+270);

                
                //vars for layers
                float maskX=ofGetWindowWidth()*4;
                float maskY=ofGetWindowHeight()*4;
                
                float mpx=maskX/2;
                float mpy=maskY/2;


                
                ofPushStyle();
                key.draw(keyX,keyY,30,30);
                ofDisableAlphaBlending();
                
                
                
                //blending for layers to simulate dark
                
                ofEnableAlphaBlending();
                ofSetColor(255,255,255,99.5);
                layer1.draw(mouseX-mpx,mouseY-mpy,maskX,maskY); // I have used mouse X and mouse Y to set the position of every layer this took a little math, the     mouseX and mouseY can be simple changed with the X and Y position of the users left hand.
                layer2.draw(righthandPos.x+300,righthandPos.y+270,maskX,maskY);
                layer3.draw(righthandPos.x+300,righthandPos.y+270,maskX,maskY);
                
                ofDisableAlphaBlending();
             
                ofPopStyle();
                
                if (!agent3.getIsPlaying()) state = 5;
    
            }
        
                if(screen5) {
                    roar.setLoop(false);
                    if(playNum == 6) {
                        roar.play();
                        playNum++;
                    }
                    ////	JAVERIYAH :	Bear Animation	////
                    int be = bearSeq.size();
                    float beTime = ofGetElapsedTimef();
                    float beDur = be/12.0;
                    float bePos = fmodf(beTime, beDur);
                    int m = int(bePos / beDur * be);
                    bearSeq[m].draw(580, 330, 670, 670);
                
                    if (!roar.getIsPlaying()) state = 6;
                }
            if(screen6) credits.draw(500, 350);
        
        
    }
    ofPushMatrix();
    ofTranslate(320, 240, -1000);
    //   user.drawPointCloud();
    ofPopMatrix();
    
    ofDisableBlendMode();
    ofPopMatrix();
    
    //	ofSetColor(0, 255, 0);
	string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate());
	//verdana.drawString(msg, 20, numDevices * 480 + 26);

    
}

//--------------------------------------------------------------
void testApp::userEvent(ofxOpenNIUserEvent & event){
    ofLogNotice() << getUserStatusAsString(event.userStatus) << "for user" << event.id << "from device" << event.deviceID;
}

//--------------------------------------------------------------
void testApp::exit(){
    
    for (int deviceID = 0; deviceID < numDevices; deviceID++){
        openNIDevices[deviceID].stop();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    int cloudRes = -1;
    switch (key) {
        case '1':
            cloudRes = 1;
            break;
        case '2':
            cloudRes = 2;
            break;
        case '3':
            cloudRes = 3;
            break;
        case '4':
            cloudRes = 4;
            break;
        case '5':
            cloudRes = 5;
            break;
        case 'x':
            for (int deviceID = 0; deviceID < numDevices; deviceID++){
                openNIDevices[deviceID].stop();
            }
            break;
        case 'i':
            for (int deviceID = 0; deviceID < numDevices; deviceID++){
                if (openNIDevices[deviceID].isImageOn()){
                    openNIDevices[deviceID].removeImageGenerator();
                    openNIDevices[deviceID].addInfraGenerator();
                    continue;
                }
                if (openNIDevices[deviceID].isInfraOn()){
                    openNIDevices[deviceID].removeInfraGenerator();
                    openNIDevices[deviceID].addImageGenerator();
                    continue;
                }
            }
            break;
        case 'b':
            for (int deviceID = 0; deviceID < numDevices; deviceID++){
                openNIDevices[deviceID].setUseBackBuffer(!openNIDevices[deviceID].getUseBackBuffer());
            }
            break;
        default:
            break;
    }
    for (int deviceID = 0; deviceID < numDevices; deviceID++){
		openNIDevices[deviceID].setPointCloudResolutionAllUsers(cloudRes);
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

