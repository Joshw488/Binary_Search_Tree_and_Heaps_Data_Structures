// File:	bintree.cpp
// Author:	Josh Watts
// Date:	2/3/20
// Description:
// Implementation of a binary search tree, nodes are created with 
// node data objects (see nodedata), and pointers to the left and 
// right children. Nodes on the left are to be smaller than its 
// parent, nodes on the right are to be larger than its parent. 
#include "bintree.h"

// ---------------------------------------------------------------------------
// Default constructor
// Initilize the root to null.
BinTree::BinTree()
{
	this->root = NULL;
}

// ---------------------------------------------------------------------------
// Overloaded copy constructor(BinTree)
// Initilize the root to null and use the assignment operator to create a 
// deep copy tree. 
BinTree::BinTree(const BinTree &treeToCopy)
{
	this->root = NULL;	//make a new null tree root
	//use the overloaded assignment operator to create an identical tree
	*this = treeToCopy;
}

// ---------------------------------------------------------------------------
// Destructor
// Use function makeEmpty to delete every node from the tree and retrieve
// the allocated memory.
BinTree::~BinTree()
{
	this->makeEmpty();
}

// ---------------------------------------------------------------------------
// isEmpty()
// Test if the tree is empty. If the root of the tree is set to null, it
// can not hold any values. If the root has data, it is not empty.
// True if empty, false if not.
bool BinTree::isEmpty() const 
{
	//the tree is empty only if the root is empty
	if (this->root == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// ---------------------------------------------------------------------------
// makeEmpty()
// Call makeEmptyHelper() to delete all nodes from the tree. Traverse to the bottom
// of the tree and start deleting and setting the values to null to recoupe memory.
// Recursively pop back up and delete the next lowest node.
void BinTree::makeEmpty()
{
	//use the helper class starting at the root
	makeEmptyHelper(this->root);
}

// ---------------------------------------------------------------------------
// makeEmptyHelper()
// Delete all nodes from the tree. Traverse to the bottom
// of the tree and start deleting and setting the values to null to recoupe memory.
// Recursively pop back up and delete the next lowest node.
void BinTree::makeEmptyHelper(Node*& current)
{
	if (current != NULL)
	{
		//go to the bottom of the tree first so you delete from there
		makeEmptyHelper(current->left);
		makeEmptyHelper(current->right);

		if (current->data != NULL)
		{
			delete current->data; //return memory
			current->data = NULL; //make data null so program behaves properly
		}

		delete current;	//return memory
		current = NULL;	//make node null so program behaves properly
	}
}

// ---------------------------------------------------------------------------
// Overloaded assignment operator
// Assign the values from the right side to the left side(this). Test
// if the two sides are equal by calling the overloaded equality operator,
// if they are, return one of them. Test if the rightHandSide is null, if it
// is, return a new tree with root as null. Call the assignment helper to
// handle the assignments (see assignmentHelper())
BinTree& BinTree::operator=(const BinTree &rightHandSide)
{
	//check if they are the same tree
	if (rightHandSide == *this)
		return *this;
	//check if the root is null
	if (rightHandSide.root == NULL)
		return *new BinTree();

	//delete the tree and assign the right to right
	this->makeEmpty();
	return assignmentHelper(rightHandSide.root);
}

// ---------------------------------------------------------------------------
// assignmentHelper(*Node)
// Assign the values from the right side to the left side(this). Use in-order
// traversal to insert the nodes in a manner that retains the binary search tree
// structure. Insertion is handled by the insertion helper.
BinTree& BinTree::assignmentHelper(Node* current)
{
	//if the node is not a leaf, add the node and call its children
	if (current != NULL)
	{
		//preorder insertion insures that the tree structure remains the same
		NodeData* temp = new NodeData(*current->data);	//create new nodeData so that memory locations are different
		insertHelper(temp, this->root);
		temp = NULL;
		assignmentHelper(current->left);
		assignmentHelper(current->right);
	}
	return *this;
}

// ---------------------------------------------------------------------------
// Overloaded equality operator
// Test if the rightHandSide tree equals the left side (this). If the 
// trees are both null, they are equal. Call equalityHelper() to handle
// the rest, see equalityHelper().
bool BinTree::operator==(const BinTree &rightHandSide) const
{
	//if both are null they are the same
	if (this->root == NULL && rightHandSide.root == NULL)
		return true;
	//call the recursive test
	else
		return equalityHelper(this->root, rightHandSide.root);
}

// ---------------------------------------------------------------------------
// equalityHelper
// Test if the rightHandSide tree equals the left side (this). Recursively 
// check if each node is equal to the same node in the other tree. If all
// tests pass, test the children.
bool BinTree::equalityHelper(Node* leftHandSide, Node* rightHandSide) const
{
	//check if one or the other is null, but not both
	if (leftHandSide == NULL ^ rightHandSide == NULL)
		return false;
	//if they both equal null, they are still equal
	if (leftHandSide == NULL && rightHandSide == NULL)
		return true;
	//check if they dont equal the same value
	if (*leftHandSide->data != *rightHandSide->data)
		return false;
	//call the checking on their children
	else
	{
		return (*leftHandSide->data == *rightHandSide->data) 
			&& (equalityHelper(leftHandSide->left, rightHandSide->left)) 
			&& (equalityHelper(leftHandSide->right, rightHandSide->right));
	}
}

// ---------------------------------------------------------------------------
// Overloaded inequality operator
// Use the overloaded equality operator to determine if two trees are equal, then
// reverse the logic with !.
bool BinTree::operator!=(const BinTree &rightHandSide) const
{
	//reverse the equality logic
	return !(*this == rightHandSide);
}

// ---------------------------------------------------------------------------
// insert
// Insert a node into (this), maintaining the bianary search tree structure
// by testing if the data is less (left) or greater (right). Utilizes
// insertHelper to add the node.
bool BinTree::insert(NodeData* addNode)
{
	//call the recursive version of insert
	return insertHelper(addNode, this->root);
}

// ---------------------------------------------------------------------------
// insertHelper
// Insert a node into (this), maintaining the bianary search tree structure
// by testing if the data is less (left) or greater (right). Once the
// insertion position is reached, a new data is created with null children.
// There is no = in either test so duplicate data is consumed.
bool BinTree::insertHelper(NodeData* addNode, Node*& currentNode)
{
	//base case, node is empty, create and add the node
	if (currentNode == NULL)
	{
		currentNode = new Node;
		currentNode->data = addNode;
		currentNode->left = NULL;
		currentNode->right = NULL;
		return true;
	}
	//the data is smaller than the node, run insert with left as current
	else if (*addNode < *currentNode->data)
	{
		insertHelper(addNode, currentNode->left);
	}
	//the data is larger than the node, run insert with right as current
	else if (*addNode > *currentNode->data)
	{
		insertHelper(addNode, currentNode->right);
	}
	//data equals either the left or right
	else
	{
		//therefore consume
		return false;
	}
}

// ---------------------------------------------------------------------------
// retrieve
// Retrieve a given data in the tree, use the binary search tree structure to 
// locate the data. foundNode is given the value of the found node and left null
// if not found. Uses retrieveHelper to do the retrieval.
bool BinTree::retrieve(const NodeData &data, NodeData* &foundNode)
{
	return retrieveHelper(data, foundNode, this->root);
}

// ---------------------------------------------------------------------------
// retrieveHelper
// Retrieve a given data in the tree, use the binary search tree structure to 
// locate the data. foundNode is given the value of the found node and left null
// if not found.
bool BinTree::retrieveHelper(const NodeData &data, NodeData*& foundNode, Node*& currentNode)
{
	//base case, node is not in the tree
	if (currentNode == NULL)
	{
		foundNode = NULL;
		return false;
	}
	//current node is one being searched for
	else if (*currentNode->data == data)
	{
		foundNode = currentNode->data;
		return true;
	}
	//value is smaller than current, call with left as new current
	else if (data < *currentNode->data)
	{
		retrieveHelper(data, foundNode, currentNode->left);
	}
	//value is greater than current, call with right as new current
	else if (data > *currentNode->data)
	{
		retrieveHelper(data, foundNode, currentNode->right);
	}
}

// ---------------------------------------------------------------------------
// getHeight
// Find the height of a given node, height of a leaf is 1 and each node
// above that is 1 higher, a height of 0 is not found. Calls heightHelper
// to find the height
int BinTree::getHeight(const NodeData &nodeToFind) const
{
	return heightHelper(nodeToFind, this->root, 0);
}

// ---------------------------------------------------------------------------
// depthHelper
// Find the height of a given node already found. Calculate the height of
// every leaf node and take the height which is the largest.
int BinTree::depthHelper(const NodeData &nodeToFind, Node* currentNode, int count, int height) const
{
	//if the node is below a leaf, make set height
	if (currentNode == NULL)
	{
		//if the leaf is deeper than a previous depth, update it
		if (count > height)
		{
			height = count;
			return height;
		}
	}
	else
	{
		//call the height helper on each side of each node (left & right children)
		//add 1 to the height each time current goes down, and minus 1 each time is pops
		height = depthHelper(nodeToFind, currentNode->left, ++count, height);
		count--;
		height = depthHelper(nodeToFind, currentNode->right, ++count, height);
		count--;
	}

	return height;
}

// ---------------------------------------------------------------------------
// heightHelper
// Find the height of a given node, height of a leaf is 1 and each node
// above that is 1 higher, a height of 0 is not found. Traverse the tree
// until the nodeToFind is found. This function cannot use the binary
// search tree properties to traverse, each path is run. When the node
// is found, call the depthHelper to find the height.
int BinTree::heightHelper(const NodeData &nodeToFind, Node* currentNode, int height) const
{
	if (currentNode == NULL)
	{
		//reached a null node, pop up 
		return height;
	}
	//the node has been reached
	else if (*currentNode->data == nodeToFind)
	{
		//find the depth of the deepest child (see depthHelper())
		height = depthHelper(nodeToFind, currentNode, 0, 0);
	}
	else
	{
		//call the height helper on each side of each node to search for the nodeToFind
		height = heightHelper(nodeToFind, currentNode->left, height);
		height = heightHelper(nodeToFind, currentNode->right, height);
	}
}


// ---------------------------------------------------------------------------
// bstreeToArray
// Convert the given tree to an array using the in-order traversal. The
// conversion is handled by the toArrayHelper, and the tree is deleted
// after. The array is assumed to be size 100, and the values are assumed
// to be null.
void BinTree::bstreeToArray(NodeData* arrayToFill[])
{
	//if this != null?
	toArrayHelper(arrayToFill, this->root, 0);

	//recoup memory of tree and make empty
	this->makeEmpty();
}

// ---------------------------------------------------------------------------
// toArrayHelper
// Convert the given tree to an array using the in-order traversal.
// The array is assumed to be size 100, and the values are assumed
// to be null.
int BinTree::toArrayHelper(NodeData* arrayToFill[], Node* currentNode, int element)
{
	//base case, pop up
	if (currentNode == NULL)
		return element;

	//go to left most leaf
	element = toArrayHelper(arrayToFill, currentNode->left, element);

	//assign data to array
	NodeData *temp;
	temp = currentNode->data;
	currentNode->data = NULL;	//remove temp from the same memory location as current
	arrayToFill[element++] = temp;	//post increment for next insert
	temp = NULL;
	
	//go to right leaf
	element = toArrayHelper(arrayToFill, currentNode->right, element);

	return element;
}

// ---------------------------------------------------------------------------
// arrayToBSTree
// Convert the given array to a binary search tree, the middle is added
// to the array each pass. The middle of the array is found by using 
// the formula low + high / 2.
void BinTree::arrayToBSTree(NodeData* arrayToCopy[])
{
	//delete the previous array
	this->makeEmpty();

	int high = 0;

	//get the number of elements in the array
	for (int i = 0; i < 100; i++)
	{
		if (arrayToCopy[i] != NULL)
			high++;
	}

	toTreeHelper(arrayToCopy, 0, high-1);
}

// ---------------------------------------------------------------------------
// toTreeHelper
// Convert the given array to a binary search tree, the middle is added
// to the array each pass. The middle of the array is found by using 
// the formula low + high / 2.
void BinTree::toTreeHelper(NodeData* arrayToFill[], int low, int high)
{
	if (low > high)
	{
		return;
	}

	//find the middle point in the given range
	int mid = (low + high) / 2;

	//create new data and insert it
	NodeData *temp;
	temp = arrayToFill[mid];
	arrayToFill[mid] = NULL;
	//use insert method to add data properly
	insert(temp);	

	//call helper on the lower half
	toTreeHelper(arrayToFill, low, mid - 1);
	//call helper on the higher half
	toTreeHelper(arrayToFill, mid + 1, high);
}

// ---------------------------------------------------------------------------
// overloaded output operator
// Output the binary search tree using in-order traversal (handled by inorderHelper).
// Left is printed first, then the node, then the right.
ostream& operator<<(ostream &outStream, const BinTree &tree)
{
	tree.inorderHelper(tree.root);
	outStream << endl;
	return outStream;
}

// ---------------------------------------------------------------------------
// inorderHelper
// Traverse the tree inorder, left is printed first, then the node, then the right.
void BinTree::inorderHelper(Node* currentNode) const
{
	if (currentNode != NULL)
	{
		inorderHelper(currentNode->left);
		cout << *currentNode->data << " ";
		inorderHelper(currentNode->right);
	}
}


//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}
