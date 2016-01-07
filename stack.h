#include <iostream>

#include "fx.h"


#define LOG(MSG) std::cout<<"log info: " << MSG <<std::endl
#define mNULL reinterpret_cast<T>(0);


template<typename T>class Stack{
private:
	struct stack{
		T data;
		stack* next, *prev;
	};
	
	stack* S;

	int currentItemNumber, stackSize;
	
public:
	stack* GetStackPointer(){
		return S;
	}	
	
	Stack(int depth){
		currentItemNumber = 0;
		stackSize = depth;
		S = new stack;
		S->prev = S->next = 0;
	} ~Stack(){}

	bool Push(T Data){
		if(currentItemNumber == stackSize) return false;

		stack* stackPointer = S;
		S->data = Data;
		S->next = new stack;
		S = S->next;
		S->prev = stackPointer;
		S->next = 0;
		currentItemNumber++;

		return true;
	}
	
	T Pop(){
		if(!currentItemNumber) return mNULL;
		
		T data = (S->prev)->data;
		S = S->prev;
		delete S->next;
		S->next = 0;
		currentItemNumber--;
		
		return data;
	}
	
};

#undef LOG
#undef mNULL
