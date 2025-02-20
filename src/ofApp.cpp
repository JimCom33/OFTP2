#include "ofApp.h"
#include <memory>
#include <vector>


// AIDE DE CHATGPT ET NOTES DE COURS


struct Node {
	int data;
	std::shared_ptr<Node> next;
	float posX, posY;
	float size;
	float angle;
};

std::shared_ptr<Node> head;
float startX = 100;
float startY = 300;
float spacing = 100;
float timeElapsed;
float oscMov = 15;
float camOffsetX = 0;
float camSpeed = 20;

void ofApp::insertAtHead(int value) {
    auto newNode = std::make_shared<Node>();
    newNode->data = value;
    newNode->posX = startX;
    newNode->posY = startY;
    newNode->size = 20 + (value % 30);
    newNode->angle = 0.0f;
    newNode->next = head;
    head = newNode;
}

void ofApp::insertAtTail(int value) {
    auto newNode = std::make_shared<Node>();
    newNode->data = value;
    newNode->posX = startX;
    newNode->posY = startY;
    newNode->size = 20 + (value % 30);
    newNode->angle = 0.0f;
    if (!head) {
        head = newNode;
        return;
    }
    auto temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void ofApp::deleteHead() {
    if (head) head = head->next;
}

void ofApp::deleteTail() {
    if (!head) return;
    if (!head->next) {
        head = nullptr;
        return;
    }
    auto temp = head;
    while (temp->next->next) {
        temp = temp->next;
    }
    temp->next = nullptr;
}

void ofApp::updateNodes(float time) {
    float x = startX + camOffsetX;
    auto temp = head;
    while (temp) {
        temp->posX = x;
        temp->posY = startY + oscMov * sin(time + temp->data);
        x += spacing;
        temp = temp->next;
    }
}

void ofApp::drawNodes() {
    auto temp = head;
    while (temp) {
        ofSetColor(255);
        ofDrawCircle(temp->posX, temp->posY, temp->size);
        ofSetColor(0, 0, 0);
        ofDrawBitmapString(ofToString(temp->data), temp->posX - 5, temp->posY + 5);
        ofSetColor(255);
        if (temp->next) {
            ofDrawLine(temp->posX, temp->posY, temp->next->posX, temp->next->posY);
        }
        temp = temp->next;
    }
}
//--------------------------------------------------------------
void ofApp::setup(){
    timeElapsed += ofGetLastFrameTime();
    updateNodes(timeElapsed);
}

//--------------------------------------------------------------
void ofApp::update(){
    timeElapsed += ofGetLastFrameTime();
    updateNodes(timeElapsed);
}

//--------------------------------------------------------------
void ofApp::draw(){
    drawNodes();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'q') insertAtHead(ofRandom(10, 100));
    if (key == 'w') insertAtTail(ofRandom(10, 100));
    if (key == 'a') deleteHead();
    if (key == 's') deleteTail();
    if (key == 'z') oscMov += 2;
    if (key == 'x') oscMov -= 2;
    if (key == OF_KEY_LEFT) camOffsetX += camSpeed;
    if (key == OF_KEY_RIGHT) camOffsetX -= camSpeed;
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
