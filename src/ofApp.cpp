#include "ofApp.h"

int debugZ=20;


//--------------------------------------------------------------
void ofApp::setup(){

    int bufferSize		= 256;
    int sampleRate 		= 44100;
    
    soundStream.setup(2, 0, 44100, 256, 4);
    soundStream.setOutput(this);
    
    bk.setup();
    mixer.addInputFrom(&bk);

    
}

//--------------------------------------------------------------
void ofApp::update(){
    bk.update();
    for(auto foreground:foregrounds){
        foreground->update();
    }
    
  }

//--------------------------------------------------------------
void ofApp::draw(){
   
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='r'){
    mixer.removeInputFrom(synths[synths.size()-1]);
    
    delete (synths[synths.size()-1]);
    synths.pop_back();
        cout<<synths.size()<<endl;
    }
    
    if(key=='a'){
        MySynth *s = new MySynth();
        s->setup(ofRandom(100,900));
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
        mixer.addInputFrom(fg);
        foregrounds.push_back(fg);
        cout<<"Number of foreground sounds: "<<foregrounds.size()<<endl;
     
    }
    
    if(key=='+'){
        debugZ++;
        foregrounds[0]->setPosition(ofVec3f(0,0,debugZ));
        
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
    mixer.audioRequested(output, bufferSize, nChannels);

}

