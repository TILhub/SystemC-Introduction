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
       while(value<10){
        sender->write(value);
       	cout<<"Writing: "<<value++<<endl;
        wait(5,SC_NS);
       }
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
       int l;
       while(l<10){
       		l=receiver->read();
         	std::cout<<"Consumer Reads: "<<l<<endl;
         	wait(10,SC_NS);
       }
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