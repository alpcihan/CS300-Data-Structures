// CS 300 HW3

#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

template <class Temp>
struct HashNode
{
	Temp word;
	Temp trans;
	HashNode* next;
	HashNode()
	{
		next = NULL;
	}
};

template <class Temp>
class HashTable
{
private:

	int wordCount;
	int tableSize;
	double full;
	int hash(const Temp & key, int tableSize);
	void Rehash();
	vector<HashNode<Temp>*> hashList;

public:

	HashTable();
	void insert(Temp wrd, Temp trs);
	HashNode<Temp>* find(Temp search);
	int GetWordCount();
	double GetLoadFactor();
};

bool isPrime( int n )
{
	if ( n == 2 || n == 3 )
		return true;
	if ( n == 1 || n % 2 == 0 )
		return false;
	for ( int i = 3; i * i <= n; i += 2 )
		if ( n % i == 0 )
			return false;
	return true;
}

int nextPrime(int n)
{
	if ( n % 2 == 0 )
		n++;

	for ( ; !isPrime( n ); n += 2 )
		;

	return n;
}

template <class Temp>
HashTable<Temp>::HashTable()
{
	HashNode<Temp>* ptr = NULL;
	for(int i = 0; i < 53; i++)
	{
		hashList.push_back(ptr);
	}
	tableSize = 53;
	wordCount = 0;
	full = 0.0;
}

template <class Temp>
void HashTable<Temp>::Rehash()
{
	/*Form new size hash table*/
	int oldSize = tableSize;
	tableSize = nextPrime(2*tableSize); // update the old table size
	HashNode<Temp>* ptr = NULL;
	HashNode<Temp>* ptr2 = NULL;

	for(int i = 0; i < tableSize - oldSize; i++) // add new rows
	{
		hashList.push_back(ptr);
	}

	for(int i = 0; i < oldSize; i++) // for each row
	{
		ptr = hashList[i];
		while(ptr != NULL && hash(ptr -> word, tableSize) != i) // if replaced node is head node
		{
			wordCount--;
			full--;
			insert(ptr -> word, ptr -> trans);

			hashList[i] = ptr -> next;
			delete ptr;
			ptr = hashList[i];


		}		
		while(ptr != NULL) // for each column
		{
			ptr2 = ptr;
			ptr = ptr -> next;
			if(ptr != NULL && hash(ptr -> word, tableSize) != i) // if place of the word need to be changed
			{
				wordCount--;
				full--;
				insert(ptr->word, ptr-> trans);
				ptr2 -> next = ptr -> next;
				delete ptr;
				ptr = ptr2 -> next;
			}			
		}
	}
	cout << "rehashed..." << endl;
	cout << "previous table size:" << oldSize <<
		", new table size:" << tableSize <<
		", current unique word count:" << wordCount <<
		", current load factor: " << full / tableSize << endl;
}

template <class Temp>
int HashTable<Temp>::hash (const Temp & key, int tableSize)
{
	int hashVal = 0;

	for (int i = 0; i < key.length();i++)
	{
		hashVal = 37 * hashVal + key.at(i);
	}
	hashVal = hashVal % tableSize;

	if (hashVal < 0)
	{
		hashVal = hashVal + tableSize;
	}
	return(hashVal);
}

template <class Temp>
void HashTable<Temp>::insert(Temp wrd, Temp trns)
{
	int key = hash(wrd, tableSize);
	HashNode<Temp>* ptr = find(wrd);
	if(ptr == NULL) // if word does not exists in the table
	{
		full++;
		wordCount++; // increases word count

		HashNode<Temp>* temp = hashList[key];
		HashNode<Temp>* ptr = new HashNode<Temp>;
		ptr -> word = wrd;
		ptr -> trans = trns;
		ptr -> next = hashList[key];
		hashList[key] = ptr;

		// increase the not empty location amount
		if(full / tableSize >= 0.5)
		{
			Rehash();
		}			
	}
	else		
		ptr -> trans += ", " + trns;
}

template <class Temp>
HashNode<Temp>* HashTable<Temp>::find(Temp search)
{
	int key = hash(search, tableSize);
	HashNode<Temp>* ptr = hashList[key];
	while(ptr != NULL)
	{
		if(ptr -> word == search)
			return ptr;

		ptr = ptr -> next;
	}
	return NULL;
}

template <class Temp>
int HashTable<Temp>::GetWordCount()
{
	return wordCount;
}

template <class Temp>
double HashTable<Temp>::GetLoadFactor()
{
	return full/tableSize;
}

#endif
