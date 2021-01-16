#ifndef _MINHEAP_H
#define _MINHEAP_H

#include <iostream>
#include <string>
using namespace std;

struct Worker
{
	int id; // id of the worker
	int days; // days that worker should to work

	Worker() // default worker constructor
	{
		id = -1;
	}
	Worker(const int & i, const int & d) // worker constructor gets id
	{
		id = i;
		days = d;
	}

	bool operator<(const Worker & w) // operator overloading
	{
		if(days == 0)
		{
			if(id < w.id)
				return true;
			else
				return false;
		}
		else
		{
			if(days < w.days)
				return true;
			else
				return false;
		}

	}
	bool operator>(const Worker & w) // operator overloading
	{
		if(days == 0)
		{
			if(id > w.id)
				return true;
			else
				return false;
		}
		else
		{
			if(days > w.days)
				return true;
			else
				return false;
		}
	}
	void operator-(const int & d) // operator overloading
	{
		days -= d;
	}
};
struct Job 
{   
	int id, deadline; // id of the job and days it takes to finnish the job

	Job()
	{
		id = -1;
		deadline = -1;
	}
	Job(const int & i, const int & d)
	{
		id = i;
		deadline = d;
	}

	bool operator<(const Job & j) 
	{
		if(id < j.id)
			return true;
		else
			return false;
	} 
	bool operator>(const Job & j)
	{ 
		if(deadline > j.deadline)
			return true;
		else
			return false;
	}
};

template <class Comparable>
class MinHeap{

public:

	MinHeap(const int & size);
	~MinHeap();

	void insert(Comparable object);
	void deleteMin(Comparable & minItem);
	void decreaseElements(const int & t);
	int getHeapSize();

private:
	Comparable* vctr;
	int heapSize;
	void percolateDown(int hole);
};

template <class Comparable>
MinHeap<Comparable>::MinHeap(const int & size)
{
	vctr = new Comparable[size + 1];
	heapSize = 0;
}

template <class Comparable>
MinHeap<Comparable>::~MinHeap()
{
	delete vctr;
}

template <class Comparable>
void MinHeap<Comparable>::insert(Comparable obj)
{
	int hole = ++heapSize;

	for (; hole > 1 && obj < vctr[ hole / 2 ]; hole /= 2 )
	{
		vctr[ hole ] = vctr[ hole / 2 ];
	}

	vctr[hole] = obj;
}

template <class Comparable>
void MinHeap<Comparable>::deleteMin(Comparable & minItem)
{
	minItem = vctr[1];
	vctr[ 1 ] = vctr[ heapSize-- ];
	percolateDown( 1 );
}

template <class Comparable>
void MinHeap<Comparable>::percolateDown( int hole )
{
	int child;

	Comparable tmp = vctr[ hole ]; // tmp is the item that will
	// be percolated down
	for(; hole * 2 <= heapSize; hole = child )
	{
		child = hole * 2;

		if ( child != heapSize && vctr[ child + 1 ] < vctr[ child ] )
			child++; // child is the minimum of the children

		if ( vctr[ child ] < tmp )
			vctr[ hole ] = vctr[ child ];

		else
			break;
	}

	vctr[ hole ] = tmp;
}

template <class Comparable>
int MinHeap<Comparable>::getHeapSize()
{
	return heapSize;
}

template <class Comparable>
void MinHeap<Comparable>::decreaseElements(const int & t)
{
	MinHeap<Comparable> tempHeap(heapSize + 1);
	int tempSize = heapSize;
	Comparable temp;
	for(int i = 0; i<tempSize; i++)
	{
		deleteMin(temp);
		temp - t;
		tempHeap.insert(temp);		
	}

	for(int i = 0; i<tempSize; i++)
	{
		tempHeap.deleteMin(temp);
		insert(temp);		
	}	
}


#endif
