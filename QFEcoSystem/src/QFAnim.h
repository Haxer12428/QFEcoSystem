#pragma once
#define NOMINMAX
#include "QFDefines.h"
#include "QFAssert.h"
#include <vector>
#include <functional>
#include <chrono>
#include <algorithm>

namespace qfAnim {
	class Basic {
	public:
		class Methods {
		public:
			static float lerp(float _Starting, float _End, float _T) {
				return _Starting + (_End - _Starting) * _T;
			}
		};
	public:
		Basic();
		virtual ~Basic();

		void setAnimMethod(const std::function<float(float, float, float)>& _Method);
		const bool setCache(const std::chrono::milliseconds& _FinishIn, const std::vector<float>& _Start, const std::vector<float>& _End, bool _AutoStart = true); 
		std::vector<float>& animCache();

		const bool isFinished() const;
		void Start();
	private:
		float getTimeDelta() const;
		void animUsingAMethod(std::function<float(float, float, float)>& _Method);
	private:
		std::function<float(float,float,float)> m_AnimMethod;

		std::chrono::high_resolution_clock::time_point m_CacheStartedTime; 
		std::chrono::high_resolution_clock::time_point m_CacheLastUpdateTime; 
		std::chrono::milliseconds m_FinishIn; 

		std::vector<float> m_Cache; 
		std::vector<float> m_CacheWanted; 
		std::vector<float> m_CacheStarting; 
	};

}