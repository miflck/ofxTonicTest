//
//  ForegroundSound.cpp
//  customSynthClass
//
//  Created by Flückiger Michael on 28.11.16.
//
//

#include "ForegroundSound.hpp"


// not sure what z is. maybe better naming?
// z should be something that relates to zPosition. here it relates to time and number of vowels
int z = 0;
int fgnotes[] = {0,0,0,0,0,0,0};
int fgbeats[] = {0,1,1,1,1,1,1,1,1,1,1};
int  scale[] = {220, 880 ,261,329,329,392,392,440,220};



void ForegroundSound::setSampleRate(int rate){
    sampleRate = rate;
}

ForegroundSound::ForegroundSound(){
}

void ForegroundSound::setup(){
    volumeForMixer	= 1;
    
    
    SineWave            tone = SineWave();
    Generator           panner = MonoToStereoPanner();
    ControlGenerator    noteFreq =  synth.addParameter("fg") ;
    ControlGenerator    panning =  synth.addParameter("panning") ;
    ControlGenerator   volume =  synth.addParameter("volume") ;
    ControlGenerator    fgcut =  synth.addParameter("fgcut") ;
    
    tone.freq(noteFreq);
    
    Generator           reveroo = Reverb();
    reveroo = Reverb().input(panner).decayTime(10).roomSize(20).wetLevel(0.5);
    panner = MonoToStereoPanner().pan(panning).input(( (tone * ADSR(0.001,0.05,0,00).trigger(fgtrig)) * volume) * fgcut);
    synth.setOutputGen(reveroo + panner);

    
    sylcont1=int(ofRandom(6));
    sylcont2=int(ofRandom(6));
    sylcont3=int(ofRandom(6));
    sylcont4=int(ofRandom(6));
    sylcont5=int(ofRandom(6));
    sylcont6=int(ofRandom(6));
    
    userPan=0;

    bRemove=false;

     maxZ=300;
    
    position.set(0,0,0);

    
    
}

void ForegroundSound::update(){
    
    //scale zpos between background and screen2-zpos
    scaledZpos=ofMap(position.z,0,maxZ,0,1,true);
    
    //-> if object reaches second screen, we need to remove it from the manager..
    cout<<position.z<<" "<<maxZ<<" "<<scaledZpos<<"num s"<<numSyllables<<" "<<fgnotes[1]<<endl;
    if ( scaledZpos == maxZ)bRemove=true;

    
    synth.setParameter("volume", scaledZpos);
    synth.setParameter("fgcut", 0.4);
    synth.setParameter("panning", userPan);
    
    // do we have to do that in every update? is that something we can set in setNumSyllables()?
    // or is it in fact vowels and we do that in the parseVowels()?
    fgnotes[0] = 0;
    fgnotes[1] =  scale[sylcont1];
    fgnotes[2] =  scale[sylcont2];
    fgnotes[3] =  scale[sylcont3];
    fgnotes[4] =  scale[sylcont4];
    fgnotes[5] =  scale[sylcont5];
    fgnotes[6] =  scale[sylcont6];
    
    
    
    
    if ( ofGetFrameNum() % 14 == 0)
    {
        z ++;
        if(z > numSyllables)
        {
            z = 0;
        }
        if (fgbeats[z] == 1){
            synth.setParameter("fg", fgnotes[z]);
           fgtrig.trigger();
        }
    }
   }

void ForegroundSound::setVowels(string _vowels){
  //  vowelsString=_vowels;
// vowelsCount=_vowels.length();
    parseVowels(_vowels);
}

void ForegroundSound::setNumSyllables(int _num){
    numSyllables=_num;

}

void ForegroundSound::setPosition(ofVec3f _position){
    position.set(_position);
    cout<<"My Position "<<position;
}


void ForegroundSound::parseVowels(string _vowels){
    vowelsString=_vowels;
    vowelsCount=_vowels.length();
    
    for (auto s:vowelsString){
        char c = s;
        switch (c) {
           
            case 'a':
                // do the a stuff
                break;
            case 'e':
                // do stuff
                break;
            case 'i':
                // do stuff
                break;
            case 'o':
                // do stuff
                break;
            case 'u':
                // do stuff
                break;
                
            default:
                break;
        }
    }
    
}


void ForegroundSound::audioRequested (float * output, int bufferSize, int nChannels){
    synth.fillBufferOfFloats(output, bufferSize, nChannels);
}


bool ForegroundSound::getBRemove(){
    return bRemove;
}

void ForegroundSound::setMaxZ(int _maxZ){
    maxZ=_maxZ;
}