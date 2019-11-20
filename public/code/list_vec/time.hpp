#include <chrono>

using namespace std::chrono;

class Time {
	private:
		time_point<high_resolution_clock> startPoint;
		time_point<high_resolution_clock> lastPoint;
		time_point<high_resolution_clock> currentPoint;

	public:
		void start();
		void set();
		long unsigned int diff();
		long unsigned int lastDiff();
};

void Time::start() {
	startPoint = high_resolution_clock::now();
	currentPoint = startPoint;
	lastPoint = startPoint;
}

void Time::set() {
	lastPoint = currentPoint;
	currentPoint = high_resolution_clock::now();
}


long unsigned int Time::diff() {
	return duration_cast<nanoseconds>(currentPoint-startPoint).count()/1000;
}

long unsigned int Time::lastDiff() {
	return duration_cast<nanoseconds>(currentPoint-lastPoint).count()/1000;
}