#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include <list>
struct tVector2 {
	double x, y;
};
struct tForce {
	float force;
	float angle;
};
class Object {
	public:
	Object(int x, int y, double xv, double yv, float _mass) {
		pos.x = x;
		pos.y = y;
		vel.x = xv;
		vel.y = yv;
		mass = _mass;
		force = 0; // set the standard force to 0, this isnt moving yet.
		fangle = 0; // irrelevant at this point
	}
	int reverse_xv() { vel.x = vel.x * -1; }
	int reverse_yv() { vel.y = vel.y * -1; }
	int x() { return floor(pos.x); }
	int y() { return floor(pos.y); }
	void info(ofTrueTypeFont& font){
		char infoString[255];
		sprintf(infoString,"x: %i, y: %i, x speed: %f y speed: %f force: %f fangle: %f in world: %i", x(), y(), vel.x, vel.y, force, fangle,binWorld);
		font.drawString(infoString, pos.x+40, pos.y);
	}
	tVector2 pos;
	tVector2 vel;
	bool binWorld;
	float mass;
	float force;
	float fangle;
};
class testApp : public ofBaseApp{
	float newtime, oldtime; // keep track of elapsed time
	list <Object*> objects; // keep track of objects
	ofTrueTypeFont arial; // one common font to rule them all.
	
	
	struct tBoundingBox {
		tVector2 max;
		tVector2 min;
	};
	tBoundingBox boxArray[1];
	// bounding box for collisions
	bool bAllGood;
	double t;
	public:
		double elapsed_time();
		void setup();
		void update();
		void draw();
		void draw_objects();
		void draw_ground();
		void apply_physics();
		void walls();
		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

};

#endif
