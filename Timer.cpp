#pragma once
#include <ctime>

class Timer
{
	
	std::clock_t start;
	double duration;

public:

	Timer() {};
	

	void Start() {
	// Get new start time
		start = std::clock();
	
	};

	double Current() {
    duration =  ((std::clock() - start) / (double)CLOCKS_PER_SEC);
	return duration;
	
	};

};



