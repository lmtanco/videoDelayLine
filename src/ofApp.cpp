#include "ofApp.h"
#include <iostream>
static uint64_t timeThen = 0;
static uint64_t timeNow = 0;
static bool FirstTime = true;
static double framesPerSecond = 0;

//--------------------------------------------------------------
ofApp::ofApp(int _initial_buffer_capacity, int max_buffer_capacity, int _camWidth, int _camHeight, int _desiredFrameRate) :
	buffer(max_buffer_capacity),
	initial_buffer_capacity(_initial_buffer_capacity),
	camWidth(_camWidth),
	camHeight(_camHeight),
	//videoWidth(ofGetWidth()*_camHeight/_camWidth),
    videoWidth(_camWidth),
	//videoHeight(ofGetHeight()),
    videoHeight(_camHeight),
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

	for(int unsigned i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName; 
		if( devices[i].bAvailable ){
			cout << endl;
            for (auto itf : devices[i].formats)
            {
                cout << "FORMAT: (" << itf.width << "," << itf.height << ")" << endl;
                cout << "--- framerates: ";
                for (auto itr: itf.framerates)
                {
                    cout << itr << ", ";
                }
                cout << endl;
            }
		}else{
			cout << " - unavailable " << endl; 
		}
	}

	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(desiredFrameRate);
	//vidGrabber.initGrabber(camWidth,camHeight);
	vidGrabber.setup(camWidth, camHeight);
	ofSetVerticalSync(true);
}

void ofApp::setupGui()
{
	// Botones
	delay.addListener(this, &ofApp::delayChanged);
    gui.setup("EL RETROESPEJO (UMA)",ofxPanelDefaultFilename,10,0);
	gui.setBackgroundColor(ofColor::darkMagenta);
	gui.setDefaultWidth(ofGetWidth()-10);
    gui.add(delay.set("retardo (segundos): ",
                        (float)initial_buffer_capacity/desiredFrameRate,
                        1.0,
                        (float)buffer.capacity()/desiredFrameRate));
	gui.add(fps.setup("fps", ""));

	// Texto
	ofTrueTypeFont::setGlobalDpi(72);
	verdana30.load("verdana.ttf", 30, true, true);
	verdana30.setLineHeight(34.0f);
	verdana30.setLetterSpacing(1.035);

}

void ofApp::delayChanged(float & _delay)
{
	static bool firstime = true;
	std::cout << "************* new delay(seconds): " << _delay << endl;
    std::cout << "************* new delay(frames, at supposedly " << desiredFrameRate << "fps): " << _delay * desiredFrameRate << endl;
    std::cout << "************* new delay(frames, at really " << framesPerSecond << "fps): " << _delay * framesPerSecond << endl;

	// Do I want rset_capacity or set_capacity?
	if (firstime) {
		buffer.set_capacity(initial_buffer_capacity);
		firstime= false;
	}
	else {
		buffer.set_capacity((int)(_delay*framesPerSecond));
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
            image.setFromPixels(vidGrabber.getPixels());
			buffer.push_back(image);
			if (FirstTime)
			{
				timeThen = ofGetSystemTimeMillis();
				FirstTime = false;
				framesPerSecond = 10; // Best guess...will improve later.
			}
			else
			{
				timeNow = ofGetSystemTimeMillis();
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
		if (verdana30.isLoaded()) {
		ofRectangle rect = verdana30.getStringBoundingBox(msg, 0, 0);
		verdana30.drawString(msg /* + ofToString(queda,0)*/, ofGetWidth() / 2 - rect.width / 2, ofGetHeight() / 2 - rect.height);
	}
	}
	else {
        double scale = (double)ofGetHeight() / videoHeight;
		ofScale(-scale,scale);
		ofTranslate(-ofGetWidth()/(double)scale,0.667*gui.getHeight()/((double)scale));
		buffer.front().draw(0,0,videoWidth,videoHeight);
	}
}

void ofApp::drawMessage(const string& msg, bool feedbacktime)
{
}

//--------------------------------------------------------------
void ofApp::keyPressed  (ofKeyEventArgs & e){
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	// Video settings no longer works in 10.7
	// You'll need to compile with the 10.6 SDK for this
    // For Xcode 4.4 and greater, see this forum post on instructions on installing the SDK
    // http://forum.openframeworks.cc/index.php?topic=10343        
	if (e.key == 's' || e.key == 'S'){
		vidGrabber.videoSettings();
	}
    else if ('1' <= e.key && e.key <= '9')
    {
        float d = e.key - '0';
        delay = d;
    }
    else if (e.key == OF_KEY_UP || e.key == '+') delay++;
    else if (e.key == OF_KEY_DOWN || e.key == '-') delay--;
	
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
