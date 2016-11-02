#pragma once

#include "ofMain.h"

#define RAIL_OFFSET 200
#define RAIL_LENGTH 1000
#define DIST_INF -7000

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

    // OpenFrameworks has many handy graphical primitive objects
    ofSpherePrimitive sun;
    ofSpherePrimitive earth;
    ofSpherePrimitive moon;
    
    float sunRotationAngle;
    float earthRotationAngle;
    
    float earthOrbitAngle;
    float moonOrbitAngle;

	ofCylinderPrimitive railLeft, railRight;
	ofCylinderPrimitive railLeftFuture, railRightFuture;
	ofCylinderPrimitive *rails[4] = { &railLeft, &railRight, &railLeftFuture, &railRightFuture };


	ofPlanePrimitive groundPlane;

	typedef struct {
		ofSpherePrimitive spheres[7];
	} Cloud;

	Cloud cloud;
	void drawCloud();
	float cloudDistance;

	ofSoundPlayer sp;
};
