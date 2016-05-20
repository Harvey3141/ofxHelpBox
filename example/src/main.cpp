#include "ofMain.h"
#include "ofApp.h"
#include "ofxHelpbox.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
	
	
	ofSetupOpenGL(1024, 768, OF_WINDOW);			// <-------- setup the GL context
	
													// this kicks off the running of my app
													// can be OF_WINDOW or OF_FULLSCREEN
													// pass in width and height too:
	ofRunApp(new ofApp());
	
	//ofGLFWWindowSettings settings;
	//
	//settings.width = 600;
	//settings.height = 600;
	//settings.setPosition(ofVec2f(300, 100));
	//settings.resizable = true;
	//shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
	//shared_ptr<ofApp> mainApp(new ofApp);
	//
	//ofRunApp(mainWindow, mainApp);
	//ofRunMainLoop();

}
