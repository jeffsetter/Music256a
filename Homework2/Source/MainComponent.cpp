// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Simple Faust-based sawtooth synthesizer.

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "FaustSawZitaWrapper.h" // the Faust module

#include <random>

//==============================================================================
/** Custom Look And Feel subclasss.

Simply override the methods you need to, anything else will be inherited from the base class.
It's a good idea not to hard code your colours, use the findColour method along with appropriate
ColourIds so you can set these on a per-component basis.
*/
struct CustomLookAndFeel : public LookAndFeel_V3
{
	void drawRoundThumb(Graphics& g, const float x, const float y,
		const float diameter, const Colour& colour, float outlineThickness)
	{
		const Rectangle<float> a(x, y, diameter, diameter);
		const float halfThickness = outlineThickness * 0.5f;

		Path p;
		p.addEllipse(x + halfThickness, y + halfThickness, diameter - outlineThickness, diameter - outlineThickness);

		const DropShadow ds(Colours::black, 1, Point<int>(0, 0));
		ds.drawForPath(g, p);

		g.setColour(colour);
		g.fillPath(p);

		g.setColour(colour.brighter());
		g.strokePath(p, PathStrokeType(outlineThickness));
	}

	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
		bool isMouseOverButton, bool isButtonDown) override
	{
		Colour baseColour(backgroundColour.withMultipliedSaturation(button.hasKeyboardFocus(true) ? 1.3f : 0.9f)
			.withMultipliedAlpha(button.isEnabled() ? 0.9f : 0.5f));

		if (isButtonDown || isMouseOverButton)
			baseColour = baseColour.contrasting(isButtonDown ? 0.2f : 0.1f);

		const bool flatOnLeft = button.isConnectedOnLeft();
		const bool flatOnRight = button.isConnectedOnRight();
		const bool flatOnTop = button.isConnectedOnTop();
		const bool flatOnBottom = button.isConnectedOnBottom();

		const float width = button.getWidth() - 1.0f;
		const float height = button.getHeight() - 1.0f;

		if (width > 0 && height > 0)
		{
			const float cornerSize = jmin(15.0f, jmin(width, height) * 0.45f);
			const float lineThickness = cornerSize * 0.1f;
			const float halfThickness = lineThickness * 0.5f;

			Path outline;
			outline.addRoundedRectangle(0.5f + halfThickness, 0.5f + halfThickness, width - lineThickness, height - lineThickness,
				cornerSize, cornerSize,
				!(flatOnLeft || flatOnTop),
				!(flatOnRight || flatOnTop),
				!(flatOnLeft || flatOnBottom),
				!(flatOnRight || flatOnBottom));

			const Colour outlineColour(button.findColour(button.getToggleState() ? TextButton::textColourOnId
				: TextButton::textColourOffId));

			g.setColour(baseColour);
			g.fillPath(outline);

			if (!button.getToggleState())
			{
				g.setColour(outlineColour);
				g.strokePath(outline, PathStrokeType(lineThickness));
			}
		}
	}

	void drawTickBox(Graphics& g, Component& component,
		float x, float y, float w, float h,
		bool ticked,
		bool isEnabled,
		bool isMouseOverButton,
		bool isButtonDown) override
	{
		const float boxSize = w * 0.7f;

		bool isDownOrDragging = component.isEnabled() && (component.isMouseOverOrDragging() || component.isMouseButtonDown());
		const Colour colour(component.findColour(TextButton::buttonColourId).withMultipliedSaturation((component.hasKeyboardFocus(false) || isDownOrDragging) ? 1.3f : 0.9f)
			.withMultipliedAlpha(component.isEnabled() ? 1.0f : 0.7f));

		drawRoundThumb(g, x, y + (h - boxSize) * 0.5f, boxSize, colour,
			isEnabled ? ((isButtonDown || isMouseOverButton) ? 1.1f : 0.5f) : 0.3f);

		if (ticked)
		{
			const Path tick(LookAndFeel_V2::getTickShape(6.0f));
			g.setColour(isEnabled ? findColour(TextButton::buttonOnColourId) : Colours::grey);

			const float scale = 9.0f;
			const AffineTransform trans(AffineTransform::scale(w / scale, h / scale)
				.translated(x - 2.5f, y + 1.0f));
			g.fillPath(tick, trans);
		}
	}

	void drawLinearSliderThumb(Graphics& g, int x, int y, int width, int height,
		float sliderPos, float minSliderPos, float maxSliderPos,
		const Slider::SliderStyle style, Slider& slider) override
	{
		const float sliderRadius = (float)(getSliderThumbRadius(slider) - 2);

		bool isDownOrDragging = slider.isEnabled() && (slider.isMouseOverOrDragging() || slider.isMouseButtonDown());
		Colour knobColour(slider.findColour(Slider::thumbColourId).withMultipliedSaturation((slider.hasKeyboardFocus(false) || isDownOrDragging) ? 1.3f : 0.9f)
			.withMultipliedAlpha(slider.isEnabled() ? 1.0f : 0.7f));

		if (style == Slider::LinearHorizontal || style == Slider::LinearVertical)
		{
			float kx, ky;

			if (style == Slider::LinearVertical)
			{
				kx = x + width * 0.5f;
				ky = sliderPos;
			}
			else
			{
				kx = sliderPos;
				ky = y + height * 0.5f;
			}

			const float outlineThickness = slider.isEnabled() ? 0.8f : 0.3f;

			drawRoundThumb(g,
				kx - sliderRadius,
				ky - sliderRadius,
				sliderRadius * 2.0f,
				knobColour, outlineThickness);
		}
		else
		{
			// Just call the base class for the demo
			LookAndFeel_V2::drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
		}
	}

	void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
		float sliderPos, float minSliderPos, float maxSliderPos,
		const Slider::SliderStyle style, Slider& slider) override
	{
		g.fillAll(slider.findColour(Slider::backgroundColourId));

		if (style == Slider::LinearBar || style == Slider::LinearBarVertical)
		{
			const float fx = (float)x, fy = (float)y, fw = (float)width, fh = (float)height;

			Path p;

			if (style == Slider::LinearBarVertical)
				p.addRectangle(fx, sliderPos, fw, 1.0f + fh - sliderPos);
			else
				p.addRectangle(fx, fy, sliderPos - fx, fh);


			Colour baseColour(slider.findColour(Slider::rotarySliderFillColourId)
				.withMultipliedSaturation(slider.isEnabled() ? 1.0f : 0.5f)
				.withMultipliedAlpha(0.8f));

			g.setColour(baseColour);
			g.fillPath(p);

			const float lineThickness = jmin(15.0f, jmin(width, height) * 0.45f) * 0.1f;
			g.drawRect(slider.getLocalBounds().toFloat(), lineThickness);
		}
		else
		{
			drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
			drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
		}
	}

	void drawLinearSliderBackground(Graphics& g, int x, int y, int width, int height,
		float /*sliderPos*/,
		float /*minSliderPos*/,
		float /*maxSliderPos*/,
		const Slider::SliderStyle /*style*/, Slider& slider) override
	{
		const float sliderRadius = getSliderThumbRadius(slider) - 5.0f;
		Path on, off;

		if (slider.isHorizontal())
		{
			const float iy = y + height * 0.5f - sliderRadius * 0.5f;
			Rectangle<float> r(x - sliderRadius * 0.5f, iy, width + sliderRadius, sliderRadius);
			const float onW = r.getWidth() * ((float)slider.valueToProportionOfLength(slider.getValue()));

			on.addRectangle(r.removeFromLeft(onW));
			off.addRectangle(r);
		}
		else
		{
			const float ix = x + width * 0.5f - sliderRadius * 0.5f;
			Rectangle<float> r(ix, y - sliderRadius * 0.5f, sliderRadius, height + sliderRadius);
			const float onH = r.getHeight() * ((float)slider.valueToProportionOfLength(slider.getValue()));

			on.addRectangle(r.removeFromBottom(onH));
			off.addRectangle(r);
		}

		g.setColour(slider.findColour(Slider::rotarySliderFillColourId));
		g.fillPath(on);

		g.setColour(slider.findColour(Slider::trackColourId));
		g.fillPath(off);
	}

	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override
	{
		const float radius = jmin(width / 2, height / 2) - 2.0f;
		const float centreX = x + width * 0.5f;
		const float centreY = y + height * 0.5f;
		const float rx = centreX - radius;
		const float ry = centreY - radius;
		const float rw = radius * 2.0f;
		const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
		const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

		if (slider.isEnabled())
			g.setColour(slider.findColour(Slider::rotarySliderFillColourId).withAlpha(isMouseOver ? 1.0f : 0.7f));
		else
			g.setColour(Colour(0x80808080));

		{
			Path filledArc;
			filledArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, angle, 0.0);
			g.fillPath(filledArc);
		}

		{
			const float lineThickness = jmin(15.0f, jmin(width, height) * 0.45f) * 0.1f;
			Path outlineArc;
			outlineArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, 0.0);
			g.strokePath(outlineArc, PathStrokeType(lineThickness));
		}
	}
};

//==============================================================================
/*
This component lives inside our window, and this is where you should put all
your controls and content.
*/
class MainContentComponent :
	public AudioAppComponent,
	private Slider::Listener,
	private ToggleButton::Listener
{
public:
	//==============================================================================
	MainContentComponent() : currentSampleRate(0.0)
	{
		// add look and feel to each slider
		for (Slider* s : sliders) {
			s->setColour(Slider::thumbColourId, Colours::white);
			s->setLookAndFeel(laf);
			s->setColour(Slider::rotarySliderFillColourId, Colour(0xff00b5f6));
		}

		addAndMakeVisible(frequencySlider);
		frequencySlider.setRange(50.0, 5000.0);
		frequencySlider.setSkewFactorFromMidPoint(500.0);
		frequencySlider.setValue(1000);
		frequencySlider.addListener(this);
		addAndMakeVisible(frequencyLabel);
		frequencyLabel.setText("Frequency", dontSendNotification);
		frequencyLabel.attachToComponent(&frequencySlider, false);

		addAndMakeVisible(gainSlider);
		gainSlider.setSliderStyle(Slider::LinearVertical);
		gainSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
		gainSlider.setRange(0.0, 1.0);
		gainSlider.setValue(0.5);
		gainSlider.addListener(this);
		addAndMakeVisible(gainLabel);
		gainLabel.setText("Gain", dontSendNotification);
		gainLabel.attachToComponent(&gainSlider, false);

		addAndMakeVisible(onOffButton);
		onOffButton.addListener(this);
		addAndMakeVisible(onOffLabel);
		onOffLabel.setText("On/Off", dontSendNotification);
		onOffLabel.attachToComponent(&onOffButton, true);

		addAndMakeVisible(reverbSlider);
		reverbSlider.setSliderStyle(Slider::LinearVertical);
		reverbSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
		reverbSlider.setRange(1.0, 8.0);
		reverbSlider.setValue(4);
		reverbSlider.addListener(this);
		addAndMakeVisible(reverbLabel);
		reverbLabel.setText("Reverb", dontSendNotification);
		reverbLabel.attachToComponent(&reverbSlider, false);

		addAndMakeVisible(intervalKnob);
		intervalKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
		intervalKnob.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
		intervalKnob.setRange(1.0, 100.0);
		intervalKnob.setValue(50);
		intervalKnob.addListener(this);
		addAndMakeVisible(intervalLabel);
		intervalLabel.setText("Interval", dontSendNotification);
		intervalLabel.attachToComponent(&intervalKnob, false);

		addAndMakeVisible(dissonanceKnob);
		dissonanceKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
		dissonanceKnob.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
		dissonanceKnob.setRange(0, 0.99);
		dissonanceKnob.setValue(0.2);
		dissonanceKnob.setSkewFactorFromMidPoint(0.2);
		dissonanceKnob.addListener(this);
		addAndMakeVisible(dissonanceLabel);
		dissonanceLabel.setText("Freq Range", dontSendNotification);
		dissonanceLabel.attachToComponent(&dissonanceKnob, false);

		// init all variables
		setSize(600, 250);

		nChans = 2; // number of output audio channels

		setAudioChannels(0, nChans);

		audioBuffer = new float*[nChans];

		interval = 50;
		intervalCount = 0;
		distribution = new std::uniform_real_distribution<double>(-0.2, 0.2);
		freqOffset = 1;
		chordLen = std::pow(semitone, distChord(generator));
	}

	~MainContentComponent()
	{
		shutdownAudio();
		delete[] audioBuffer;
		delete laf;
		delete distribution;
	}

	//==============================================================================
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
	{
		currentSampleRate = sampleRate;
		blockSize = samplesPerBlockExpected;

		saw.init(sampleRate); // initializing the Faust module
		saw.buildUserInterface(&sawControl); // linking the Faust module to the controler

											 // Print the list of parameters address of "saw"
											 // To get the current (default) value of these parameters, sawControl.getParamValue("paramPath") can be used
		for (int i = 0; i<sawControl.getParamsCount(); i++) {
			std::cout << sawControl.getParamAdress(i) << "\n";
		}

		// setting default values for the Faust module parameters
		sawControl.setParamValue("/ZitaReverb/saw/freq1", 1000);
		sawControl.setParamValue("/ZitaReverb/saw/freq2", 1000*chordLen);
		sawControl.setParamValue("/ZitaReverb/saw/gain", 0.5);
		sawControl.setParamValue("/ZitaReverb/saw/decay", 4);
	}

	// Case where the buffer loop is implemented in Faust (faustSample is not needed in that case)
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override
	{
		// every set of audio blocks (based on knob), pick random pitches
		if (interval * 5 < intervalCount) {
			intervalCount = 0;
			std::uniform_real_distribution<double> dist = *distribution;

			freqOffset = 1 + dist(generator); // get new offset off of center freq (from slider)
			double freq = frequencySlider.getValue()*freqOffset;
			chordLen = std::pow(semitone, distChord(generator)); // get new chord
			sawControl.setParamValue("/ZitaReverb/saw/freq1", freq);
			sawControl.setParamValue("/ZitaReverb/saw/freq2", freq*chordLen);

		}
		intervalCount++;

		audioBuffer[0] = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);

		// any processing before going to "saw" could be done here in a dedicated buffer loop

		saw.compute(blockSize, NULL, audioBuffer); // computing one block with Faust

												   // any processing before going to "saw" could be done here in a dedicated buffer loop
												   // An alternative solution could be to use only one buffer loop and to set the blockSize
												   // of "reverb.compute" to 1...
	}

	void releaseResources() override
	{
		// This will be called when the audio device stops, or when it is being
		// restarted due to a setting change.

		// For more details, see the help for AudioProcessor::releaseResources()
	}

	void resized() override
	{
		const int sliderLeft = 80;
		const int sliderTop = 20;
		const int buffer = 20;
		const int midpoint = 100;

		gainSlider.setBounds(getWidth() - buffer - 40, buffer+sliderTop, 40, getHeight() - buffer*2 - sliderTop);
		reverbSlider.setBounds(getWidth() - 2*buffer - 80, buffer+sliderTop, 60, getHeight() - buffer*2 - sliderTop);
		frequencySlider.setBounds(buffer, sliderLeft+buffer*2, getWidth() - sliderLeft - midpoint, sliderTop);
		onOffButton.setBounds(sliderLeft, getHeight() - buffer - sliderTop, getWidth() - 2*sliderLeft - midpoint, sliderTop);
		intervalKnob.setBounds(sliderLeft*3/2, sliderTop, sliderLeft, sliderLeft);
		dissonanceKnob.setBounds(sliderLeft * 3, sliderTop, sliderLeft, sliderLeft);
	}

	void sliderValueChanged(Slider* slider) override
	{
		if (currentSampleRate > 0.0) {
			if (slider == &frequencySlider)	{
				double freq = frequencySlider.getValue()*freqOffset;
				chordLen = std::pow(semitone, distChord(generator));
				sawControl.setParamValue("/ZitaReverb/saw/freq1", freq);
				sawControl.setParamValue("/ZitaReverb/saw/freq2", freq*chordLen);
			} else if (slider == &gainSlider) {
				sawControl.setParamValue("/ZitaReverb/saw/gain", gainSlider.getValue());
			} else if (slider == &reverbSlider) {
				sawControl.setParamValue("/ZitaRever/saw/decay", reverbSlider.getValue());
			} else if (slider == &intervalKnob) {
				interval = intervalKnob.getValue();
			} else if (slider == &dissonanceKnob) {
				stepRange = dissonanceKnob.getValue();
				distribution = new std::uniform_real_distribution<double>(-stepRange, stepRange);
			}
		}
	}

	void buttonClicked(Button* button) override
	{
		if (button == &onOffButton && onOffButton.getToggleState()) {
			sawControl.setParamValue("/ZitaReverb/saw/gate", 1);
		}
		else {
			sawControl.setParamValue("/ZitaReverb/saw/gate", 0);
		}
	}

private:
	mydsp saw; // the Faust module (FaustSawZita.h)
	MapUI sawControl; // used to easily control the Faust module (FaustSawZita.h)

	Slider frequencySlider, gainSlider, reverbSlider;
	Slider intervalKnob, dissonanceKnob;
	Slider* sliders[5] = { &frequencySlider, &gainSlider, &reverbSlider, &intervalKnob, &dissonanceKnob };
	LookAndFeel *laf = new CustomLookAndFeel();

	ToggleButton onOffButton;

	Label frequencyLabel, gainLabel, reverbLabel;
	Label intervalLabel, dissonanceLabel;
	Label onOffLabel;

	int blockSize, nChans;
	double currentSampleRate;

	int interval, intervalCount;
	double freqOffset, stepRange;
	std::default_random_engine generator;
	std::uniform_real_distribution<double> *distribution;
	const double semitone = std::pow(2.0, 1.0 / 12.0); // size of equally-sized semitone
	std::uniform_int_distribution<int> distChord= std::uniform_int_distribution<int>(0, 12); // uniform dist of one octave
	float chordLen;

	float** audioBuffer; // multichannel audio buffer used both for input and output

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent() { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
