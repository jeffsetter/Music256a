#pragma once

#include "ofMain.h"
#include "sizeDefs.h"

enum Scene {
	Forest, Cave, Candyland, Upsidedown
};

class GraphicObj {
public:
	virtual float getDefaultZ() = 0;
	virtual void draw(Scene scene) = 0;
	virtual void setup() { };
	virtual void timestep(float userSpeed, float userX, float userY) {
		positionY += 2 * userSpeed * userY;
		positionX -= 2 * userSpeed * userX;
	}
	virtual void timestep(float userSpeed, float userX, float userY, Scene scene) {
		timestep(userSpeed, userX, userY);
	}
	virtual void updateVolume(float globalGain) = 0;

	float positionX;
	float positionY;
	float positionZ;

	void setPosition(float x, float y, float z) {
		positionX = x;
		positionY = y;
		positionZ = z;
	}
	void setPosition(float x, float y) {
		setPosition(x, y, getDefaultZ());
	}

	ofSoundPlayer player;
	void setupAudio(string audioFile) {
		player.setLoop(true);
		/*player.load(audioFile);
		player.setVolume(0);
		if (player.isLoaded() == false) {
			std::cout << "sound not loaded" << std::endl;
			std::exit(49);
		}*/
	}

};

class Cloud : public GraphicObj {
public:
	ofSpherePrimitive spheres[7];
	ofConePrimitive stalactiteS;
	ofConePrimitive stalactiteL;

	void setup() {
		for (int i = 0; i < 7; i++) {
			spheres[i].setRadius(150);
		}
		//spheres[0].setRadius(100);
		//spheres[5].setRadius(100);
		stalactiteL.setRadius(40);
		stalactiteL.setHeight(600);
		stalactiteS.setRadius(20);
		stalactiteS.setHeight(200);
		setupAudio("cloud.mp3");
	}
	void draw(Scene scene);
	float getDefaultZ() {
		return -2000;
	}
	void updateVolume(float globalGain) {
		player.setVolume(globalGain * 300 / abs(positionY));
	}
};

class Tree : public GraphicObj {
public:
	ofSpherePrimitive leaves;
	ofCylinderPrimitive trunk;
	ofConePrimitive stalagmiteS;
	ofConePrimitive stalagmiteL;

	void setup() {
		leaves.setRadius(200);
		trunk.setHeight(300);
		trunk.setRadius(75);
		stalagmiteL.setRadius(40);
		stalagmiteL.setHeight(600);
		stalagmiteS.setRadius(20);
		stalagmiteS.setHeight(200);
		setupAudio("tree.mp3");
	}
	void draw(Scene scene);
	float getDefaultZ() {
		return GROUND_DEPTH - trunk.getHeight() / 2;
	}
	void updateVolume(float globalGain) {
		player.setVolume(globalGain * 300 / abs(positionY));
	}
};

class Grass : public GraphicObj {
public:
	ofConePrimitive blade;

	void setup() {
		blade.setRadius(10);
		blade.setHeight(100);
	}
	void draw(Scene scene);
	float getDefaultZ() {
		return GROUND_DEPTH - blade.getHeight() / 2;
	}
	void updateVolume(float globalGain) {};
};

class Pond : public GraphicObj {
public:
	float length = 1000;
	float width = 400;
	float sandWidth = 75;
	void draw(Scene scene);
	void setup() {
		setupAudio("lake.mp3");
	}
	float getDefaultZ() {
		return GROUND_DEPTH - 1;
	}
	void updateVolume(float globalGain) {
		player.setVolume(globalGain * 300 / abs(positionY));
	}
};

class Bird : public GraphicObj {
public:
	float wingRotation = -20;
	float wingRotGen = 0;
	ofBoxPrimitive wing;
	ofBoxPrimitive body;
	void setup() {
		wing.setDepth(30);
		wing.setWidth(75);
		wing.setHeight(5);
		body.setDepth(30);
		body.setWidth(30);
		body.setHeight(5);
		setupAudio("seagull.mp3");
	}
	void draw(Scene scene);
	float getDefaultZ() {
		return -700;
	}
	void timestep(float userSpeed, float userX, float userY, Scene scene) override {
		if (scene == Cave) {
			GraphicObj::timestep(3* userSpeed, userX, userY);
			wingRotGen += 0.01 * userSpeed * userSpeed * userSpeed * 5;
			wingRotation = 35 * sin(wingRotGen) - 55;
		} else {
			GraphicObj::timestep(userSpeed, userX, userY);
			wingRotGen += 0.01 * userSpeed * userSpeed * userSpeed;
			wingRotation = 35 * sin(wingRotGen) - 55;
		}
	}
	void updateVolume(float globalGain) {
		player.setVolume(globalGain * 800 / abs(positionY));
	}
};