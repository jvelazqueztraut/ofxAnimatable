//
//  ofxAnimatableImage.h
//  exampleAdvanced
//
//  Created by jvelazqueztraut on 06/05/13.
//
//  masOTROS SRL

#pragma once

#include "ofxAnimatableObject.h"

class ofxAnimatableOfImage : public ofxAnimatableObject {
    
public:
    ~ofxAnimatableImage(){};
    
    void loadImage(string file){
        image.loadImage(file);
    }
    
    void draw(){
        ofxAnimatableObject::beginDraw();
        image.draw(0,0);
        ofxAnimatableObject::endDraw();
    }
    
    void setAnchorPercent(float xPct,float yPct){
        image.setAnchorPercent(xPct,yPct);
    }

    ofImage     image;
};
