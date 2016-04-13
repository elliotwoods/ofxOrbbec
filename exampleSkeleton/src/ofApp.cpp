#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	this->astra.open();
	this->astra.initDepth();
	this->astra.initPoints();
	this->astra.initSkeleton();
}

//--------------------------------------------------------------
void ofApp::update(){
	this->astra.update();
	if (this->astra.isFrameNew()) {
		{
			auto pixels = this->astra.getSkeleton()->getUserMask();
			for (auto & pixel : pixels) {
				pixel *= 255;
			}
			this->userMask.loadData(pixels);
		}
		{
			auto pixels = this->astra.getSkeleton()->getLabelsImage();
			for (auto & pixel : pixels) {
				pixel *= 16;
			}
			this->labels.loadData(pixels);
		}
		{
			this->probability.loadData(this->astra.getSkeleton()->getProbabilityMap(labelIndex));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (this->userMask.isAllocated()) {
		this->userMask.draw(0, 0);
	}
	if (this->labels.isAllocated()) {
		this->labels.draw(640, 0);
	}

	ofPushStyle();
	{
		ofSetLineWidth(3.0f);
		ofSetColor(0);
		this->astra.getSkeleton()->drawSkeleton2D();

		ofSetLineWidth(1.0f);
		ofSetColor(255);
		this->astra.getSkeleton()->drawSkeleton2D();
	}
	ofPopStyle();

	this->astra.getPoints()->draw(0, 480);
	this->probability.draw(640, 480, 640, 480); // this map is actually at a reduced size
	ofDrawBitmapStringHighlight("Application : " + ofToString(ofGetFrameRate()) + "fps", 650, 500);
	ofDrawBitmapStringHighlight("Device : " + ofToString(this->astra.getFrameRate()) + "fps", 650, 530);
	ofDrawBitmapStringHighlight("Showing probability field for label : " + ofToString(this->labelIndex), 650, 560);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	this->labelIndex = float(x) / ofGetWidth() * 20.0f;
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
