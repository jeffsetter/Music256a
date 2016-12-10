#include "objects.h"

void Cloud::draw(Scene scene) {
	ofPushMatrix();
	ofPushStyle();
	if (scene == Cave) {
		ofSetColor(92, 64, 51); // dark brown
		ofTranslate(0, 2000 + CEILING_DEPTH+stalactiteS.getHeight()/2, 0);
		ofRotateX(180);
		stalactiteL.draw();
		ofTranslate(20, 0, 20);
		stalactiteS.draw();
		ofTranslate(-40, 0, 40);
		stalactiteS.draw();
		ofTranslate(-60, 0, -50);
		stalactiteS.draw();
	}
	else {
		if (scene == Forest) {
			ofSetColor(255, 255, 255); // white
		}
		else if (scene == Upsidedown) {
			ofSetColor(80, 80, 80); // dark gray
		}
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
	}

	ofPopStyle();
	ofPopMatrix();
}

void Tree::draw(Scene scene) {
	ofPushMatrix();
	ofPushStyle();

	if (scene == Cave) {
		ofSetColor(92, 64, 51); // dark brown
		ofTranslate(0, trunk.getHeight() / 2, 0);
		stalagmiteL.draw();
		ofTranslate(20, 0, 20);
		stalagmiteS.draw();
		ofTranslate(-40, 0, 40);
		stalagmiteS.draw();
		ofTranslate(-60, 0, -50);
		stalagmiteS.draw();
	}
	else {
		if (scene == Forest) {
			ofSetColor(160, 82, 45); // brown
		} else if (scene == Upsidedown) {
			ofSetColor(60, 22, 5); // dark brown
		}
		trunk.draw();

		if (scene == Forest) {
			ofSetColor(34, 139, 34); // green leaves
		} else if (scene == Upsidedown) {
			ofSetColor(0, 10, 0); // black 
		}
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
	}


	ofPopStyle();
	ofPopMatrix();
}

void Grass::draw(Scene scene) {
	ofPushMatrix();
	ofPushStyle();

	if (scene == Forest) {
		ofSetColor(50, 205, 50); // green
	} else if (scene == Cave) {
		ofSetColor(50, 205, 50); // green
	} else if (scene == Upsidedown) {
		ofSetColor(50, 205, 50); // green
	}
	blade.draw();
	ofTranslate(20, 0, 20);
	blade.draw();
	ofTranslate(-10, 0, 0);
	blade.draw();

	ofPopStyle();
	ofPopMatrix();
}

void Pond::draw(Scene scene) {
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

void Bird::draw(Scene scene) {
	ofPushMatrix();
	ofPushStyle();

	ofPushMatrix();
	if (scene == Forest) {
		ofSetColor(255, 255, 255); // white
	} else if (scene == Cave) {
		ofSetColor(0, 0, 0); // black
	} else if (scene == Upsidedown) {
		ofSetColor(0, 0, 0); // black
	}
	if (scene != Cave) {
		ofRotateZ(55);
		ofTranslate(-body.getWidth() / 2, 0, 0);
		body.draw();
	}
	else {
		ofTranslate(10, 0);
		ofTranslate(-body.getWidth() / 2, 0, 0);
		body.draw();
		ofRotateZ(40);
	}

	ofTranslate(-body.getWidth() / 2, 0, 0);
	ofRotateZ(wingRotation);
	ofTranslate(-wing.getWidth() / 2, 0, 0);
	wing.draw();

	ofPopMatrix();
	if (scene != Cave) {
		ofRotateZ(-55);
		ofTranslate(body.getWidth() / 2, 0, 0);
		body.draw();
	}
	else {
		ofTranslate(-10, 0);
		ofTranslate(body.getWidth() / 2, 0, 0);
		body.draw();
		ofRotateZ(-40);
	}

	ofTranslate(body.getWidth() / 2, 0, 0);
	ofRotateZ(-wingRotation);
	ofTranslate(wing.getWidth() / 2, 0, 0);
	wing.draw();

	ofPopStyle();
	ofPopMatrix();
}