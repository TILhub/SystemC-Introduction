#include "systemc.h"
#include "iostream"
#define CLOCK_PULSE 2		//In nano Seconds
using namespace std;
class HCLK:public sc_module{
	private:
		
		int w;
	
	public:
	
		sc_signal<sc_bit> clk;
   	
   		SC_HAS_PROCESS(HCLK);
	
		HCLK(sc_module_name name,int v):sc_module(name),w(v){
	
			clk=sc_bit('1');	
    
          SC_THREAD(start_clk);
	
		}
	
		void start_clk(){
	
			for(int i=0;i<10;i++){
	
				cout<<" # "<<sc_time_stamp()<<" Clock Pulse: "<<false<<endl;
	
				clk=sc_bit('0');
	
				wait(w,SC_NS);
	
				clk=sc_bit('1');
	
				cout<<" # "<<sc_time_stamp()<<" Clock Pulse: "<<true<<endl;
	
				wait(w,SC_NS);
            }
	

		}
};
HCLK t("C",CLOCK_PULSE);

class master:public sc_module{
	public:
	
		sc_port<sc_fifo_out_if<sc_uint<32> > > send_list;
		
		sc_signal<sc_bit> hwrite;						//high -- write to slave;	//low -- read from slave

		int r_val;										//random value to be written
		
		SC_HAS_PROCESS(master);
	
		master(sc_module_name name):sc_module(name){
	
			SC_THREAD(writer_function);
	
		}	
		void writer_function(){
          wait(CLOCK_PULSE,SC_NS);
			for(int i=0;i<5;i++){
				if(t.clk==sc_bit('0'))
				{
					cout<<" # Random value written at: "<<sc_time_stamp()<<endl;
					cout<<" # Value: "<<r_val<<"\n\n";
					r_val=rand()%1024;
					send_list->write(r_val);
					wait(CLOCK_PULSE,SC_NS);
				}
			}
		}
};

class slave:public sc_module{
	public:
	
		sc_port<sc_fifo_in_if<sc_uint<32> > > reciever_list;
	
		int r_val;
	
		SC_HAS_PROCESS(slave);
	
		slave(sc_module_name name):sc_module(name){
	
			SC_THREAD(reader_function);
	
		}	
		void reader_function()
		{
           wait(CLOCK_PULSE,SC_NS);
			for(int i=0;i<5;i++){
				if(t.clk==sc_bit('0'))
              	{
              		wait(CLOCK_PULSE,SC_NS);
					int temp=reciever_list->read();
					cout<<" @ Value Read From Master at: "<<sc_time_stamp()<<endl;
					cout<<" @ Value: "<<temp<<endl<<endl;
					
				}
			}
				
		}
};
class top : public sc_module
{
   public:

     sc_fifo <sc_uint<32> > *fifo_inst;
   	 
     master *m;
     slave *s;

     top(sc_module_name name) : sc_module(name)
     {
       
       fifo_inst = new sc_fifo<sc_uint<32> >(100);

       m = new master("Master");
       m->send_list(*fifo_inst);

       s = new slave("Slave1");
       s->reciever_list(*fifo_inst);
     }
};

int sc_main (int argc , char *argv[])
{
   //sc_clock clock ("my_clock",10,0.5);
	//setting clock frequency to 10 Ns.
	top t1("Main");
	sc_start();				//starting the functions
	return 0;				//terminate code
}