//User Defined Linked List of Numbers
//Written by: Ricardo Williams II
//ID: 1043326

#include<stdio.h>
#include<iostream>
#include<string.h>

using namespace std;

class Node
{
public:
	int input;   //Our data that will be updated per node
	Node* next; //connection to next node
	Node(int d);
	Node::Node()
	{
	}
};

Node::Node(int data) {  //constructor to convert int to node data type
	input = data;

}
class LinkedStack {
protected:
	Node * top;
public:
	int count = 0;
	LinkedStack()
	{
		top = 0;
	}
	bool isEmpty()
	{
		return top == 0;
	}

	int Push(int inp);
	int Pop();
	void Print();
};

int LinkedStack::Push(int inp)  //accepting input data from the user
{
	Node * temp = new Node(inp);
	if (isEmpty())
		top = temp;
	else {
		temp->next = top;
		top = temp;
	}
	return count++;  //increment count to match size of list
}

int LinkedStack::Pop()
{
	if (isEmpty()) //if Stack is empty zero is returned and following code executes
		cout << "Err: The stack is empty" << endl;
	else  // if not empty following code executes
	{
		cout << top->input << endl;
		Node * temp = top; // create temporary variable 
		top = top->next;   // top now set to previous next pointer
		delete temp;       // clean up
	}
	return count--;        //decrementing 
}
void LinkedStack::Print()
{
	cout << "The Stack (from the top): ";
	for (Node *temp = top; temp != 0; temp = temp->next) {     //prints out until temp is equal to zero
		cout << temp->input << " ";
		cout << endl;
	}
}

int main() {
	int input = 0, choice;
	LinkedStack entry;
	while (input != -1) {
		cout << "Pop or push onto the stack? Enter -1 to exit" << " " << endl;
		cout << "1. Push" << endl;
		cout << "2. Pop" << endl;
		cin >> choice;
		switch (choice) {
		case 1: {
			cout << "More? : ";
			cin >> input;
			entry.Push(input);
			cout << "Items on stack: " << entry.count << endl;
			break;
		}
		case 2: {
			entry.Pop();
			cout << "Items on stack: " << entry.count << endl;
			break;
		}
		}
		entry.Print();
	}
	
	system("pause");
}