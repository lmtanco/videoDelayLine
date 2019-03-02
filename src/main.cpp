#include "ofMain.h"
#include "ofApp.h"

// TODO: Take these from the command line
const int initial_buffer_capacity = 1;
const int max_buffer_capacity = 1000;
//const int captureWidth = 640;
//const int captureHeight = 480;
const int captureWidth = 1920;
const int captureHeight = 1080;
const int desiredFrameRate = 30;


//========================================================================
int main( ){

//#ifndef NDEBUG
//   ofSetupOpenGL(1024,768, OF_WINDOW);            // <-------- setup the GL context
//#else
	//ofSetupOpenGL(1024,768,OF_FULLSCREEN); // w and h are ignored
	ofSetupOpenGL(1920, 1080, OF_FULLSCREEN); // w and h are ignored
//#endif
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
