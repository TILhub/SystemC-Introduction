
#include "systemc.h"
SC_MODULE(updown)
{
	sc_in< bool > P_clk;
	sc_in< bool > P_reset;
	sc_in< bool > P_updown;
	sc_out<sc_int<8> > P_ctr_val;
	int int_ctr_s;
	void behaviour();
	void print_res();
	SC_CTOR(updown)
	{
		int_ctr_s = 0;
		SC_METHOD(behaviour);
		sensitive_pos << P_clk;
		sensitive_pos << P_reset;
		SC_METHOD(print_res);
		sensitive << P_clk << P_reset << P_updown;
	}
};

void updown::behaviour()
{
	if (P_reset)
		int_ctr_s = 0;
	else
	{
		if (P_updown)
		{
			if (int_ctr_s == 255)
				int_ctr_s = 0;
			else
				int_ctr_s++;
		}
		else
		{
			if (int_ctr_s == 0)
				int_ctr_s = 255;
			else
				int_ctr_s--;
		}
	}
	P_ctr_val = int_ctr_s ;
}
void updown::print_res()
{
	cout << sc_simulation_time() << " "<< P_reset << " " << P_clk
	<< " "
	<< " " << P_updown << " " << int_ctr_s << "\n";
}

	int sc_main(int argc, char* argv[]) {
	sc_signal<bool> Rst;
	sc_signal< sc_int<8> > cval;
	sc_signal<bool> up_down;
	// sc_clock clk("clock", 20);
	sc_signal<bool> clk;
	int i;
	Rst = 1; // power on reset
	up_down = 1 ;
	updown U1 ("updown");
	U1.P_clk(clk);
	U1.P_reset(Rst);
	U1.P_updown(up_down);
	U1.P_ctr_val(cval);
	// trace file
	sc_trace_file *tf = sc_create_vcd_trace_file("updown_wave");
	// External Signals
	sc_trace(tf, clk, "clock");
	sc_trace(tf, Rst, "reset");
	sc_trace(tf, cval, "counter");
	sc_trace(tf, up_down, "updown");
	// sc_start(500);
	sc_initialize();
	for (i = 0; i<= 5; i++)
	{
		clk = 1;
		sc_cycle(10);
		clk = 0;
		sc_cycle(10);
	};
	Rst = 0;
	for (i = 0; i<= 15; i++)
	{
		clk = 1;
		sc_cycle(10);
		clk = 0;
		sc_cycle(10);
	};
	up_down = 0;
	for (i = 0; i<= 20; i++)
	{
		clk = 1;
		sc_cycle(10);
		clk = 0;
		sc_cycle(10);
	};
	sc_close_vcd_trace_file(tf);
	sc_stop();
	return (0);
	}