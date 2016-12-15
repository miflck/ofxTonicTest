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
/*int z = 0;
int fgnotes[] = {0,0,0,0,0,0,0};
int fgbeats[] = {0,1,1,1,1,1,1,1,1,1,1};
int  scale[] = {220, 880 ,261,329,329,392,392,440,220};*/


void ForegroundSound::setSampleRate(int rate){
    sampleRate = rate;
}



void ForegroundSound::setup(){
    volume = 1;
    z = 0;
    
    SineWave            tone = SineWave();
    Generator           panner = MonoToStereoPanner();
    ControlGenerator    noteFreq =  synth.addParameter("fg") ;
    ControlGenerator    panning =  synth.addParameter("panning") ;
    ControlGenerator    volume =  synth.addParameter("volume") ;
    ControlGenerator    fgcut =  synth.addParameter("fgcut") ;
    
    tone.freq(noteFreq);
    
    panner = MonoToStereoPanner().pan(panning).input(( (tone * ADSR(0.001,0.05,0,00).trigger(fgtrig)) * volume) * fgcut);
    synth.setOutputGen(panner);
    
    
    int notes[] = {0,0,0,0,0,0,0};
    int beats[] = {0,1,1,1,1,1,1,1,1,1,1};
    int fgscale[] = {220, 880 ,261,329,329,392,392,440,220};
    
    /*fgnotes=notes;
    fgbeats=beats;
    scale=fgscale;*/

    
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
    // that remap of position seems a bit overcomplicated, but that gives me the possibility to
    // set or move the both screen planes in virtual room later. these are not yet definitively set....
    scaledZpos=ofMap(position.z,0,maxZ,0,1,true);
    
    /*-> if object reaches second screen, we need to remove it from the manager..
    // that replaces your:
    if ( user1Zpos == 1)               {
        user1Zpos = 0;
    }*/
   // cout<<position.z<<" "<<maxZ<<" "<<scaledZpos<<"num s"<<numSyllables<<" "<<fgnotes[1]<<endl;
    
    if (scaledZpos == maxZ)bRemove=true;

    //synth.setParameter("volume", scaledZpos);
    synth.setParameter("volume", 1);

    synth.setParameter("fgcut", 0.4);
    synth.setParameter("panning", userPan);
    
    // do we have to do that in every update? is that something we can set in setNumSyllables()?
    // or is it in fact vowels and we do that in the parseVowels()?
    // uncomment for version 2
    
     fgnotes[0] = 0;
    fgnotes[1] =  scale[sylcont1];
    fgnotes[2] =  scale[sylcont2];
    fgnotes[3] =  scale[sylcont3];
    fgnotes[4] =  scale[sylcont4];
    fgnotes[5] =  scale[sylcont5];
    fgnotes[6] =  scale[sylcont6];
    
    
    if( ofGetFrameNum() % timeSubDiv == 0) //ofGetElapsedTimeMillis()
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

void ForegroundSound::setTimingSubDiv(int _timeSubDiv) {
    timeSubDiv = _timeSubDiv;
}


void ForegroundSound::parseVowels(string _vowels){
    vowelsString=_vowels;
    vowelsCount=_vowels.length();
    
    //-> Not sure if thats really what you want.
    /* i belive you want to say: if fist vowel is an a, then the first tone should be X
     as far as i understand your code, that would be made here:
     fgnotes[1] =  scale[sylcont1];
     so the scale array is like the note?
     See below, how we could probably do that and remove this stuff out of update.
     
     */
/*
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
    }*/
    
    // VERSION 2 like in the comment above
    
    int  index;
    for (auto s:vowelsString){
        char c = s;
        switch (c) {
                
            case 'a':
                // do the a stuff
                fgnotes[index] =  scale[0]; // scale[0] is just a suggestion to keep up the order.if i understand your intention right.
                break;
            case 'e':
                fgnotes[index] =  scale[1];
                break;
            case 'i':
                fgnotes[index] =  scale[2];
                break;
            case 'o':
                fgnotes[index] =  scale[3];
                break;
            case 'u':
                fgnotes[index] =  scale[4];
                break;
                
            default:
                break;
        index++;
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