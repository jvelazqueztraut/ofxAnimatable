//
//  ofxAnimatableVideo.h
//  exampleAdvanced
//
//  Created by Wanda on 06/05/13.
//
//  masOTROS SRL

#pragma once

#include "ofxAnimatableItem.h"

class ofxAnimatableVideo : public ofxAnimatableItem {
    
public:
    ~ofxAnimatableVideo(){};
    
    void loadVideo(string name){
        video.loadMovie(name);
    }
    void setLoopState(ofLoopType l){
        video.setLoopState(l);
    }
    void update(float dt){
        ofxAnimatableItem::update(dt);
        video.update();
    }
    void draw(){
        ofxAnimatableItem::beginDraw();
        video.draw(0,0);
        ofxAnimatableItem::endDraw();
    }
    
    void setAnchorPercent(float xPct,float yPct){
        video.setAnchorPercent(xPct,yPct);
    }
    
    ofVideoPlayer     video;
};
