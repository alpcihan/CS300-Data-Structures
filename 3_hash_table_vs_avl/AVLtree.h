// CS 300 HW3

#ifndef _AVLTREE_H
#define _AVLTREE_H

#include <string>
#include <iostream>
using namespace std;

template <class Temp>
struct wordNode
{
	Temp word; // english word
	Temp transWord; // translation of the english word
	wordNode* left; // left of the wordNode
	wordNode* right; // righ of the wordNode
	int height; // height of the wordNode respect to its location in the AVL tree

	wordNode(Temp wrd, Temp trnsWrd, wordNode* lft, wordNode* rght, int hght = 0) 
		: word(wrd), transWord(trnsWrd), left(lft), right(rght), height(hght)
	{
	}	
};

template <class Temp>
class AvlTree
{
private:
	wordNode<Temp>* root;
	int max( int lhs, int rhs );
	void insert( Temp wrd, Temp trnsWrd, wordNode<Temp>* & ptr );
	Temp & elementAt( wordNode<Temp>* ptr );

	wordNode<Temp>* find( Temp & wrd, wordNode<Temp>* ptr ); 
	const Temp ITEM_NOT_FOUND;

	void makeEmpty ( wordNode<Temp> * & ptr );

public:
	AvlTree();
	~AvlTree();

	void insert( Temp wrd, Temp trnsWrd );
	int height( wordNode<Temp>* ptr );
	void rotateWithRightChild( wordNode<Temp>* & k1 );
	void rotateWithLeftChild( wordNode<Temp>* & k2 );
	void doubleWithLeftChild( wordNode<Temp>* & k3 );
	void doubleWithRightChild( wordNode<Temp>* & k1 );

	Temp find( Temp & wrd );
	void makeEmpty();
};

template <class Temp>
AvlTree<Temp>::AvlTree()
{
	root = NULL;
}

template <class Temp>
AvlTree<Temp>::~AvlTree()
{
	makeEmpty();
}

template <class Temp>
int AvlTree<Temp>::height( wordNode<Temp> * ptr )
{
	if (ptr == NULL)
		return -1;

	return ptr -> height;
}

template <class Temp>
int AvlTree<Temp>::max( int lhs, int rhs )
{
	if (lhs > rhs)
		return lhs;

	return rhs;            
}

template <class Temp>
void AvlTree<Temp>::rotateWithLeftChild( wordNode<Temp>* & k2 ) 
{
	wordNode<Temp> *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
	k1->height = max( height( k1->left ), k2->height ) + 1;
	k2 = k1;
}
template <class Temp>
void AvlTree<Temp>::rotateWithRightChild( wordNode<Temp> * & k1 )
{
	wordNode<Temp> *k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
	k2->height = max( height( k2->right ), k1->height ) + 1;
	k1 = k2;
}
template <class Temp>
void AvlTree<Temp>::doubleWithLeftChild( wordNode<Temp> * & k3 )
{
	rotateWithRightChild( k3->left );
	rotateWithLeftChild( k3 );
}
template <class Temp>
void AvlTree<Temp>::doubleWithRightChild( wordNode<Temp> * & k1 )
{
	rotateWithLeftChild( k1->right );
	rotateWithRightChild( k1 );
}

template <class Temp>
void AvlTree<Temp>::insert( Temp wrd, Temp trnsWrd, wordNode<Temp>* & ptr )
{
	if ( ptr == NULL ) // if avl tree is empty insert new node to the root
		ptr = new wordNode<Temp>( wrd, trnsWrd, NULL, NULL );

	else if ( wrd < ptr -> word )
	{
		insert( wrd, trnsWrd, ptr -> left );

		if ( height( ptr -> left ) - height( ptr -> right ) == 2 )
		{
			if ( wrd < ptr -> left -> word ) 
			{
				rotateWithLeftChild( ptr );
			}
			else // X was inserted to the left-right subtree!
			{
				doubleWithLeftChild( ptr );
			}			
		}
	}
	else if( ptr -> word < wrd )
	{    // Otherwise X is inserted to the right subtree
		insert( wrd, trnsWrd, ptr -> right );
		if ( height( ptr -> right ) - height( ptr -> left ) == 2 )
		{
			if ( ptr -> right -> word < wrd )
			{
				rotateWithRightChild( ptr );
			}						
			else // X was inserted to right-left subtree
			{
				doubleWithRightChild( ptr );
			}
		}				
	}
	else // if word already exists instead of inserting the word insert translation to the word's translation
	{
		ptr -> transWord += ", " + trnsWrd;
	}
	// update the height the node
	ptr -> height = max( height( ptr -> left ), height( ptr -> right ) ) + 1;
}
template <class Temp>
void AvlTree<Temp>::insert( Temp wrd, Temp trnsWrd )
{
	insert(wrd, trnsWrd, root);
}

template <class Temp>
Temp & AvlTree<Temp>::elementAt( wordNode<Temp>* ptr )
{
	return ptr -> transWord;
}

template <class Temp>
wordNode<Temp>* AvlTree<Temp>::find( Temp & wrd, wordNode<Temp> * ptr ) 
{
	if ( ptr == NULL )
		return NULL;

	else if( wrd < ptr->word )
		return find( wrd, ptr->left );

	else if( ptr->word < wrd )
		return find( wrd, ptr->right );

	else
		return ptr; // Match
}

template <class Temp>
Temp AvlTree<Temp>::find( Temp & wrd )
{
	wordNode<Temp>* ptr = find(wrd, root);
	
	if(ptr ==NULL)
		return "";
	else
		return elementAt( find( wrd, root ) );
}

template <class Temp>
void AvlTree<Temp>::makeEmpty( wordNode<Temp> * & ptr ) 
{
	if( ptr != NULL )
	{
		makeEmpty( ptr->left );
		makeEmpty( ptr->right );
		delete ptr;
	}
	ptr = NULL;
}
template <class Temp>
void AvlTree<Temp>::makeEmpty()
{
	makeEmpty(root);
}
#endif
