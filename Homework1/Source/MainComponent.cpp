// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Modified by: Jeff Setter (setterDOTstanfordDOTedu)
// Description: Simple JUCE sine wave synthesizer

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#define NUM_FREQ 4

#include "../JuceLibraryCode/JuceHeader.h"
#include "Sine.h"

class MainContentComponent :
    public AudioAppComponent,
    private Slider::Listener,
    private ToggleButton::Listener
{
public:
    MainContentComponent() : onOff (0), samplingRate(0.0)
    {
		// iterate left and right sides
		for (int j = 0; j < 2; ++j) { 

			// iterate over each freq/gain slider pair
			for (int i = 0; i < NUM_FREQ; ++i) {

				// define index variable
				int idx = j*NUM_FREQ + i;

				// configuring frequency slider and adding it to the main window
				addAndMakeVisible(frequencySlider[idx]);
				frequencySlider[idx].setRange(50.0, 5000.0);
				frequencySlider[idx].setSkewFactorFromMidPoint(500.0);
				frequencySlider[idx].setValue(1000); // will also set the default frequency of the sine osc
				frequencySlider[idx].addListener(this);

				// configuring frequency label box and adding it to the main window
				addAndMakeVisible(frequencyLabel[idx]);
				frequencyLabel[idx].setText("Frequency", dontSendNotification);
				frequencyLabel[idx].attachToComponent(&frequencySlider[idx], true);

				// configuring gain slider and adding it to the main window
				addAndMakeVisible(gainSlider[idx]);
				gainSlider[idx].setRange(0.0, 1.0);
				gainSlider[idx].setValue(0.5); // will alsi set the default gain of the sine osc
				gainSlider[idx].addListener(this);

				// configuring gain label and adding it to the main window
				addAndMakeVisible(gainLabel);
				gainLabel[idx].setText("Gain", dontSendNotification);
				gainLabel[idx].attachToComponent(&gainSlider[idx], true);

			}
		}

		// configuring on/off button and adding it to the main window
		addAndMakeVisible(onOffButton);
		onOffButton.addListener(this);

		// configuring on/off label and adding it to the main window
		addAndMakeVisible(onOffLabel);
		onOffLabel.setText("On/Off", dontSendNotification);
		onOffLabel.attachToComponent(&onOffButton, true);

		// configuring balance slider and adding it to the main window
		addAndMakeVisible(balanceSlider);
		balanceSlider.setRange(0.0, 1.0);
		balanceSlider.setValue(0.5);
		balanceSlider.addListener(this);

		// configuring balance label and adding it to the main window
		addAndMakeVisible(balanceLabel);
		balanceLabel.setText("Balance", dontSendNotification);
		balanceLabel.attachToComponent(&balanceSlider, true);
        
        setSize(1000, 40+60*NUM_FREQ);
        nChans = 1;
        setAudioChannels (0, nChans); // no inputs, one output
    }
    
    ~MainContentComponent()
    {
        shutdownAudio();
    }
    
    void resized() override
    {
        // placing the UI elements in the main window
        // getWidth has to be used in case the window is resized by the user
        const int sliderLeft = 80;
		const int halfWidth = getWidth() / 2;
		const int sliderWidth = halfWidth - sliderLeft - 20;

		for (int idx = 0; idx < NUM_FREQ; ++idx) {
			// place the left sliders
			frequencySlider[idx].setBounds(sliderLeft, 10 + 60*idx, sliderWidth, 20);
			gainSlider[idx].setBounds(sliderLeft, 40 + 60*idx, sliderWidth, 20);

			// place the right sliders
			int r_idx = idx + NUM_FREQ;
			frequencySlider[r_idx].setBounds(halfWidth + sliderLeft, 10 + 60 * idx, sliderWidth, 20);
			gainSlider[r_idx].setBounds(halfWidth + sliderLeft, 40 + 60 * idx, sliderWidth, 20);
		}

		// add the on/off button and balance slider
		onOffButton.setBounds(sliderLeft, 10 + 60*NUM_FREQ, sliderLeft, 20);
		balanceSlider.setBounds(40 + 2*sliderLeft, 10 + 60 * NUM_FREQ, 2*(halfWidth - 2*sliderLeft - 40) - sliderLeft, 20);

    }
    
    void sliderValueChanged (Slider* slider) override
    {
		if (samplingRate > 0.0) {
			// iterate through all of the sliders
			for (int idx = 0; idx < NUM_FREQ * 2; ++idx) {
				if (slider == &frequencySlider[idx]) {
					sine[idx].setFrequency(frequencySlider[idx].getValue());
				}
				else if (slider == &gainSlider[idx]) {
					gain[idx] = gainSlider[idx].getValue();
				}
				else if (slider == &balanceSlider) {
					balance = balanceSlider.getValue();
				}
			}
		}
    }
    
    void buttonClicked (Button* button) override
    {
        // turns audio on or off
        if(button == &onOffButton && onOffButton.getToggleState()){
            onOff = 1;
        }
        else{
            onOff = 0;
        }
    }
    
    void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) override
    {
        samplingRate = sampleRate;
		for (int i = 0; i < NUM_FREQ * 2; ++i) {
			sine[i].setSamplingRate(sampleRate);
		}
    }
    
    void releaseResources() override
    {
    }
    
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        // getting the audio output buffer to be filled
        float* const buffer = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
        
        // computing one block
        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
			if (onOff == 1) {
				float sum = 0;

				// add the left frequencies
				for (int i = 0; i < NUM_FREQ; ++i) {
					sum += sine[i].tick() * gain[i] / NUM_FREQ * (1-balance);
				}
				// add the right frequencies
				for (int i = NUM_FREQ; i < NUM_FREQ*2; ++i) {
					sum += sine[i].tick() * gain[i] / NUM_FREQ * balance;
				}

				buffer[sample] = sum;
			}
            else buffer[sample] = 0.0;
        }
    }
    
    
private:
    // UI Elements
    Slider frequencySlider[NUM_FREQ*2];
    Slider gainSlider[NUM_FREQ*2];
	Slider balanceSlider;
    ToggleButton onOffButton;
    
	Label frequencyLabel[NUM_FREQ * 2], gainLabel[NUM_FREQ * 2];
	Label onOffLabel, balanceLabel;
    
    Sine sine[NUM_FREQ*2]; // the sine wave oscillator
    
    // Global Variables
    float gain[NUM_FREQ*2];
	float balance;
    int onOff, samplingRate, nChans;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
