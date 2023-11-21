#include "DelayedCall.h"

DelayedCall::DelayedCall(uint16_t _count)
{
	count = _count;
	delays = (Delay**)calloc(count, sizeof(Delay*));
	usedDelays = (Delay**)calloc(count, sizeof(Delay*));
}

DelayedCall::Delay* DelayedCall::call(void (*function)(void), uint32_t totalTime)
{
	if(index >= count){
		return NULL;
	}
	else if((millis() + totalTime) < totalTime){
		return NULL;
	}
	
	Delay* myDelay;
	if(indexOfUsedDelays > 0){
		myDelay = usedDelays[indexOfUsedDelays - 1];
		indexOfUsedDelays--;
	}
	else{
		myDelay = (Delay*)malloc(sizeof(Delay));	// Allocate new area
		if(myDelay == NULL){
			return NULL;
		}
	}
	
	myDelay->function = function;
	myDelay->totalTime = totalTime;
	myDelay->startTime = millis();
	myDelay->callCount = 1;
	myDelay->id = 0;
	myDelay->isFinished = false;
	delays[index++] = myDelay;
	
	return myDelay;
}

bool DelayedCall::remove(Delay* myDelay)
{	
	for(uint16_t i=0; i<index; i++){
		if(delays[i] == myDelay){
			usedDelays[indexOfUsedDelays++] = myDelay;
			delays[i] = NULL;
			dispose();
			return true;
		}
	}
	return false;
}

void DelayedCall::dispose(){
	uint16_t current_index = 0;

	for(uint16_t i=0; i<count; i++){
		if(delays[i] != NULL){
			if(current_index != i){
				delays[current_index] = delays[i];
				delays[i] = NULL;
			}
			current_index++;
		}
	}
	index = current_index;
}

void DelayedCall::update(){
	if(index <= 0)
		return;
	
	uint32_t elapsed_time = 0;	
	for(uint16_t i=0; i<index; i++)
	{
		Delay* myDelay = delays[i];
		if(myDelay != NULL)
		{	
			elapsed_time = millis() - myDelay->startTime;
			
			if(elapsed_time >= myDelay->totalTime)
			{
				if(*(myDelay->function))
					(*(myDelay->function))(myDelay);
				
				if(myDelay->callCount > 1){
					myDelay->startTime = millis();
					myDelay->callCount--;
				}
				else if(myDelay->callCount == 1){
					myDelay->isFinished = true;
					remove(myDelay);
				}
				else if(myDelay->callCount == 0){
					myDelay->startTime = millis();
				}
			}
		}
	}
}

uint16_t DelayedCall::getCount(){
	return index;
}

void DelayedCall::setForever(Delay* delay){
	delay->callCount = 0;
}

bool DelayedCall::contains(Delay* delay){
	for(uint16_t i=0; i<index; i++){
		if(delays[i] == delay){
			return true;
		}
	}
	return false;
}

void DelayedCall::resetTime(Delay* delay){		
	delay->startTime = millis();
}




