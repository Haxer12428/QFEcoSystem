#pragma once
#include <cstdint>


class qfIdManager {
public:
	qfIdManager(uint64_t _StartingId = 0);
	virtual ~qfIdManager() = default;

	uint64_t generate();
private:
	uint64_t m_LastId; 
};
