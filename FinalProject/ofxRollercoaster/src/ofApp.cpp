#include "ofApp.h"

void ofApp::audioSetup() {
	// 2 output channels,
	// 0 input channels
	// 44100 samples per second
	// 512 samples per buffer
	// 4 num buffers (latency)

	int bufferSize = 256;
	sampleRate = 44100;
	nInputChans = 2;
	phase = 0;
	phaseAdder = 0.0f;
	phaseAdderTarget = 0.0f;
	volume = 1.0f;
	bNoise = false;

	lAudio.assign(bufferSize, 0.0);
	rAudio.assign(bufferSize, 0.0);
	audioBuffer = new float*[2];
	audioBuffer[0] = &lAudio[0];
	audioBuffer[1] = &rAudio[0];

	soundStream.printDeviceList();

	//if you want to set the device id to be different than the default
	soundStream.setDeviceID(0); 	//note some devices are input only and some are output only 

	soundStream.setup(this, nInputChans, 0, sampleRate, bufferSize, 4);

	// on OSX: if you want to use ofSoundPlayer together with ofSoundStream you need to synchronize buffersizes.
	// use ofFmodSetBuffersize(bufferSize) to set the buffersize in fmodx prior to loading a file.
	//ofFmodSetBuffersize(bufferSize);
	//ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::setup(){
    // This gets called once when we start our app

    // Make the app full screen
    //ofSetFullscreen(true);
	ofBackground(0, 170, 255); 	// Sky blue background
    
    // Turn on depth testing so rendering happens according to z-depth rather
    // than draw order.
    ofEnableDepthTest();
	ofSetVerticalSync(true);
	light.enable();

	// Create grass plane
	groundPlane.setWidth(ofGetWindowWidth()*100);
	groundPlane.setHeight(ofGetWindowHeight()*100);

	// play sound
	//audioSetup();
	globalGain = 0.5;
	int i = 0;
	for (auto player : audioPlayers) {
		player->setLoop(true);
		player->load(audioFiles[i]); i++;
		if (i > 0) { player->setVolume(0); }
		player->play();
		if (player->isLoaded() == false) {
			std::cout << "sound not loaded" << std::endl;
			std::exit(13);
		}
	}


	// set user variables
	userDir = Direction::Straight;
	userSpeed = 1;

	// Size rails correctly
	for (ofCylinderPrimitive *rail : rails) {
		rail->setRadius(25);
		rail->setHeight(RAIL_LENGTH);
	}
	railFutureMeshLeft = ofMesh::cylinder(25, RAIL_LENGTH);
	railFutureMeshRight = ofMesh::cylinder(25, RAIL_LENGTH);
	middleRail.setHeight(20);
	middleRail.setWidth(20);
	middleRail.setDepth(RAIL_LENGTH+350);
	strutStart = 0;
	strut.setup();

	// Size objects correctly
	Cloud* cloud = new Cloud();
	Tree* tree = new Tree();
	Grass* grass = new Grass();
	Pond* pond = new Pond();
	Bird* bird = new Bird();
	cloud->setup();
	cloud->setPosition(-300, DIST_INF);
	tree->setup();
	tree->setPosition(600, DIST_INF/2);
	tree->positionY = DIST_INF/2;
	grass->setup();
	grass->setPosition(-500, DIST_INF/4);
	pond->setPosition(-1000, DIST_INF/3);
	bird->setup();
	bird->setPosition(200, DIST_INF*2/3);
	objs.push_back(cloud);
	objs.push_back(tree);
	objs.push_back(grass);
	objs.push_back(pond);
	objs.push_back(bird);

	for (int i = 0; i < 3; i++) {
		userRot[i] = 0;
		userPos[i] = 0;
		userTilt[i] = 0;
	}

}

void deformRail(float amt_x, float amt_y, float amt_z, ofMesh* mesh) {
	vector<ofPoint> indices = mesh->getVertices();
	mesh->clearVertices();
	float offsetx = indices[0].y;
	for (int i = 0; i < indices.size(); i++) {
		float dist = indices[i].y + offsetx;
		float curve = (dist / 100.0)*(dist / 100.0);
		float xtrans = amt_x * curve;
		float ytrans = amt_y * curve;
		float ztrans = amt_z * curve;
		indices[i].set(indices[i].x + xtrans, indices[i].y + ytrans, indices[i].z + ztrans);
		mesh->addVertex(indices[i]);
	}
}

GraphicObj* chooseRandObj() {
	int num = rand() % 5;
	switch (num) {
	case 0:
		return new Cloud();
		break;
	case 1:
		return new Tree();
		break;
	case 2:
		return new Bird();
		break;
	case 3:
		return new Pond();
		break;
	case 4:
		return new Grass();
		break;
	default:
		return new Bird();
		break;
	}
}

//--------------------------------------------------------------
void ofApp::update(){
    // This gets called once for each graphical frame, right before draw()

	// update user position and rotation
	userRot[0] += userTilt[0];
	userRot[1] += userTilt[1];
	targetFrequency = userRot[0] *30 + 440;

	float userZ = sin(userRot[0] / 90.0 * PI);
	float userY = cos(userRot[1] / 90.0 * PI);
	float userX = sin(userRot[1] / 90.0 * PI);

	userPos[2] += userZ;

	for (int i = 0; i < objs.size(); ++i) {
		GraphicObj* obj = objs[i];
		obj->timestep(userSpeed, userX, userY, curScene);
		obj->updateVolume(globalGain);
		float objAngle = atan2(-obj->positionX, -obj->positionY)*180/PI;
		if (abs(objAngle-userRot[1]) > 90) {
			delete objs[i];
			objs.erase(objs.begin() + i);
		}
	}

	// create a new obj
	if (objs.size() < numObjs) {
		float randDeg = (rand() % 1500 - 750)/100.0;
		GraphicObj* newObj = chooseRandObj();
		newObj->setup();
		float angle = userRot[1] / 90.0 * PI + randDeg;
		newObj->setPosition(sin(angle)*DIST_INF, cos(angle)*DIST_INF);
		objs.push_back(newObj);
	}

	audioPlayers[0]->setVolume(globalGain);
	//audioPlayers[1]->setVolume(globalGain * 300 / abs(tree.positionY));
	//audioPlayers[2]->setVolume(globalGain * 300 / abs(cloud.positionY));
	//audioPlayers[3]->setVolume(globalGain * 800 / abs(bird.positionY));
	//audioPlayers[4]->setVolume(globalGain * 300 / abs(pond.positionY));

	strutStart -= 2*userSpeed;
	if (strutStart < -RAIL_STRUT_SPACING) {
		strutStart = 0;
	}

	float deformConst = 0.001*userSpeed;
	float rotationConst = 0.0001*userSpeed;
	float tiltMax = 1000000 * abs(rotationConst);

	switch (userDir) {
	case Direction::Straight:
		break;
	case Direction::Left:
		deformTotal[0] -= deformConst;
		deformRail(-deformConst, 0, 0, &railFutureMeshLeft);
		deformRail(-deformConst, 0, 0, &railFutureMeshRight);
		userTilt[1] -= rotationConst;
		break;
	case Direction::Right:
		deformTotal[0] += deformConst;
		deformRail(deformConst, 0, 0, &railFutureMeshLeft);
		deformRail(deformConst, 0, 0, &railFutureMeshRight);
		userTilt[1] += rotationConst;
		break;
	case Direction::Up:
		deformTotal[1] += deformConst;
		deformRail(0, 0, deformConst, &railFutureMeshLeft);
		deformRail(0, 0, deformConst, &railFutureMeshRight);
		userTilt[0] += rotationConst;
		break;
	case Direction::Down:
		deformTotal[1] -= deformConst;
		deformRail(0, 0, -deformConst, &railFutureMeshLeft);
		deformRail(0, 0, -deformConst, &railFutureMeshRight);
		userTilt[0] -= rotationConst;
		break;
	default:
		printf("invalid direction\n");
		std::exit(13);
	}

	for (int i = 0; i < 3; ++i) {
		if (userTilt[i] > tiltMax) {
			userTilt[i] = tiltMax;
		} else if (userTilt[i] < -tiltMax) {
			userTilt[i] = -tiltMax;
		}
	}

}


void ofApp::drawStrut() {
	ofPushMatrix();
	ofPushStyle();

	// draw vertical bars under the rails
	ofTranslate(RAIL_OFFSET, 40, 0);
	strut.vBar.draw();
	ofTranslate(-2 * RAIL_OFFSET, 0, 0);
	strut.vBar.draw();
	ofTranslate(RAIL_OFFSET, 0, 0);

	// draw the horizontal strut
	ofTranslate(0, 20, 0);
	strut.hBar.draw();
	ofTranslate(0, 20, 0);
	strut.vBar.draw();

	ofPopStyle();
	ofPopMatrix();
}


//--------------------------------------------------------------
void ofApp::draw() {
	if (USER_CAMERA) {
		cam.begin();
	}
	if (newBackground) {
		if (curScene == Forest) {
			ofBackground(0, 170, 255); 	// Sky blue background
		} else if (curScene == Upsidedown) {
			ofBackground(105, 105, 105); // dim gray
		} else if (curScene == Cave) {
			ofBackground(10, 10, 10); // blackish
		}
		newBackground = false;
	}

	// This gets called once for each graphical frame, right after update()
	// This is where you draw all the graphics
	ofPushMatrix(); // Save our state for later

        // Since our coordinates start in the top left, translate to the center front.
		ofTranslate(ofGetWindowWidth()*0.5, ofGetWindowHeight());

        ofPushMatrix(); // Save center front state
		ofPushStyle(); // Save initial style state

			// create the rails
			ofTranslate(0, 100, 0);
			ofSetColor(200, 10, 0); // dark red color
			middleRail.draw();
			ofTranslate(0, -100, 0);

			ofTranslate(RAIL_OFFSET, 0);
			ofRotateX(90);
            
			ofSetColor(255, 10, 0); // red color
			railLeft.draw();
			ofTranslate(-RAIL_OFFSET*2, 0);
			railRight.draw();

			ofTranslate(0, -RAIL_LENGTH);

			railFutureMeshLeft.drawWireframe();
			ofTranslate(RAIL_OFFSET * 2, 0, 0);
			railFutureMeshRight.drawWireframe();

     
        ofPopMatrix(); // Back to center front state
		ofPushMatrix();
			ofTranslate(0, 0, -strutStart);
			for (int d = -strutStart; d < RAIL_LENGTH; d += RAIL_STRUT_SPACING) {
				drawStrut();
				ofTranslate(0, 0, -RAIL_STRUT_SPACING);
			}

		ofPopStyle(); // Back to initial style state  
		ofPopMatrix(); // Back to center front state

		ofRotateX(userRot[0]);
		ofRotateY(userRot[1]);
		ofRotateZ(userRot[2]); // used for rolls
		if (curScene == Upsidedown) {
			ofRotateZ(180);
			ofTranslate(0, 1000);
		}
		ofTranslate(userPos[0], userPos[2], userPos[1]);

		// draw the ground plane
		ofPushMatrix();
		ofPushStyle();
		ofTranslate(0, GROUND_DEPTH);


		if (curScene == Forest) {
			ofSetColor(124, 252, 0); // lawn green
		} else if (curScene == Upsidedown) {
			ofSetColor(0, 70, 0); // dark green
		} else if (curScene == Cave) {
			ofSetColor(92, 64, 51); // dark brown
			
			ofRotateX(90);
			groundPlane.draw();

			ofPushMatrix();
			ofRotateY(80);
			ofTranslate(0, 0, 2000);
			groundPlane.draw();
			ofPopMatrix();
			
			ofPushMatrix();
			ofRotateY(100);
			ofTranslate(0, 0, -2000);
			groundPlane.draw();
			ofPopMatrix();
			
			ofRotateX(-90);
			ofTranslate(0, CEILING_DEPTH-GROUND_DEPTH);
		}
		ofRotateX(90);
		groundPlane.draw();
		ofPopStyle();
		ofPopMatrix();

		// draw the objects
		for (GraphicObj* obj : objs) {
			ofPushMatrix();
			ofTranslate(obj->positionX, obj->positionZ, obj->positionY);
			obj->draw(curScene);
			ofPopMatrix();
		}

    ofPopMatrix(); // Back to initial state at the top-left of our window.

	if (USER_CAMERA) {
		cam.end();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case '8':
		userDir = Direction::Up;
		globalGain += 0.1;
		break;
	case '4':
		userDir = Direction::Left;
		pan -= 0.05;
		audioPlayers[1]->setPan(-pan);
		audioPlayers[2]->setPan(pan);
		audioPlayers[3]->setPan(-pan);
		audioPlayers[4]->setPan(pan);
		break;
	case '6':
		userDir = Direction::Right;
		pan += 0.05;
		audioPlayers[1]->setPan(-pan);
		audioPlayers[2]->setPan(pan);
		audioPlayers[3]->setPan(-pan);
		audioPlayers[4]->setPan(pan);
		break;
	case '2':
		userDir = Direction::Down;
		globalGain -= 0.1;
		break;
	case '5':
		userDir = Direction::Straight;
		break;
	case '+':
		userSpeed += SPEED_INCREMENT;
		for (auto audio : audioPlayers) {
			audio->setSpeed(userSpeed);
		}
		break;
	case '-':
		userSpeed -= SPEED_INCREMENT;
		for (auto audio : audioPlayers) {
			audio->setSpeed(userSpeed);
		}
		break;
	case '[':
		numObjs--;
		break;
	case ']':
		numObjs++;
		break;
	case 'q':
		curScene = Forest;
		newBackground = true;
		break;
	case 'w':
		curScene = Cave;
		newBackground = true;
		break;
	case 'r':
		curScene = Upsidedown;
		newBackground = true;
		break;

	case ' ':
		userDir = Straight;
		deformRail(-deformTotal[0], 0, -deformTotal[1], &railFutureMeshLeft);
		deformRail(-deformTotal[0], 0, -deformTotal[1], &railFutureMeshRight);
		for (int i = 0; i < 3; ++i) {
			userRot[i] = 0;
			userTilt[i] = 0;
			userPos[i] = 0;
			deformTotal[i] = 0;
		}
		break;
	default:
		break;
	}

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

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
	//pan = 0.5f;
	float leftScale = 1 - pan;
	float rightScale = pan;
	volume = 1.0f;
	bNoise = false;
	phaseAdderTarget = (targetFrequency / (float)sampleRate) * TWO_PI;

	// sin (n) seems to have trouble when n is very large, so we
	// keep phase in the range of 0-TWO_PI like this:
	while (phase > TWO_PI) {
		phase -= TWO_PI;
	}

	myMutex.lock();
	if (bNoise == true) {
		// ---------------------- noise --------------
		for (int i = 0; i < bufferSize; i++) {
			lAudio[i] = output[i*nChannels] = ofRandom(0, 1) * volume * leftScale;
			rAudio[i] = output[i*nChannels + 1] = ofRandom(0, 1) * volume * rightScale;
		}
	}
	else {
		phaseAdder = 0.95f * phaseAdder + 0.05f * phaseAdderTarget;
		for (int i = 0; i < bufferSize; i++) {
			phase += phaseAdder;
			float sample = sin(phase);
			lAudio[i] = output[i*nChannels] = sample * volume * leftScale;
			rAudio[i] = output[i*nChannels + 1] = sample * volume * rightScale;
		}
	}

	// Reverb stuff
	//reverb.compute(bufferSize, audioBuffer, audioBuffer); // computing one block with Faust
	myMutex.unlock();

	// Interleave the output buffer
	for (int i = 0; i < bufferSize; i++)
	{
		output[2 * i] = lAudio[i]; //audioBuffer[0][i];
		output[2 * i + 1] = rAudio[i]; //audioBuffer[1][i];
	}

}