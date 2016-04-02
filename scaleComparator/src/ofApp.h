#pragma once

#include "ofxCcv.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void setupImage();
    
    ofxCcv ccv;
    vector<ofxCcv::Classification> results;
    ofVideoGrabber cam;
    vector<ofImage> images;
    vector<string> imageNames;
    
    ofImage curr_image;
    ofImage scaled_image;
    int curr_index;
};