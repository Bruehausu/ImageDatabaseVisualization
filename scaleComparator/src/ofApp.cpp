#include "ofApp.h"

void ofApp::setup() {
    //ccv.setup("image-net-2012-vgg-d.sqlite3");
    ccv.setup("image-net-2012.sqlite3");
               
//    ofPixels img;
//    ofLoadImage(img, "cat.jpg");
//    ccv.classify(img);
    
    images.push_back(ofImage("bomb-32.png"));
    images.push_back(ofImage("bomb-96.png"));
    images.push_back(ofImage("bomb-228.png"));
    images.push_back(ofImage("bomb-864.png"));
    images.push_back(ofImage("bomb-2592.png"));
    
    imageNames.push_back("bomb-32.png");
    imageNames.push_back("bomb-96.png");
    imageNames.push_back("bomb-228.png");
    imageNames.push_back("bomb-864.png");
    imageNames.push_back("bomb-2592.png");
    
    curr_index = 0;
    setupImage();
    
}

void ofApp::setupImage(){
    curr_image = images[curr_index];
    scaled_image = images[curr_index];
    if(scaled_image.getWidth() > 864){
        scaled_image.resize(864, 864);
    }
    results = ccv.classify(curr_image);
}

void ofApp::keyPressed(int key){
    curr_index = (curr_index + 1) % images.size();
    setupImage();
}

void ofApp::update() {
    
}

void ofApp::draw() {
    if (!ccv.isLoaded()) {
        ofSetColor(0);
        ofDrawBitmapString("Network file not found! Check your data folder to make sure it exists.", 20, 20);
        return;
    }
    ofSetColor(255);
    //cam.draw(0, 0);
    scaled_image.draw(0, 0);
    ofPushStyle();
    ofTranslate(5, 5);
    ofDrawBitmapString(imageNames[curr_index], 0, 7);
    ofTranslate(0, 15);
    for(int i = 0; i < results.size(); i++) {
        ofSetColor(ofColor::white);
        ofFill();
        ofDrawRectangle(0, 0, 100, 10);
        ofSetColor(ofColor::black);
        ofDrawRectangle(1, 1, (100-2) * results[i].confidence, 10-2);
        ofSetColor(ofColor::white);
        ofDrawBitmapStringHighlight(results[i].imageNetName, 105, 10);
        ofTranslate(0, 15);
    }
    
    ofPopStyle();
}
