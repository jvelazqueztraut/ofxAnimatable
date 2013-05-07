//
//  ofxAnimatableImage.h
//  exampleAdvanced
//
//  Created by Wanda on 06/05/13.
//
//  masOTROS SRL

#pragma once

#include "ofxAnimatableItem.h"

class ofxAnimatableImage : public ofxAnimatableItem {
    
public:
    ~ofxAnimatableImage(){};
    
    void loadImage(string file){
        image.loadImage(file);
    }
    void draw(){
        ofxAnimatableItem::beginDraw();
        image.draw(0,0);
        ofxAnimatableItem::endDraw();
    }
    void setAnchorPercent(float xPct,float yPct){
        image.setAnchorPercent(xPct,yPct);
    }

    ofImage     image;
};
