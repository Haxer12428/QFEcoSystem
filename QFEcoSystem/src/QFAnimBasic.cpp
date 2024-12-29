#include "QFAnim.h"
#include <iostream>

namespace chrono = std::chrono;
using ccl = chrono::high_resolution_clock;

/* Max delta time used for clamp */
constexpr const float _qfAnimBasicMaxDeltaTime = 1.0f;

namespace qfAnim {
	/* Constructor & Destructors */
	Basic::Basic() = default; 
	Basic::~Basic() = default;	 

	/* Set cache operators */
	const bool Basic::setCache(
		const chrono::milliseconds& _FinishIn, const std::vector<float>& _Start, const std::vector<float>& _End, bool _AutoStart
		) {
		const bool vecSizeMatch = (_Start.size() == _End.size());
		_qfAssert(vecSizeMatch, "Condition must be met: _Start == _End");
		
		if (!vecSizeMatch) return false; 

		m_FinishIn = _FinishIn;
		m_CacheStarting = _Start; 
		m_CacheWanted = _End; 
		m_Cache = _Start;

		/* Autostart */
		if (!_AutoStart) return true; 
		Start();

		return true; 
	}

	void Basic::setAnimMethod(const std::function<float(float, float, float)>& _Method) {
		m_AnimMethod = _Method;
	}

	/* Checks */
	const bool Basic::isFinished() const {
		return getTimeDelta() >= _qfAnimBasicMaxDeltaTime;
	}

	/* Start */
	void Basic::Start() {
		m_CacheStartedTime = ccl::now();
	}
	/* Anim */
	std::vector<float>& Basic::animCache() {
		animUsingAMethod(m_AnimMethod);

		return m_Cache;
	}

	float Basic::getTimeDelta() const {
		chrono::milliseconds timeSinceStart = chrono::duration_cast<chrono::milliseconds>(
			ccl::now() - m_CacheStartedTime);

		float timeDelta = (static_cast<float>(timeSinceStart.count()) / static_cast<float>(m_FinishIn.count()));
		timeDelta = std::clamp(timeDelta, 0.0f, _qfAnimBasicMaxDeltaTime);

		return timeDelta;
	}

	void Basic::animUsingAMethod(std::function<float(float, float, float)>& _Method) {
		_qfAssert(m_AnimMethod, "Cannot proceed without anim method");
		const float deltaTime = getTimeDelta();

		/* Anim for all elements of cache */
		for (size_t _It = 0; _It < m_Cache.size(); _It++) {
			float starting = m_CacheStarting[_It];
			float end = m_CacheWanted[_It];
			/* Use method */
			m_Cache[_It] = _Method(starting, end, deltaTime);
		}
	}
	

}