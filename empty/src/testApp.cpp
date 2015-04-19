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

bool xB = false;
bool yB = false;
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
   // fireflies.loadSound("fireFliesLoop.wav");
   // main.setLoop(true);
    main.setVolume(0.2);
  //  fireflies.setVolume(0.3);
  
//-------------------------------------character setup
    smile.loadImage("girl.png");
    rHand.loadImage("rhand.gif");
    lHand.loadImage("lhand.gif");
    rFoot.loadImage("rfoot.gif");
    lFoot.loadImage("lfoot.gif");
    arm.loadImage("arm.png");
    leg.loadImage("leg.png");
    torso.loadImage("torso.png");
    
//----------------------------------------firefly setup
    catcher.loadImage("splash.png");
    net.loadImage("net.gif");
    lantern.loadImage("lantern.png");
    
    //how to use vectors
    //mFlies.push_back(ofFirefly());
    //mFlies.erase(mFlies.begin());
    
    fly[0].SetAlive(true);
    numOfAliveFlies = 0;
    targetTime = ofGetElapsedTimeMillis() + 5000;
    
    lantern.width = 100;
    lantern.height = 80;
    
  //  lantern.x = 200;
   // lantern.y = 200;
    
//-----------------------------------------screens setup
    beanstalk.loadImage("beanstalk.png");
    nubes.loadImage("nubes.png");
    intro.loadImage("intro.png");
    mayorscreen.loadImage("mayor.png");
    jungle.loadImage("jungle.png");
    pandora[0].loadImage("pandora1.png");
    pandora[1].loadImage("pandora2.png");
    pandora[2].loadImage("pandora3.png");
    pandora[3].loadImage("pandora4.png");
    pandora[4].loadImage("pandora5.png");
    

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
    
    mPosX = mouseX;
    mPosY = mouseY;
    for(int i=0; i<NFLIES; i++)
    {
        if(fly[i].GetAlive())fly[i].update();
        fly[i].caughtX = mouseX;
        fly[i].caughtY = mouseY;
    }
    
    
    
    if(numOfAliveFlies < 9){
        if(ofGetElapsedTimeMillis() >  targetTime){
            numOfAliveFlies++;
            fly[numOfAliveFlies].SetAlive(true);
            targetTime = ofGetElapsedTimeMillis() + 5000;
        }
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
        
        
    } else {}
   
    cout<<state<<endl;

    
}





//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255, 255, 255);
    main.setLoop(true);
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
    
    // do some drawing of user clouds and masks
    ofPushMatrix();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    int numUsers = openNIDevices[0].getNumTrackedUsers();
    for (int nID = 0; nID < numUsers; nID++){
        ofxOpenNIUser & user = openNIDevices[0].getTrackedUser(nID);
       // user.drawMask();
       
        if (user.isFound()) {
            state = 1;
        }
        if (screen1){
            
            mayor.setLoop(false);
            if(playNum == 2){
                
                mayor.play();
                playNum += 1;
                
            }
            mayorscreen.draw(0, 0);
            for (int i = 0; i < 5; i++){
                ofPushMatrix();
                pandora[i].draw(440, 140, 150, 150);
                ofPopMatrix();
            }
            int time = 50.00;
            cout<<ofGetElapsedTimef()<<endl;
            if (ofGetElapsedTimef()> time) state = 2;
        }
        
  
//-----------------------------------------------------------------character draw
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
        
        
//--------------------------------------------------------------swimming gesture
//****************** STATE N.2 *****************************************//
        if (screen2){
    
            agent1.setLoop(false);
            if(playNum == 3){
                agent1.play();
                playNum +=1;
            }

      //---------------background features (beanstalk)
      nubes.draw(150, 150);
      beanstalk.draw(400,swimCount-400);
      

        int tTime = 2000;
        
        //hands up calibration Gesture
        
        if(righthandPos.y < rightarmPos.y && righthandPos.y > rightarmPos.y && ofGetElapsedTimeMillis() > tTime ) {
            cout <<" This is BANANAS"<<endl;
            
        }
        
        //Swim gesture
        
        if(righthandPos.y < rightarmPos.y && wasRightArmUp){
            cout <<"right Click"<<endl;
            swimCount += 20;
        }else if(righthandPos.y > rightarmPos.y && !wasRightArmUp){
            cout << "right Clock" << endl;
            swimCount += 20;
        }
        
        wasRightArmUp = righthandPos.y > rightarmPos.y; // this returns true or false ... it's just a shortcut instead of using and if
        
        
        if(lefthandPos.y < leftarmPos.y && wasLeftArmUp){
            cout <<"left Click"<<endl;
            swimCount += 20;
        }else if(lefthandPos.y > leftarmPos.y && !wasLeftArmUp){
            cout << "left Clock" << endl;
            swimCount += 20;
        }
        
        wasLeftArmUp = lefthandPos.y > leftarmPos.y; // this returns true or false ... it's just a shortcut instead of using an if
            
            
            ofPushMatrix();
            ofTranslate(200, 250);
            ofScale(0.8, 0.8);
            kid.leftHand(lHand, arm, leftelbPos, lefthandPos);
            kid.leftUpArm(arm, leftarmPos, leftelbPos);
            kid.rightHand(rHand, arm, rightelbPos, righthandPos);
            kid.rightUpArm(arm, rightarmPos, rightelbPos);
            kid.leftFoot(lFoot, leg, lkneePos, leftfootPos);
            kid.leftUpLeg(leg, leftHipPos, lkneePos);
            kid.rightFoot(rFoot, leg, rkneePos, rightfootPos);
            kid.rightUpLeg(leg, rightHipPos, rkneePos);
            
            ofPushMatrix();
            kid.torso(torso, headPos);
            kid.head(smile, headPos);
            ofPopMatrix();
            ofPopMatrix();
            
            if (swimCount - 400 > 600) state = 3;

        }
    
    
        if (screen3) {
        
        
       
//--------------------------------------------------------------fireflies draw
//************** STATE N.3 *******************************///
 
        ofSetRectMode(OF_RECTMODE_CENTER);
        
            agent2.setLoop(false);
            //fireflies.setLoop(true);
            
            
            
            if(playNum == 4){
                agent2.play();
                playNum += 1;
            }
        
        // ofBackground(50, 50, 50);
        jungle.draw(500, 350);
        
      //  ofSetColor(200, 0, 0);
       
       // ofFill();
      //  ofRect(lantern);
      
        for(int i=0; i<NFLIES; i++)
        {
            if(fly[i].GetAlive())fly[i].draw();
        }

        
        mPosX = righthandPos.x - 50;
        mPosY = righthandPos.y;

        ofPushMatrix();
        ofPushStyle();

        ofTranslate(200, 250);
        
            ofNoFill();
            
            net.draw(mPosX, mPosY + 20, 300, 350);
           // ofCircle(lefthandPos.x + 40, lefthandPos.y + 20, 20);

           // lantern.draw(250, 150, 200, 200);
          //  ofCircle(mPosX, mPosY, 50);

        
        
        //Collision
        
        for(int i=0; i<NFLIES; i++){
            
            if(fly[i].GetAlive()){
                if(fly[i].x > (mPosX + 200 - 25) && fly[i].x < (mPosX + 200 + 25)){
                    xB = true;
                } else {
                    xB = false;
                }
                
                if(fly[i].y > (mPosY + 200 - 25) && fly[i].y < (mPosY + 200 + 25)){
                    yB = true;
                } else {
                    yB = false;
                }
                
                if(xB == true && yB == true){
                    if(fly[i].inNet){
                        fly[i].keepFlying = false;
                        fly[i].caught(mPosX + 200, mPosY + 200);
                    }
                }
                
                //if(lantern.inside(fly[i].x, fly[i].y)){
                // fly[i].inNet = false;
                // fly[i].x = 50;
                // fly[i].y = 430;
                // }
            }
        }
        
        //cout << numOfAliveFlies << endl;
        //cout << ofGetElapsedTimeMillis() << endl;
        //cout << newFly << endl;
            ofPopStyle();
        ofPopMatrix();

  //------------------------------------------------------------------------------------------>>
        
        
        ofPushMatrix();
        ofTranslate(200, 250);
        ofScale(0.8, 0.8);
        kid.leftHand(lHand, arm, leftelbPos, lefthandPos);
        kid.leftUpArm(arm, leftarmPos, leftelbPos);
        kid.rightHand(rHand, arm, rightelbPos, righthandPos);
        kid.rightUpArm(arm, rightarmPos, rightelbPos);
        kid.leftFoot(lFoot, leg, lkneePos, leftfootPos);
        kid.leftUpLeg(leg, leftHipPos, lkneePos);
        kid.rightFoot(rFoot, leg, rkneePos, rightfootPos);
        kid.rightUpLeg(leg, rightHipPos, rkneePos);
        
        ofPushMatrix();
        kid.torso(torso, headPos);
        kid.head(smile, headPos);
        ofPopMatrix();
        ofPopMatrix();
        
        }

        
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

