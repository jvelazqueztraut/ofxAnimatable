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

class ofxAnimatableImageMasked : public ofxAnimatableObject<ofFbo> {
public:
    ofxAnimatableImageMasked() : ofxAnimatableObject<ofFbo>(){
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

        type = DIAGONAL;
        
        hasAux = false;
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

        ofPushStyle();
        ofPushMatrix();
        ofFill();
        if(mask.val()==1.){
            ofFbo::begin();
                ofSetColor(255);
                tex.draw(0,0);
            ofFbo::end();
        }
        else{
            ofFbo::begin();
                ofClear(0,0);
                ofSetColor(255);
                if(hasAux){
                    aux.draw(0,0);
                }
                switch(type){
                    case RECTANGULAR:
                        shader.begin();
                        shader.setUniformTexture("tex",tex,1);
                            ofRect(0,0,width*mask.val(),height);
                        shader.end();
                        break;
                    case CIRCULAR:
                        shader.begin();
                        shader.setUniformTexture("tex",tex,1);
                            ofCircle(width*anchor.x,height*anchor.y,radius*mask.val());
                        shader.end();
                        break;
                    case DIAGONAL:
                        shader.begin();
                        shader.setUniformTexture("tex",tex,1);
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
                        shader.setUniformTexture("tex",tex,1);
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
                        shader.setUniformTexture("tex",tex,1);
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
                        shader.setUniformTexture("tex",tex,1);
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
                        tex.draw(0,0);
                        break;
                    case VERTICAL:
                        ofTranslate(0,height-mask.val()*height);
                        tex.draw(0,0);
                        break;
                }

            ofFbo::end();
        }
        ofPopMatrix();
        ofPopStyle();
    }

    bool isOrWillBeAnimating(){
        return (mask.isOrWillBeAnimating() || ofxAnimatableObject<ofFbo>::isOrWillBeAnimating());
    }

    void setMask(float m){mask.reset(m);}

    void setMaskType(MaskType t){
        type=t;
    }
    
    void loadAuxImage(string path){
        ofPixels image;
        ofLoadImage(image, path);
        
        aux.loadData(image);
        hasAux = true;
    }

    ofxAnimatableFloat mask;
private:
    ofTexture tex;
    ofShader shader;
    MaskType type;
    float width;
    float height;
    float radius;
    
    ofTexture aux;
    bool hasAux;
};
