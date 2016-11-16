#include "objects.h"

void Cloud::draw() {
	ofPushMatrix();
	ofPushStyle();

	ofSetColor(255, 255, 255); // white
	ofTranslate(0, 0, -200);
	spheres[0].draw();
	ofTranslate(-50, 25, 100);
	spheres[1].draw();
	ofTranslate(-50, -70, 50);
	spheres[2].draw();
	ofTranslate(-50, 70, 100);
	spheres[3].draw();
	ofTranslate(-50, -25, 100);
	spheres[5].draw();

	ofPopStyle();
	ofPopMatrix();
}

void Tree::draw() {
	ofPushMatrix();
	ofPushStyle();

	ofSetColor(160, 82, 45); // brown
	trunk.draw();

	ofSetColor(34, 139, 34); // green
	ofTranslate(0, -trunk.getHeight(), 0);
	ofTranslate(100, 0, 0);
	leaves.draw();
	ofTranslate(-100, 0, 100);
	leaves.draw();
	ofTranslate(-100, 0, -100);
	leaves.draw();
	ofTranslate(100, 0, -100);
	leaves.draw();
	ofTranslate(0, -100, 100);
	leaves.draw();

	ofPopStyle();
	ofPopMatrix();
}

void Grass::draw() {
	ofPushMatrix();
	ofPushStyle();

	ofSetColor(50, 205, 50); // green
	blade.draw();
	ofTranslate(20, 0, 20);
	blade.draw();
	ofTranslate(-10, 0, 0);
	blade.draw();

	ofPopStyle();
	ofPopMatrix();
}

void Pond::draw() {
	ofPushMatrix();
	ofPushStyle();

	ofRotateX(90);
	ofSetColor(210, 180, 140); // tan
	ofDrawEllipse(0, 0, width + sandWidth, length+sandWidth);
	ofFill();
	ofTranslate(0, 0, 1);
	ofSetColor(0, 0, 255); // blue
	ofDrawEllipse(0, 0, width, length);
	ofFill();

	ofPopStyle();
	ofPopMatrix();
}

void Bird::draw() {
	ofPushMatrix();
	ofPushStyle();

	ofPushMatrix();
	ofSetColor(255, 255, 255); // white
	ofRotateZ(55);
	ofTranslate(-body.getWidth()/2, 0, 0);
	body.draw();
	ofTranslate(-body.getWidth() / 2, 0, 0);
	ofRotateZ(wingRotation);
	ofTranslate(-wing.getWidth() / 2, 0, 0);
	wing.draw();

	ofPopMatrix();
	ofRotateZ(-55);
	ofTranslate(body.getWidth()/2, 0, 0);
	body.draw();
	ofTranslate(body.getWidth() / 2, 0, 0);
	ofRotateZ(-wingRotation);
	ofTranslate(wing.getWidth() / 2, 0, 0);
	wing.draw();

	ofPopStyle();
	ofPopMatrix();
}