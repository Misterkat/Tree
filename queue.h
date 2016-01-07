#include "fx.h"
//#include "Stack.h"

template<typename T>
class Queue{
private:
	struct queue{
		T data;
		queue* next;
	};
	queue* Q, *fE;
	int ci, size;
public:
	Queue(int size){
		Q = new queue;
		fE = Q;
		this->size = size;
		ci = 0;
	} ~Queue(){}

	void Push(T data){
		 if(ci == size){
			WriteLn("Queue overflow!");
			return;
		}
		Q->data = data;
		Q->next = new queue;
		Q = Q->next;
		Q->data = 0;
		ci++;
	}

	T Pop(){
		if(!ci){
			//WriteLn("Queue is empty!");
			return 0;
		}

		T ret = fE->data;
		fE = fE->next;
		ci--;
		return ret;
	}

	/*void PrintQueue(){
		if(!ci) return;
		Stack<int>* S = new Stack<int>(ci);
		
		queue* pfE = fE;
		do{
			//WriteLn(pfE->data);
			S->Push(pfE->data);
			pfE = pfE->next;
		} while(pfE->data);

		for(int i  = 0; i < ci; i++){
			WriteLn(S->Pop());
		}
	}*/
};
