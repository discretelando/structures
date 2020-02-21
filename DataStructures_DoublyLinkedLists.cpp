/*
Doubly Linked List that prints sorted list
*/
#include<cstdlib>
#include<string>
#include<iostream>
#include<iomanip>

using namespace std;

class Node
{
public:
	int input; //Our data that will be updated per node
	string text;

	Node* next; //connection to next node
	Node* prev; //connection to previous node
	Node(int d, string s);
	Node::Node() //constructor to convert input data to Node data types
	{
	}
};
Node::Node(int data, string s) {  //constructor to convert int to node data type
	input = data;
	text = s;
}

class LinkedStack:Node
{
friend Node;
protected:
	Node* head = NULL; //initializing as NULL head and tail
	Node* tail = NULL; //keep track of list as we build

public:
	void Push(int s, string g);
	//void Sort_Input();
	void Print(); //can be called at any time
	bool isEmpty() //return an err if print is called while empty
	{
		return head = 0;
	}
};

void LinkedStack::Push(int s, string g) {
	Node * n = new Node(s, g);
	n->input = s;
	n->text = g;

	if (head == NULL) //only runs once
	{
		head = n;
		tail = n;
	}
	else if (head != NULL) //passes every time until end of call
	{
		for (Node*temp = head; temp != 0; temp = temp->next) //iterates through the entire list 
		{
			if (temp->next == NULL && n->input > temp->input) { //null check if only one entry has been made, this is necessary to avoid null exception errs
				temp->next = n;
			}
			if(temp->prev ==NULL && n->text > temp->text) //same as above, except runs if no previous entry has been entered
			{
				temp->prev = n;
			}
				if (n->input > temp->input && n->input < temp->next->input) //normal insertion
				{
					n->next = temp->next;
					temp->next = n;
				}
				if (n->text > temp->text && n->text < temp->prev->text) //normal insertion based on input text values
				{
					n->prev = temp->prev;
					temp->prev = n;
				}
				if (n->text < tail->text) { //these next two are final plausible checks, to ensure every input gets placed in the list
					n->prev = tail;
					tail = n;
				}
				if (n->input < head->input) {
					n->next = head;
					head = n;
				}
		}
		if (head->next == NULL && n->input < head->input) { //if the input value is less than head, then head gets updated
			head->next = n;
		}
		if (tail->prev == NULL && n->text > tail->text) { //if the input text value is less than tail, then tail gets updated
			tail->prev = n;
		}
	}
}

void LinkedStack::Print()
{
	cout << "The Stack (from the top): ";
	for (Node *temp = head; temp != 0; temp = temp->next) {  //standard for loop iterating through the entire list using the head ptr (sorted weight values)
		cout << temp->input << " ";
		cout << temp->text << " ";
		cout << endl;	
	}
	cout << "The Stack (from the bottom): ";
	for (Node *temp = tail; temp != 0; temp = temp->prev) { //standard for loop iterating through the entire list using the tail ptr(sorted name values)
		cout << temp->input << " ";
		cout << temp->text << " ";
		cout << endl;
	}
}

int main()
{
	LinkedStack link; //rest is all standard main operations, calling and passing input variables
	int weight = 0;
	string name;
	cout << "Welcome to the sorted list" << endl;
	cout << "Please enter the name followed by weight" << endl;
	cout << "Name:" << endl;
	getline(cin, name);
	cout << "Weight:";
	cin >> weight;
	link.Push(weight, name);
	cin.ignore();
	while(weight != -999)
	{
		cout << "Add Name: " << endl;
		getline(cin, name);
		cout << "Add Weight: " << endl;
		cin >> weight;
		if (weight == -999)
			break;
		link.Push(weight, name);
		cin.ignore();
	}
	cout << "The ordered list:" << endl;
	link.Print();
	system("pause");
}
 //OUTPUT
/*
Welcome to the sorted list
Please enter the name followed by weight
Name:
Jim
Weight:150
Add Name:
Tom
Add Weight:
212
Add Name:
Michael
Add Weight:
174
Add Name:
Abe
Add Weight:
199
Add Name:
Richard
Add Weight:
200
Add Name:
April
Add Weight:
117
Add Name:
Claire
Add Weight:
124
Add Name:
Bobby
Add Weight:
109
Add Name:
Bob
Add Weight:
156
Add Name:
Kevin
Add Weight:
145
Add Name:
Jason
Add Weight:
182
Add Name:
Brian
Add Weight:
150
Add Name:
Chris
Add Weight:
175
Add Name:
Steven
Add Weight:
164
Add Name:
Annabelle
Add Weight:
99
Add Name:
v
Add Weight:
-999
The ordered list:
The Stack (from the top): 99 Annabelle
109 Bobby
117 April
124 Claire
145 Kevin
150 Jim
156 Bob
164 Steven
174 Michael
175 Chris
182 Jason
199 Abe
200 Richard
212 Tom
The Stack (from the bottom): 199 Abe
99 Annabelle
117 April
156 Bob
109 Bobby
150 Brian
124 Claire
182 Jason
150 Jim
145 Kevin
174 Michael
200 Richard
164 Steven
212 Tom
Press any key to continue . . .
*/