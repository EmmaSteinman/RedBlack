//=======================================================================================
//Emma Steinman and
//RedBlack.h
//This file contains the function declarations for the Red Black Tree Class
//November 17, 2017
//=======================================================================================
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
using namespace std;
//=======================================================================================
//=======================================================================================
#ifndef REDBLACK_H
#define REDBLACK_H
template <class KeyType>
class Node
{
public:
	KeyType 	*data;
	Node 			*left;
	Node 			*right;
	Node			*p;
	string 		color;

	Node		(void)																		//default constructor
	{
		data = NULL;
		left = NULL;
		right = NULL;
		p = NULL;
		color = "red";
	};
	Node		(KeyType *item)														//constructor with item
	{
		data = item;
		left = NULL;
		right = NULL;
		p = NULL;
		color = "red";
	};
	Node 		(KeyType *item, Node<KeyType>* nil)				//nil pointer constuctor
	{
		data = item;
		left = nil;
		right = nil;
		p = nil;
		color = "red";
	};


};

template <class KeyType>
class RBT
{
protected:
	void 						RBTFix					(Node<KeyType> *current);
	void 						LeftRotate			(Node<KeyType> *z);
	void 						RightRotate			(Node<KeyType> *z);
	string					inOrderHelper		(Node<KeyType> *z, stringstream &s);
	string					preOrderHelper	(Node<KeyType> *z, stringstream &s);
	string					postOrderHelper	(Node<KeyType> *z, stringstream &s);
	Node<KeyType>* 	copy						(Node<KeyType> *z);
	void 						clear						(Node<KeyType> *z);
	Node<KeyType>*	find						(Node<KeyType> *r, KeyType k) const;

public:

	Node<KeyType> * root;        	// root pointer for red black tree
	Node<KeyType> * nil;		// null pointer for leaf nodes

                	RBT         		(void);
                 ~RBT         		(void);
                	RBT         		(const RBT<KeyType> & r);

    bool        	Empty       		(void) const;
    KeyType     	*get        		(const KeyType& k);
    void        	insert      		(KeyType *k);
    void        	remove      		(const KeyType& k);
    KeyType     	*maximum    		(void) const;
    KeyType     	*minimum    		(void) const;
    KeyType     	*successor  		(const KeyType& k) const;
    KeyType     	*predecessor		(const KeyType& k) const;
    string      	inOrder     		(void) const;
    string      	preOrder    		(void) const;
    string      	postOrder   		(void) const;

};


class EmptyError {};

#endif
#include "RedBlack.cpp"
