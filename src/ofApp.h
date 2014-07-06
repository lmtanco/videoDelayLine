#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include <boost/circular_buffer.hpp>

class ofApp : public ofBaseApp{
	
	public:

		ofApp(int initial_buffer_capacity, int max_buffer_capacity, int _camWidth, int _camHeight, int _desiredFrameRate);
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

		void setupVideo();
		void setupGui();

		void delayChanged(int &);
		void drawMessage(const string & msg, bool feedbacktime);

		ofVideoGrabber 					vidGrabber;
		boost::circular_buffer<ofImage>	buffer;
		int initial_buffer_capacity;
		int 							camWidth;
		int 							camHeight;
		int								videoWidth;
		int								videoHeight;
		ofxIntSlider					delay;
		ofxLabel						fps;
		ofxPanel						gui;
		ofTrueTypeFont					verdana30;
		int desiredFrameRate;

};
