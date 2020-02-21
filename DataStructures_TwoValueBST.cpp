//Binary Search Tree Assignment
//Written by: Ricardo Williams II

/* Data Structures
The Traversals of Trees
*/

#include <iostream>
#include <cstdlib>
#include<string>
#include<iostream>
#include<iomanip>
using namespace std;

class Tree
{
private:
	struct leafs
	{
		leafs* left;  //creating a route to go left
		leafs* right; // and to go right through linked pointers
		int data; //each node leaf will have both a left and right property as well as data and name
		string name;
	};
	leafs* root;
	int count = 0;
	bool ran = false; //keeping track of whether or not the it is the root, in order to iniitiate the lowest values
	int ldata = 0;
	string aname;

public:
	Tree()
	{
		root = NULL;
	}

	bool isEmpty() const { return root == NULL; }
	void print_inorder();
	void inorder(leafs*);
	void print_preorder();
	void preorder(leafs*);
	void print_postorder();
	void postorder(leafs*);
	int height(leafs*);
	void print_height();
	void Insert(int d, string s);
	void searcher(string s);
	void children(leafs*);
	void print_children();
};

void Tree::Insert(int d, string s)
{
	leafs* t = new leafs; //creating new leaves as we build, to later attach to the tree
	leafs* parent;
	t->data = d;
	if (ran != true)  //initializing these values to be the same as the root
	{
		ldata = d;
		aname = s;
	}
	t->name = s;
	t->left = NULL;
	t->right = NULL;
	parent = NULL;

	if (t->data < ldata) //updating the data and or name values depending on if they are smaller than the current ldata and aname variables
	{
		ldata = t->data;
	}
	if (t->name < aname)
	{
		aname = t->name;
	}
	if (isEmpty()) root = t;
	else                //if it is not the root, then we add the leaf to the tree using the name as our key value
	{
		leafs* curr;
		curr = root;

		while (curr)
		{
			parent = curr;
			if (t->name > curr->name) curr = curr->right;
			else curr = curr->left;
		}

		if (t->name < parent->name)
			parent->left = t;
		else
			parent->right = t;
	}
	ran = true;  //setting the bool true after the first pass
}

int Tree::height(leafs* t)  //using recursion to go down each side and return the longest length +1 which acocunts for the root as a part of the tree
{
		if (t == NULL) {
			return -1;
		}

		int lefth = height(t->left);
		int righth = height(t->right);

		if (lefth > righth) {
			return lefth + 1;
		}
		else {
			return righth + 1;
		}
}
void Tree::searcher(string s)  //uses a while loop instead of recursion, for simplicity's sake, to traverse the tree and look for the entered value
{
	bool found = false;
	if (isEmpty())
	{
		cout << " This Tree is empty! " << endl;
		return;
	}

	leafs* curr;
	leafs* parent = NULL;
	curr = root;

	while (curr != NULL)
	{
		if (curr->name == s) //if found it ends the while loop after reading the weight to the screen
		{
			found = true;
			cout << "The Data Has Been Found With A Weight Of: " << curr->data << endl;
			break;
		}
		else //if not found it continues on
		{
			parent = curr;
			if (s > curr->name) curr = curr->right;
			else curr = curr->left;
		}
	}
	if (!found)
	{
		cout << " Data not found! " << endl;
		return;
	}
}

void Tree::print_children() // all print methods are essentially the same, they all use recursion to operate
{
	children(root);
	cout << count << endl;
	cout << "The Lowest Weight In The Tree Is: " << ldata << endl;
	cout << "The First Name In the Alphabet Is: " << aname << endl;
}
void Tree::children(leafs *o)
{
	if (o->left == NULL && o->right == NULL)
	{
		count++;
	}
	if(o->left != NULL)
	{
		children(o->left);
	}
	if (o->right != NULL)
	{
		children(o->right); //i used if statements for each one, so as to make sure that each part of the tree gets visited and checked for children
	}                       // if else or else statements would only traverse either left or right or stop at a specific node even if it has children
}

void Tree::print_inorder()
{
	inorder(root);
}

void Tree::inorder(leafs* p)
{
	if (p != NULL)
	{
		if (p->left) inorder(p->left);
		cout << " " << p->name << " " << p->data << " ";
		if (p->right) inorder(p->right);
	}
	else return;
}

void Tree::print_preorder()
{
	preorder(root);
}

void Tree::print_height()
{
	int out = height(root);
	cout << out;
}
void Tree::preorder(leafs* p)
{
	if (p != NULL) 
	{
		cout << " " << p->name << " " << p->data << " ";
		if (p->left) preorder(p->left);
		if (p->right) preorder(p->right);
	}
	else return;
}

void Tree::print_postorder()
{
	postorder(root);
}

void Tree::postorder(leafs* p)
{
	if (p != NULL)
	{
		if (p->left) postorder(p->left);
		if (p->right) postorder(p->right);
		cout << " " << p->name << " " << p->data << " ";
	}
	else return;
}

int main() //pretty standard main function
{
	Tree b;
	int weight = 0, count = 0;
	string name;
	while (1)
	{
		cout << "Hello Welcome to the Binary Tree" << endl;
		while (count != 15)
		{
			cout << " Enter Name and Weight to be inserted : ";
			getline(cin, name);
			cin >> weight;
			b.Insert(weight, name);
			cin.ignore();  //flushing the input for potential input of string
			count++;
		}
		cin.ignore(); //verifying that the stream is clear
		cout << "Please Enter The Name to Search" << endl;
		getline(cin, name);
		b.searcher(name);
		cout << "Let's TRAVERSE!" << endl;
		cout << ("The Inorder Traversal:");
		b.print_inorder();
		cout << endl;
		cout << ("The Preorder Traversal:");
		b.print_preorder();
		cout << endl;
		cout << ("The Post-Order Traversal:");
		b.print_postorder();
		cout << endl;
		cout << ("The Height Of The Tree Is: ");
		b.print_height();
		cout << ("\nLeaves:");
		b.print_children();
		system("pause");
	}
}

/*
Hello Welcome to the Binary Tree
Enter Name and Weight to be inserted : ccc
99
Enter Name and Weight to be inserted : aaa
123
Enter Name and Weight to be inserted : bbb
111
Enter Name and Weight to be inserted : ggg
21
Enter Name and Weight to be inserted : ddd
76
Enter Name and Weight to be inserted : zzz
14
Enter Name and Weight to be inserted : yyy
234
Enter Name and Weight to be inserted : xxx
543
Enter Name and Weight to be inserted : ttt
77
Enter Name and Weight to be inserted : rty
321
Enter Name and Weight to be inserted : asd
906
Enter Name and Weight to be inserted : iyt
88
Enter Name and Weight to be inserted : wer
33
Enter Name and Weight to be inserted : try
66
Enter Name and Weight to be inserted : wds
1456

Please Enter The Name to Search
iyt
The Data Has Been Found With A Weight Of: 88
Let's TRAVERSE!
The Inorder Traversal: aaa 123  asd 906  bbb 111  ccc 99  ddd 76  ggg 21  iyt 88  rty 321  try 66  ttt 77  wds 1456  wer 33  xxx 543  yyy 234  zzz 14
The Preorder Traversal: ccc 99  aaa 123  bbb 111  asd 906  ggg 21  ddd 76  zzz 14  yyy 234  xxx 543  ttt 77  rty 321  iyt 88  try 66  wer 33  wds 1456
The Post-Order Traversal: asd 906  bbb 111  aaa 123  ddd 76  iyt 88  try 66  rty 321  wds 1456  wer 33  ttt 77  xxx 543  yyy 234  zzz 14  ggg 21  ccc 99
The Height Of The Tree Is: 7
Leaves:5
The Lowest Weight In The Tree Is: 14
The First Name In the Alphabet Is: aaa
Press any key to continue . . .
*/