// CS 300 HW3

#include <string>
#include <iostream>
#include "AVLtree.h"
#include "HashTable.h"
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

void timeOutput(int N, long long & timer)
{
	if(N >= 1 && N <= 9)
	{
		cout << N << "     " << timer;
	}
	else if(N >= 10 && N <= 99)
	{
		cout << N << "    " << timer;
	}
	else if(N >= 100 && N <= 999)
	{
		cout << N << "   " << timer;
	}
	else if(N >= 1000 && N <= 9999)
	{
		cout << N << "  " << timer;
	}
	else
	{
		cout << N << " " << timer;
	}
	cout << endl;
}
long long BenchMarkResults(int count, long long time, string type)
{
	cout << "***********************************************" << endl;
	cout <<	"Benchmark results for ";

	if(type == "bst")
		cout << "Binary Search Tree (BST):" << endl;
	else if(type == "ht")
		cout << "Hash Table:" << endl;

	cout << "***********************************************" << endl;

	cout << "+ Elapsed time: " << time << " ns" << endl;
	cout << "+ Average query time: " <<time/count << " ns" << endl;
	return (double)time/count;
}

long long TreeQueries(vector<string> & words, AvlTree<string> & tree, int number)
{
	/* Number == 1 means it is elapsed times process */
	ofstream treef;	
	int waste;	// do N*waste times instead of N times in order to observe time better then divide the time by waste
	
	for(int j = 1; j <= number; j = j*2) // start from 1 increase by 2 the query repetation
	{
		waste = (10 / j) + 1; // for j > 10 waste == 1 since big j values consists huge repetitions already
		auto start = std::chrono::high_resolution_clock::now();
		for(int i = 0; i < j*waste; i++) // j times
		{
			if(number != 1)
				treef.open("bst_result.txt");
			for(int k = 0; k < words.size(); k++) // for each word
			{
				string str = tree.find(words[k]); // find translation of the word
				if(number != 1) // if it is first time print it to the txt
					treef << words[k] << " " << str << endl; // push the translation to the file
			}
		}
		if(number==1)
		{
			long long timer2 = long long ((std::chrono::high_resolution_clock::now()-start).count());
			timer2 = timer2/waste;
			return BenchMarkResults(words.size(), timer2, "bst");
		}
		else
		{
			auto end = std::chrono::high_resolution_clock::now();
			long long timer = long long ((std::chrono::high_resolution_clock::now()-start).count());
			timer = timer/waste;
			timeOutput(j, timer);
		}
	}
	treef.close(); // close the file
	cout << endl;
	return 0;
}
long long TableQueries(vector<string> & words, HashTable<string> & table, int number)
{
	/* Number == 1 means it is elapsed times process */
	ofstream hashf;	
	int waste; // do N*was times instead of N times in order to observe time better then divide the time by waste		
	for(int j = 1; j <= number; j = j*2) // start from 1 increase by 2 (1,2,4,8......4096)
	{
		waste = (10/j) + 1; // for j > 10 waste == 1 since big j values consists huge repetitions already
		auto start = std::chrono::high_resolution_clock::now();
		for(int i = 0; i < j*waste; i++) // j times
		{
			if(number != 1)
				hashf.open("ht_result.txt");
			for(int k = 0; k < words.size(); k++) // for each word in the query vector
			{
				HashNode<string>* ptr = table.find(words[k]); // find translation of the word in the hash table

				if(number != 1) // if it is first time print it to the txt	
					hashf << words[k] << " " << ptr ->trans << endl; // push the translation to the file
			}			
		}
		if(number==1)
		{
			long long timer2 = long long ((std::chrono::high_resolution_clock::now()-start).count());
			timer2 = timer2/waste;
			return BenchMarkResults(words.size(), timer2, "ht");
		}
		else
		{
			auto end = std::chrono::high_resolution_clock::now();
			long long timer = long long ((std::chrono::high_resolution_clock::now()-start).count());
			timer = timer/waste;
			timeOutput(j, timer);
		}
	}
	hashf.close(); 
	return 0;
}
void AllQueries(vector<string> & words, AvlTree<string> & tree, HashTable<string> & table)
{
	cout << "Running queries in query1.txt..." << endl << endl;
	/* Calculate elapsed and average times for bts and ht*/
	long long treeSpeed = TreeQueries(words, tree, 1);
	long long tableSpeed = TableQueries(words, table, 1);
	cout << endl << "+ Speed up: " << (double)treeSpeed/(double)tableSpeed << "x" << endl << endl;

	cout << "Time measurements in ns (N, 4096N):" << endl;
	cout << "*****************************" << endl;

	/* Evaluate for bts tree */
	cout << "bst" << endl;
	cout << "N     time" << endl;
	TreeQueries(words, tree, 4096);

	/* Evaluate for hash table */
	cout << "ht" << endl;
	cout << "N     time" << endl;
	TableQueries(words, table, 4096);
}
void fillVector(vector<string> & words)
{
	/* Fill the query vector */
	ifstream queryFile;
	queryFile.open("query1.txt");
	string line,temp;
	while(getline(queryFile, line)) // for each line
	{
		istringstream iss(line);
		while(iss >> temp) // for each word
		{
			words.push_back(temp);
		}
	}
}
void fillAll(vector<string> & words, AvlTree<string> & tree, HashTable<string> & table, ifstream & dictionaryFile)
{
	cout << "Building a binary tree for dict.txt..." << endl;
	cout << "Building a hash table for dict.txt..." << endl;

	/* Insert words and translations to the binary tree and hash table*/
	string line = "";
	string word = "";
	string translation = "";
	string temp = "";
	int count = 0;
	while(getline(dictionaryFile, line)) // for each line
	{
		if(line.length() > 3) // if line is not empty
		{
			istringstream iss(line);
			iss >> word;

			while(iss>>temp)
			{
				translation += temp + " ";
			}
			translation = translation.substr(0,translation.length()-1);

			table.insert(word, translation);
			tree.insert(word, translation);
		}
		translation = "";
	}
	cout << "After preprocessing, the unique word count is " << table.GetWordCount() <<
		". Current load ratio is " << table.GetLoadFactor() << endl;
	fillVector(words);
}

int main()
{
	ifstream dictionaryFile; // dictionary file
	dictionaryFile.open("dict.txt");

	HashTable<string> table; // hash table
	AvlTree<string> tree; // bts tree
	vector<string> words; // query vector

	fillAll(words, tree, table, dictionaryFile);
	AllQueries(words, tree, table);

	return 0;
}
