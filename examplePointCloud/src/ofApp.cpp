#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	this->astra.open();
	this->astra.initPoints();

	this->camera.setPosition(2000, 1000, 0);
	this->camera.lookAt(ofVec3f(0, 0, 3000));
}

//--------------------------------------------------------------
void ofApp::update() {
	this->astra.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(40, 0);

	this->camera.begin();
	{
		ofDrawGrid(1000.0f, 10, true, false);
		this->astra.getPoints()->getMesh().drawVertices();
	}
	this->camera.end();

	ofDrawBitmapStringHighlight("Application : " + ofToString(ofGetFrameRate()) + "fps", 20, 30);
	ofDrawBitmapStringHighlight("Device : " + ofToString(this->astra.getFrameRate()) + "fps", 20, 60);
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
