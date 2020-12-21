#pragma once
#include <chrono>

class Timer {
public:
	void reset();
	int elapsed();   // in milliseconds
	
	Timer();

private:
	std::chrono::steady_clock::time_point m_point;	
};
