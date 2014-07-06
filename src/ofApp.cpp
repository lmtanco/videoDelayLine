#include "ofApp.h"
#include <iostream>
static unsigned long long timeThen = 0;
static unsigned long long timeNow = 0;
static bool FirstTime = true;
static double framesPerSecond = 0;

//--------------------------------------------------------------
ofApp::ofApp(int _initial_buffer_capacity, int max_buffer_capacity, int _camWidth, int _camHeight, int _desiredFrameRate) :
	buffer(max_buffer_capacity),
	initial_buffer_capacity(_initial_buffer_capacity),
	camWidth(_camWidth),
	camHeight(_camHeight),
	videoWidth(ofGetWidth()*_camHeight/_camWidth),
	videoHeight(ofGetHeight()),
	desiredFrameRate(_desiredFrameRate)

{
	// Capacity of buffer is _initial_capacity
	// Size is however 0 (no images in the buffer yet)
}


void ofApp::setup(){
	//ofSetFrameRate(desiredFrameRate);
	setupVideo();
	setupGui();
}


void ofApp::setupVideo()
{

	//we can now get back a list of devices. 
	vector<ofVideoDevice> devices = vidGrabber.listDevices();

	for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName; 
		if( devices[i].bAvailable ){
			cout << endl;
		}else{
			cout << " - unavailable " << endl; 
		}
	}

	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(desiredFrameRate);
	vidGrabber.initGrabber(camWidth,camHeight);
	ofSetVerticalSync(true);
}

void ofApp::setupGui()
{
	// Botones
	delay.addListener(this, &ofApp::delayChanged);
	gui.setup();
	gui.setBackgroundColor(ofColor::darkMagenta);
	gui.setDefaultWidth(240);
	gui.add(delay.setup("delay",initial_buffer_capacity,1,buffer.capacity()));
	gui.add(fps.setup("frames p. segundo", ""));

	// Texto
	ofTrueTypeFont::setGlobalDpi(72);
	verdana30.loadFont("verdana.ttf", 30, true, true);
	verdana30.setLineHeight(34.0f);
	verdana30.setLetterSpacing(1.035);

}

void ofApp::delayChanged(int & _delay)
{
	static bool firstime = true;
	std::cout << "************* new delay: " << _delay << endl;; 

	// Do I want rset_capacity or set_capacity?
	if (firstime) {
		buffer.set_capacity(initial_buffer_capacity);
		firstime= false;
	}
	else { 
		buffer.set_capacity(_delay);
	}

	std::cout << "************* buffer.size: " << buffer.size() << endl
			  << "************* buffer.capacity: " << buffer.capacity() << endl; 
}

//--------------------------------------------------------------
void ofApp::update(){
	
	ofBackground(50,50,50);
	vidGrabber.update();
	
	if (vidGrabber.isFrameNew()){
			ofImage image; 
			image.setFromPixels(vidGrabber.getPixels(), camWidth, camHeight, OF_IMAGE_COLOR);
			buffer.push_back(image);
			if (FirstTime)
			{
				timeThen = ofGetSystemTime();
				FirstTime = false;
				framesPerSecond = 10; // Best guess...will improve later.
			}
			else
			{
				timeNow = ofGetSystemTime();
				unsigned long long deltaTime = timeNow - timeThen;
				timeThen = timeNow;
				framesPerSecond = framesPerSecond*0.99 + (1000.0/deltaTime)*0.01; 
			}
			fps = ofToString(framesPerSecond);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.draw();
		// Only start drawing if buffer is full;
	if (buffer.size() < buffer.capacity()) {
		string msg = "Espera, estoy capturando...";
//		float queda = (buffer.capacity() - buffer.size());
		ofRectangle rect = verdana30.getStringBoundingBox(msg,0,0);
		verdana30.drawString(msg /* + ofToString(queda,0)*/, ofGetWidth()/2 - rect.width/2,ofGetHeight()/2- rect.height);
	}
	else {
		ofScale(-1.0,1.0);
		ofTranslate(-ofGetWidth(),0);
		buffer.front().draw(0,0,videoWidth,videoHeight);
	}
}

void ofApp::drawMessage(const string& msg, bool feedbacktime)
{
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	// Video settings no longer works in 10.7
	// You'll need to compile with the 10.6 SDK for this
    // For Xcode 4.4 and greater, see this forum post on instructions on installing the SDK
    // http://forum.openframeworks.cc/index.php?topic=10343        
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
