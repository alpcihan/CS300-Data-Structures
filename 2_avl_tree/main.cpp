#include "AVLtree.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void Option_3(AvlTree<string> & avlDictionary)
{
	string word, translation;
	cout << "Enter New Word: ";
	cin >> word;
	translation = avlDictionary.find(word);
	if(translation != "") // if word already exists in the dictionary
		cout << "Word already exists, if you want to add new translation please use command 2." << endl;
	else // if not add new word
	{
		cout << "Enter Translations: ";
		cin >> translation;
		avlDictionary.insert(word, translation);
		cout << "***UPDATED***" << endl;
	}

}
bool Does_Translation_Exists(string temp, string translation, AvlTree<string> & avlDictionary)
{
	/* Check if "translation" translation is already exists for "temp" named word */
	for(int i = 0; i < translation.length(); i++)
	{
		string temp2 = "";
		while(i < translation.length() && translation.at(i) != ',')
		{
			temp2 += translation.at(i);
			i++;
		}
		if(i+1 < translation.length() && translation.at(i+1) == ' ')
			i++;
		
		if(temp2 == temp)
			return true;

	}
	return false;
}
void Option_2(AvlTree<string> & avlDictionary)
{
	string word, translation;
	cout << "Which word do you want to edit: ";
	cin >> word;
	translation = avlDictionary.find(word);
	if(translation == "") // if word is not found
		cout << "Word is not found, if you want to add new word please use command 3." << endl;
	else // if word is found
	{
		string temptrans;
		cout << "Enter the new translation: ";
		cin >> temptrans;
		if(Does_Translation_Exists(temptrans, translation, avlDictionary) == true) // if user try to add a translation that already exists for that word
			cout << "Translation already exist for the word." << endl;
		else // if same translation is not exist then add the translation to the word
		{
			avlDictionary.insert(word, temptrans);
			cout << "***UPDATED***" << endl;
		}		
	}
}
void Option_1(AvlTree<string> & avlDictionary)
{
	string word, translation;
	cout << "Enter queried word: ";
	cin >> word;
	translation = avlDictionary.find(word);
	if(translation == "") // .find returns "" if there is no "word" word exists
		cout << "Word is not found, if you want to add new word please use command 3." << endl;
	else // if word exists
	{
		cout << word << " ---> " << translation << endl;
	}		
}
	
void Options(AvlTree<string> & avlDictionary)
{
	cout << "***Help***" << endl;
	cout << "Query: 1" << endl;
	cout << "Add new translation: 2" << endl;
	cout << "Add new word: 3" << endl;
	cout << "Exit: 0" << endl;
	
	string opt = "";
	while (opt != "0" )
	{	
		cout << "Enter Command: ";
		cin >> opt;
		if(opt == "1") // query
		{
			Option_1(avlDictionary); 
		}
		else if(opt == "2") // add new translation
		{
			Option_2(avlDictionary);
		}
		else if(opt == "3") // add new word
		{
			Option_2(avlDictionary);
		}
		else if(opt == "0") // exit
		{
			cout << "Bye..." << endl;
		}
	}
}
void Same_Word_Fill(ifstream & dictionaryFile, string word1, string & word2, int & current)
{
	string temp = word1;
	string tempword2;
	
	string line; // line to read line by line
	while(getline(dictionaryFile, line) && temp == word1)
	{
		string addword = ""; // translation that going to be added to the original word
		istringstream iss(line);
		iss >> temp;
		if(temp == word1) // if same word
		{
			while(iss >> tempword2) // add all translation of the same word
				addword += tempword2 + " ";

			addword = addword.substr(0, addword.length() - 1); //remove ' ' at the end
			
			if(!addword.empty()) // in order to prevent empty additions
				word2 += ", " + addword;

			current = dictionaryFile.tellg(); // update the location in the file
		}
	}
}
void Fill_The_Tree(ifstream & dictionaryFile, AvlTree<string> & avlDictionary)
{
	string line;
	while(getline(dictionaryFile, line)) // get line by line
	{
		if(!line.empty()) // if line is empty skip the line
		{
			istringstream iss(line);

			string word1; string word2 = ""; // word 1 is the word word 2 is the translations of the word	
			
			iss >> word1; // first get word
			
			string tempword2;
			while(iss >> tempword2) // get all translations and add to word2 at once
			{
				word2 += tempword2 + " ";
			}
				
			word2 = word2.substr(0, word2.length() - 1); // remove ' ' at the end
			
			int current = dictionaryFile.tellg(); // while searching, if the same word exists getting back the extra getline
			Same_Word_Fill(dictionaryFile, word1, word2, current); // if same word add to the translation of the word
			dictionaryFile.seekg(current); // get back the extra getline() in order to prevent skipping lines;
		
			avlDictionary.insert(word1, word2); // insert to the tree
		}
	}
}

int main()
{
	AvlTree<string> avlDictionary;

	ifstream dictionaryFile; // file that contains the dictionary txt
	dictionaryFile.open("dictEN.txt");

	Fill_The_Tree(dictionaryFile, avlDictionary); // fill the tree

	Options(avlDictionary);
	
	return 0;
}
