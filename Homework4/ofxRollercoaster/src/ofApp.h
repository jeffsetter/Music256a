#pragma once

#include "ofMain.h"
#include "sizeDefs.h"
#include "objects.h"


enum Direction {
	Straight, Up, Down, Right, Left
};

typedef struct {
	ofBoxPrimitive hBar;
	ofBoxPrimitive vBar;
	void setup() {
		hBar.setHeight(20);
		hBar.setWidth(RAIL_OFFSET * 2);
		hBar.setDepth(70);
		vBar.setHeight(50);
		vBar.setWidth(20);
		vBar.setDepth(20);
	}
} Strut;



class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

	ofPlanePrimitive groundPlane;
	ofEasyCam cam;
	ofLight light;

	ofSoundPlayer sp[5];
	string audioFiles[5] = { "rollercoaster.mp3", "tree.mp3", "cloud.mp3", "seagull.mp3", "lake.mp3" };
	ofSoundPlayer* audioPlayers[5] = { &sp[0], &sp[1], &sp[2], &sp[3], &sp[4] };
	float globalGain = 1;

	float userTilt[3];
	float userRot[3];
	float userPos[3];
	Direction userDir;
	float userSpeed;

	// objects for the rollercoaster
	ofCylinderPrimitive railRight, railLeft, railFutureRight, railFutureLeft;
	ofCylinderPrimitive *rails[4] = { &railRight, &railLeft, &railFutureRight, &railFutureLeft };

	ofMesh railFutureMeshRight;
	ofMesh railFutureMeshLeft;
	ofBoxPrimitive middleRail;

	// methods for rollercoaster struts
	Strut strut;
	void drawStrut();
	float strutStart;

	// create objects
	Cloud cloud;
	Tree tree;
	Grass grass;
	Pond pond;
	Bird bird;

	void audioOut(float * input, int bufferSize, int nChannels);
	ofSoundStream soundStream;

	float 	pan = 0;
	int		sampleRate, nInputChans;
	bool 	bNoise = true;
	float 	volume;

	vector <float> lAudio;
	vector <float> rAudio;

	//------------------- for the simple sine wave synthesis
	float 	targetFrequency;
	float 	phase;
	float 	phaseAdder;
	float 	phaseAdderTarget;

	void audioSetup();
	float **audioBuffer; // The 2d audio buffer that Faust wants to work with
	ofMutex myMutex;


};
