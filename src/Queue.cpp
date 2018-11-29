#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
struct Element
{
    T value;
    Element* next;
};

template <typename T>
class Stack
{
    Element<T>* top;
    int size;

public:
    Stack<T>();
    ~Stack<T>();
    Stack<T>(const Stack<T>& st);
    Stack<T>& operator=(const Stack<T>& st);

    int getSize() const;
    bool isEmpty() const;
    T getTop() const;

    void push(const T& value);
    void pop();
    void clear();

    friend void print(const Stack<T>& st);

private:
    void destroy();
    void copy(const Stack<T>& st);
};

template <typename T>
Stack<T>::Stack<T>() {
    top = NULL;
    size = 0;
}

template <typename T>
Stack<T>::~Stack<T>() {
    destroy();
}

template <typename T>
Stack<T>::Stack(const Stack<T>& st) {
    copy(st);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& st) {
    if (this != &st) {
        destroy();
        copy(st);
    }
    return *this;
}

template <typename T>
void Stack<T>::destroy() {
    while (! isEmpty()) {
        pop();
    }
}

template <typename T>
void Stack<T>::copy(const Stack<T>& st) {
    Element<T>* tmp = st.top;
    while (tmp) {
        push(tmp->value);
        tmp = tmp->next;
    }
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return (size == 0);
}

template <typename T>
int Stack<T>::getSize() const {
    return size;
}

template <typename T>
T Stack<T>::getTop() const {
    assert (top != NULL);
    return top->value;
}

template <typename T>
void Stack<T>::clear() {
    destroy();
}

template <typename T>
void Stack<T>::push(const T& value) {
    if (size > 0) {
	    Element<T>* el = new Element<T>;
	    el->value = value;
		el->next = top;
		top = el;
    }
    else {
		Element<T>* el = new Element<T>;
		el->value = value;
		el->next = NULL;
		top = el;
    }
    
    size++;
}

template <typename T>
void Stack<T>::pop() {
    assert (size > 0);

	Element<T>* tmp = top;
    top = top->next;
    delete tmp;
    
    size--;
    if (size == 0) {
        top = NULL;
    }
}

template <typename T>
void print(const Stack<T>& st) {
    Element<T>* tmp = st.top;
    while (tmp) {
        cout << tmp->value << " ";
        tmp = tmp->next;
    }
    cout << endl;
}

template <typename T>
class Queue {
	  public:
		 Queue<T>();
		 ~Queue<T>();
         Queue<T>(const Queue<T>& st);
         Queue<T>& operator=(const Queue<T>& st);

		 void push(const T& a) ;
		 void pop();
		 T getFront() ;
		 bool isEmpty() const;
		 
		 const Stack<T>& getInboxStack() const {
			return inboxStack;
         }

		 const Stack<T>& getOutboxStack() const {
            return outboxStack;
         }

	  private:
   	  	Stack<T> inboxStack;
	    Stack<T> outboxStack;
        void emptyInboxStack();
        
		void destroy();
	    void copy(const Queue<T>& q);
};

template <typename T>
Queue<T>::Queue<T>() {
}

template <typename T>
Queue<T>::~Queue<T>() {
	destroy();
}

template <typename T>
Queue<T>::Queue<T>(const Queue<T>& q) {
    copy(q);
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& q) {
    if (this != &q) {
        destroy();
        copy(q);
    }
    return *this;
}

template <typename T>
void Queue<T>::destroy() {
	inboxStack.clear();
	outboxStack.clear();
}

template <typename T>
void Queue<T>::copy(const Queue<T>& q) {
	 inboxStack = q.getInboxStack();
	 outboxStack = q.getOutboxStack();
}

template <typename T>
void Queue<T>::push(const T& a) {
	 inboxStack.push(a);
}

template <typename T>
void Queue<T>::pop() {
	 this->emptyInboxStack();
	 outboxStack.pop();
}

template <typename T>
T Queue<T>::getFront() {
	this->emptyInboxStack();
    return outboxStack.getTop();
}

template <typename T>
void Queue<T>::emptyInboxStack() {
	 if (! outboxStack.isEmpty()) {
		 return;
     }

	 while (! inboxStack.isEmpty()) {
		   outboxStack.push(inboxStack.getTop());
		   inboxStack.pop();
     }
}

template <typename T>
bool Queue<T>::isEmpty() const {
	 return inboxStack.empty() && outboxStack.isEmpty();
}

int main() {
	/*
	Stack<int> b;
	b.push(1);
	b.push(2);
	cout << b.getTop() << endl;
	b.pop();
	cout << b.getTop() << endl;
	b.push(3);
	cout << b.getTop() << endl;
	b.pop();
	cout << b.getTop() << endl;
	b.pop();
	*/
	
	Queue<int> a;
	a.push(1);
	a.push(2);
	a.push(3);
	a.push(5);

	cout << a.getFront() << endl;
	a.pop();
	cout << a.getFront() << endl;
	a.pop();
	cout << a.getFront() << endl;
	
	return 0;
}
