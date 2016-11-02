#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    // This gets called once when we start our app

    // Make the app full screen
    //ofSetFullscreen(true);
    
    // Turn on depth testing so rendering happens according to z-depth rather
    // than draw order.
    ofEnableDepthTest();
    
    // Sky blue background
    ofBackground(0, 170, 255);

	// Create green grass plane
	groundPlane.setWidth(ofGetWindowWidth()*10);
	groundPlane.setHeight(ofGetWindowHeight()*10);


    
    // Set the size of our sphere "planets"
    sun.setRadius( 120.0 );
    earth.setRadius( 50.0 );
    moon.setRadius( 12.0 );
    
    // Initialize orbit rotation angles to zero
    sunRotationAngle = 0;
    earthOrbitAngle = 0;
    moonOrbitAngle = 0;

	for (ofCylinderPrimitive *rail : rails) {
		rail->setRadius(25);
		rail->setHeight(RAIL_LENGTH);
	}

	ofSpherePrimitive *spheres = cloud.spheres;
	for (int i = 0; i < 7; i++) {
		spheres[i].setRadius(50);
	}

	cloudDistance = DIST_INF;

	sp.setLoop(true);
	sp.load("rollercoaster.mp3");
	sp.play();

	if (sp.isLoaded() == false) { 
		std::cout << "sound not loaded" << std::endl;
		std::exit(13);
	}

}

//--------------------------------------------------------------
void ofApp::update(){
    // This gets called once for each graphical frame, right before draw()
    
    // Update orbit rotation angles -- larger increment == faster rotation.
    sunRotationAngle += 0.1;
    earthRotationAngle += 2.0;
    earthOrbitAngle += 0.5;
    moonOrbitAngle += 2.5;

	cloudDistance += 2;
	if (cloudDistance > 1000) {
		cloudDistance = DIST_INF;
	}
}

void ofApp::drawCloud() {
	ofPushMatrix();
	ofPushStyle();

	ofSetColor(255, 255, 255); // white
	ofTranslate(0, 0, -200);
	cloud.spheres[0].draw();
	ofTranslate(60, 25, 100);
	cloud.spheres[1].draw();
	ofTranslate(0, -50, 0);
	cloud.spheres[2].draw();
	ofTranslate(60, 0, 100);
	cloud.spheres[3].draw();
	ofTranslate(0, 50, 0);
	cloud.spheres[4].draw();
	ofTranslate(60, -25, 100);
	cloud.spheres[5].draw();

	ofPopStyle();
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::draw(){
	// draw the ground plane
	ofPushMatrix();
	ofPushStyle();
		ofTranslate(0, ofGetWindowHeight()+100);
		ofRotateX(90);
		ofSetColor(124, 252, 0); // lawn green
		groundPlane.draw();
	ofPopStyle();
	ofPopMatrix();


    // This gets called once for each graphical frame, right after update()
    // This is where you draw all the graphics
    
    ofPushMatrix(); // Save our state for later

        // Since our coordinates start in the top left, translate to the center front.
        //ofTranslate( ofGetWindowWidth()*0.5, ofGetWindowHeight()*0.5 );
		ofTranslate(ofGetWindowWidth()*0.5, ofGetWindowHeight());

        ofPushMatrix(); // Save center front state
        
            //ofRotateY( sunRotationAngle ); // Sun's rotation about its axis

            
			ofTranslate(RAIL_OFFSET, 0);
			ofRotateX(90);
            ofPushStyle(); // Save initial style state
                // Set the color of the rails
                ofSetColor(255, 25, 0); // red color
				railLeft.draw();
				ofTranslate(-RAIL_OFFSET*2, 0);
				railRight.draw();

				ofTranslate(0, -RAIL_LENGTH);
				railRightFuture.drawWireframe();
				ofTranslate(RAIL_OFFSET * 2, 0, 0);
				railLeftFuture.drawWireframe();

            ofPopStyle(); // Back to initial style state
        
        ofPopMatrix(); // Back to center state

		ofTranslate(-300, -2000, cloudDistance);
		drawCloud();

        // Rotate our axes and then translate, for Earth orbit
        ofRotateY( earthOrbitAngle );
        ofTranslate(350, -100, 0);
    
		/*
        ofPushMatrix(); // Save Earth-centric state
            ofRotateZ( earthRotationAngle ); // Rotate Earth about its own axis
            ofPushStyle();  // Save initial style state
                // Set the color of the Earth
                ofSetColor(0, 0, 256);
                // Draw the Earth (also wireframe so we can see rotation)
                earth.drawWireframe();
            ofPopStyle(); // Back to initial style state
        ofPopMatrix(); // Back to un-rotated Earth-centric state
    
        // Recall that our axes are still centered about the Earth.
        // Now do another rotate and translate, thus we rotate the moon about
        // the Earth.
        ofRotateY( moonOrbitAngle );
        // ofRotateX( moonOrbitAngle ); // also rotate about the X direction?
        ofTranslate(0, 0, 100); // and translate in the Z direction just for fun
        
        ofPushStyle();  // Save initial style state
            // Set the Moon color
            ofSetColor(256, 256, 256);
            // Draw the moon
            moon.drawWireframe();
        ofPopStyle(); // Back to initial style state
		*/

    ofPopMatrix(); // Back to initial state at the top-left of our window.
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
