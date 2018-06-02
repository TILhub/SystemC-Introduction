#include "systemc.h"
#include <iostream>
SC_MODULE(simple_process_ex) {
	sc_time t;
	void my_thread_process(void);
	SC_CTOR(simple_process_ex) {
		t = sc_time(10, SC_NS);
		//SC_THREAD(my_thread_process);
	}
};
void simple_process_ex::my_thread_process(void) {
	std::cout << "MY THREAD EXECUTED\n"<<name()<<std::endl;
}
int sc_main(int i, char* c[]) {
	std::cout << sc_time_stamp()<<std::endl;
	sc_simulation_time(10,SC_SEC);
	std::cout << sc_time_stamp() << std::endl;
	simple_process_ex obj("igh");
	sc_start(10,SC_SEC);
	return 0;
}