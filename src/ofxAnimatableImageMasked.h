//
//  ofxImageMasked.h
//  unmaskImage
//
//  Created by Zaira on 05/02/14.
//
//

#pragma once
#include "ofMain.h"
#include "ofxAnimatableObject.h"
#include "ofxAnimatableFloat.h"

enum MaskType{
    RECT=0,
    CIRCULAR,
    DIAGONAL,
};

class ofxAnimatableImageMasked : public ofxAnimatableObject<ofFbo> {
public:
    ofxAnimatableImageMasked() : ofxAnimatableObject<ofFbo>(){
        string shaderProgram =
		"uniform sampler2DRect tex;\
		\
		void main (void){\
        vec2 pos = gl_FragCoord.xy;\
		vec4 color = texture2DRect(tex,pos);\
		gl_FragColor = color;\
		}";

		shader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
		shader.linkProgram();
        
        mask.reset(1.);
        
        type = DIAGONAL;
    }
    
    ~ofxAnimatableImageMasked(){};
    
    void loadImage(string path){
        ofPixels image;
        ofLoadImage(image, path);
        
        width = image.getWidth();
        height = image.getHeight();
        
        ofFbo::allocate(width,height,GL_RGBA);
        tex.loadData(image);
        
        radius = 0.5 * sqrt( width*width + height*height );
    }
    
    void update(float dt){
        
        size.update(dt);
        color.update(dt);
        position.update(dt);
        rotation.update(dt);
        
        mask.update(dt);
        
        if(mask.val()==1.){
            ofFbo::begin();
                ofSetColor(255);
                tex.draw(0,0);
            ofFbo::end();
        }
        else{
            ofFbo::begin();
                ofClear(0,0);
        
                shader.begin();
                shader.setUniformTexture("tex",tex,1);
        
                    ofSetColor(255);
                    switch(type){
                        case RECT:
                            ofRect(0,0,width*mask.val(),height);
                            break;
                        case CIRCULAR:
                            ofCircle(width*anchor.x,height*anchor.y,radius*mask.val());
                            break;
                        case DIAGONAL:
                            ofSetPolyMode(OF_POLY_WINDING_ODD);	// this is the normal mode
                            ofBeginShape();
                                ofVertex(0,0);
                                ofVertex((width+height)*mask.val(),0);
                                ofVertex((width+height)*mask.val()-height,height);
                                ofVertex(0,height);
                            ofEndShape();
                            break;
                        //VARIOS RECTANGULOS
                        //
                    }
        
                shader.end();
            ofFbo::end();
        }
    }
    
    bool isOrWillBeAnimating(){
        return (mask.isOrWillBeAnimating() || ofxAnimatableObject<ofFbo>::isOrWillBeAnimating());
    }
    
    void setMask(float m){mask.reset(m);}
    
    void setMaskType(MaskType t){
        type=t;
    }
    
    ofxAnimatableFloat mask;
private:
    ofTexture tex;
    ofShader shader;
    MaskType type;
    float width;
    float height;
    float radius;
};