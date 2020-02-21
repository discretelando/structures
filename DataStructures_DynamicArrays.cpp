//Dynamic Arrays
//Written by: Ricardo Williams II

#include<iostream>
#include<stdio.h>

using namespace std;

int main()
{
	int size, count = 0;
	bool end = false;
	cout << "Please enter the size of the array" << endl;
	cin >> size;
	int* arr = new int[size];

	for (int i = 0; i < size; i++)
	{
		cout << "Enter the next number to add to array: " << endl;
		cin >> arr[i];

		if (arr[i] == -1)
		{
			end = true;
			break;
		}
		count = i;
	}
	while (end !=  true)
	{
		int * newarr = new int[size]; // you actually cannot dynamically add toan array in c++ so instead i'm creating a new array
		newarr = arr; // and then copying it over everytime an addition is needed
		arr = newarr;
		//delete[]newarr;
		cout << "Enter the next number to add to array:.... " << endl;
		cin >> arr[size];
		if (arr[size] == -1)
			end = true;
		else
		cout << "Array extended" << endl;
		size++;
	}
	cout << "Stack: " << endl;
	for (int i = 0; i <= size; i++)
	{
		if (arr[i] == -1)
			break;
		cout << arr[i] << endl;
	}

	system("pause");
}