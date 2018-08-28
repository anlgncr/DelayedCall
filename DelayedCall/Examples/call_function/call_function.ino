#include <DelayedCall.h>

/*This constructor takes one argument and it is 
 the count of how many delayedCall we will use*/
DelayedCall my_delays(1);

// A pointer to the delay object
DelayedCall::Delay my_delay1;

void setup() {
  Serial.begin(9600);
  
  /*This will call the printSomething for 5 times after 2000 ms
  if repat_count is greater than 0 then it will repeat that much
  if repeat_count is 0 then it will repeat forever (as long as you do not remove it)*/
  my_delay1 ={printSomething, 2000, 0};
  my_delays.add(&my_delay1);
}

void loop() {
  //we need to update delays
  my_delays.update();
}

void printSomething(){
  Serial.print("DelayedCall added at ");
  Serial.print(my_delay1.start_time / 1000);
  Serial.println(" minutes");
}