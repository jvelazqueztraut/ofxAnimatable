//
//  ofxAnimatableVideo.h
//  exampleAdvanced
//
//  Created by jvelazqueztraut on 06/05/13.
//
//  masOTROS SRL

#pragma once

#include "ofxAnimatableObject.h"

class ofxAnimatableOfVideoPlayer : public ofxAnimatableObject, public ofVideoPlayer {
    
public:
    ~ofxAnimatableOfVideoPlayer(){};
    
    void update(float dt){
        ofxAnimatableObject::update(dt);
        ofVideoPlayer::update();
    }
    
    void draw(){
        ofxAnimatableObject::beginDraw();
        ofVideoPlayer::draw(0,0);
        ofxAnimatableObject::endDraw();
    }
};
