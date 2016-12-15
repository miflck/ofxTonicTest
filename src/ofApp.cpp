#include "ofApp.h"

int debugZ=20;


//--------------------------------------------------------------
void ofApp::setup(){

    int bufferSize		= 2048;
    int sampleRate 		= 44100;
    
    soundStream.setup(2, 0, 44100, bufferSize, 4);
    soundStream.setOutput(this);
    
    bk.setup();
    mixer.addInputFrom(&bk);
    
    volume				= 0.81f;
    wetness				= 0.2f;
    verbRoomSize		= 0.99f;
    verbDamp			= 0.2f;
    verbWidth			= 0.99f;

    bReverb=!bReverb;
}

//--------------------------------------------------------------
void ofApp::update(){
    bk.update();
    
    //Check if we have to remove a foreground, else update it
    for (int i=0;i<foregrounds.size();i++){
        if(foregrounds[i]->getBRemove()){
            delete (foregrounds[i]);
            foregrounds.erase(foregrounds.begin()+i);
        }else{
            foregrounds[i]->update();
        }
    }

    
    /*
    for(auto foreground:foregrounds){
        foreground->update();
    }*/
    
  }

//--------------------------------------------------------------
void ofApp::draw(){
   
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
//    if(key=='r'){
//        bReverb=!bReverb;
//    }
    
    if(key=='R'){
    mixer.removeInputFrom(synths[synths.size()-1]);
    
    delete (synths[synths.size()-1]);
    synths.pop_back();
        cout<<synths.size()<<endl;
    }
    
    if(key=='a'){
        MySynth *s = new MySynth();
        s->setup(55);        // ANT frequency here should be from scale
        mixer.addInputFrom(s);
        synths.push_back(s);
        cout<<synths.size()<<endl;

    }
    
    
 if(key=='f'){
        ForegroundSound *fg = new ForegroundSound();
        fg->setup();
         //hello
        fg->setNumSyllables(2);
        fg->setVowels("eo");
        fg->setPosition(ofVec3f(0,0,0));
        fg->setTimingSubDiv(10 + int(ofRandom(20)));
        mixer.addInputFrom(fg);
        foregrounds.push_back(fg);
        cout<<"Number of foreground sounds: "<<foregrounds.size()<<endl;
    }
    
    if(key=='+'){
        debugZ++;
        foregrounds[0]->setPosition(ofVec3f(0,0,debugZ));
        
    }
    
    
    
    if(key=='p'){
        ForegroundSound *fg = new ForegroundSound();
        fg->setup();
        //pattern
        fg->setTimingSubDiv(10 + int(ofRandom(20)));
        fg->setNumSyllables(4);
        fg->setVowels("aeou");
        fg->setPosition(ofVec3f(0,0,34));
        mixer.addInputFrom(fg);
        foregrounds.push_back(fg);
        cout<<"Number of foreground sounds: "<<foregrounds.size()<<endl;
    }
    
    if(key=='o'){
        ForegroundSound *fg = new ForegroundSound();
        fg->setup();
        //pattern
        fg->setTimingSubDiv(10 + int(ofRandom(20)));
        fg->setNumSyllables(6);
        fg->setVowels("aeouyu");
        fg->setPosition(ofVec3f(0,0,34));
        mixer.addInputFrom(fg);
        foregrounds.push_back(fg);
        cout<<"Number of foreground sounds: "<<foregrounds.size()<<endl;
    }
    
    
    
    if(key=='P'){
        ForegroundSound *fg = new ForegroundSound();
        fg->setup();
        //retart
        fg->setTimingSubDiv(10 + int(ofRandom(20)));
        fg->setNumSyllables(3);
        fg->setVowels("eae");
        fg->setPosition(ofVec3f(0,0,34));
        mixer.addInputFrom(fg);
        foregrounds.push_back(fg);
        cout<<"Number of foreground sounds: "<<foregrounds.size()<<endl;
    }
    
    
    
    if(key=='w'){       
        bk.setNumWords(bk.getNumWords()+10);
    }


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    
    
    float pan = 0.5f;
    float leftScale = 1 - pan;
    float rightScale = pan;
    
    
    reverb.setroomsize(verbRoomSize);
    reverb.setdamp(verbDamp);
    reverb.setwidth(verbWidth);
    reverb.setwet(wetness);
    reverb.setdry(1.0f - wetness);

    
   mixer.audioRequested(output, bufferSize, nChannels);
    
    
    
    for (int i = 0; i < bufferSize; i++){
        float left =output[i*nChannels]* volume * leftScale;
        float right =output[i*nChannels+1]* volume * leftScale;
        
        if(bReverb) {
            reverb.processreplace(&left, &right, &output[i*nChannels], &output[i*nChannels + 1], 1, 1);
        }else{
            output[i*nChannels + 0] = left;
            output[i*nChannels + 1] = right ;
            
        }
    }

}

