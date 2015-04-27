//
//  Character.cpp
//  openNiSample007
//
//  Created by Sharon Profita on 08/03/2015.
//
//

#include "Character.h"
#include "ofGraphics.h"

void Character::setup(){
    
    pin.loadImage("pin.png");
}

void Character::torso(ofImage img, ofVec3f position){
    
    ofPushMatrix();
    img.draw(position.x + 10, position.y + 180, 300, 350);
    ofPopMatrix();
    
}

void Character::head(ofImage img, ofVec3f position){
  
    ofPushMatrix();
    img.draw(position.x, position.y + 30, 200, 200);
    ofPopMatrix();
    
}

void Character::rightHand(ofImage img1, ofImage img2, ofVec3f RefPos, ofVec3f jointPos){
    
    ofVec2f refJoint2d(RefPos.x, RefPos.y);
    ofVec2f joint2d(jointPos.x, jointPos.y);
    
    ofVec2f refJointv = refJoint2d - joint2d;
    refJointv.normalize();
 
    float angle = refJointv.angle(ofVec2f(0, 1));
    
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    

    ofPushMatrix();
        //pin.draw(RefPos.x, RefPos.y, 50, 50);

        ofTranslate(jointPos.x, jointPos.y);
        ofRotate(90, 0, 0, 1);
        ofRotate(-angle, 0, 0, 1);
        img2.draw(50, 10, 140, 110);
        img1.draw(0, 0, 60, 60);
    ofPopMatrix();

    ofPopStyle();
    
}

void Character::leftHand(ofImage img1, ofImage img2, ofVec3f refPos, ofVec3f jointPos){
    
    ofVec2f refJoint2d(refPos.x, refPos.y);
    ofVec2f joint2d(jointPos.x, jointPos.y);
    
    ofVec2f refJointv = refJoint2d - joint2d;
    refJointv.normalize();
    float angle = refJointv.angle(ofVec2f(0, 1));

    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    ofPushMatrix();
    ofTranslate(jointPos.x, jointPos.y);
    ofRotate(-90, 0, 0, 1);
    ofRotate(-angle, 0, 0, 1);
    img2.draw(-50, 10, 140, 110);
    img1.draw(0, 0, 50, 50);
    ofPopMatrix();

}

void Character::rightFoot(ofImage img1, ofImage img2, ofVec3f refPos, ofVec3f jointPos){
    
    ofVec2f refJoint2d(refPos.x, refPos.y);
    ofVec2f joint2d(jointPos.x, jointPos.y);
    
    ofVec2f refJointv = refJoint2d - joint2d;
    refJointv.normalize();
    float angle = refJointv.angle(ofVec2f(-1, 0));
    
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    ofPushMatrix();
    ofTranslate(jointPos.x, jointPos.y);
    ofRotate(-90, 0, 0, 1);
    ofRotate(-angle, 0, 0, 1);
    img2.draw(0, -50, 110, 180);
    img1.draw(-20, 10, 70, 60);
    ofPopMatrix();
    
}

void Character::leftFoot(ofImage img1, ofImage img2, ofVec3f refPos, ofVec3f jointPos){
    
    ofVec2f refJoint2d(refPos.x, refPos.y);
    ofVec2f joint2d(jointPos.x, jointPos.y);
    
    ofVec2f refJointv = refJoint2d - joint2d;
    refJointv.normalize();
    float angle = refJointv.angle(ofVec2f(-1, 0));
    
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    ofPushMatrix();
    ofTranslate(jointPos.x, jointPos.y);
    ofRotate(-90, 0, 0, 1);
    ofRotate(-angle, 0, 0, 1);
    img2.draw(0, -50, 110, 180);
    img1.draw(10, 10, 70, 60);
    ofPopMatrix();
    
}

void Character::rightUpArm(ofImage img, ofVec3f refPos, ofVec3f jointPos){
    
    ofVec2f refJoint2d(refPos.x, refPos.y);
    ofVec2f joint2d(jointPos.x, jointPos.y);
    
    ofVec2f refJointv = refJoint2d - joint2d;
    refJointv.normalize();
    
    float angle = refJointv.angle(ofVec2f(0, 1));
    
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    ofPushMatrix();
    ofTranslate(jointPos.x, jointPos.y);
    ofRotate(90, 0, 0, 1);
    ofRotate(-angle, 0, 0, 1);
    img.draw(40, 10, 120, 100);
    ofPopMatrix();
    
    ofPopStyle();

}

void Character::leftUpArm(ofImage img, ofVec3f refPos, ofVec3f jointPos){
    
    ofVec2f refJoint2d(refPos.x, refPos.y);
    ofVec2f joint2d(jointPos.x, jointPos.y);
    
    ofVec2f refJointv = refJoint2d - joint2d;
    refJointv.normalize();
    
    float angle = refJointv.angle(ofVec2f(0, 1));
    
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    ofPushMatrix();
    ofTranslate(jointPos.x, jointPos.y);
    ofRotate(90, 0, 0, 1);
    ofRotate(-angle, 0, 0, 1);
    img.draw(40, 10, 120, 100);
    ofPopMatrix();
    
    ofPopStyle();
    
}

void Character::rightUpLeg(ofImage img, ofVec3f refPos, ofVec3f jointPos){
    
    ofVec2f refJoint2d(refPos.x, refPos.y);
    ofVec2f joint2d(jointPos.x, jointPos.y);
    
    ofVec2f refJointv = refJoint2d - joint2d;
    refJointv.normalize();
    
    float angle = refJointv.angle(ofVec2f(0, 1));
    
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    ofPushMatrix();
    ofTranslate(jointPos.x, jointPos.y);
    ofRotate(-25, 0, 0, 1);
    ofRotate(-angle, 0, 0, 1);
    img.draw(0, 50, 110, 110);
    ofPopMatrix();
    
    ofPopStyle();

}

void Character::leftUpLeg(ofImage img, ofVec3f refPos, ofVec3f jointPos){
    
    ofVec2f refJoint2d(refPos.x, refPos.y);
    ofVec2f joint2d(jointPos.x, jointPos.y);
    
    ofVec2f refJointv = refJoint2d - joint2d;
    refJointv.normalize();
    
    float angle = refJointv.angle(ofVec2f(0, 1));
    
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    ofPushMatrix();
    ofTranslate(jointPos.x, jointPos.y);
    ofRotate(20, 0, 0, 1);
    ofRotate(-angle, 0, 0, 1);
    img.draw(0, 50, 110, 110);
    ofPopMatrix();
    
    ofPopStyle();
    
}