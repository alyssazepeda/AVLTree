#pragma once
#include <iostream>
using namespace std;

class Node {
	friend class AVLTree;
private:
	string data;
	int count;
	Node* left;
	Node* right;
	Node* parent;
public:
	Node() :data(""), count(0), left(0), right(0), parent(0) {}
	Node(const string& val) :data(val), count(0), left(0), right(0), parent(0) {}
};