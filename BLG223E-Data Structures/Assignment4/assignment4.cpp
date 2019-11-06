/* @erhanonal
Erhan Önal
Date: <13.12.2018> */


#include <iostream>
using namespace std;
/**
        Structure for one node of stack and queue
        @number Number of the node
        @next Pointer to the next node
*/
struct Node{
	int number;
	Node* next;
};

/**
        Structure for stack
        @topNode  Pointer to the top ant of the stack
*/
struct stackAnt{
	Node* topNode;
	void create();
	void push(int);
	int pop();
	bool isEmpty();
	void printStack();
};

/**
        Funtion for creating stack structure
*/
void stackAnt::create(){
	topNode=NULL;
}
/**
        Function for pushing an ant to the stack
        @param number Number of the ant
*/
void stackAnt::push(int number){
	Node* newNode=new Node;
	newNode->number=number;
	if(isEmpty()){
		newNode->next=NULL;
	}
	else{
		newNode->next=topNode;
	}
	topNode=newNode;
}
/**
        Funtion for taking out the top ant of the stack
        return Number of the ant 
*/
int stackAnt::pop(){
	Node* deleteNode=topNode;
	int result=topNode->number;
	topNode=topNode->next;
	delete deleteNode;
	return result;	
}
/**
        Function for checking if the stack is empty
        @return returns true if the stack is empty
*/
bool stackAnt::isEmpty(){
	if(topNode==NULL){
		return true;
	}
	else{
		return false;
	}
}
/**
        Function for printing all nodes of the stack
*/
void stackAnt::printStack(){
	Node* traverse=topNode;
	while(traverse){
		cout<<traverse->number<<" ";
		traverse=traverse->next;
	}
	cout<<endl;
}
/**
        Structure for the queue of ants or hole depths
        @front Pointer to the first ant or hole on the queue
        @back  Pointer to the last ant or hole on the queue
*/
struct queueAnt{
	Node* front;
	Node* back;
	void create();
	void enqueue(int);
	int dequeue();
	bool isEmpty();
	void printQueue();
};
/**
        Function for creating a queue
*/
void queueAnt::create(){
	front=NULL;
	back=NULL;
}
/**
        Function for adding an ant or hole to the queue
        @param number Number of the ant or the depth of the hole
*/
void queueAnt::enqueue(int number){
	Node* newNode=new Node;
	newNode->next=NULL;
	newNode->number=number;
	
	if(isEmpty()){
		front=newNode;
		back=newNode;
	}	
	else{
		back->next=newNode;
		back=newNode;	
	}
}
/**
        Function for taking the first ant or hole out of the queue
        @return The number of the ant or the depth of the hole
*/
int queueAnt::dequeue(){
	Node* deleteNode=front;
	int result=front->number;
	front=front->next;
	delete deleteNode;
	return result;
}
/**
        Functions for checking if the queue is empty
        @return Returns true if its empty
*/
bool queueAnt::isEmpty(){
	if(back && front)
		return false;
	else
		return true;
}
/**
        Function for printing all nodes of the queue
*/
void queueAnt::printQueue(){
	Node* traverse=front;
	while(traverse){
		cout<<traverse->number<<" ";
		traverse=traverse->next;
	}
	cout<<endl;
}
/**
       	Structure given in the assignment
       	@ants Queue of the ants
       	@holedepths Queue holding the depths of the hole
       	@hole Stack for ants entering a hole
*/
struct Ants{
	queueAnt ants;
	queueAnt holeDepths;
	stackAnt hole;
	void ReadFile(char*);
	void ShowContents(bool);
	void CrossRoad();
};
/**
        Function for reading the number of ants and hole depths from a file and creating the queues for ants and hole depths
        @param inputTxt pointer to the file
*/
void Ants::ReadFile(char* inputTxt){
	ants.create();
	holeDepths.create();
	
	FILE* filePtr=fopen(inputTxt,"r");
	int antCount;
	fscanf(filePtr,"%d",&antCount);
	for(int i=1;i<=antCount;i++){//Adds antCount number of ants to the ants queue according to the input
		ants.enqueue(i);
	}
	
	int holeDepth;
	while(fscanf(filePtr,"%d",&holeDepth)==1){//Adds hole depths to the holeDepths queue until input ends
		holeDepths.enqueue(holeDepth);
	}
	fclose(filePtr);
}
/**
        Function for printing ants in the queue or hole depths
        @param selector Prints ants for true,prints hole depths for false
*/
void Ants::ShowContents(bool selector){
	if(selector){
		ants.printQueue();
	}
	else{
		holeDepths.printQueue();
	}
}
/**
        Makes the ants cross the road and changes the queue according to the holes
*/
void Ants::CrossRoad(){
	hole.create();
	Node* holeTraverse=holeDepths.front;
	while(holeTraverse){//Traverses holes until the end
		for(int i=0;i<holeTraverse->number;i++){//Takes ants out of the queue and puts them in the hole stack for the depth of the hole
		
			hole.push(ants.dequeue());
		}
		while(!hole.isEmpty()){//Takes ants out of the hole stack and puts them to the back of the queue until the hole is empty
			ants.enqueue(hole.pop());
		}
		holeTraverse=holeTraverse->next;//Moves on to the next hole
	}
}

int main (int argc , char ** argv ){
	Ants a ;
	a.ReadFile(argv[1]); // store the number of ants and depths of holes
	cout<<"The initial Ant sequence is: ";
	a.ShowContents(1); // list ant sequence ( initially : 1 , 2 , ... , N)
	cout<<"The depth of holes are: ";
	a.ShowContents(0);// list depth of holes
	a.CrossRoad ();
	cout<<"The final Ant sequence is: ";
	a.ShowContents(1);
	return 0;
}
