#include "QFIDManager.h"

qfIdManager::qfIdManager(uint64_t _StartingId) :
	m_LastId{ _StartingId } {};

uint64_t qfIdManager::generate() {
	const uint64_t generatedId = (m_LastId);
	m_LastId++;
	return generatedId; 
}