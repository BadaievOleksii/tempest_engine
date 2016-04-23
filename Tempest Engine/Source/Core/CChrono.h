#pragma once


#include "Core\TempestSharedHeader.h"

namespace Tempest {
	namespace Core {
		class Chrono{
		private:
			LARGE_INTEGER* mTicksPerSec;
			LARGE_INTEGER* mMsrmStart;
			LARGE_INTEGER* mMsrmEnd;
			LARGE_INTEGER* mMsrmElapsed;
			LARGE_INTEGER* mTimeStamp;


			map<u32, u32> mTimerTicks;
		public:
			Chrono();
			~Chrono();

			u32 getTime();
			u64 getTime64();
			u64 getTimeMicro64();

			/*
			Metronome
			Returns true if the time in period elapsed from the last function call with the same period
			*/
			bool tickEveryMilis(u32 period);

			/*
			Sets the starting point for time measuring
			*/
			void startMeasure();			

			/*
			Writes microseconds elapsed from the last startMeasure call
			*/
			void endMeasure(u64&);
		};
	}
}