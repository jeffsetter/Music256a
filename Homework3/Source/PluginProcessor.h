// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Simple JUCE sine wave synthesizer plug-in

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Sine.h"
#include "Smooth.h"

#define nOvertones 6
#define nVoices 6

//==============================================================================
/**
*/
class BasicAudioPlugInAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    BasicAudioPlugInAudioProcessor();
    ~BasicAudioPlugInAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	
    Sine sine[nVoices][nOvertones];
	Smooth sineSmooth[nVoices][nOvertones];
	
    bool onOff[nVoices];
	float level[nVoices];
	Smooth levelSmooth[nVoices];
	double freq[nVoices], envelope[nVoices];
	
	double timbreLevels[nOvertones];
    int samplingRate;
    
private:
    float** audioBuffer;
    int nChans;
	const int maxVelocity = 127;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicAudioPlugInAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
