#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

const int TABLESIZE = 10;
const int MAX = 69;
struct Node
{
	string varName;
	int value;
	Node *next;
};

class HashTable {

private:

	Node *table[TABLESIZE]; // chaining implemented for collision resolution

	int computeHash(string varName)
	{
		int hash = 0;
		//modulo by standard convention, using table size
		for (unsigned i = 0; i<varName.length(); i++) {
			hash += varName.at(i) * (i + 1);
		}
		hash = hash % TABLESIZE;
		return hash;
	}
public:

	HashTable()
	{
		for (int i = 0; i < TABLESIZE; i++)
		{
			table[i] = NULL;
		}
	}

	Node* search(string varName) { 
		int hashKey = computeHash(varName);
		if (table[hashKey] == NULL)
		{

			return NULL;
		}
		else
		{
			Node *node = table[hashKey];
			while (node != NULL && node->varName != varName)
			{
				node = node->next;
			}
			return node;
		}
	}

	void insert(string varName, int varValue) 
	{
		int hashKey = computeHash(varName);

		Node* newNode = new Node();
		newNode->varName = varName;
		newNode->value = varValue;
		newNode->next = NULL;

		if (table[hashKey] == NULL) 
		{
			table[hashKey] = newNode;
		}
		else
		{
			Node *entry = table[hashKey];
			while (entry->next != NULL && entry->varName.compare(varName) == 0)
			{
				entry = entry->next;
			}

			if (entry->varName.compare(varName) == 0)
			{
				entry->value = varValue;
			}
			else
			{
				entry->next = newNode;
			}

		}
	}

	void DeleteScope()
	{
		for (int i = 0; i< TABLESIZE; i++)
		{
			Node *node = table[0];
			Node* curr = node;
			while (node != NULL)
			{
				node = node->next;
				delete curr;
				curr = node;
			}
		}

	}
};

class Borg
{
private:
	int lineNumber;
	HashTable block[MAX];
	int currentBlockLevel;

	bool StringToInteger(string sInt, int *result) 
	{

		istringstream convert(sInt);
		if (!(convert >> *result))
		{
			return false;
		}
		return true;
	}
	int pow(int val1, int val2)
	{
		int result = 1;
		for (int i = 0; i < val2; i++)
			result *= val1;

		return result;
	}

	int GetTokens(string line, string tokens[], int maxtokens)
	{
		stringstream stream(line);
		string word;
		int index = 0;
		while ((stream >> word) && (index < maxtokens))
		{
			tokens[index++] = word;
		}
		return index;
	}

	void DeclarationStatement(string line)
	{
		string tokens[4];
		int tokenCount = GetTokens(line, tokens, 4);
		if (tokenCount != 4)
		{
			cout << "Syntax error in line: " << line << endl;
			return;
		}

		int value = 0;
		if (!StringToInteger(tokens[3], &value))
		{
			cout << "Invalid number " << tokens[3] << " in line: " << line << endl;
			return;
		}
		block[currentBlockLevel].insert(tokens[1], value);
	}

	void PrintStatement(string line)
	{
		int result = 0;
		string tokens[4];
		int tokenCount = GetTokens(line, tokens, 4);

		switch (tokenCount)
		{
		case 2:
			if (!GetTokenValue(tokens[1], &result))
				return;
			cout << tokens[1] << " IS " << result << endl;
			break;
		case 3:
			if (!ProcessUnaryExpression(tokens[1], tokens[2], &result))
				return;
			cout << tokens[1] << tokens[2] << " IS " << result << endl;
			break;
		case 4:
			if (!ProcessBinaryExpression(tokens[1], tokens[3], tokens[2], &result))
				return;
			cout << tokens[1] << " " << tokens[2] << " " << tokens[3] << " IS " << result << endl;
			break;
		}

	}

	bool ProcessUnaryExpression(string operand, string pOperator, int* result)
	{
		bool ok = false;
		Node* node = SearchVar(operand);

		if (node != NULL)
		{
			if (pOperator.compare("++") == 0)
				node->value++;

			if (pOperator.compare("--") == 0)
				node->value--;

			*result = node->value;
			ok = true;
		}
		else
		{
			cout << "Unknown variable " << operand << " at line number " << lineNumber << endl;
		}
		return ok;
	}

	void ProcessAssignment(string line)
	{
		int result = 0;
		string tokens[5];
		int tokenCount = GetTokens(line, tokens, 5);

		Node* node = SearchVar(tokens[0]);
		if (node == NULL)
		{
			cout << "SYNTAX ERROR: " << line << " at line number " << lineNumber << endl;
			return;
		}

		switch (tokenCount)
		{
		case 2: 
			if (!ProcessUnaryExpression(tokens[0], tokens[1], &result))
				return;
			break;
		case 3:
			if (!(GetTokenValue(tokens[2], &result)))
				return;
			node->value = result;
			break;
		case 4:
			if (!ProcessUnaryExpression(tokens[2], tokens[3], &result))
				return;
			node->value = result;
			break;
		case 5: 
			if (!ProcessBinaryExpression(tokens[2], tokens[4], tokens[3], &result))
				return;
			node->value = result;
			break;
		}
	}

	bool ProcessBinaryExpression(string operand1, string operand2, string oper, int* result)
	{
		int val1 = 0;
		int val2 = 0;

		if (!GetTokenValue(operand1, &val1))
			return false;
		if (!GetTokenValue(operand2, &val2))
			return false;

		if (oper.compare("+") == 0)
		{
			*result = val1 + val2;
			return true;
		}

		if (oper.compare("-") == 0)
		{
			*result = val1 - val2;
			return true;
		}

		if (oper.compare("*") == 0)
		{
			*result = val1 * val2;
			return true;
		}

		if (oper.compare("/") == 0)
		{
			*result = val1 / val2;
			return true;
		}

		if (oper.compare("%") == 0)
		{
			*result = val1 % val2;
			return true;
		}

		if (oper.compare("^") == 0)
		{
			*result = pow(val1, val2);
			return true;
		}

		return true;
	}

	bool GetTokenValue(string token, int* result)
	{
		bool ok = false;
		Node* node = SearchVar(token);
		if (node == NULL)
		{
			if (!StringToInteger(token, result))
			{
				cout << "Unknown variable " << token << " at line number " << lineNumber << endl;
				return false;
			}
			ok = true;
		}
		else
		{
			*result = node->value;
			ok = true;
		}
		return ok;
	}

	Node* SearchVar(string varName)
	{
		for (int i = currentBlockLevel; i >= 0; i--)
		{
			Node* node = block[i].search(varName);
			if (node != NULL)
				return node;
		}
		return NULL;
	}
public:
	Borg()
	{
		lineNumber = 0;
		currentBlockLevel = 0;
	}
	void ProcessLine(string line)
	{
		lineNumber++;
		stringstream stream(line);
		string word;
		while (stream >> word)
		{
			if (word.compare("COM") == 0)
				return;

			if (word.compare("VAR") == 0)
				return DeclarationStatement(line);

			if (word.compare("PRINT") == 0)
				return PrintStatement(line);

			if (word.compare("START") == 0)
			{
				currentBlockLevel++;
				if (currentBlockLevel >= MAX)
				{
					cout << "Too many scope/blocks" << endl;
					return;
				}
				return;
			}

			if (word.compare("FINISH") == 0)
			{
				block[currentBlockLevel].DeleteScope();
				currentBlockLevel--;
				return;
			}

			return ProcessAssignment(line);
		}
	}

};

int main()
{

	Borg borg;
	cout << endl << "Output of Test.txt" << endl;
	std::ifstream infile(".\\Test.txt");
	std::string line;
	while (std::getline(infile, line))
	{
		borg.ProcessLine(line);
	}
	cout << endl << "Finally done. Here is the output:" << endl;
	std::ifstream infile2(".\\myprogram.txt");
	while (std::getline(infile2, line))
	{
		borg.ProcessLine(line);
	}
	system("pause");
	return 0;
}
/*
Output!!!!
/*
Output of Test.txt
BORAMIR IS 25
LEGOLAS IS 101
Unknown variable GANDALF at line number 9
BORAMIR * 2 IS 52
GANDALF IS 49
BORAMIR IS 26
Unknown variable GANDALF at line number 19
LEGOLAS IS 1000
LEGOLAS IS 1000
LEGOLAS IS 999

Output of myprogram.txt BORG code
RICARDOSPROGRAM IS 100
RICARDOSPROGRAM IS 101
RICARDOSPROGRAM IS 8
Unknown variable WHATEVER at line number 38
Press [Enter] key to exit...
*/
