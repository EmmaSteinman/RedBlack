//=======================================================================================
//Emma Steinman and
//RedBlack.cpp
//This file contains the methods for the Red Black Tree Class
//November 17, 2017
//=======================================================================================
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
using namespace std;


//=======================================================================================
//public methods
//=======================================================================================

//=======================================================================================
//Default Constructor
//Pre-Condition:
//Post-Condition:
//Parameters: void
//Return Value: void
//=======================================================================================
template <class KeyType>
			RBT<KeyType>::RBT	(void)
{
	root = nil;
}
//=======================================================================================
//Copy Constructor
//Pre-Condition:
//Post-Condition:
//Parameters: void
//Return Value: void
//=======================================================================================
template <class KeyType>
			RBT<KeyType>::RBT		(const RBT<KeyType> & r)
{
	root = copy(r.root);
}
//=======================================================================================
//Destructor
//Pre-Condition:
//Post-Condition:
//Parameters: void
//Return Value: void
//=======================================================================================
template <class KeyType>
			RBT<KeyType>::~RBT		(void)
{
	Node<KeyType> *ptr = root;
	if (ptr != nil)
	{
		clear(ptr->left);
		clear(ptr->right);
		delete ptr;
	}
}
//=======================================================================================
//Empty
//Tests if RBT is empty
//Pre-Condition:
//Post-Condition:
//Parameters: void
//Return Value: boolean value indicating whether RBT is empty
//=======================================================================================
template <class KeyType>
bool 		RBT<KeyType>::Empty		(void)	const
{
	return (root == nil);
}
//=======================================================================================
//get
//finds item in RBT
//Pre-Condition:
//Post-Condition:
//Parameters: KeyType &k - item to be found
//Return Value: KeyType* - pointer to item
//=======================================================================================
template <class KeyType>
KeyType*	RBT<KeyType>::get		(const KeyType &k)
{
	Node<KeyType> *current = root;
	while (current != nil && *current->data != k)
	{
		if (k > *current->data)
		{
			current = current->right;
		}
		else
		{
			current = current->left;
		}
	}
	if (current == nil)
	{
		throw EmptyError();
	}
	return current->data;							//??? should we return this or just current lmk
}
//=======================================================================================
//insert
//inserts item into RBT
//Pre-Condition:
//Post-Condition:
//Parameters: KeyType *k - pointer to item to be inserted
//Return Value: void
//=======================================================================================
template <class KeyType>
void		RBT<KeyType>::insert	(KeyType *k)
{
	Node<KeyType> *parent = nil;
	Node<KeyType> *current = root;
	Node<KeyType> *newNode = new Node<KeyType>(k, nil);			//?????
	//newNode->left = nil;
	//newNode->right = nil;
	while (current != nil)												//find where to insert newNode
	{
		parent = current;
		if (*newNode->data > *current->data)
		{
			current = current->right;
		}
		else
		{
			current = current->left;
		}
	}
	if (current == nil)														//newNode inserted at root
	{
		root = newNode;
	}
	if (current == current->p->left)							//newNode should be inserted to left
	{
		parent->left = newNode;
	}
	else
	{
		parent->right = newNode;										//inserted to right
	}

	RBTFix(newNode);															//fix black heights and balance tree


}
/*
//=======================================================================================
//remove
//removes item from RBT
//Pre-Condition:
//Post-Condition:
//Parameters: KeyType &k - item to be removed
//Return Value: void
//=======================================================================================
template <class KeyType>
void		RBT<KeyType>::remove	(const KeyType &k)
{


}*/
//=======================================================================================
//maximum
//returns maximum item in RBT
//Pre-Condition:
//Post-Condition:
//Parameters: void
//Return Value: KeyType* - pointer to maximum value
//=======================================================================================
template <class KeyType>
KeyType*	RBT<KeyType>::maximum	(void)	const
{
	Node<KeyType> *ptr = root;
	if (ptr == nil)
	{
		throw EmptyError();
	}
	else
	{
		while (ptr->right != nil)
		{
			ptr = ptr->right;												//rightmost item in tree
		}
	}
	return ptr->data;														//again do we return this or just ptr??
}
//=======================================================================================
//minimum
//returns minimum item in RBT
//Pre-Condition:
//Post-Condition:
//Parameters: void
//Return Value: KeyType* - pointer to minimum value
//=======================================================================================
template <class KeyType>
KeyType*	RBT<KeyType>::minimum	(void)	const
{
	Node<KeyType> *ptr = root;
	if (ptr == nil)
	{
		throw EmptyError();
	}
	else
	{
		while (ptr->left != nil)
		{
			ptr = ptr->left;												//leftmost item in tree
		}
	}
	return ptr->data;														//return ptr->data or ptr?????
}
//=======================================================================================
//successor
//finds successor of an item in RBT
//Pre-Condition:
//Post-Condition:
//Parameters: KeyType &k - item to find successor of
//Return Value: KeyType* - pointer to successor
//=======================================================================================
template <class KeyType>
KeyType*	RBT<KeyType>::successor	(const KeyType &k)	const
{
	Node<KeyType> *z = find(root, k);
	if (root == nil)
	{
		throw EmptyError();
	}
	else
	{
		if (z->right != nil)									//returns minimum in right subtree
		{
			return minimum(z->right);
		}
		else
		{
			Node<KeyType> *par = z->p;
			while (par != nil && z == par->right)
			{
				z = par;
				par = par->p;											//goes all the way back left and
			}																		//one right
			return par->data;
		}
	}
}
//=======================================================================================
//predecessor
//finds predecessor of an item in RBT
//Pre-Condition:
//Post-Condition:
//Parameters: KeyType &k - item to find predecessor of
//Return Value: KeyType* - pointer to predecessor
//=======================================================================================
template <class KeyType>
KeyType*	RBT<KeyType>::predecessor(const KeyType &k)	const
{
	Node<KeyType> *z = find(root, k);
	if (root == nil)																//empty tree
	{
		throw EmptyError();
	}
	else
	{
		if (z->left != nil)														//returns maximum in left subtree
		{
			return maximum(z->left);
		}
		else
		{
			Node<KeyType> *par = z->p;
			while (par != nil && z == par->left)
			{
				z = par;
				par = par->p;															//goes all the way back left
			}																						//and one right
			return par->data;
		}
	}
}
//=======================================================================================
//inOrder
//returns string in order of elements in RBT
//Pre-Condition:
//Post-Condition:
//Parameters: void
//Return Value: string inOrder (left, node, right)
//=======================================================================================
template <class KeyType>
string		RBT<KeyType>::inOrder	(void)	const
{
	stringstream s;
	if (root == nil)
	{
		throw EmptyError();
	}
	string str = inOrderHelper(root, s);
	str.pop_back();													//removes trailing space from helper function
	return str;
}
//=======================================================================================
//preOrder
//returns string in pre order of elements in RBT
//Pre-Condition:
//Post-Condition:
//Parameters: void
//Return Value: string in preOrder (node, left, right)
//=======================================================================================
template <class KeyType>
string		RBT<KeyType>::preOrder	(void) const
{
	stringstream s;
	if (root == nil)
	{
		throw EmptyError();
	}
	string str = preOrderHelper(root, s);
	str.pop_back();													//removes trailing space from helper function
	return str;
}
//=======================================================================================
//postOrder
//returns string in post order of elements in RBT
//Pre-Condition:
//Post-Condition:
//Parameters: void
//Return Value: string in postOrder (left, right, node)
//=======================================================================================
template <class KeyType>
string		RBT<KeyType>::postOrder	(void)	const
{
	stringstream s;
	if (root == nil)
	{
		throw EmptyError();
	}
	string str = postOrderHelper(root, s);
	str.pop_back();													//removes trailing space from helper function
	return str;
}

//=======================================================================================
//protected methods
//=======================================================================================


//=======================================================================================
//LeftRotate
//rotates the node left
//Pre-Condition:
//Post-Condition:
//Parameters: Node *current - pointer to node to be rotated
//Return Value: void
//=======================================================================================
template <class KeyType>
void		RBT<KeyType>::LeftRotate(Node<KeyType> *z)
{
	Node<KeyType> y = z->right;					//sets y to z's right child
	z->right = y->left;									//sets z's right subtree to y's left subtree
	if (y->left != nil)
	{
		y->left->p = z;										//sets y's left subtree parent to z
	}
	y->p = z->p;												//sets y's parent to z's parent
	if (z->p == nil)										//case 1: z is root
	{
		root = y;
	}
	else if (z == z->p->left)						//case 2: z is left child
	{
		z->p->left = y;
	}
	else 																//case 3: z is right child
	{
		z->p->right = y;
	}
	y->left = z;												//put z on y's left
	z->p = y;
}
//=======================================================================================
//RightRotate
//rotates node right
//Pre-Condition:
//Post-Condition:
//Parameters:  Node *current - pointer to node to be rotated
//Return Value: void
//=======================================================================================
template <class KeyType>
void		RBT<KeyType>::RightRotate(Node<KeyType> *z)
{
	Node<KeyType> y = z->left;					//sets y to z's left child
	z->left = y->right;									//sets y's right subtree to z's left subtree
	if (y->right != nil)
	{
		y->right->p = z;
	}
	y->p = z->p;
	if (z->p == nil)										//case 1: z is root
	{
		root = y;
	}
	else if (z == z->p->left)						//case 2: z is left child
	{
		z->p->left = y;
	}
	else																//case 3: z is right child
	{
		z->p->right = y;
	}
	y->right = z;												//put z on y's right
	z->p = y;
}
//=======================================================================================
//RBTFix
//"fixes" RBT to uphold RBT properties after an insert
//Pre-Condition:
//Post-Condition:
//Parameters: Node *current - pointer to node to be rotated
//Return Value: void
//=======================================================================================
template <class KeyType>
void		RBT<KeyType>::RBTFix	(Node<KeyType> *current)
{
	while (current->p->color == "red")
	{
		if (current->p == current->p->p->left)							//parent is left child
		{
			Node<KeyType> *uncle = current->p->p->right;
			if (uncle->color == "red")												//if uncle is red can just
			{																									//change color of parent
				current->p->color = "black";										//and uncle to fix
				uncle->color = "black";													//black height
				current->p->p->color = "red";
				current = current->p->p;
			}
			else
			{
				if (current == current->p->right)
				{
					current = current->p;													//makes current a
					LeftRotate(current);													//left child
				}
				current->p->color = "black";
				current->p->p->color = "red";										//fixes colors
				RightRotate(current->p->p);											//right rotate
			}
		}
		else																								//parent is right child
		{
			Node<KeyType> *uncle = current->p->p->left;
			if (uncle->color == "red")
			{
				current->p->color = "black";										//switches color of uncle
				uncle->color = "black";													//and parent to fix
				current->p->p->color = "red";										//black height
				current = current->p->p;
			}
			else
			{
				if (current == current->p->left)
				{
					current = current->p;
					RightRotate(current);													//makes current a right
				}																								//child
				current->p->color = "black";
				current->p->p->color = "red";										//fixes colors
				LeftRotate(current->p->p);											//left rotate
			}
		}
	}
	root->color = "black";																//fixes root color to black
}

//=======================================================================================
//inOrderHelper
//creates string inOrder
//Pre-Condition:
//Post-Condition:
//Parameters: Node *z - pointer to node to be printed
//						stringstream s: stringstream to be loaded
//Return Value: string in order (left, node, right)
//=======================================================================================
template <class KeyType>
string		RBT<KeyType>::inOrderHelper(Node<KeyType> *z, stringstream &s)
{
	if (z != nil)
	{
		inOrderHelper(z->left, s);
		s << (*z->data);
		s << " ";
		inOrderHelper(z->right, s);
	}
	return s.str();
}
//=======================================================================================
//preOrderHelper
//rotates node right
//Pre-Condition:
//Post-Condition:
//Parameters: Node *z - pointer to node to be printed
//						stringstream s: stringstream to be loaded
//Return Value: string in preOrder (node, left, right)
//=======================================================================================
template <class KeyType>
string		RBT<KeyType>::preOrderHelper(Node<KeyType> *z, stringstream &s)
{
	if (z != nil)
	{
		s << (*z->data);
		s << " ";
		preOrderHelper(z->left, s);
		preOrderHelper(z->right, s);
	}
	return s.str();
}

//=======================================================================================
//postOrderHelper
//rotates node right
//Pre-Condition:
//Post-Condition:
//Parameters: Node *z - pointer to node to be printed
//						stringstream s: stringstream to be loaded
//Return Value: string in order (left, right, node)
//=======================================================================================
template <class KeyType>
string		RBT<KeyType>::postOrderHelper(Node<KeyType> *z, stringstream &s)
{
	if (z != nil)
	{
		postOrderHelper(z->left, s);
		postOrderHelper(z->right, s);
		s << (*z->data);
		s << " ";
	}
	return s.str();
}

//=======================================================================================
//copy
//Pre-Condition:
//Post-Condition:
//Parameters: Node<KeyType> *z - pointer to begin copying
//Return Value: Node<KeyType>* - pointer to copied tree
//=======================================================================================
template <class KeyType>
Node<KeyType> * RBT<KeyType>::copy		(Node<KeyType> *z)
{
	if (z == nil)
	{
		return nil;
	}
	else
	{
		Node<KeyType> *ptr = new Node<KeyType>;
		ptr->data = z->data;
		ptr->left = copy(z->left);							//copy left subtree
		ptr->right = copy(z->right);						//copy right subtree
		return ptr;
	}

}


//=======================================================================================
//clear
//Pre-Condition:
//Post-Condition:
//Parameters: Node<KeyType> *ptr - pointer to node to begin deleting at
//Return Value: void
//=======================================================================================
template <class KeyType>
void 		RBT<KeyType>::clear		(Node<KeyType> *z)
{
	if (z != nil)
	{
		clear(z->left);												//clear left subtree
		clear(z->right);											//clear right subtree
		delete z;															//delete root
	}
}

//=======================================================================================
//find
//finds Node of an item in RBT
//Pre-Condition:
//Post-Condition:
//Parameters: KeyType &k - item to find successor of
//Return Value: KeyType* - pointer to successor
//=======================================================================================
template <class KeyType>
Node<KeyType>*	RBT<KeyType>::find	(Node<KeyType> *r, KeyType k)	const
{
	if (root == nil)													//empty tree
	{
		throw EmptyError();
	}
	else
	{
		if (r == nil)														//item not found
		{
			return nil;
		}
		else if (*r->data == k)
		{
			return r;
		}
		else if (*r->data != k)
		{
			if (k < *r->data)
			{
				find(r->left, k);										//search left subtree
			}
			else
			{
				find(r->right, k);									//search right subtree
			}
		}
	}
}
