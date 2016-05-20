#include "ofMain.h"
#include "ofApp.h"
#include "Helpbox.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
	ofGLFWWindowSettings settings;

	settings.width = 600;
	settings.height = 600;
	settings.setPosition(ofVec2f(300, 100));
	settings.resizable = true;
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
	shared_ptr<ofApp> mainApp(new ofApp);

	//settings.width = 1000;
	//settings.height = 1400;
	//settings.setPosition(ofVec2f(900, 100));
	//settings.resizable = false;
	//shared_ptr<ofAppBaseWindow> helpBoxWindow = ofCreateWindow(settings);
	//shared_ptr<HelpBoxApp> helpBoxApp(new HelpBoxApp("helpBox\\exampleText.txt", "helpBox\\Arial Unicode.ttf"));
	//
	//ofRunApp(helpBoxWindow, helpBoxApp);
	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();

}
