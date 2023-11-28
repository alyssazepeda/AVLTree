//Collaborated with Kiyomi Sugita and Victor Omosor

#include "AVLTree.h"
#include <fstream>

void AVLTree::visualizeTree(const string& outputFilename) {
	ofstream outFS(outputFilename.c_str());
	if (!outFS.is_open()) {
		cout << "Error" << endl;
		return;
	}
	outFS << "digraph G {" << endl;
	visualizeTree(outFS, root);
	outFS << "}";
	outFS.close();
	string jpgFilename = outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
	string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
	system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node * n) {
	if (n) {
		if (n->left) {
			visualizeTree(outFS, n->left);
			outFS << n->data << " -> " << n->left->data << ";" << endl;
		}

		if (n->right) {
			visualizeTree(outFS, n->right);
			outFS << n->data << " -> " << n->right->data << ";" << endl;
		}
	}
}

int AVLTree::height(Node* node)
{
	int h = 0;
	if (node != nullptr)
	{
		int lheight = height(node->left);
		int rheight = height(node->right);
		int max_height = max(lheight, rheight);
		h = max_height + 1;
	}
	return h;
}

int AVLTree::max(int a, int b)
{
	return (a > b) ? a : b;
}

//Return the balance factor of a given node.
int AVLTree::balanceFactor(Node* node) {
	int left = height(node->left);
	int right = height(node->right);
	int balance = left - right;

	return balance;
}

//Traverseand print the tree in inorder notation.Print the string followed by istr balance factor in parentheses followed by a, and one space.
void AVLTree::printBalanceFactors() {
	printBalanceFactors(root);
	cout << endl;
}

//Find and return the closest unbalanced node(with balance factor of 2 or -2) to the inserted node.
Node* AVLTree::findUnbalancedNode(Node* node) {
	Node* curr = node;
	int balance;

	while (curr->parent != 0) {
		balance = balanceFactor(curr->parent);
		if (balance == 2 || balance == -2) {
			return curr->parent;
		}
		else {
			curr = curr->parent;
		}
	}

	return 0;
}

//Insert an item to the binary search tree and perform rotation if necessary.
void AVLTree::insert(const string& str) {
	Node* unbalancedNode = nullptr;

	if (root == nullptr) {
		root = new Node(str);
		return;
	}
	else {
		Node* curr = root;
		while (curr != nullptr) {
			if (str == curr->data) {
				return;
			}

			if (str > curr->data) {
				if (curr->right == nullptr) {
					curr->right = new Node(str);
					curr->right->parent = curr;

					unbalancedNode = nullptr;
					unbalancedNode = findUnbalancedNode(curr->right);

					if (unbalancedNode != nullptr) {
						rotate(unbalancedNode);
					}

					return;
				}
				else {
					curr = curr->right;
				}
			}
			else {
				if (curr->left == nullptr) {
					curr->left = new Node(str);
					curr->left->parent = curr;

					unbalancedNode = nullptr;
					unbalancedNode = findUnbalancedNode(curr->left);

					if (unbalancedNode != nullptr) {
						rotate(unbalancedNode);
					}
					return;
				}
				else {
					curr = curr->left;
				}
			}
		}
	}
}

//Implement four possible imbalance cases and update the parent of the given node.
void AVLTree::rotate(Node* node) {
	if (balanceFactor(node) == 2) {
		if (balanceFactor(node->left) == 1) { //1) rotate right
			rotateRight(node);
		}
		else if (balanceFactor(node->left) == -1) { //2) rotate left, then right
			rotateLeft(node->left);
			rotateRight(node);

		}
	}

	if (balanceFactor(node) == -2) {
		if (balanceFactor(node->right) == -1) { //3) rotate left
			rotateLeft(node);
		}
		else if (balanceFactor(node->right) == 1) { //4) rotate right, then left
			rotateRight(node->right);
			rotateLeft(node);
		}
	}
}

//Rotate the subtree to left at the given node and returns the new subroot.
Node* AVLTree::rotateLeft(Node* node) {
	Node* curr = nullptr;

	curr = node->right;
	node->right = curr->left;

	if (node != root) {
		if (node->parent->left == node) {
			node->parent->left = curr;
		}

		if (node->parent->right == node) {
			node->parent->right = curr;
		}
	}

	curr->parent = node->parent;
	node->parent = curr;
	curr->left = node;

	if (node == root) {
		root = curr;
	}

	return curr;
}

//Rotate the subtree to right at the given node and returns the new subroot.
Node* AVLTree::rotateRight(Node* node) {
	Node* curr = nullptr;

	curr = node->left;
	node->left = curr->right;

	if (node != root) {
		if (node->parent->left == node) {
			node->parent->left = curr;
		}

		if (node->parent->right == node) {
			node->parent->right = curr;
		}
	}

	curr->parent = node->parent;
	node->parent = curr;
	curr->right = node;

	if (node == root) {
		root = curr;
	}

	return curr;
}

void AVLTree::printBalanceFactors(Node* node) {
	if (node == nullptr)
	{
		return;
	}
	if (node->left != nullptr)
	{
		printBalanceFactors(node->left);
	}
	cout << node->data << "(" << balanceFactor(node) << ")" << ", ";
	if (node->right != nullptr)
	{
		printBalanceFactors(node->right);
	}
}