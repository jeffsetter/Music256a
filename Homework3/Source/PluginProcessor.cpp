// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Simple JUCE sine wave synthesizer plug-in

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
BasicAudioPlugInAudioProcessor::BasicAudioPlugInAudioProcessor() : samplingRate(0.0)
{
    nChans = getTotalNumOutputChannels();
    audioBuffer = new float*[nChans];
}

BasicAudioPlugInAudioProcessor::~BasicAudioPlugInAudioProcessor()
{
    delete [] audioBuffer;
}

//==============================================================================
const String BasicAudioPlugInAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BasicAudioPlugInAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BasicAudioPlugInAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double BasicAudioPlugInAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BasicAudioPlugInAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BasicAudioPlugInAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BasicAudioPlugInAudioProcessor::setCurrentProgram (int index)
{
}

const String BasicAudioPlugInAudioProcessor::getProgramName (int index)
{
    return String();
}

void BasicAudioPlugInAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void BasicAudioPlugInAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    samplingRate = sampleRate;
	for (int i = 0; i < nVoices; i++) {
		for (int j = 0; j < nOvertones; j++) {
			sine[i][j].setSamplingRate(sampleRate);
			sine[i][j].setFrequency(1000*(j+1)); // default value for frequency
		}
		onOff[i] = 0;
		level[i] = 0;
		freq[i] = 0;
		envelope[i] = 0;
	}

	for (int j = 0; j < nOvertones; j++) {
		timbreLevels[j] = 0;
	}
	timbreLevels[0] = 1;
}

void BasicAudioPlugInAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BasicAudioPlugInAudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
{
    // Reject any bus arrangements that are not compatible with your plugin

    const int numChannels = preferredSet.size();

   #if JucePlugin_IsMidiEffect
    if (numChannels != 0)
        return false;
   #elif JucePlugin_IsSynth
    if (isInput || (numChannels != 1 && numChannels != 2))
        return false;
   #else
    if (numChannels != 1 && numChannels != 2)
        return false;

    if (! AudioProcessor::setPreferredBusArrangement (! isInput, bus, preferredSet))
        return false;
   #endif

    return AudioProcessor::setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif

void BasicAudioPlugInAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < nChans; ++channel)
    {
        audioBuffer[channel] = buffer.getWritePointer (channel);
    }
	
	MidiMessage m;
	int time;
	for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
    {
        if (m.isNoteOn())
        {
			double frequency = MidiMessage::getMidiNoteInHertz(m.getNoteNumber());

			// find the note in our array
			int index = -1;
			int freeIndex = -1;
			for (int i = 0; i < nVoices; ++i) {
				if (frequency == freq[i]) {
					index = i;
				} else if (freq[i] == 0) {
					freeIndex = i;
				}
			}
			if (index == -1) {
				index = freeIndex;
			}
			if (index == -1) { printf("no room for another voice\n");  break; }

			// set the note properties
			onOff[index] = true;
			level[index] = m.getVelocity();
			freq[index] = frequency;

			// produce the smoothed sine wave sum
			for (int i = 0; i < nOvertones; ++i) {
				sineSmooth[index][i].setSmooth(0);
				sineSmooth[index][i].tick(frequency*(i + 1));
				sine[index][i].setFrequency(frequency*(i + 1));
				sineSmooth[index][i].setSmooth(0.999);
				levelSmooth[index].setSmooth(0.999);
			}

        }
        else if (m.isNoteOff())
        {
			double frequency = MidiMessage::getMidiNoteInHertz(m.getNoteNumber());

			// find the note in our array
			int index = -1;
			for (int i = 0; i < nVoices; ++i) {
				if (frequency == freq[i]) {
					index = i;
				}
			}
			if (index == -1) { printf("could not find note to turn off\n");  break; }

			// turn off note
			onOff[index] = false;
			level[index] = 0;

        }
        else if (m.isAftertouch())
        {
        }
        else if (m.isPitchWheel())
        {
        }
	}

	
	double sumTimbre = 0.001;
	for (int j = 0; j < nOvertones; j++) {
		sumTimbre += timbreLevels[j];
	}

    // computing one block
	for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
		float currentSample = 0;

		for (int idx = 0; idx < nVoices; idx++) {
			// only compute block if note is on!
			if (envelope[idx] != 0 || onOff) {
				envelope[idx] = levelSmooth[idx].tick(level[idx]); // here we use a smoother as an envelope generator

				for (int ovt = 0; ovt < nOvertones; ovt++) {
					currentSample += (float)(sine[idx][ovt].tick() * envelope[idx] * timbreLevels[ovt] / (sumTimbre*nVoices*maxVelocity));
				}

				// if tail off is disabled, we end the note right away, otherwise, we wait for envelope
				// to reach a safe value
				if (!onOff[idx] && (envelope[idx] < 0.001)) {
					envelope[idx] = 0;
					freq[idx] = 0;
				}
			}
		}
		audioBuffer[0][sample] = currentSample;

		for (int channel = 1; channel < nChans; ++channel)
		{
			audioBuffer[channel][sample] = audioBuffer[0][sample];
		}
	}
}

//==============================================================================
bool BasicAudioPlugInAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BasicAudioPlugInAudioProcessor::createEditor()
{
    return new BasicAudioPlugInAudioProcessorEditor (*this);
}

//==============================================================================
void BasicAudioPlugInAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BasicAudioPlugInAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BasicAudioPlugInAudioProcessor();
}
