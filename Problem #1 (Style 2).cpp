#define SIZE 10
#include "systemc.h"
using namespace std;
SC_MODULE(Producer){
	sc_uint<4> producer_data;
	sc_port<sc_fifo_out_if<sc_uint<4> > > sender;
	SC_CTOR(Producer):producer_data(0){
		SC_THREAD(producer_thread);
	}
	void producer_thread(){
		while(producer_data<10){
			//producer_data++;
			wait(5,SC_NS);
			std::cout<<std::endl<<sc_time_stamp()<<": Producer Thread\n";
			sender->write(producer_data++);
			cout<<"DATA WRITTEN: "<<producer_data<<endl;
        }
	}
};
SC_MODULE(Consumer){
	sc_uint<4> consumer_data;
	sc_port<sc_fifo_in_if<sc_uint<4> > > reciever; 
	SC_CTOR(Consumer){
		SC_THREAD(consumer_thread);
	}
	void consumer_thread(){
		while(consumer_data<10){
			wait(10,SC_NS);
			std::cout<<std::endl<<sc_time_stamp()<<": Consumer Thread\n";
			int l=reciever->read();
			cout<<"Reciever: "<<l<<endl;
		}
	}
};
SC_MODULE(TOP){
	Producer pro;
	Consumer con;
	sc_fifo<sc_uint<4> > *queue;
	SC_CTOR(TOP):pro("Producer!"),con("Consumer"){
		//pro(from_producer,queue);
		//con(queue,reciever);
	
    	queue = new sc_fifo<sc_uint<4> >(10);

      // prod_inst = new producer("Producer1");
       pro.sender(*queue);

       //cons_inst = new consumer("Consumer1");
       con.reciever(*queue);
    
    }

};
int sc_main(int,char**){
	TOP object_1("TOPPER");
	sc_start();
	return 0;
}