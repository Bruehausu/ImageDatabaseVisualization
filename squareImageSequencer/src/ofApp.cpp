#include "ofApp.h"

const string allowed_ext[] = {"jpg", "png", "gif", "jpeg"};

class imgObj {
public:
    ofImage img;
    float id;
};

// a boolean function that tells ofSort how to compare two items
bool sortMe(imgObj & a, imgObj & b){
    if (a.id < b.id){
        return true;
    } else {
        return false;
    }
}

int get_distance(ofImage a, ofImage b){
    int total_diff = 0;
    for(int i = 0; i < a.getWidth(); i++){
        for(int j = 0; j < a.getHeight(); j++){
            ofColor c_a = a.getColor(i, j);
            ofColor c_b = b.getColor(i, j);
            int r_diff = pow((int)c_a.r - (int)c_b.r, 2);
            int g_diff = pow((int)c_a.g - (int)c_b.g, 2);
            int b_diff = pow((int)c_a.b - (int)c_b.b, 2);
            total_diff += (r_diff + g_diff + b_diff);
        }
    }
    return total_diff;
}

ofImage make_average(vector<ofImage> imgs){
    ofImage res = ofImage(imgs[0]);
    for(int i = 0; i < res.getWidth(); i++){
        for(int j = 0; j < res.getHeight(); j++){
            int avg_r = 0;
            int avg_g = 0;
            int avg_b = 0;
            for(int k = 0; k < imgs.size(); k++){
                avg_r += imgs[k].getColor(i,j).r;
                avg_g += imgs[k].getColor(i,j).g;
                avg_b += imgs[k].getColor(i,j).b;
                
            }
            res.setColor(i,j,ofColor(avg_r/imgs.size(),
                                     avg_g/imgs.size(),
                                     avg_b/imgs.size()));
        }
    }
    return res;
                         
}

void ofApp::scan_dir_imgs(ofDirectory dir){
    ofDirectory new_dir;
    int size = dir.listDir();
    for (int i = 0; i < size; i++){
        if (dir.getFile(i).isDirectory()){
            new_dir = ofDirectory(dir.getFile(i).getAbsolutePath());
            new_dir.listDir();
            new_dir.sort();
            scan_dir_imgs(new_dir);
        } else if (std::find(std::begin(allowed_ext),
                             std::end(allowed_ext),
                             dir.getFile(i).getExtension()) != std::end(allowed_ext)) {
            images.push_back(dir.getFile(i));
        }
    }
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    int recent_count = 4;
    
    string imageDir = "/Users/guydebree/Documents/of_root/apps/myApps/squareImageSequencer/bin/data/images";

    // load all the images
    ofLog() << "Gathering images...";
    ofDirectory dir = ofDirectory(imageDir);
    scan_dir_imgs(dir);
    
    ofLog() << "Found " << images.size() << " images";
    ofLog() << "constructing image sequence";
    
    /*vector<imgObj> imgObjs;
    for(int i = 0; i < images.size(); i++){
        imgObj img = *new imgObj();
        img.img = images[i];
        img.id = imagePoints[i][0];
        
        imgObjs.push_back(img);
    }
    
    ofSort(imgObjs, sortMe);
    
    ofLog() << "saving image sequence";
    */
    
    int full_size = images.size();
    ofImage curr = images[0];
    images.erase(images.begin() + 0);
    int count = 0;
    
    while(images.size() > 0){
        if (count % 20 == 0)    ofLog() << " - sorted images "<< count <<" / "<<full_size <<
            " - " << images.size() << "remain";
        
        string outpath = ofToString(count) + ".png";
        while (outpath.length() < 13){
            outpath = '0' + outpath;
        }
        outpath = "out/img" + outpath;
        
        curr.save(outpath);
        
        recents.push_back(curr);
        if(recents.size() > recent_count){
            recents.erase(recents.begin() + 0);
        }
        
        ofImage avg = make_average(recents);
        
        int min_found = -1;
        int min_dist = INT_MAX;
        
        for(int i =0; i < images.size(); i++){
            int diff = get_distance(avg, images[i]);
            if (diff < min_dist){
                min_found = i;
                min_dist = diff;
            }
        }
        
        curr = images[min_found];
        images.erase(images.begin() + min_found);
        
        
        count += 1;
    }
    
    
    
    /*
     int curr = 0;
     vector<int> visited;

     for(int j = 0; j < images.size() - 1; j++){
        
        if (j % 20 == 0)    ofLog() << " - sorting image "<< j <<" / "<<images.size();
        
        string outpath = ofToString(curr) + ".png";
        while (outpath.length() < 13){
            outpath = '0' + outpath;
        }
        
        outpath = "out/" + outpath;
        
        images[curr].save(outpath);
        visited.push_back(curr);
        
        double min_dist = 100;
        int min_i = -1;
        
        for(int i = 0; i < images.size(); i++){
            if(!(std::find(visited.begin(), visited.end(),
                         i) != visited.end())) {
                double new_dist = sqrt(pow(imagePoints[i][0] - imagePoints[curr][0], 2) +
                                       pow(imagePoints[i][1] - imagePoints[curr][1], 2));
                if (min_i == -1 || (new_dist < min_dist)){
                    min_i = i;
                    min_dist = new_dist;
                }
            }
        }
        
        curr = min_i;
    }*/
    
}



//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    
    for (int i=0; i<imagePoints.size(); i++) {
        float x = ofMap(imagePoints[i][0], 0, 1, 0, ofGetWidth());
        float y = ofMap(imagePoints[i][1], 0, 1, 0, ofGetHeight());
        images[i].draw(x, y, imageSize * images[i].getWidth(), imageSize * images[i].getHeight());
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
