#include "qfTimeCounter.h"

qfTimeCounter::qfTimeCounter() {}
qfTimeCounter::~qfTimeCounter() = default; 

void qfTimeCounter::fromThisMoment() {
	m_Start = std::chrono::high_resolution_clock::now();
}

std::chrono::milliseconds qfTimeCounter::getMsPassed() {
	auto timeNow = std::chrono::high_resolution_clock::now();

	std::chrono::milliseconds passedMs = std::chrono::duration_cast<std::chrono::milliseconds>
		(timeNow - m_Start);

	return passedMs;
}

float qfTimeCounter::getCyclesPerSecond() {
	std::chrono::microseconds timePassed			 = std::chrono::duration_cast<std::chrono::microseconds>
		(std::chrono::high_resolution_clock::now() - m_Start);

	constexpr int microSecInSecond						 = 1000 * 1000;

	int timePassedInt = timePassed.count();

	float cyclesPerSec = (
		static_cast<float>(microSecInSecond) / static_cast<float>(timePassedInt)
		);
	
	return cyclesPerSec;
}