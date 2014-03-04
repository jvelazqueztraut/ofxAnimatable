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
    RECTANGULAR=0,
    CIRCULAR,
    DIAGONAL,
    ARROW,
    MULTI_ARROW,
    RECTANGLES,
    HORIZONTAL,
    VERTICAL
};

#define RECTANGLES_X 5
#define RECTANGLES_Y 3
#define RECTANGLES_DELAY 0.05
#define RECTANGLES_TIME 0.2
template <class T>
class ofxAnimatableObjectMasked : public ofxAnimatableObject<ofFbo>, public T{
public:
    ofxAnimatableObjectMasked() : ofxAnimatableObject<ofFbo>() , T(){
        string shaderProgram =
		"#extension GL_ARB_texture_rectangle: enable\n\
		\n\
		uniform sampler2DRect tex;\n\
		\n\
		void main (void){\n\
        vec2 pos = gl_FragCoord.xy;\n\
		vec4 color = texture2DRect(tex,pos);\n\
		gl_FragColor = color;\n\
		}";
        
		shader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
		shader.linkProgram();
        
        mask.reset(1.);
        
        width = height = 0;
        
        type = DIAGONAL;
    }
    
    ~ofxAnimatableObjectMasked(){};
    
    void allocate(){
        width = T::getWidth();
        height = T::getHeight();
            
        ofFbo::allocate(width,height,GL_RGBA);
            
        radius = 0.5 * sqrt( width*width + height*height );
    }
    
    void update(float dt){
        
        if(!ofFbo::isAllocated()){
            allocate();
        }
        
        ofxAnimatableObject<ofFbo>::update(dt);
        
        mask.update(dt);
        
        if(mask.isOrWillBeAnimating()){
            ofPushStyle();
            ofPushMatrix();
            ofFill();
            ofFbo::begin();
            glEnable(GL_BLEND);
            glBlendFuncSeparate(GL_ONE, GL_SRC_COLOR, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
            ofClear(0,0);
            ofSetColor(255);
            
            if(aux.isAllocated()){
                aux.draw(0,0);
            }
            
            if(mask.val()==1.){
                T::draw(0,0);
            }
            else{
                switch(type){
                    case RECTANGULAR:
                        shader.begin();
                        shader.setUniformTexture("tex",T::getTextureReference(),0);
                        ofRect(0,0,width*mask.val(),height);
                        shader.end();
                        break;
                    case CIRCULAR:
                        shader.begin();
                        shader.setUniformTexture("tex",T::getTextureReference(),0);
                        ofCircle(width*this->anchor.x,height*this->anchor.y,radius*mask.val());
                        shader.end();
                        break;
                    case DIAGONAL:
                        shader.begin();
                        shader.setUniformTexture("tex",T::getTextureReference(),0);
                        ofSetPolyMode(OF_POLY_WINDING_ODD);	// this is the normal mode
                        ofBeginShape();
                        ofVertex(0,0);
                        ofVertex((width+height)*mask.val(),0);
                        ofVertex((width+height)*mask.val()-height,height);
                        ofVertex(0,height);
                        ofEndShape();
                        shader.end();
                        break;
                    case ARROW:
                        shader.begin();
                        shader.setUniformTexture("tex",T::getTextureReference(),0);
                        ofSetPolyMode(OF_POLY_WINDING_ODD);	// this is the normal mode
                        ofBeginShape();
                        ofVertex(0,0);
                        ofVertex((width+height*0.5)*mask.val()-height*0.5,0);
                        ofVertex((width+height*0.5)*mask.val(),height*0.5);
                        ofVertex((width+height*0.5)*mask.val()-height*0.5,height);
                        ofVertex(0,height);
                        ofEndShape();
                        shader.end();
                        break;
                    case MULTI_ARROW:
                        shader.begin();
                        shader.setUniformTexture("tex",T::getTextureReference(),0);
                        ofSetPolyMode(OF_POLY_WINDING_ODD);	// this is the normal mode
                        ofBeginShape();
                        ofVertex(0,0);
                        ofVertex((width+height*1.75)*mask.val()-height*1.75,0);
                        ofVertex((width+height*1.75)*mask.val()-height*1.25,height*0.5);
                        ofVertex((width+height*1.75)*mask.val()-height*1.75,height);
                        ofVertex(0,height);
                        ofEndShape();
                        ofBeginShape();
                        ofVertex((width+height*1.75)*mask.val()-height,0);
                        ofVertex((width+height*1.75)*mask.val()-height*0.5,0);
                        ofVertex((width+height*1.75)*mask.val(),height*0.5);
                        ofVertex((width+height*1.75)*mask.val()-height*0.5,height);
                        ofVertex((width+height*1.75)*mask.val()-height,height);
                        ofVertex((width+height*1.75)*mask.val()-height*0.5,height*0.5);
                        ofEndShape();
                        shader.end();
                        break;
                    case RECTANGLES:
                        shader.begin();
                        shader.setUniformTexture("tex",T::getTextureReference(),0);
                        ofSetRectMode(OF_RECTMODE_CENTER);
                        for(int x=0;x<RECTANGLES_X;x++){
                            for(int y=0;y<RECTANGLES_Y;y++){
                                if(mask.val()>(x*RECTANGLES_Y+y)*RECTANGLES_DELAY){
                                    if((mask.val()-(x*RECTANGLES_Y+y)*RECTANGLES_DELAY)/RECTANGLES_TIME<1.){
                                        ofRect((x*2+1)*width/(RECTANGLES_X*2),(y*2+1)*height/(RECTANGLES_Y*2),width/(RECTANGLES_X)*(mask.val()-(x*RECTANGLES_Y+y)*RECTANGLES_DELAY)/RECTANGLES_TIME,height/(RECTANGLES_Y)*(mask.val()-(x*RECTANGLES_Y+y)*RECTANGLES_DELAY)/RECTANGLES_TIME);
                                    }
                                    else{
                                        ofRect((x*2+1)*width/(RECTANGLES_X*2),(y*2+1)*height/(RECTANGLES_Y*2),width/RECTANGLES_X,height/RECTANGLES_Y);
                                    }
                                }
                            }
                        }
                        shader.end();
                        break;
                    case HORIZONTAL:
                        ofTranslate(width-mask.val()*width,0);
                        T::draw(0,0);
                        break;
                    case VERTICAL:
                        ofTranslate(0,height-mask.val()*height);
                        T::draw(0,0);
                        break;
                }
            }
            ofFbo::end();
            ofPopMatrix();
            ofPopStyle();
        }
    }
    
    void draw(){
        ofxAnimatableObject<ofFbo>::draw();
    }
    
    void setAnchorPercent(float xPct,float yPct){
		ofxAnimatableObject<ofFbo>::setAnchorPercent(xPct,yPct);
	}
    
    bool isOrWillBeAnimating(){
        return (mask.isOrWillBeAnimating() || ofxAnimatableObject<ofFbo>::isOrWillBeAnimating());
    }
    
    void setMask(float m){mask.reset(m);}
    
    void setMaskType(MaskType t){
        type=t;
    }
    
    ofxAnimatableFloat mask;
    T aux;
private:
    ofShader shader;
    MaskType type;
    float width;
    float height;
    float radius;
};