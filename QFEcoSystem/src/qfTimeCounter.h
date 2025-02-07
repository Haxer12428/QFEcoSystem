#pragma once
#include <chrono>

class qfTimeCounter {
public:
	qfTimeCounter(); 
	~qfTimeCounter();

	void fromThisMoment();
	std::chrono::milliseconds getMsPassed();

	float getCyclesPerSecond();
private:
	std::chrono::high_resolution_clock::time_point m_Start;
};