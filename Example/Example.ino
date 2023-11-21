#include <DelayedCall.h>
/*
 * This constructor takes one argument and it is 
 * the count of how many delayedCall we use 
 */
DelayedCall delayManager(50);
/*
 * myDelay argument contains datas about delayedCall
 * such as "id", "callCount", "totalTime", "startTime", "isFinished"
 * eg. myDelay->id
 */
void sayHello(DelayedCall::Delay *myDelay){
  Serial.println("Hello!");
}

void setup() {
  Serial.begin(9600);
  /*
   * sayHello will be called after 3 seconds and 
   * it will be removed from the pool
   */
  delayManager.call(sayHello, 3000);
}

void loop() {
  /*
   * In order to use delayedCalls
   * we need to update the manager
   */
  delayManager.update();
}
