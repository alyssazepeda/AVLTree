#pragma once
#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

class AVLTree {

private:
	Node* root = nullptr;

public:
	//Insert an item to the binary search treeand perform rotation if necessary.
	void insert(const string&);

	//Return the balance factor of a given node.
	int balanceFactor(Node*);

	//Traverseand print the tree in inorder notation.Print the string followed by its balance factor in parentheses followed by a, and one space.
	void printBalanceFactors();

	//Generate dotty fileand visualize the tree using dotty program.Call this function beforeand after rotation.
	void visualizeTree(const string&);

private:
	//Find and return the closest unbalanced node(with balance factor of 2 or -2) to the inserted node.
	Node* findUnbalancedNode(Node*);

	//Implement four possible imbalance casesand update the parent of the given node.
	void rotate(Node*);

	//Rotate the subtree to left at the given nodeand returns the new subroot.
	Node* rotateLeft(Node*);

	//Rotate the subtree to right at the given nodeand returns the new subroot.
	Node* rotateRight(Node*);

	void printBalanceFactors(Node*);

	void visualizeTree(ofstream&, Node*);

	int height(Node*);

	int max(int, int);
};