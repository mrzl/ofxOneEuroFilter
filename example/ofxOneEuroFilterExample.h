#pragma once

#include "ofMain.h"
#include "ofxOneEuroFilter.h"

class ofxOneEuroFilterExample : public ofBaseApp {
public:

	ofxOneEuroFilter oneEuroFilterX, oneEuroFilterY;
	double valueX, valueY;
	void setup() {
		oneEuroFilterX.setup( 120, 3.0, 0.007, 1.0 );
		oneEuroFilterY.setup( 120, 3.0, 0.007, 1.0 );
	}

	void update() {
		valueX = oneEuroFilterX.filter( ofGetMouseX() );
		valueY = oneEuroFilterY.filter( ofGetMouseY() );
	}

	void draw() {
		ofBackground( 0 );
		ofSetColor( 255 );
		ofDrawCircle( ofGetMouseX(), ofGetMouseY(), 10 );
		ofSetColor( 0, 255, 0 );
		ofDrawCircle( valueX, valueY, 10 );
	}
};


int main() {
	ofSetupOpenGL( 800, 800, OF_WINDOW );
	ofRunApp( new ofxOneEuroFilterExample() );
}
