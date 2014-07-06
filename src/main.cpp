#include "ofMain.h"
#include "ofApp.h"

const int initial_buffer_capacity = 500;
const int max_buffer_capacity = 1000;
const int captureWidth = 640;
const int captureHeight = 480;
const int desiredFrameRate = 50;


//========================================================================
int main( ){

#ifndef NDEBUG
	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context
#else
	ofSetupOpenGL(1024,768,OF_FULLSCREEN); // w and h are ignored
#endif
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( 
		new ofApp(initial_buffer_capacity, 
		max_buffer_capacity, 
		captureWidth, 
		captureHeight, 
		desiredFrameRate)
		);

}
