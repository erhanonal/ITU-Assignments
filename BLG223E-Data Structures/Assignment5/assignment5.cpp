/* @erhanonal
Erhan Önal
Date: <25.12.2018> */


#define MAX_INPUT 100
#include <iostream>
#include <fstream>
using namespace std;
/**
        Structure for one node of the tree
        @data Number on the node
        @left Pointer to the left node
        @right Pointer to the right node
*/
struct Node{
	int data;
	Node* left;
	Node* right;
};

/**
        Structure for one node of stack 
        @data Number of the node
        @next Pointer to the next node
*/
struct StackNode{
	int data;
	StackNode* next;
};
/**
        Structure for the stack,stacks will be used to hold the path to the target sum
        @topNode pointer to the top node of the Stack
*/
struct Stack{
	StackNode* topNode;
	void push(int data);
	int pop();
	void create();
	bool isEmpty();
	void printStack();
};
/**
        Function for printing all nodes of the Stack
*/
void Stack::printStack()
{
	StackNode* traverse=topNode;
	while(traverse){
		cout<<traverse->data<<endl;
		traverse=traverse->next;
	}
}
/**
        Function for creating the stack
*/
void Stack::create(){
	topNode=NULL;
}

/**
        Function for checking if the stack is empty
        @return Returns true if the stack is empty,returns true if not
*/
bool Stack::isEmpty(){
	if(topNode==NULL){
		return true;
	}
	else{
		return false;
	}
}

/**
        Function for pushing a node to the top of the stack
        @data Number to push into the stack
*/
void Stack::push(int data){
	StackNode* newNode=new StackNode;
	newNode->data=data;
	if(!topNode){
		newNode->next=NULL;
	}
	else{
		newNode->next=topNode;
	}
	topNode=newNode;
}
/**
        Function for poppping one node from the top of the stack
        @return Number of the top node
*/
int Stack::pop(){
	StackNode* deleteNode=topNode;
	int result=topNode->data;
	topNode=topNode->next;
	delete(deleteNode);
	return result;
}
/**
        Structure for Tree
        @root Pointer to the root node of the tree
*/
struct Tree{
	Node* root;
	Node* fillTree(int[],int,int);
	void create();
	void printTree(Node*);
};

/**
        Function for printing all nodes of the tree
*/
void Tree::printTree(Node* nodePtr){
	
	if(nodePtr){
		cout<<nodePtr->data<<endl;
		printTree(nodePtr->left);
		printTree(nodePtr->right);
	}
}
/**
        Function for creating Tree
*/
void Tree::create(){
	root=NULL;
}
/**
        Function for filling the tree according to the input file
        @inputs Array containing the inputs
        @inputCount Number of inputs on the first line of the text file
        @index Index of the input to put into the tree
        @return Returns a pointer to the new node
*/
Node* Tree::fillTree(int inputs[],int inputCount,int index){

	Node* newNode=new Node;
	newNode->data=inputs[index-1];//Creating a node and assigning the value from the inputs array according to the index

	if(index==1){
		root=newNode;//If the index is 1,it is the first input and the root of the tree
	}
	

	if(index*2>inputCount){//If index*2 is greater than inputCount, the node has no left and right child
		newNode->left=NULL;
		newNode->right=NULL;
	}
	else if(index*2+1>inputCount){//if index*2+1 is greater than inputCount,but index*2 is not, the node has only left child
		newNode->left=fillTree(inputs,inputCount,index*2);//The left childs pointer is equal to the call of the function with index*2
		newNode->right=NULL;
	}
	else{//if index*2 and index*2+1 is not greater than inputCount the node has a left and a right child
		newNode->left=fillTree(inputs,inputCount,index*2);//The left childs pointer is equal to the call of the function with index*2
		newNode->right=fillTree(inputs,inputCount,index*2+1);//The right childs pointer is equal to the call of the function with index*2+1
	}
	
	return newNode;//Returns a pointer to the newNode
}

/**
        Recursive function for finding the corresponding path to the target sum and storing it in a stack
        @node Pointer to the node to find the sum
        @target Target number to reach with sums
        @sum Sum of the nodes 
        @found Pointer to the boolean value controlling if the target has been reached
        @stack Stack to hold the patch leading to the correct sum
*/

void FindSum(Node* node,int target,int sum,bool* found,Stack* stack){

	stack->push(node->data);//Push the number of this node to the stack
	sum+=node->data;//Add the number to the sum
	
	if(sum==target){
		*found=true;//If sum has reached the target found is set to true
	}
	
	
	if(!*found && node->left){//If the target is not reached and the left child exists Findsum funciton is called again for the left child node
		FindSum(node->left,target,sum,found,stack);
	}
	
	if(!*found && node->right){//If the target is not reached and the right child exist FindSum function is called again for the right child node
		FindSum(node->right,target,sum,found,stack);
	}
	
	if(!*found){
		stack->pop();//If the target is not reached, this nodes value is removed from the stack
	}
	

}

/**
        Function for printing the result
        @rootValue Number on the root node
        @stack pointer to the stack holding the path
*/
void printResult(int rootValue,Stack* stack){
	
	if(!stack->isEmpty()) {//If the stack is not empty a path is found
   		cout << "Path Found: ";
    	Stack tempStack;//A temporary stack is created to reverse the path
    	tempStack.create();
    	while(!stack->isEmpty()) {
    		int temp = stack->pop();
      		tempStack.push(temp);//The result stack is reversed and pushed to the temporary stack so the order is right
    	}
    	
    	cout << rootValue << " ";//Prints the value of the root node to the screed
   		while(!tempStack.isEmpty()) {
      		int temp = tempStack.pop();
     		cout << temp << " ";//Prints the rest of the path from the temporary stack
   		}
   		cout<<endl;
 	}
 	else {
   		 cout << "No Path Found"<<endl;//If the stack is empty , no path is found
 	}
 	
}

int main(int argc,char** argv){
	
	if(argc!=2){//Quits program if the number of parameter are wrong
		return 1;
	}
	ifstream input;
	input.open(argv[1]);//Open the input file
	int data;
	int inputCount=0;
	int inputs[MAX_INPUT];//Creates an array to hold input
	
	while(input>>data){//Fill the input array with values from input file and stores inputCount
		inputs[inputCount]=data;
		inputCount++;
	}
	inputCount--;//inputCount is reduced by 1 to remove the counting for the second line 
	Tree newTree;
	newTree.create();
	newTree.fillTree(inputs,inputCount,1);//Creates a new Tree and fills it according to the inputs from the array
	int target=inputs[inputCount]-inputs[0];//Target number is set to the number on the second line minus the root node value
		
	bool leftFound=false;
	int leftSum=0;//Variables for the left node are set
	
	Stack leftStack;
	leftStack.create();//A stack is created to hold the path to the correct sum for the left part of the tree
	FindSum(newTree.root->left,target,leftSum,&leftFound,&leftStack);//FindSum function finds a correct path to the sum and stores it to the stack if it exists
	
 	bool rightFound=false;
	int rightSum=0;//Variables for the right node are set
	
	Stack rightStack;
	rightStack.create();//A Stack is created to hold the path to the correct sum for the right part of the tree
	FindSum(newTree.root->right,target,rightSum,&rightFound,&rightStack);//FindSum function finds a correct path to the sum and stores is to the stack if it exists
	
	printResult(inputs[0],&leftStack);
	printResult(inputs[0],&rightStack);//Prints the results for boths sides of the root

}
