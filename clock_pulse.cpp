#include "systemc.h"
using namespace std;
class HCLK:public sc_module{
	private:
		sc_signal<sc_bit> clk;
		int w;
	public:
   SC_HAS_PROCESS(HCLK);
		HCLK(sc_module_name name,int v):sc_module(name),w(v){
			clk=sc_bit('1');	
          SC_THREAD(start_clk);
		}
		void start_clk(){
			for(int i=0;i<10;i++){
				wait(w,SC_NS);
				cout<<" # "<<sc_time_stamp()<<" Clock Pulse: "<<false<<endl;
				clk=sc_bit('0');
				wait(w,SC_NS);
				clk=sc_bit('1');
				cout<<" # "<<sc_time_stamp()<<" Clock Pulse: "<<true<<endl;
			}
		}
};
int sc_main (int argc , char *argv[])
{
	HCLK t("trial3",10);
	sc_start();
	return 0;
}