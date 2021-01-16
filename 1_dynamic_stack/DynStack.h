#ifndef _DYNSTACK_H
#define _DYNSTACK_H

template < class T >
class DynStack
{
private:
   // Structure for stack nodes
   struct StackNode
   {
      T value;        // Value in the node
      StackNode *next;  // Pointer to the next node
   };

   StackNode *top;      // Pointer to the stack top

public:
   // Constructor
   DynStack()
      {  top = nullptr; }

   // Destructor
   ~DynStack();

   // Stack operations
   DynStack<T> & operator = (const DynStack<T> & rhs);
   void push( T );
   void pop( T & );
   bool isEmpty();
}; 
#endif 

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************

template < class T >
DynStack<T>::~DynStack()
{
   StackNode *nodePtr, *nextNode;

   // Position nodePtr at the top of the stack.
   nodePtr = top;

   // Traverse the list deleting each node.
   while (nodePtr != 0)
   {
      nextNode = nodePtr->next;
      delete nodePtr;
      nodePtr = nextNode;
   }
}

//************************************************
// Member function push pushes the argument onto *
// the stack.                                    *
//************************************************
template < class T >
void DynStack<T>::push( T num )
{
   StackNode *newNode; // Pointer to a new node

   // Allocate a new node and store num there.
   newNode = new StackNode;
   newNode->value = num;

   // If there are no nodes in the list
   // make newNode the first node.
   if (isEmpty())
   {
      top = newNode;
      newNode->next = nullptr;
   }
   else  // Otherwise, insert NewNode before top.
   {
      newNode->next = top;
      top = newNode;
   }
}

//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************
template < class T >
void DynStack<T>::pop( T &num )
{
   StackNode *temp; // Temporary pointer

   if (!isEmpty())  // If stack is not empty pop value off top of stack
   {
      num = top->value;
      temp = top->next;
      delete top;
      top = temp;
   }
}

//****************************************************
// Member function isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
template < class T >
bool DynStack<T>::isEmpty()
{
   bool status;

   if (!top)
      status = true;
   else
      status = false;

   return status;
}

//**********************************************************
// Operator function equals this to rhs then return (*this)*
//**********************************************************
template <class T>
DynStack<T> & DynStack<T>::operator= (const DynStack<T> & rhs)
{
	while( !(*this).isEmpty() ) // Empty the stack.
	{
		char ch;
		(*this).pop(ch);
	}

	StackNode* ptr = rhs.top; // to travel the rhs stack
	StackNode* tempTop = nullptr; // temp top pointer
	
	if( rhs.top != nullptr ) // Create first Node of the tempTop
	{
		tempTop = new StackNode;
		tempTop -> value = rhs.top -> value;
		tempTop -> next = nullptr;
		ptr = ptr -> next;
	}
	
	StackNode* tPtr = tempTop;
	
	while( ptr != nullptr) // Copy rhs stack to the tempTop top stack.
	{
		StackNode* tPtr2;
		tPtr2 = new StackNode;
		tPtr2 -> value = ptr -> value;
		tPtr2 -> next = nullptr;

		tPtr -> next = tPtr2;
		tPtr = tPtr2;

		ptr = ptr -> next;		
	}

	(*this).top = tempTop; // Equal this top to the tempTop's top.
	
	return (*this);
}