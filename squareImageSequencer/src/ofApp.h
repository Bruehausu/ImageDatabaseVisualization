#pragma once

#include "ofMain.h"
#include "ofxCcv.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void scan_dir_imgs(ofDirectory dir);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofxCcv ccv;
    
        int recent_count;
        vector<ofImage> recents;
    
        vector<ofImage> images;

        vector<vector<double> > imagePoints;
        vector<vector<float> > encodings;

        ofParameter<float> scale;
        ofParameter<float> imageSize;
    
        int t;
		
};
