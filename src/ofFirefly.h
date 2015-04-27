//
//  ofFirefly.h
//  fireflyTest
//
//  Created by Alex Mold on 09/03/2015.
//
//

#ifndef __OF_FIREFLY
#define __OF_FIREFLY

#include <iostream>
#include "ofMain.h"


class ofFirefly {
public:
    
    ofFirefly();
    void setup();
    void update();
    void draw();
    
    
    float x;
    float y;
    float caughtX;
    float caughtY;
    float speedX;
    float speedY;
    int dim;

    bool keepFlying;
    bool GetAlive();
    void SetAlive(bool b);
    void caught(float _x, float _y);
    bool inNet;
    
    private:
    
    bool isAlive;
    int noiseAdd;
};


#endif /* defined(__fireflyTest__ofFirefly__) */
