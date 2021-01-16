/************************\
	SABANCI UNIVERSITY 
	SPRING 2018-2019
	CS300 HOMEWORK 1
\*************************/
#include <iostream>
#include <string>
#include "DynStack.h"

using namespace std;

/*************************************************************************\
	Reverse the mainStck by poping it to tempStck then equaling mainStck to
	tempStck by using operator overloading.
\*************************************************************************/
void Reverse_It ( DynStack<char> & mainStck )
{
	DynStack<char> tempStck;

	/*Pop from mainStck, pop to the tempStck */
	while( !mainStck.isEmpty() )
	{
		char ch;
		mainStck.pop(ch);
		tempStck.push(ch);
	}
	mainStck = tempStck; // Equal mainStck to tempStck with operator overloading.
}

/*************************************************************************\
	Delete the char before the '2' from the mainStck stack by poping it.
\*************************************************************************/
void Delete_Previous( DynStack<char> & mainStck )
{
	char ch;
	mainStck.pop(ch);
}

/**********************************************************************\
	Pop all chars from the mainStck and push to tempStck char if it
	is not same with tempChar char. Then push all chars into mainStck
	stack again.
\**********************************************************************/
void Delete_All_X ( DynStack<char> & mainStck, char tempChar )
{
	DynStack<char> tempStck; // to store not deleted chars

	while( !mainStck.isEmpty() ) // while mainStck stack is not empty
	{
		char ch;
		mainStck.pop(ch);

		if( ch != tempChar )
		{
			tempStck.push(ch);
		}

	}

	while( !tempStck.isEmpty() ) // while mainStck stack is not empty
	{
		char ch;
		tempStck.pop(ch);

		if( ch != tempChar )
		{
			mainStck.push(ch);
		}
	}
}

/******************************************************************\
	Move the invisible cursor right by pop ch from Stck2 stack
	and push ch to the mainStck stack.
\******************************************************************/
void Move_Right( DynStack<char> & mainStck, DynStack<char> & Stck2 )
{
	char ch = NULL;
	Stck2.pop(ch); // pop from mainStck
	
	if ( ch != NULL ) // If ch is not NULL
	{
		mainStck.push( ch ); // push to the Stck2	
	}
	
}

/******************************************************************\
	Move the invisible cursor left by pop ch from mainStck stack
	and push ch to the Stck2 stack.
\******************************************************************/
void Move_Left( DynStack<char> & mainStck, DynStack<char> & Stck2 )
{
	char ch = NULL;
	mainStck.pop( ch ); // pop from mainStck

	if ( ch != NULL ) // If ch is not NULL
	{
		Stck2.push( ch ); // push to the Stck2	
	}	
}

/*********************************************************************\
	Fill Stck2 stack to the mainStck stack.
	Then in order to proper the order of the output rever the mainStck
	stack then print the mainStck.
\*********************************************************************/
void Print_Stack( DynStack<char> & mainStck, DynStack<char> & Stck2 )
{
	/* Fill Stck2 stack to the mainStck stack */
	while ( !Stck2.isEmpty() )
	{
		char ch;
		Stck2.pop(ch);
		mainStck.push(ch);
	}

	/* Reverse the mainStck stack which will make it straight */
	Reverse_It (mainStck);

	/* Print the mainStck stack */
	while ( !mainStck.isEmpty() )
	{
		char ch;
		mainStck.pop(ch);
		cout << ch;
	}
	cout << endl;
}

/*******************************************************************\
	Get input from the user. Read the input char by char. 	 
	While reading the input store it in the "mainStck" stack.
	While storing the input send "mainsStck" stack to the related
	input manipulation function according to the input.
\*******************************************************************/
void Get_Input( DynStack<char> & mainStck, DynStack<char> & Stck2 )
{
	string input; // Input of the user.
	cin >> input; // Get input from the user.
	for(int i = 0; i < input.length(); i++ ) // Get input char by char.
	{
		if( input.at(i) == '1' ) // If ch is '1' end the process and print the final output.
		{
			Print_Stack ( mainStck, Stck2 );
			return;
		}
		else if( !mainStck.isEmpty() && input.at(i) == '2' ) // If ch is '2' and mainStck is not empty
		{
			Delete_Previous( mainStck );
		}
		else if( !mainStck.isEmpty() && input.at(i) == '3' ) // else if ch is equal to '3' and mainStck stack is not empty.
		{
			Move_Left( mainStck, Stck2 );
		}
		else if( !Stck2.isEmpty() && input.at(i) == '4' ) // else if ch is equal to '4' and Stck2 stack is not empty.
		{
			Move_Right( mainStck, Stck2 );
		}
		else if( !mainStck.isEmpty() && input.at(i) == '5' ) // else if ch is equal to '5' and mainStck stack is not empty.
		{
			Reverse_It ( mainStck );
		}
		else if( input.at(i) == '6' && // else if ch is equal to '6'
				(i+1) < input.length() && // If '6' is not the last element.
				!(input.at(i+1) >= '0' && input.at(i+1) <= '9') ) // if i+1 is not another number except 0 (it was not covered in the homework instructions)
		{
			Delete_All_X( mainStck, input.at(i+1) );
			i++;
		}
		else if( !(input.at(i) >= '0' && input.at(i) <= '9')  ) // If ch is not a input manipulator directly push ch to the mainStck stack 
		{
			mainStck.push(input.at(i));
		}
	}
}

int main()
{
	DynStack<char> mainStck, Stck2;

	Get_Input( mainStck, Stck2 );
	
	return 0;
}
