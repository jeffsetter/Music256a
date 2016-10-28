// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Simple JUCE sine wave synthesizer plug-in

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
BasicAudioPlugInAudioProcessorEditor::BasicAudioPlugInAudioProcessorEditor(BasicAudioPlugInAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(600, 30*nOvertones + 20);

	/*
	// configuring frequency slider and adding it to the main window
	addAndMakeVisible(frequencySlider);
	frequencySlider.setRange(50.0, 5000.0);
	frequencySlider.setSkewFactorFromMidPoint(500.0);
	frequencySlider.setValue(1000);
	frequencySlider.addListener(this);

	// configuring frequency label box and adding it to the main window
	addAndMakeVisible(frequencyLabel);
	frequencyLabel.setText("Frequency", dontSendNotification);
	frequencyLabel.attachToComponent(&frequencySlider, true);
	*/

	for (int i = 0; i < nOvertones; i++) {
		// configuring gain slider and adding it to the main window
		addAndMakeVisible(gainSlider[i]);
		gainSlider[i].setRange(0.0, 1.0);
		gainSlider[i].setValue(0.5);
		gainSlider[i].addListener(this);

		// add look and feel to each slider
		gainSlider[i].setColour(Slider::thumbColourId, Colours::white);
		gainSlider[i].setLookAndFeel(laf);
		gainSlider[i].setColour(Slider::rotarySliderFillColourId, Colour(0xff00b5f6));


		// configuring gain label and adding it to the main window
		addAndMakeVisible(gainLabel[i]);
		String label;
		if (i == 0) {
			label = "Base Freq";
		}
		else {
			label = "Overtone " + String(i);
		}

		gainLabel[i].setText(label, dontSendNotification);
		gainLabel[i].attachToComponent(&gainSlider[i], true);
	}
    
    
    // configuring on/off button and adding it to the main window
	/*
    addAndMakeVisible(onOffButton);
    onOffButton.addListener(this);
    
    
    // configuring on/off label and adding it to the main window
    addAndMakeVisible(onOffLabel);
    onOffLabel.setText ("On/Off", dontSendNotification);
    onOffLabel.attachToComponent (&onOffButton, true);
	*/
}

BasicAudioPlugInAudioProcessorEditor::~BasicAudioPlugInAudioProcessorEditor()
{
	delete laf;
}

//==============================================================================
void BasicAudioPlugInAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::lightgrey);
}

void BasicAudioPlugInAudioProcessorEditor::resized()
{
    const int sliderLeft = 80;
    frequencySlider.setBounds (sliderLeft, 10, getWidth() - sliderLeft - 20, 20);
	int y = 10;
	for (int i = 0; i < nOvertones; i++) {
		gainSlider[i].setBounds(sliderLeft, y, getWidth() - sliderLeft - 20, 20);
		y += 30;
	}
    onOffButton.setBounds (sliderLeft, y, getWidth() - sliderLeft - 20, 20);
}

void BasicAudioPlugInAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    if (processor.samplingRate > 0.0){
        if (slider == &frequencySlider){
            processor.sine[0][0].setFrequency(frequencySlider.getValue());
        }
        else {
			for (int i = 0; i < nOvertones; i++) {
				if (slider == &gainSlider[i]) {
					processor.timbreLevels[i] = gainSlider[i].getValue();
				}
			}
        }
    }
}

void BasicAudioPlugInAudioProcessorEditor::buttonClicked(Button *button){
    if(button == &onOffButton && onOffButton.getToggleState()){
        processor.onOff[0] = 1.0;
    }
    else{
        processor.onOff[0] = 0.0;
    }
}
