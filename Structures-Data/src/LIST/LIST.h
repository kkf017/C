typedef struct TElement TElement;
struct TElement{
	int element;
	TElement *next;
};



void push(TElement **first,int n);
int pop(TElement **first,int n);
void clear(TElement **first);
void display(TElement **first);


