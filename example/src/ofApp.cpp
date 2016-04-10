#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	this->astra.open();
	this->astra.initColor();
	//this->astra.initInfrared(); //only the color OR the infrared can be enabled (not both)
	this->astra.initDepth();
	this->astra.initPoints();
}

//--------------------------------------------------------------
void ofApp::update(){
	this->astra.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	this->astra.getColor()->draw(0, 0);
	//this->astra.getInfrared()->draw(0, 0);
	this->astra.getDepth()->draw(640, 0);
	this->astra.getPoints()->draw(640, 480);
	ofDrawBitmapStringHighlight("Application : " + ofToString(ofGetFrameRate()) + "fps", 10, 30);
	ofDrawBitmapStringHighlight("Device : " + ofToString(this->astra.getFrameRate()) + "fps", 10, 60);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
