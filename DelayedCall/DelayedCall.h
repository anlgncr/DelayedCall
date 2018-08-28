#ifndef DelayedCall_h
#define DelayedCall_h
#include "arduino.h"


class DelayedCall{
	public:
		DelayedCall(unsigned int);
		
		struct Delay{
			void (*function)(void);
			uint32_t total_time;
			int repeat_count;
			bool isFinished;
			uint32_t start_time;
		};
		
		Delay* create(void (*)(void), uint32_t, int);
		bool add(Delay*);
		bool remove(Delay*);
		bool update();
		uint16_t getIndex();
		
	private:
		Delay** delays;
		uint16_t delayed_call_num = 0;
		uint16_t last_index = 0;
		void dispose();
};
#endif