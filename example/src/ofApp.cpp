#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

void ofApp::openHelpBoxWindow() {
	ofGLFWWindowSettings settings;

	settings.width = 1000;
	settings.height = 1400;
	settings.setPosition(ofVec2f(900, 100));
	settings.resizable = false;
	shared_ptr<ofAppBaseWindow> helpBoxWindow = ofCreateWindow(settings);

	shared_ptr<HelpBoxApp> helpBoxApp(new HelpBoxApp("helpBox\\exampleText.txt", "helpBox\\Arial Unicode.ttf", 30, settings.width, settings.height));

	ofRunApp(helpBoxWindow, helpBoxApp);
	ofRunMainLoop();

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDrawBitmapString("Frame rate: " + ofToString(ofGetFrameRate()), ofGetWidth() - 138, ofGetHeight() - 14);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'h':
		openHelpBoxWindow();
		break;
	default: break;
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
