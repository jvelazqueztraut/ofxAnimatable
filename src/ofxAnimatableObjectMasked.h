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
class ofxAnimatableObjectMasked : public ofxAnimatableObject< ObjectMasked<T> >{
public:
    ofxAnimatableObjectMasked() : ofxAnimatableObject< ObjectMasked<T> >(){
        string shaderProgram =
        "#extension GL_ARB_texture_rectangle: enable\n\
		\n\
        uniform float width;\n\
        uniform float height;\n\
        uniform float HH;\n\
        uniform vec2 offset;\n\
        uniform vec2 limits;\n\
		uniform sampler2DRect tex;\n\
		\n\
		void main (void){\n\
        vec2 pos = vec2(gl_FragCoord.x,HH-gl_FragCoord.y) - offset;\n\
		vec4 color = texture2DRect(tex,pos);\n\
        vec2 bounds = vec2(gl_FragCoord.x,HH-gl_FragCoord.y) - limits;\n\
        if(bounds.x<0. || bounds.x>width || bounds.y<0. || bounds.y>height){\n\
            color = vec4(0.,0.,0.,0.);\n\
        }\n\
		gl_FragColor = color;\n\
		}";
        
		shader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
		shader.linkProgram();
    }
    
    ~ofxAnimatableObjectMasked(){};
    
    void update(float dt){      
        ofxAnimatableObject< ObjectMasked<T> >::update(dt);
        
        ObjectMasked<T>::mask.update(dt);
        
        if(N>0){
            for(int i=0;i<N;i++){
                aux[i].mask.update(dt);
            }
        }
        
        GLfloat m[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, m);
        reference = ofMatrix4x4(m);
    }
    
    void draw(){
        ofPushStyle();
        ofPushMatrix();
        ofFill();
        ofTranslate(ofxAnimatableObject< ObjectMasked<T> >::position.getCurrentPosition());
        ofRotateX(ofxAnimatableObject< ObjectMasked<T> >::rotation.getCurrentPosition().x);
        ofRotateY(ofxAnimatableObject< ObjectMasked<T> >::rotation.getCurrentPosition().y);
        ofRotateZ(ofxAnimatableObject< ObjectMasked<T> >::rotation.getCurrentPosition().z);
        if(ofxAnimatableObject< ObjectMasked<T> >::size.val()<0) ofScale(0.,0.,0.);
        else ofScale(ofxAnimatableObject< ObjectMasked<T> >::size.val(),ofxAnimatableObject< ObjectMasked<T> >::size.val(),ofxAnimatableObject< ObjectMasked<T> >::size.val());
        ofSetColor(ofxAnimatableObject< ObjectMasked<T> >::color.getCurrentColor());

        if(N>0){
            for(int i=(N-1);i>=0;i--){
                if(aux[i].isAllocated()){
                    if(aux[i].mask.val()==1. || ofGetMousePressed()){
                        aux[i].draw(0,0);
                    }
                    else if(aux[i].mask.val()){
                        updateFbo(aux[i].getTextureReference(),aux[i].mask.val(),aux[i].type,aux[i].orientation,aux[i].center);
                    }
                }
            }
        }
        if(ObjectMasked<T>::mask.val()==1. || ofGetMousePressed()){
            ObjectMasked<T>::draw(0,0);
        }
        else if(ObjectMasked<T>::mask.val()){
            updateFbo(ObjectMasked<T>::getTextureReference(),ObjectMasked<T>::mask.val(),ObjectMasked<T>::type,ObjectMasked<T>::orientation,ObjectMasked<T>::center);
        }
        ofPopMatrix();
        ofPopStyle();
    }
    
    void updateFbo(ofTexture& tex, float m, MaskType t, bool o, ofVec2f c){
        int width = ObjectMasked<T>::getWidth();
        int height = ObjectMasked<T>::getHeight();
        ofPushMatrix();
        ofTranslate(-ofxAnimatableObject< ObjectMasked<T> >::anchor.x*width,-ofxAnimatableObject< ObjectMasked<T> >::anchor.y*height);
        
        GLfloat mm[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, mm);
        ofMatrix4x4 mat(mm);
        ofVec3f offset = (ofPoint(0,0) * reference.getInverse()) * mat;
        
        if(o){
            if(t==RECTANGULAR_H || t==DIAGONAL || t==ARROW || t==RECTANGLES || t==HORIZONTAL){
                ofTranslate(width,0);
                ofScale(-1,1);
            }
            else if(t==RECTANGULAR_V || t==VERTICAL){
                ofTranslate(0,height);
                ofScale(1,-1);
            }
        }
        
        shader.begin();
        shader.setUniformTexture("tex",tex,0);
        shader.setUniform2f("offset",offset.x,offset.y);
        shader.setUniform2f("limits",offset.x,offset.y);
        shader.setUniform1f("width",width);
        shader.setUniform1f("height",height);
        shader.setUniform1f("HH",ofGetHeight());
        
        switch(t){
            case RECTANGULAR_H:
                ofRect(0,0,width*m,height);
                break;
            case RECTANGULAR_V:
                ofRect(0,0,width,height*m);
                break;
            case CIRCULAR:
                ofCircle(width*c.x,height*c.y,RADIUS(width,height,c.x,c.y)*m);
                break;
            case RADIAL:
                p.clear();
                if(o)
                    p.arc(ofPoint(0,0), RADIUS(width,height,c.x,c.y), RADIUS(width,height,c.x,c.y), 360 - (RADIAL_EPSILON + (360-RADIAL_EPSILON)*m), 360);
                else
                    p.arc(ofPoint(0,0), RADIUS(width,height,c.x,c.y), RADIUS(width,height,c.x,c.y), 0, RADIAL_EPSILON + (360-RADIAL_EPSILON)*m);
                p.draw(width*c.x,height*c.y);
                break;
            case DIAGONAL:                
                ofSetPolyMode(OF_POLY_WINDING_ODD);	// this is the normal mode
                ofBeginShape();
                    ofVertex(0,0);
                    ofVertex((width+height)*m,0);
                    ofVertex((width+height)*m-height,height);
                    ofVertex(0,height);
                ofEndShape();
                break;
            case ARROW:                
                ofBeginShape();
                    ofVertex(0,0);
                    ofVertex((width+height)*m-height*c.y,0);
                    ofVertex((width+height)*m,height*c.y);
                    ofVertex((width+height)*m-height*(1-c.y),height);
                    ofVertex(0,height);
                ofEndShape();
                break;
            case MULTI_ARROW:
                ofSetPolyMode(OF_POLY_WINDING_ODD);	// this is the normal mode
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
                break;
            case RECTANGLES:
                ofSetRectMode(OF_RECTMODE_CENTER);
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
                break;
            case HORIZONTAL:
                if(o){
                    shader.setUniform2f("offset",offset.x+(1.-m)*width,offset.y);
                }
                else{
                    shader.setUniform2f("offset",offset.x-(1.-m)*width,offset.y);
                }
                ofRect(0,0,width*m,height);
                break;
            case VERTICAL:
                if(o){
                    shader.setUniform2f("offset",offset.x,offset.y+(1.-m)*height);
                }
                else{
                    shader.setUniform2f("offset",offset.x,offset.y-(1.-m)*height);
                }
                ofRect(0,0,width,height*m);
                break;
        }
        shader.end();
        ofPopMatrix();
    }
    
    void setAnchorPercent(float xPct,float yPct){
		ofxAnimatableObject< ObjectMasked<T> >::setAnchorPercent(xPct,yPct);
        if(N>0){
            for(int i=0;i<N;i++){
                aux[i].setAnchorPercent(xPct,yPct);
            }
        }
	}
    
    bool isOrWillBeAnimating(){
        return (ObjectMasked<T>::mask.isOrWillBeAnimating() || ofxAnimatableObject<ofFbo>::isOrWillBeAnimating());
    }
    
    ObjectMasked<T> aux[N];
private:
    ofShader shader;
    ofPath p;
    ofMatrix4x4 reference;
};

