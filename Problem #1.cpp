/*

1. Producer
module producer(input producer_iclk, output logic [3:0] producer_data); endmodule
 Producer will produce the data starting from 1 into the FIFO (using produce_data port)
2. Consumer
module consumer(input consumer_iclk, output bit consumer_req, input logic[3:0]
consumer_data); endmodule
 Consumer will issue a request (using consumer_req port) to FIFO to consume data from
it and receive data (if available) from FIFO on consumer_data port.
3. FIFO
module fifo(input logic[3:0] producer_data, input bit, consumer_req, output logic[3:0]
consumer_data); endmodule
 FIFO is an array of only 10 elements.
 FIFO will receive the data from producer on produce_data port till it gets full and then it
calls $finish
 FIFO will receive request from consumer on consumer_req port. FIFO will respond back
to Consumer with data using consumer_data port (if data is available). If FIFO is empty,
it will return 0 on consumer_data port.
4. TOP
module top(); endmodule
 All modules are instantiated in top module.
 Clock of 5ns time period and 10ns time period is passed to producer & consumer
respectively.
 All modules/ sub-module print messages of data generated/ consumed

*/



#include <systemc.h>


class producer : public sc_module {
   public:
  	 sc_port<sc_fifo_out_if<sc_uint<4> > > sender;
  	 int value;

     SC_HAS_PROCESS(producer);

     producer(sc_module_name name) : sc_module(name), value(1){
       SC_THREAD(produce);
     }
     void produce(){
       
     }
};

class consumer : public sc_module {
   public:
	 sc_port<sc_fifo_in_if<sc_uint<4> > > receiver; 

     SC_HAS_PROCESS(consumer);

     consumer(sc_module_name name) : sc_module(name){
       SC_THREAD(consume);
     }

     void consume(){
       
     }
};

class top : public sc_module
{
   public:
     sc_fifo <sc_uint<4> > *fifo_inst;
     producer *prod_inst;
     consumer *cons_inst;

     top(sc_module_name name) : sc_module(name)
     {
       fifo_inst = new sc_fifo<sc_uint<4> >(10);

       prod_inst = new producer("Producer1");
       prod_inst->sender(*fifo_inst);

       cons_inst = new consumer("Consumer1");
       cons_inst->receiver(*fifo_inst);
     }
};

int sc_main (int argc , char *argv[]) {
   top top1("Top1");
   sc_start();
   return 0;
}