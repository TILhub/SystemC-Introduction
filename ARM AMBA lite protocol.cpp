#include "systemc.h"

#define HCLK 20

bool to_slave=false;
bool to_master=false;

SC_MODULE(Master)
{

	sc_in< bool > P_clk;

	sc_in< bool > hwrite;

	sc_in<bool> hreset;

	sc_port<sc_fifo_out_if< int > > sender;
  
  	sc_port<sc_fifo_in_if<int > >receiver; 

	void writer();

	void reader();

	SC_CTOR(Master)
	{

		SC_METHOD(writer);

		sensitive<< P_clk ;sensitive<<hwrite;

		//next_trigger(P_clk.posedge_event() & hwrite.negedge_event())

		SC_METHOD(reader);

		sensitive<<P_clk<<hwrite;


	}
};

void Master::reader(){
	if(hreset && (P_clk.posedge()==true) && (hwrite.posedge()==true)){

	cout<<" % Master: " << sc_simulation_time()<< " P_CLK.posedge: " << P_clk.posedge()<<" Hreset: "<<hreset<<" Hwrite.negedge: "<<hwrite.negedge()<<endl	;
	cout<<" % Master Sending signal to recieve Data\n\n";
	to_master=true;

	}
}
void Master::writer()
{

  if((hwrite.negedge()==false) && (P_clk.posedge()==true) && hreset)
  {

	cout<<" % Master: " << sc_simulation_time()<< " P_CLK.posedge: " << P_clk.posedge()<<" Hreset: "<<hreset<<" Hwrite.negedge: "<<hwrite.negedge()<<endl	;

	int val=rand()%1024+1024;

	cout<<" % Value Sending(Master End): "<<val<<endl<<endl;

	sender->write(val);

    to_slave=true;

	}

}




SC_MODULE(Slave)
{

	sc_in< bool > P_clk;

	sc_in< bool > hwrite;

	sc_in<bool> hreset;

	sc_port<sc_fifo_in_if<int > >receiver; 

	sc_port<sc_fifo_out_if< int > > sender;

	void reader();

	void writer();

	SC_CTOR(Slave)
	{

		SC_METHOD(reader);

		sensitive << P_clk << hwrite ;


		SC_METHOD(writer);

		sensitive_pos<<hwrite<<P_clk;

	}

};

void Slave::writer(){

	if(to_master==true && hreset && (P_clk.posedge()==true) && (hwrite.negedge()==true)){

		cout<<" # Slave: " << sc_simulation_time()<< " P_CLK.negedge: " << P_clk.negedge()<<" Hreset: "<<hreset<<" Hwrite.posedge: "<<hwrite.posedge()<<endl;

		int t=(-1)*rand()%1024;

		cout<<" # Value Sent By Slave: "<<t<<endl<<endl;

		//sender->write(t);	

		to_master=false;	

	}
}

void Slave::reader()
{

  if(P_clk.negedge()==false && hwrite.posedge()==true && hreset && to_slave==true){

	cout<<" # Slave: " << sc_simulation_time()<< " P_CLK.negedge: " << P_clk.negedge()<<" Hreset: "<<hreset<<" Hwrite.posedge: "<<hwrite.posedge()<<endl;

    cout<<" # Value Recieved(Slave): "<<receiver->read()<<endl<<endl;

    to_slave=false;

	}
}

int sc_main(int argc, char* argv[]) {

	sc_clock clk("clock", HCLK,0.5,1,true);

	sc_clock hwrite("HWRITE",HCLK*2,0.5,1,false);

	sc_signal< bool > hreset;

	sc_fifo<int>* fifo_inst;fifo_inst=new sc_fifo<int>(20);

	sc_fifo<int>* fifo_inst_0;fifo_inst_0=new sc_fifo<int>(20);

	Slave S1("Slave");

	Master U1 ("Master");

	hreset=1;
	

	U1.P_clk(clk);

	U1.sender(*fifo_inst);

	U1.receiver(*fifo_inst_0);

	U1.hwrite(hwrite);

	U1.hreset(hreset);
	

	S1.P_clk(clk);

	S1.receiver(*fifo_inst);

	S1.sender(*fifo_inst_0);

	S1.hwrite(hwrite);

	S1.hreset(hreset);
	
	sc_start();

	sc_initialize();

	sc_stop();

	return (0);
}