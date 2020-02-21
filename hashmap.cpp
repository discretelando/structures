#include <stdio.h>
#include <string.h>

class Node{
public:
	Node next;
	std::string value;
}

class LinkedList{
public:
	Node head;
	
private:
	void addNode(std::string val);
}

long hashFunction(std::string input){
	long hash = 0;
	long len = input.size();
	hash = (len*2)%10;
	return hash;
}

int main(){
std:string input = "";
long hash = 0;
LinkedList array[100];
while(input != "-999"){
	std::cin >> input;
	hash = hashFunction(input);
	if(array[hash] != NULL){
		LinkedList head = LinkedList(input);
		array[hash] = head;
	}
	else{
		LinkedList list = array[hash];
		Node node = list.head;
		while(node->next != null)
			node = node->next;
		node->next = LinkedList(input);
	}
}

return 1;
}