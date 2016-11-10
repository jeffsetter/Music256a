#pragma once

#include "ofMain.h"

class GraphicObj {
public:
	float distance;
	void setup() {};
	void draw() {};
};

class Cloud : public GraphicObj {
public:
	ofSpherePrimitive spheres[7];

	void setup() {
		for (int i = 0; i < 7; i++) {
			spheres[i].setRadius(150);
		}
		//spheres[0].setRadius(100);
		//spheres[5].setRadius(100);
	}
	void draw();
};

class Tree : public GraphicObj {
public:
	ofSpherePrimitive leaves;
	ofCylinderPrimitive trunk;

	void setup() {
		leaves.setRadius(200);
		trunk.setHeight(300);
		trunk.setRadius(75);
	}
	void draw();
};

class Grass : public GraphicObj {
public:
	ofConePrimitive blade;

	void setup() {
		blade.setRadius(10);
		blade.setHeight(100);
	}
	void draw();
};

class Pond : public GraphicObj {
public:
	float length = 1000;
	float width = 400;
	float sandWidth = 75;
	void draw();
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
	}
	void draw();
};