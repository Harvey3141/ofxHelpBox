#pragma once

#include "ofMain.h"
#include "ofxFontStash.h"
#include "ofxXmlSettings.h"

struct Page {
	int lineStart;
	int lineEnd;
};

class HelpBoxApp: public ofBaseApp{
public:
	// Paths should be relative to the data folder, font MUST be .ttf
	HelpBoxApp(string _pathTxtFile, string _pathFont);
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

	void generatePages();
	void loadPage(int page);

	bool loadSettings(string settingsPath, int expectedSize);
	void saveSettings(string settingsPath, int size);

	int currentPage;

	bool stringFitsFbo(string s, ofRectangle column, ofFbo textFbo, int fontSize, int x, int y, int numLines, bool wordsWereCropped);
	void drawStringToFbo (string s, ofRectangle column, ofFbo textFbo, int fontSize, int x, int y, int numLines, bool wordsWereCropped);

	ofxFontStash unicodeFont;

	string pathTxtFile;
	string pathSettingsFile;

	string text;
	ofBuffer textBuf;
	ofFbo textFbo;
	int textFboYpos;
	int currentLine; // which line of the text do we start with when drawing to the fbo

	vector <Page> pages;

	float lineHeight;
	float x;
	float y;
	float fontSize;

	int numLines;
	bool wordsWereCropped;
	ofRectangle column;

	vector <string> linesOfTheFile;
};
