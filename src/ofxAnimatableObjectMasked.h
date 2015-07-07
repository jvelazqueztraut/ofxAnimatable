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
    RECTANGULAR_H=0,
    RECTANGULAR_V,
    CIRCULAR,
    RADIAL,
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

#define RADIAL_EPSILON 1

#define RADIUS(w,h,x,y) (0.5 * sqrt( pow(w+w*2*abs(x-0.5),2) + pow(h+h*2*abs(y-0.5),2)))

template <class T>
class ObjectMasked : public T{
public:
    ObjectMasked() : T(){
        mask.reset(1.);
        type = RECTANGULAR_H;
        orientation = false;
        center.set(0.5,0.5);
    };
    ~ObjectMasked(){};
    
    ofTexture& getTextureReference(){
        return (T::getTextureReference());
    }
    
    void setMask(float m){mask.reset(m);}
    
    void setMaskType(MaskType t){type=t;}
    
    void setMaskOrientation(bool o){orientation=o;}
    
    void setMaskCenter(ofVec2f c){center.set(c);}
    
    ofxAnimatableFloat mask;
    MaskType type;
    bool orientation;
    ofVec2f center;
};

template <>
class ObjectMasked<ofTexture> : public ofTexture{
public:
    ObjectMasked<ofTexture>() : ofTexture(){
        mask.reset(1.);
        type = RECTANGULAR_H;
        orientation = false;
        center.set(0.5,0.5);
    };
    ~ObjectMasked<ofTexture>(){};
    
    ofTexture& getTextureReference(){
        return ((ofTexture&) *this);
    }
    
    void setMask(float m){mask.reset(m);}
    
    void setMaskType(MaskType t){type=t;}
    
    void setMaskOrientation(bool o){orientation=o;}
    
    void setMaskCenter(ofVec2f c){center.set(c);}
    
    ofxAnimatableFloat mask;
    MaskType type;
    bool orientation;
    ofVec2f center;
};

template <class T, int N=0>
class ofxAnimatableObjectMasked : public ObjectMasked<T>, public ofxAnimatableObject<ofFbo>{
public:
    ofxAnimatableObjectMasked() : ofxAnimatableObject<ofFbo>() , ObjectMasked<T>(){
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
                    
        width = height = 0;
    }
    
    ~ofxAnimatableObjectMasked(){};
    
    void allocate(){
        width = ObjectMasked<T>::getWidth();
        height = ObjectMasked<T>::getHeight();
            
        ofxAnimatableObject<ofFbo>::allocate(width,height,GL_RGBA);
    }
    
    void update(float dt){
        if(!ofxAnimatableObject<ofFbo>::isAllocated()){
            allocate();
        }
        
        ofxAnimatableObject<ofFbo>::update(dt);
        
        ObjectMasked<T>::mask.update(dt);
        
        if(N>0){
            for(int i=0;i<N;i++){
                aux[i].mask.update(dt);
            }
        }
        
        ofPushStyle();
        ofPushMatrix();
        ofFill();
        ofxAnimatableObject<ofFbo>::begin();
        if(N==0){
            glBlendFuncSeparate(GL_ONE, GL_SRC_COLOR, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        }
        ofClear(0,0);
        ofSetColor(255);
        
        if(N>0){
            for(int i=(N-1);i>=0;i--){
                if(aux[i].isAllocated()){
                    if(aux[i].mask.val()){
                        updateFbo(aux[i].getTextureReference(),aux[i].mask.val(),aux[i].type,aux[i].orientation,aux[i].center,ObjectMasked<T>::mask.val());
                    }
                }
            }
        }
        
        if(ObjectMasked<T>::mask.val()==1.){
            ObjectMasked<T>::draw(0,0);
        }
        else if(ObjectMasked<T>::mask.val()){
            updateFbo(ObjectMasked<T>::getTextureReference(),ObjectMasked<T>::mask.val(),ObjectMasked<T>::type,ObjectMasked<T>::orientation,ObjectMasked<T>::center);
        }
        
        ofxAnimatableObject<ofFbo>::end();
        ofPopMatrix();
        ofPopStyle();
    }
    
    void updateFbo(ofTexture& tex, float m, MaskType t, bool o, ofVec2f c,float mm=0.){
        switch(t){
            case RECTANGULAR_H:
                shader.begin();
                shader.setUniformTexture("tex",tex,0);
                if(o){
                    ofTranslate(width,0);
                    ofScale(-1,1);
                }
                ofRect(0,0,width*m,height);
                shader.end();
                break;
            case RECTANGULAR_V:
                shader.begin();
                shader.setUniformTexture("tex",tex,0);
                if(o){
                    ofTranslate(0,height);
                    ofScale(1,-1);
                }
                ofRect(0,0,width,height*m);
                shader.end();
                break;
            case CIRCULAR:
                shader.begin();
                shader.setUniformTexture("tex",tex,0);
                ofCircle(width*c.x,height*c.y,RADIUS(width,height,c.x,c.y)*m);
                shader.end();
                break;
            case RADIAL:
                shader.begin();
                shader.setUniformTexture("tex",tex,0);
                p.clear();
                if(o)
                    p.arc(ofPoint(0,0), RADIUS(width,height,c.x,c.y), RADIUS(width,height,c.x,c.y), 360 - (RADIAL_EPSILON + (360-RADIAL_EPSILON)*m), 360);
                else
                    p.arc(ofPoint(0,0), RADIUS(width,height,c.x,c.y), RADIUS(width,height,c.x,c.y), 0, RADIAL_EPSILON + (360-RADIAL_EPSILON)*m);
                p.draw(width*c.x,height*c.y);
                shader.end();
                break;
            case DIAGONAL:
                shader.begin();
                shader.setUniformTexture("tex",tex,0);
                ofSetPolyMode(OF_POLY_WINDING_ODD);	// this is the normal mode
                if(o){
                    ofTranslate(width,0);
                    ofScale(-1,1);
                }
                ofBeginShape();
                    ofVertex(0,0);
                    ofVertex((width+height)*m,0);
                    ofVertex((width+height)*m-height,height);
                    ofVertex(0,height);
                ofEndShape();
                shader.end();
                break;
            case ARROW:
                shader.begin();
                shader.setUniformTexture("tex",tex,0);
                ofSetPolyMode(OF_POLY_WINDING_ODD);	// this is the normal mode
                if(o){
                    ofTranslate(width,0);
                    ofScale(-1,1);
                }
                ofBeginShape();
                    ofVertex(0,0);
                    ofVertex((width+height)*m-height*c.y,0);
                    ofVertex((width+height)*m,height*c.y);
                    ofVertex((width+height)*m-height*(1-c.y),height);
                    ofVertex(0,height);
                    if(mm){
                        ofVertex((width+height)*mm-height*(1-c.y),height);
                        ofVertex((width+height)*mm,height*c.y);
                        ofVertex((width+height)*mm-height*c.y,0);
                    }
                ofEndShape();
                shader.end();
                break;
            case MULTI_ARROW:
                shader.begin();
                shader.setUniformTexture("tex",tex,0);
                ofSetPolyMode(OF_POLY_WINDING_ODD);	// this is the normal mode
                if(o){
                    ofTranslate(width,0);
                    ofScale(-1,1);
                }
                ofBeginShape();
                    ofVertex(0,0);
                    ofVertex((width+height*1.75)*m-height*1.75,0);
                    ofVertex((width+height*1.75)*m-height*1.25,height*0.5);
                    ofVertex((width+height*1.75)*m-height*1.75,height);
                    ofVertex(0,height);
                ofEndShape();
                ofBeginShape();
                    ofVertex((width+height*1.75)*m-height,0);
                    ofVertex((width+height*1.75)*m-height*0.5,0);
                    ofVertex((width+height*1.75)*m,height*0.5);
                    ofVertex((width+height*1.75)*m-height*0.5,height);
                    ofVertex((width+height*1.75)*m-height,height);
                    ofVertex((width+height*1.75)*m-height*0.5,height*0.5);
                ofEndShape();
                shader.end();
                break;
            case RECTANGLES:
                shader.begin();
                shader.setUniformTexture("tex",tex,0);
                ofSetRectMode(OF_RECTMODE_CENTER);
                if(o){
                    ofTranslate(width,0);
                    ofScale(-1,1);
                }
                for(int x=0;x<RECTANGLES_X;x++){
                    for(int y=0;y<RECTANGLES_Y;y++){
                        if(m>(x*RECTANGLES_Y+y)*RECTANGLES_DELAY){
                            if((m-(x*RECTANGLES_Y+y)*RECTANGLES_DELAY)/RECTANGLES_TIME<1.){
                                ofRect((x*2+1)*width/(RECTANGLES_X*2),(y*2+1)*height/(RECTANGLES_Y*2),width/(RECTANGLES_X)*(m-(x*RECTANGLES_Y+y)*RECTANGLES_DELAY)/RECTANGLES_TIME,height/(RECTANGLES_Y)*(m-(x*RECTANGLES_Y+y)*RECTANGLES_DELAY)/RECTANGLES_TIME);
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
                if(o){
                    ofTranslate(width-m*width,0);
                }
                else{
                    ofTranslate(m*width-width,0);
                }
                tex.draw(0,0);
                break;
            case VERTICAL:
                if(o){
                    ofTranslate(0,height-m*height);
                }
                else{
                    ofTranslate(0,m*height-height);
                }
                tex.draw(0,0);
                break;
        }
    }
    
    void draw(){
        ofxAnimatableObject<ofFbo>::draw();
    }
    
    float getWidth(){
        return ofxAnimatableObject<ofFbo>::getWidth();
    }
    
    float getHeight(){
        return ofxAnimatableObject<ofFbo>::getHeight();
    }
    
    bool isAllocated(){
        return ofxAnimatableObject<ofFbo>::isAllocated();
    }
    
    void setAnchorPercent(float xPct,float yPct){
		ofxAnimatableObject<ofFbo>::setAnchorPercent(xPct,yPct);
	}
    
    void setPosition(ofPoint p){ofxAnimatableObject<ofFbo>::setPosition(p);}
    void setPosition(float x, float y,float z=0.){ofxAnimatableObject<ofFbo>::setPosition(ofPoint(x,y,z));}
    
    void setSize(float s){ofxAnimatableObject<ofFbo>::setSize(s);}
    
    void setColor(ofColor c){ofxAnimatableObject<ofFbo>::setColor(c);}
    void setColor(int r, int g, int b, int a=255){ofxAnimatableObject<ofFbo>::setColor(ofColor(r,g,b,a));}
    void setColor(int b, int a){ofxAnimatableObject<ofFbo>::setColor(ofColor(b,a));}
    void setColor(int b){ofxAnimatableObject<ofFbo>::setColor(ofColor(b));}
    
    void setRotation(ofPoint r){ofxAnimatableObject<ofFbo>::setRotation(r);}
    void setRotation(float x, float y=0., float z=0.){ofxAnimatableObject<ofFbo>::setRotation(ofPoint(x,y,z));}
    
    bool isOrWillBeAnimating(){
        return (ObjectMasked<T>::mask.isOrWillBeAnimating() || ofxAnimatableObject<ofFbo>::isOrWillBeAnimating());
    }
    
    ObjectMasked<T> aux[N+1];
private:
    ofShader shader;
    ofPath p;
    float width;
    float height;
};

