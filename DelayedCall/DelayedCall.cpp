#include "DelayedCall.h"

DelayedCall::DelayedCall(uint16_t _delayed_call_num){
	delayed_call_num = _delayed_call_num;
	delays = (Delay**)calloc(delayed_call_num, sizeof(Delay*));
}

DelayedCall::Delay* DelayedCall::create(void (*function)(void), uint32_t total_time, int repeat_count){
	if(last_index >= delayed_call_num)
		return NULL;
	else if((millis() + total_time) < total_time)
		return NULL;
	
	Delay* my_delay = (Delay*)malloc(sizeof(Delay));
	*my_delay = {function, total_time, repeat_count, false, millis()};
	delays[last_index] = my_delay;
	last_index++;
	
	return my_delay;
}

bool DelayedCall::add(Delay* my_delay){
	if(last_index >= delayed_call_num)
		return false;
	
	for(uint16_t i=0; i<last_index; i++)
		if(delays[i] == my_delay)
			return false;
	
	my_delay->start_time = millis();
	
	if((my_delay->start_time + my_delay->total_time) < my_delay->total_time)
		return false;
	
	my_delay->isFinished = false;
	delays[last_index] = my_delay;
	last_index++;
	
	return true;
}

bool DelayedCall::remove(Delay* my_delay){
	if(last_index <= 0)
			return false;
		
		for(uint16_t i=0; i<last_index; i++){
			if(delays[i] == my_delay){
				delays[i] = NULL;
				dispose();
				return true;
			}
		}
		return false;
}

void DelayedCall::dispose(){
	uint16_t current_index = 0;

	for(uint16_t i=0; i<delayed_call_num; i++){
		if(delays[i] != NULL){
			if(current_index != i){
				delays[current_index] = delays[i];
				delays[i] = NULL;
			}
			current_index++;
		}
	}
	last_index = current_index;
}

bool DelayedCall::update(){
	if(last_index <= 0)
		return false;
	
	uint32_t elapsed_time = 0;	
	for(uint16_t i=0; i<last_index; i++)
	{
		Delay* my_delay = delays[i];
		if(my_delay != NULL)
		{	
			elapsed_time = millis() - my_delay->start_time;
			
			if(elapsed_time >= my_delay->total_time)
			{
				if(*(my_delay->function))
					(*(my_delay->function))();
				
				if(my_delay->repeat_count > 1){
					my_delay->start_time = millis();
					my_delay->repeat_count--;
				}
				else if(my_delay->repeat_count == 0){
					my_delay->start_time = millis();
				}
				else{
					my_delay->isFinished = true;
					remove(my_delay);
				}
			}
		}
	}
}

uint16_t DelayedCall::getIndex(){
	return last_index;
}




