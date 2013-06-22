//
//  ofxAnimatableOfxSprite.h
//
//  Created by Wanda on 21/06/13.
//

#pragma once

#include "ofxAnimatableObject.h"
#include "ofxSprite.h"

class ofxAnimatableOfxSprite : public ofxAnimatableObject, public ofxSprite {
    
public:
    ~ofxAnimatableOfxSprite(){};
    
    void update(float dt){
        ofxAnimatableObject::update(dt);
        ofxSprite::update();
    }
    
    void draw(){
        ofxAnimatableObject::beginDraw();
        ofxSprite::draw(0,0);
        ofxAnimatableObject::endDraw();
    }
};