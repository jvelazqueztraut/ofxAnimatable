//
//  ofxAnimatableVideo.h
//  exampleAdvanced
//
//  Created by jvelazqueztraut on 06/05/13.
//
//  masOTROS SRL

#pragma once

#include "ofxAnimatableObject.h"

class ofxAnimatableOfVideoPlayer : public ofxAnimatableObject {
    
public:
    ~ofxAnimatableOfVideoPlayer(){};
    
    void loadMovie(string name){
        movie.loadMovie(name);
    }
    
    void setLoopState(ofLoopType l){
        movie.setLoopState(l);
    }
    
    void update(float dt){
        ofxAnimatableObject::update(dt);
        movie.update();
    }
    
    void draw(){
        ofxAnimatableObject::beginDraw();
        movie.draw(0,0);
        ofxAnimatableObject::endDraw();
    }
    
    void setAnchorPercent(float xPct,float yPct){
        movie.setAnchorPercent(xPct,yPct);
    }
    
    ofVideoPlayer     movie;
};
