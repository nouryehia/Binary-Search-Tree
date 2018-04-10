//Includes.
#include <iostream>

using namespace std;

//If undefined.
#ifndef TREE_H 
#define TREE_H

//Define class.
class tree {
public:

	//Define variables.
	struct node { 
		int data;
		node *right, *left;
	};
	node* head;

	//Define functions.
	tree();
	node* add(int, node*&);
	void remove(int, node*&);
	void print(node*, int);
}; 

//Constructor.
tree::tree(){
	head = NULL;
}

//Add elements to tree.
tree::node* tree::add(int data, node* &head){
	node* toAdd = new node;
	toAdd->data = data;

	if (!head){
		head = toAdd;
		head->right = head->left = NULL;
	}
	else {
		if (toAdd->data <= head->data) head->left = add(data, head->left);
		else head->right = add(data, head->right); 
	}
	return head;
}

//Remove elements from tree.
void tree::remove(int data, node* &head){
	node* toRemove = head;
	node* parent = NULL;
	node* temp;

	if (!head) {
		cout << "\nTree is empty. Cannot remove node.\n";
		return;
	}
	while (toRemove && toRemove->data != data){
		parent = toRemove;
		if (data < toRemove->data) toRemove = toRemove->left;
		else toRemove = toRemove->right;
	}
	if (!toRemove) {
		cout << "\nNo node containing the number " << data << " was found in your tree.\n";
		return;
	}
	if (!toRemove->left && !toRemove->right){
		if (!parent){
			delete toRemove;
			head = NULL;
		}
		else {
			if (toRemove->data <= parent->data) parent->left = NULL;
			else parent->right = NULL;
			delete toRemove;
		}
	}
	else if (!toRemove->left){
		if (!parent){
			temp = toRemove->right;
			delete toRemove;
			head = temp;
		}
		else{
			if (toRemove->data <= parent->data) parent->left = toRemove->right;
			else parent->right = toRemove->right;
			delete toRemove;
		}
	}
	else if (!toRemove->right){
		if (!parent){
			temp = toRemove->left;
			delete toRemove;
			head = temp;
		}
		else{
			if (toRemove->data <= parent->data) parent->left = toRemove->left;
			else parent->right = toRemove->left;
			delete toRemove;
		}
	}
	else {
		if (!parent) {
			parent = toRemove;
			temp = toRemove->left;
			while (temp->right){
				parent = temp;
				temp = temp->right;
			}
			toRemove->data = temp->data;
			if (temp->left) parent->right = temp->left;
			else parent->right = NULL;
			delete temp;
		}
		else if (toRemove->data <= parent->data) {
			parent = toRemove;
			temp = toRemove->left;
			while (temp->right){
				parent = temp;
				temp = temp->right;
			}
			toRemove->data = temp->data;
			if (temp->left) parent->left = temp->left;
			else parent->left = NULL;
			delete temp;
		}
		else if (toRemove->data > parent->data){
			parent = toRemove;
			temp = toRemove->right;
			while (temp->left){
				parent = temp;
				temp = temp->left;
			}
			toRemove->data = temp->data;
			if (temp->right) parent->right = temp->right;
			else parent->right = NULL;
			delete temp;
		}
	}
}

//Print tree.
void tree::print(node* head, int space){
	int count = 4;

	if (!head) return;
	space += count;

	print(head->right, space);
	cout << endl;
	for (int i = count; i < space; i++) cout << " ";
	cout << head->data;
	print(head->left, space);
}
#endif