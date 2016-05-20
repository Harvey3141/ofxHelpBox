#include "HelpBox.h"

HelpBoxApp::HelpBoxApp(string _pathTxtFile, string _pathFont) {

	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
	ofSetFrameRate(60); // TODO - framerate should be independent of ofMain, separate thread
	ofBackground(22, 22, 22, 255);

	pathTxtFile = _pathTxtFile;

	// TODO - currently this will only work for text files with a 3 character file extension! 
	pathSettingsFile = pathTxtFile.substr(0, pathTxtFile.size() - 4) + "_settings.txt";

	// Load font
	ofFile fontFileTest;
	if (!fontFileTest.doesFileExist(_pathFont, true)) {
		cout << "[error] Helpbox - can't find font at path: " << ofToDataPath(_pathFont) << " closing helpbox window" << endl;
		return;
		// TODO - close window here
	}

	unicodeFont.setup(_pathFont,			//font file, ttf only
		1.0,								//lineheight percent
		1024,								//texture atlas dimension
		true,								//create mipmaps of the font, useful to scale down the font at smaller sizes
		8,									//texture atlas element padding, shouldbe >0 if using mipmaps otherwise
		2.0f								//dpi scaleup, render textures @2x the reso
		);									//lower res mipmaps wil bleed into each other


	lineHeight = 2;
	unicodeFont.setLineHeight(lineHeight);
	x = 30;
	y = 40;
	fontSize = 28;
	numLines = 0;
	wordsWereCropped = false;
	textFboYpos = 0;

	// Load text file 
	ofFile textFileTest;
	if (!textFileTest.doesFileExist(pathTxtFile, true)) {
		cout << "[error] Helpbox - can't fine text file at path: " << ofToDataPath(pathTxtFile) << " closing helpbox window" << endl;
		return;
		// TODO - close window here
	} 

	textBuf = ofBufferFromFile(ofToDataPath(pathTxtFile));
	for (auto line : textBuf.getLines()) {
		linesOfTheFile.push_back(line);
	}
	cout << "Helpbox - number of lines in the file: " << linesOfTheFile.size() << endl;

	currentPage = 0;

	textFbo.allocate(ofGetWidth(), ofGetHeight());

	// Try and load settings, if the file has not been created OR buffer size has changed then regenerate pages
	if (!loadSettings(pathSettingsFile, textBuf.size()))
		generatePages();

	loadPage(currentPage);
	
}
void HelpBoxApp::setup() {

}

void HelpBoxApp::generatePages() {
	
	int currentLine = 0;
	
	while (currentLine < linesOfTheFile.size()) {
		string s = linesOfTheFile[currentLine];
		Page newPage;
		newPage.lineStart = currentLine;
		newPage.lineEnd = currentLine;

		currentLine += 1;
		
		for (int l = currentLine; l < linesOfTheFile.size(); l++) {

			s += linesOfTheFile[l] + "\n";

			cout << "Helpbox - Current page, start line: " << newPage.lineStart << ", current line: " << l << ", string size: " << s.size() << endl;

			if (stringFitsFbo(s, column, textFbo, fontSize, x, y, numLines, wordsWereCropped)) {
				newPage.lineEnd = l;
				
			}
			else {
				pages.push_back(newPage);
				cout << "Page complete - Start line: " << newPage.lineStart << ", End Line: " << newPage.lineEnd << endl;
				break;
			}

			if (l == linesOfTheFile.size() - 1) {
				pages.push_back(newPage);
				cout << "Page complete - Start line: " << newPage.lineStart << ", End Line: " << newPage.lineEnd << endl;
				cout << "Pages complete - number of pages: " << pages.size() << endl;
				break;
			}
		}

		currentLine = newPage.lineEnd + 1;
	}

	saveSettings(pathSettingsFile,textBuf.size());

}

void HelpBoxApp::loadPage(int page) {
	string s = "";
	for (int p = pages[page].lineStart; p < pages[page].lineEnd; p++) {
		s += linesOfTheFile[p]+"\n";
	}
	drawStringToFbo(s, column, textFbo, fontSize, x, y, numLines, wordsWereCropped);
}

bool HelpBoxApp::stringFitsFbo(string s, ofRectangle column ,ofFbo textFbo, int fontSize, int x, int y, int numLines, bool wordsWereCropped)
{
	bool isFits = false;
	column = unicodeFont.drawMultiLineColumn(s,	/*string*/
		fontSize,								/*size*/
		x, y,									/*where*/
		MAX(10, ofGetWidth() - x),				/*column width*/
		numLines,								/*get back the number of lines*/
		true,									/* if true, we wont draw (just get bbox back) */
		100,									/* max number of lines to draw, crop after that */
		true,									/*get the final text formatting (by adding \n's) in the supplied string;
												BE ARWARE that using TRUE in here will modify your supplied string! */
		&wordsWereCropped						/* this bool will b set to true if the box was to small to fit all text*/
		);

	if (column.getHeight() <= textFbo.getHeight()) isFits = true;
	return isFits;
}

void HelpBoxApp::drawStringToFbo(string s, ofRectangle column, ofFbo textFbo, int fontSize, int x, int y, int numLines, bool wordsWereCropped)
{

	textFbo.begin();
	ofBackground(0);
	ofSetColor(255);
	column = unicodeFont.drawMultiLineColumn(s,	/*string*/
		fontSize,								/*size*/
		x, y,									/*where*/
		MAX(10, ofGetWidth() - x),				/*column width*/
		numLines,								/*get back the number of lines*/
		false,									/* if true, we wont draw (just get bbox back) */
		10000,									/* max number of lines to draw, crop after that */
		true,									/*get the final text formatting (by adding \n's) in the supplied string;
												BE ARWARE that using TRUE in here will modify your supplied string! */
		&wordsWereCropped						/* this bool will b set to true if the box was to small to fit all text*/
		);
	textFbo.end();
}

void HelpBoxApp::update() {
	unicodeFont.setLodBias(ofMap(ofGetMouseX(), 0, ofGetWidth(), -1, 1));
}

void HelpBoxApp::draw() {
	textFbo.draw(0, textFboYpos, textFbo.getWidth(), textFbo.getHeight());
}

bool HelpBoxApp::loadSettings(string settingsPath, int expectedSize) {
	ofxXmlSettings settings;
	if (settings.loadFile(settingsPath)) {
		int size = settings.getValue("settings:bufferSize",0);
		if (textBuf.size() != size) {
			cout << "Helpbox - Textfile buffer size has changed" << endl;
			return false;
		}
		settings.pushTag("pages");
		int numberOfSavedPoints = settings.getNumTags("page");
		for (int i = 0; i < numberOfSavedPoints; i++) {
			settings.pushTag("page", i);

			Page newPage;
			newPage.lineStart = settings.getValue("lineStart", 0);
			newPage.lineEnd	 = settings.getValue("lineEnd", 0);

			pages.push_back(newPage);
			settings.popTag();
		}

		settings.popTag();
	}
	else {
		ofLogError("Helpbox settings file did not load!");
		return false;
	}
	return true;
}

void HelpBoxApp::saveSettings(string settingsPath, int size) {
	ofxXmlSettings settings;
	settings.setValue("settings:bufferSize", size);
	settings.addTag("pages");
	settings.pushTag("pages");

	for (int i = 0; i < pages.size(); i++) {
		settings.addTag("page");
		settings.pushTag("page", i);
		settings.addValue("lineStart", pages[i].lineStart);
		settings.addValue("lineEnd", pages[i].lineEnd);
		settings.popTag();
	}
	settings.popTag();
	settings.saveFile(settingsPath);
}

//--------------------------------------------------------------
void HelpBoxApp::keyPressed(int key) {
	switch (key) {
	case OF_KEY_DOWN:

		currentPage = ofClamp(currentPage + 1, 0, pages.size() - 1);
		loadPage(currentPage);
		break;
	case OF_KEY_UP:

		currentPage = ofClamp(currentPage - 1, 0, pages.size() - 1);
		loadPage(currentPage);
		break;
	default: break;
	}
}