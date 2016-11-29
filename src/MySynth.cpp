//
//  MySynth.cpp
//  example_Basic
//
//  Created by Ant Dickinson on 16/11/2016.
//
//


#include "MySynth.h"


void MySynth::setSampleRate(int rate){
    sampleRate = rate;
}




void MySynth::setup(float _p){
    volume	= 0.79f;


    
    // create a new oscillator which we'll use for the actual audio signal
    SineWave tone = SineWave();
    
    // create a sine wave we'll use for some vibrato
    SineWave vibratoOsc = SineWave();
    vibratoOsc.freq(1);
    
    // you can use the regular arithmatic operators on Generators and their subclasses (SineWave extends Generator)
    float basePitch = _p;
    Generator frequency = basePitch + (vibratoOsc * basePitch * 0.01);
    
    // plug that frequency generator into the frequency slot of the main audio-producing sine wave
    tone.freq(frequency);
    
    // let's also create a tremelo effect
    SineWave tremeloSine = SineWave().freq(0.1);
    
    // set the synth's final output generator
    synth.setOutputGen( tone * tremeloSine );
    
    
}

void MySynth::audioRequested (float * output, int bufferSize, int nChannels){
    synth.fillBufferOfFloats(output, bufferSize, nChannels);
}




