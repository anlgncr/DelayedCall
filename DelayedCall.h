#ifndef DelayedCall_h
#define DelayedCall_h
#include "arduino.h"


class DelayedCall{
	public:
		DelayedCall(unsigned int);
		
		struct Delay{
			void (*function)(Delay*);
			uint32_t totalTime;
			uint32_t startTime;
			int callCount;
			uint8_t id;
			bool isFinished;
		};
		
		Delay* call(void (*)(void), uint32_t);
		void update();
		
		bool remove(Delay*);
		bool contains(Delay*);
		void setForever(Delay*);
		void resetTime(Delay*);
		
		uint16_t getCount();
		
	private:
		Delay** delays;
		Delay** usedDelays;
		uint16_t count = 0;
		uint16_t index = 0;
		uint16_t indexOfUsedDelays = 0;
		void dispose();
};
#endif