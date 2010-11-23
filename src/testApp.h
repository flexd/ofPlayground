#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include <list>
class Object {
	public:
		Object(int x, int y, double x_velocity, double y_velocity) {
			_x = x;
			_y = y;
			_x_velocity = x_velocity;
			_y_velocity = y_velocity;
		}
		int x() { return (int)_x; }
		int y() { return (int)_y; }
		int setY(int y) { _y = (int)y; }
		int reverse_x_vel() { _x_velocity = _x_velocity * -1; }
		int reverse_y_vel() { _y_velocity = _y_velocity * -1; }
		void move(double time_delta) {
			_x += time_delta * _x_velocity * 2.25;
			_y += time_delta * _y_velocity * 2.25;
		}
		double _x, _y;
		double _x_velocity;
		double _y_velocity;
};
class testApp : public ofBaseApp{
	float newtime, oldtime;
	list <Object*> objects;
	ofTrueTypeFont arial;
	
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
