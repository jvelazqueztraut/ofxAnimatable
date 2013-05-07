//
//  ofxAnimatableFBO.h
//  exampleAdvanced
//
//  Created by Wanda on 06/05/13.
//
//  masOTROS SRL

#pragma once

#include "ofxItem.h"

class ofxAnimatableFBO : public ofxAnimatableItem {
public:
    ~ofxAnimatableFBO(){};
    
    void setup(int w, int h){
        fbo.allocate(w,h);
        fbo.begin();
        ofClear(0,0);
        fbo.end();
    }
    void update(float dt){
        ofxItem::update(dt);
        fbo.begin();
        fbo.end();
    }
    void draw(){
        ofxAnimatableItem::beginDraw();
        fbo.draw(0,0);
        ofxAnimatableItem::endDraw();
    }
    
    void setAnchorPercent(float xPct,float yPct){
        fbo.setAnchorPercent(xPct,yPct);
    }
    
    ofFbo       fbo;
};
