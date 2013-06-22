//
//  ofxAnimatableImage.h
//  exampleAdvanced
//
//  Created by jvelazqueztraut on 06/05/13.
//
//  masOTROS SRL

#pragma once

#include "ofxAnimatableObject.h"

class ofxAnimatableOfImage : public ofxAnimatableObject, public ofImage {
    
public:
    ~ofxAnimatableOfImage(){};
    
    void draw(){
        ofxAnimatableObject::beginDraw();
        ofImage::draw(0,0);
        ofxAnimatableObject::endDraw();
    }
};
