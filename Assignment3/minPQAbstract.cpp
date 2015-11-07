//Name:						Nicolas Fry
//UF ID:			
//GatorID:					nicolascoding
//Discussion Section: 		1085
//Assignment: 				3

class minPQ 
{
	public:
		virtual minPQ() = 0;
		virtual bool empty() = 0;
		virtual int size() = 0;
		virtual void push(int time) = 0;
		virtual int top() = 0;
		virtual void pop() = 0;
};
