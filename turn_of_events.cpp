#include <iostream>
#include "systemc.h"
SC_MODULE(turn_of_events) {
// Constructor
SC_CTOR(turn_of_events) {
	SC_THREAD(turn_knob_thread);
	SC_THREAD(stop_signal_thread);
}
sc_event signal_stop, signals_off;
sc_event stop_indicator_on, stop_indicator_off;
void turn_knob_thread(); // stimulus process
void stop_signal_thread(); // indicator process
};//endclass turn_of_events
void turn_of_events::turn_knob_thread() {
// This process provides stimulus using stdin
enum directions {STOP='S', OFF='F'};
char direction; // Selects appropriate indicator
bool did_stop = false;
// allow other threads to get into waiting state
wait(SC_ZERO_TIME);
for(;;) {
// Sit in an infinite loop awaiting keyboard
// or STDIN input to drive the stimulus…
std::cout << "Signal command: ";
std::cin >> direction;
switch (direction) {
case STOP:
// Make sure the other signals are off
signals_off.notify();
signal_stop.notify(); // Turn stop light on
// Wait for acknowledgement of indicator
wait(stop_indicator_on);
did_stop = true;
break;
case OFF:
// Make the other signals are off
signals_off.notify() ;
if (did_stop) wait(stop_indicator_off) ;
did_stop = false;
break;
}//endswitch
}//endforever
}//end turn_knob_thread()
int sc_main(int i,char* c[]){
	turn_of_events obj("2");
	sc_start();
  return 0;
}