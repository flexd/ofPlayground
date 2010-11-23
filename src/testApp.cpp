#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	oldtime = ofGetElapsedTimef();
	objects.push_back(new Object(110, 110, 0, 0));
	ofSetWindowTitle("Hello physics!!");
	arial.loadFont("LiberationSans-Regular.ttf",12);
	if (arial.bLoadedOk) { printf("success loading font!\n"); }
}
double testApp::elapsed_time(){
	double diff;
	newtime = ofGetElapsedTimef();
	diff = double(newtime - oldtime);
	oldtime = ofGetElapsedTimef();
	return diff;
}
void testApp::apply_physics()
{
	double delta = elapsed_time();
	//printf("Delta is: %f\n", delta);
	//printf("ofGetElapsedTimef(): %f\n", ofGetElapsedTimef());
	for (list<Object*>::iterator oi = objects.begin(); oi != objects.end(); oi++) {
		Object* o = *oi;
		//printf("x: %i, y: %i x_vel: %f, y-vel: %f\n", o->x(), o->y(), o->_x_velocity, o->_y_velocity);
		o->move(delta);
	}
}

void testApp::walls() {
  for (list<Object*>::iterator oi = objects.begin(); oi != objects.end(); oi++) {
		Object* o = *oi;
    int x = o->x();
    int y = o->y();
    if (!ofInRange(x, 0, ofGetWidth())) {
      o->reverse_x_vel();
		}
		if (!ofInRange(y,0, ofGetHeight()-200)) {
			o->reverse_y_vel();
			//delete o;
      //oi = objects->erase(oi);
    }  
		if (oi == objects.end()) break;
  }
}
void testApp::draw_objects() {
	for (list<Object*>::iterator oi = objects.begin(); oi != objects.end(); oi++) {
		Object* o = *oi;
		ofSetColor(255, 0, 0);
		ofFill();
		ofCircle(o->x(), o->y(), 25);
		char infoString[255];
		sprintf(infoString,"x: %i, y: %i, x speed: %f y speed: %f", o->x(), o->y(), o->_x_velocity, o->_y_velocity);
		arial.drawString(infoString, o->x()+40, o->y());
	}
}
void testApp::draw_ground() {
	int y = ofGetHeight()-200;
	ofSetColor(200, 100, 0);
	ofLine(0, y, ofGetWidth(), y);
}
//--------------------------------------------------------------
void testApp::update(){
	walls();
	apply_physics();
}

//--------------------------------------------------------------
void testApp::draw(){
	char infoString[255];
	sprintf(infoString,"w: %i h: %i", ofGetWidth(),ofGetHeight());
	arial.drawString(infoString, 20, 20);
	draw_objects();
	draw_ground();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == OF_KEY_UP) {
		for (list<Object*>::iterator oi = objects.begin(); oi != objects.end(); oi++) {
			Object* o = *oi;
			o->_y_velocity -= 1;
		}
		
	}
	if (key == OF_KEY_DOWN) {
		for (list<Object*>::iterator oi = objects.begin(); oi != objects.end(); oi++) {
			Object* o = *oi;
			o->_y_velocity += 1;
		}
		
	}
	if (key == OF_KEY_LEFT) {
		for (list<Object*>::iterator oi = objects.begin(); oi != objects.end(); oi++) {
			Object* o = *oi;
			o->_x_velocity -= 1;
		}
		
	}
	if (key == OF_KEY_RIGHT) {
		for (list<Object*>::iterator oi = objects.begin(); oi != objects.end(); oi++) {
			Object* o = *oi;
			o->_x_velocity += 1;
		}
		
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

