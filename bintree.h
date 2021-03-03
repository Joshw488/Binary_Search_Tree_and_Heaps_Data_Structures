// File:	bintree.h
// Author:	Josh Watts
// Date:	2/3/20
// Description:
// Implementation of a binary search tree, nodes are created with 
// node data objects (see nodedata), and pointers to the left and 
// right children. Nodes on the left are to be smaller than its 
// parent, nodes on the right are to be larger than its parent. 
#ifndef BINTREE_H
#define BINTREE_H

#include "nodedata.h"

class BinTree 
{		
	//overloaded output stream
	friend std::ostream& operator<<(std::ostream &outStream, const BinTree &);

public:
	//BST constructors/destructors
	BinTree();								// constructor
	BinTree(const BinTree &);				// copy constructor
	~BinTree();								// destructor, calls makeEmpty	

	//Test BST empty and make empty
	bool isEmpty() const;					
	void makeEmpty();						

	//Overloaded assingment operator
	BinTree& operator=(const BinTree &);

	//Overloaded equality/ inequality operators
	bool operator==(const BinTree &) const;
	bool operator!=(const BinTree &) const;

	//Getter and setter
	bool insert(NodeData*);
	bool retrieve(const NodeData &, NodeData* &);
	int getHeight(const NodeData &) const;

	//Display function to show the tree sideways
	void displaySideways() const;			

	//Conversion functions to convert a tree to array and vice versa
	void bstreeToArray(NodeData*[]);
	void arrayToBSTree(NodeData*[]);
	
private:
	struct Node {
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
	};
	Node* root;								// root of the tree

	// Utility/helper functions
	void inorderHelper(Node*) const;			//assists inOrder traversa;
	void sideways(Node*, int) const;			//assists display sideways
	bool insertHelper(NodeData*, Node*&);		//assists insert
	bool retrieveHelper(const NodeData &, NodeData*& , Node*&);	//assists retrieve
	int depthHelper(const NodeData &, Node*, int, int) const;	//assists height helper
	int heightHelper(const NodeData &, Node*, int) const;		//assists getHeight
	bool equalityHelper(Node*, Node*) const;	//assists overloaded equality operator
	BinTree& assignmentHelper(Node*);			//assists overloaded assignment operator
	void makeEmptyHelper(Node*&);				//assists makeEmpty
	int toArrayHelper(NodeData*[], Node*, int);//assists bstreeToArray
	void toTreeHelper(NodeData*[], int, int);	//assists arrayToBSTree

};
#endif 