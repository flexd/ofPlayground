#include "testApp.h"
//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(30);
	//oldtime = ofGetElapsedTimef();
	objects.push_back(new Object(110, 110, 0, 0, 1));
	ofSetWindowTitle("Hello physics!!");
	arial.loadFont("LiberationSans-Regular.ttf",12);
	// world box/borders.
	boxArray[1].min.x = 100; 
	boxArray[1].max.x = 500;
	boxArray[1].min.y = 100;
	boxArray[1].max.y = 500;
	t = 0.0;
}
double testApp::elapsed_time(){
	double diff;
	newtime = ofGetElapsedTimef();
	diff = double(newtime - oldtime);
	oldtime = ofGetElapsedTimef();
	return diff;
}
struct State {
	float x, y; // position
	float v; // velocity
};
struct Derivative {
	float dx, dy; // derivative of position: velocity
	float dv; // derivative of velocity: acceleration
};
float acceleration(const State &state, float t)
{
	const float k = 10;
	const float b = 1;
	return -k * state.x - b*state.v;
}
Derivative evaluate(const State &initial, float t, float dt, const Derivative &d)
{
	State state;
	state.x = initial.x + d.dx*dt;
	state.v = initial.v + d.dv*dt;
	
	Derivative output;
	output.dx = state.v;
	output.dv = acceleration(state, t+dt);
	return output;
}

void integrate(State &state, float t, float dt)
{
	Derivative a = evaluate(state, t, 0.0f, Derivative());
	Derivative b = evaluate(state, t+dt*0.5f, dt*0.5f, a);
	Derivative c = evaluate(state, t+dt*0.5f, dt*0.5f, b);
	Derivative d = evaluate(state, t+dt, dt, c);
	
	const float dxdt = 1.0f/6.0f * (a.dx + 2.0f*(b.dx + c.dx) + d.dx);
	const float dvdt = 1.0f/6.0f * (a.dv + 2.0f*(b.dv + c.dv) + d.dv);
	
	state.x = state.x + dxdt * dt;
	state.v = state.v + dvdt * dt;
}
void testApp::apply_physics()
{
	double delta = elapsed_time();
	//printf("Delta is: %f\n", delta);
	//printf("ofGetElapsedTimef(): %f\n", ofGetElapsedTimef());
	for (list<Object*>::iterator oi = objects.begin(); oi != objects.end(); oi++) {
		Object* o = *oi;
		State state;
		integrate(state, t, delta);
		t += delta;
		
		
		// basic euler integration for x and y, silly ! TODO: Understand and implement RK4.
		//o->force = 9.81*o->mass; // it's gravity bitches! TODO: implement air resistance to enable objects having maximum falling speeds.
		//o->_x = o->_x + o->_xv * delta;
		//o->_xv = o->_xv + (o->force_x()/o->mass) * delta;
		//o->pos.y = o->pos.y + o->vel.y * delta;
		//o->vel.y = o->vel.y + (o->force/o->mass) * delta;
		//printf("x: %i, y: %i x_vel: %f, y-vel: %f\n", o->x(), o->y(), o->_x_velocity, o->_y_velocity);
		//o->_yv = o->_yv + 9.81;
		//o->move(delta);
		
	}
}

void testApp::walls() {
  for (list<Object*>::iterator oi = objects.begin(); oi != objects.end(); oi++) {
		Object* o = *oi;
    
		if (o->x() < boxArray[1].max.x && o->x() > boxArray[1].min.x && o->y() < boxArray[1].max.y && o->y() > boxArray[1].min.y) {
			o->binWorld = true;
		}
		else {
			o->binWorld = false;
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
		
		o->info(arial);
	}
}
void testApp::draw_ground() {
	//int y = ofGetHeight()-200;
	ofSetColor(200, 100, 0);
	//ofLine(0, y, ofGetWidth(), y);
}
//--------------------------------------------------------------
void testApp::update(){
	walls();
	apply_physics();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofRect(boxArray[1].min.x,boxArray[1].min.y,400,400);
	ofSetColor(0,0,0);
	char infoString[255];
	sprintf(infoString,"w: %i h: %i fps: %f", ofGetWidth(),ofGetHeight(), ofGetFrameRate());
	arial.drawString(infoString, 20, 20);
	draw_objects();
	draw_ground();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == OF_KEY_UP) {
		for (list<Object*>::iterator oi = objects.begin(); oi != objects.end(); oi++) {
			Object* o = *oi;
			o->force -= 5;
		}
		
	}
	if (key == OF_KEY_DOWN) {
		for (list<Object*>::iterator oi = objects.begin(); oi != objects.end(); oi++) {
			Object* o = *oi;
			o->force += 5;
		}
		
	}
	if (key == OF_KEY_LEFT) {
		for (list<Object*>::iterator oi = objects.begin(); oi != objects.end(); oi++) {
			Object* o = *oi;
			o->fangle -= 1;
		}
		
	}
	if (key == OF_KEY_RIGHT) {
		for (list<Object*>::iterator oi = objects.begin(); oi != objects.end(); oi++) {
			Object* o = *oi;
			o->fangle += 1;
		}
	if (key == 'r') {
		for (list<Object*>::iterator oi = objects.begin(); oi != objects.end(); oi++) {
			Object* o = *oi;
			o->pos.x = 50;
			o->pos.y = 50;
		}
	}	
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	char infoString[255];
	sprintf(infoString,"mouse x: %i, y: %i", x, y);
	arial.drawString(infoString, x, y);
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

