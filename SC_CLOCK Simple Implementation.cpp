
#include "systemc.h"
SC_MODULE(updown)
{
	sc_in< bool > P_clk;
	void print_res();
	SC_CTOR(updown)
	{
		SC_METHOD(print_res);
		sensitive << P_clk ;
	}
};
void updown::print_res()
{
	cout << sc_simulation_time()<< " P_CLK: " 
	<< P_clk<<endl	;
}

	int sc_main(int argc, char* argv[]) {
		sc_clock clk("clock", 20);
		updown U1 ("updown");
		U1.P_clk(clk);
		sc_start();
		sc_initialize();
		sc_stop();
		return (0);
	}