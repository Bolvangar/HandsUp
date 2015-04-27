//
//  ofFirefly.cpp
//  fireflyTest
//
//  Created by Alex Mold on 09/03/2015.
//
//

#include "ofFirefly.h"
#include "math.h"


ofFirefly::ofFirefly(){
    
    x = 0;
    y = 0;
   
    speedY = 0;
    speedX = 0;
    isAlive = false;
    dim = 15;
}

void ofFirefly::setup(){
    keepFlying = true;
    x = ofRandom( 100.0,  620.0 );
    y = ofRandom(400);
    speedY = ofRandom( 0.2 , 1.5 );
    speedX = ofRandom(-0.5, 0.5);
    noiseAdd = ofRandom(0,5000000);
    dim = ofRandom(5, 15);
    inNet = true;
}

void ofFirefly::update(){
    
    /*if(keepFlying){
        x = ofNoise((ofGetElapsedTimeMillis() + noiseAdd )/1000.0) * 640;
        y = ofNoise((ofGetElapsedTimeMillis() + 1000 + noiseAdd)/1000.0) * 480;
   
        cout << x << "," << y << endl;
     
    } else {
        x = caughtX;
        y = caughtY;
    }*/
    
    y += speedY;
    x += speedX;
    //Flying around
    
    //Y stuff
    if(y > 240){
        speedY -= 0.01;
        if(speedY < -2.0){
            speedY = -1.5;
        }
    } else {
        speedY += 0.01;
        if(speedY > 2.0){
            speedY = 1.5;
        }
    }
    
    //X stuff
    if(x > 600){
        speedX -= 0.01;
        if(speedX < -0.5){
            speedX = -0.5;
        }
    } else if(x < 40){
        speedX += 0.01;
        if(speedX > 0.5){
            speedX = 0.5;
        }
    }
    
   
}

void ofFirefly::caught(float _x, float _y){
    if(inNet){
        x = _x+10;
        y = _y+10;
    } 
}

void ofFirefly::draw(){
  
    ofPushStyle();
    ofSetColor(255,255,0);
    ofCircle(x, y, dim);
    ofPopStyle();
}

bool ofFirefly::GetAlive(){
    return isAlive;
}

void ofFirefly::SetAlive(bool b){
    isAlive = b;
    if(isAlive)setup();
}


