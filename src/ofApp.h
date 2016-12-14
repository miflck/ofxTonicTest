#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "MySynth.h"
#include "Background.h"
#include "ForegroundSound.hpp"
#include "ofxReverb.h"





class ofApp : public ofBaseApp{

    

    
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    
    void audioOut(float * output, int bufferSize, int nChannels);

    ofSoundStream soundStream;
    MySynth boo;
    MySynth boo2;
    ofSoundMixer mixer;

    vector< MySynth * > synths;
    
    vector< ForegroundSound * > foregrounds;


    Background bk;
    
    //Reverb
    float 	volume;

    ofxReverb	reverb;
    float		wetness,verbRoomSize,verbDamp,verbWidth;
    float		reverbOUT;
    bool bReverb = false;

    
};
