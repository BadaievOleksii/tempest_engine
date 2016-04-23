#include "CChrono.h"

namespace Tempest {
	namespace Core {
		//==============================================================================================
		Chrono::Chrono(){
			mTicksPerSec = new LARGE_INTEGER();
			mMsrmStart = new LARGE_INTEGER();
			mMsrmEnd = new LARGE_INTEGER();
			mMsrmElapsed = new LARGE_INTEGER();
			mTimeStamp = new LARGE_INTEGER();
		}
		//==============================================================================================
		Chrono::~Chrono(){
			delete mTicksPerSec;
			delete mMsrmStart;
			delete mMsrmEnd;
			delete mMsrmElapsed;
			delete mTimeStamp;
		}
		//==============================================================================================
		u32 Chrono::getTime(){
			return timeGetTime();
		}
		//==============================================================================================
		u64 Chrono::getTime64(){
			return GetTickCount64();
		}
		//==============================================================================================
		u64 Chrono::getTimeMicro64(){
			QueryPerformanceCounter(mTimeStamp);

			mTimeStamp->QuadPart *= 1000000;
			mTimeStamp->QuadPart /= mTicksPerSec->QuadPart;

			return mTimeStamp->QuadPart;
		}
		//==============================================================================================
		bool Chrono::tickEveryMilis(u32 period){
			if (mTimerTicks.find(period) == mTimerTicks.end()){
				mTimerTicks[period] = timeGetTime();
			}
			if (timeGetTime() - mTimerTicks[period] > period){
				mTimerTicks[period] = timeGetTime();
				return true;
			}
			return false;
		}
		//==============================================================================================
		//==============================================================================================
		void Chrono::startMeasure(){
			QueryPerformanceFrequency(mTicksPerSec);
			QueryPerformanceCounter(mMsrmStart);
		}
		//==============================================================================================
		void Chrono::endMeasure(u64& res){
			QueryPerformanceCounter(mMsrmEnd);
			mMsrmElapsed->QuadPart = mMsrmEnd->QuadPart - mMsrmStart->QuadPart;
			mMsrmElapsed->QuadPart *= 1000000;
			mMsrmElapsed->QuadPart /= mTicksPerSec->QuadPart;
			res = mMsrmElapsed->QuadPart;
		}
		//==============================================================================================
	}
}