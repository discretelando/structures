/* Data Structures
The Traversals of Trees
*/

#include <iostream>
#include <cstdlib>
using namespace std;

class The_Search
{
private:
	struct leafs
	{
		leafs* left;
		leafs* right;
		int data;
	};
	leafs* root;

public:
	The_Search()
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
	void insert(int);
	void remove(int);
};

void The_Search::insert(int d)
{
	leafs* t = new leafs;
	leafs* parent;
	t->data = d;
	t->left = NULL;
	t->right = NULL;
	parent = NULL;

	if (isEmpty()) root = t;
	else
	{
		leafs* curr;
		curr = root;

		while (curr)
		{
			parent = curr;
			if (t->data > curr->data) curr = curr->right;
			else curr = curr->left;
		}

		if (t->data < parent->data)
			parent->left = t;
		else
			parent->right = t;
	}
}

void The_Search::remove(int d)
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
		if (curr->data == d)
		{
			found = true;
			break;
		}
		else
		{
			parent = curr;
			if (d>curr->data) curr = curr->right;
			else curr = curr->left;
		}
	}
	if (!found)
	{
		cout << " Data not found! " << endl;
		return;
	}

	if ((curr->left == NULL && curr->right != NULL) || (curr->left != NULL
		&& curr->right == NULL))
	{
		if (curr->left == NULL && curr->right != NULL)
		{
			if (parent->left == curr)
			{
				parent->left = curr->right;
				delete curr;
			}
			else
			{
				parent->right = curr->right;
				delete curr;
			}
		}
		else
		{
			if (parent->left == curr)
			{
				parent->left = curr->left;
				delete curr;
			}
			else
			{
				parent->right = curr->left;
				delete curr;
			}
		}
		return;
	}

	if (curr->left == NULL && curr->right == NULL)
	{
		if (parent->left == curr) parent->left = NULL;
		else parent->right = NULL;
		delete curr;
		return;
	}

	if (curr->left != NULL && curr->right != NULL)
	{
		leafs* chkr;
		chkr = curr->right;
		if ((chkr->left == NULL) && (chkr->right == NULL))
		{
			curr = chkr;
			delete chkr;
			curr->right = NULL;
		}
		else 
		{

			if ((curr->right)->left != NULL)
			{
				leafs* lcurr;
				leafs* lcurrp;
				lcurrp = curr->right;
				lcurr = (curr->right)->left;
				while (lcurr->left != NULL)
				{
					lcurrp = lcurr;
					lcurr = lcurr->left;
				}
				curr->data = lcurr->data;
				delete lcurr;
				lcurrp->left = NULL;
			}
			else
			{
				leafs* tmp;
				tmp = curr->right;
				curr->data = tmp->data;
				curr->right = tmp->right;
				delete tmp;
			}

		}
		return;
	}

}

void The_Search::print_inorder()
{
	inorder(root);
}

void The_Search::inorder(leafs* p)
{
	if (p != NULL)
	{
		if (p->left) inorder(p->left);
		cout << " " << p->data << " ";
		if (p->right) inorder(p->right);
	}
	else return;
}

void The_Search::print_preorder()
{
	preorder(root);
}

void The_Search::preorder(leafs* p)
{
	if (p != NULL)
	{
		cout << " " << p->data << " ";
		if (p->left) preorder(p->left);
		if (p->right) preorder(p->right);
	}
	else return;
}

void The_Search::print_postorder()
{
	postorder(root);
}

void The_Search::postorder(leafs* p)
{
	if (p != NULL)
	{
		if (p->left) postorder(p->left);
		if (p->right) postorder(p->right);
		cout << " " << p->data << " ";
	}
	else return;
}

int main()
{
	The_Search b;
	int ch, tmp = 0, tmp1;
	while (1)
	{
		cout << "Hello Welcome to the Binary Tree" << endl;
		cout << " Enter your choice : ";
		cout << "To Exit Enter -999" << endl;
		while (tmp != -999)
		{
			cout << " Enter Number to be inserted : ";
			cin >> tmp;
			if (tmp == -999) { break; }
			b.insert(tmp);
		}
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

		system("pause");
	}
}

/*
Hello Welcome to the Binary Tree
Enter your choice : To Exit Enter -999
Enter Number to be inserted : 32
Enter Number to be inserted : 45
Enter Number to be inserted : 67
Enter Number to be inserted : 88
Enter Number to be inserted : 12
Enter Number to be inserted : 13
Enter Number to be inserted : -999
Let's TRAVERSE!
The Inorder Traversal: 12  13  32  45  67  88
The Preorder Traversal: 32  12  13  45  67  88
The Post-Order Traversal: 13  12  88  67  45  32
Press any key to continue . . .


*/