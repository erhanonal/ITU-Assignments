/* @erhanonal
* Erhan Önal
* 08.11.2018 */

//IMPORTANT NOTE:Space character works as a console input with " " . I only focused on english input.
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/**
        Structure for occur_node
        @character Character of the occur_node
        @next Pointer for the next occur_node
        @occurence Number of occurences for the occur_node
*/
struct occur_node {
	char character;
	occur_node *next;
	int occurence;
};

/**
        Structure for vocab_node
        @character Character of the vocab_node
        @next Pointer for the next vocab_node
        @list Pointer for the first occur_node of this vocab_node
*/

struct vocab_node {
	char character;
	vocab_node *next;
	occur_node *list;
};

/**
        Structure for vocab_list
        @head Pointer for the first vocab_node of the linked list structure
        @next Pointer for the next occur_node
        Functions of the structure is explained below
*/

struct vocab_list{
	vocab_node *head;
	void create();
	void printNodes();
	void printOccurences(char);
	void printModel();
	void add_char(char);
	void add_occurence(char, char);
	int get_occurence(char );
	int get_union_occurence(char , char );
	double calculate_probability(char, char);
};

/**
        Creates the vocab_list
*/
void vocab_list::create(){
	head=NULL;
}

/**
    Adds a character to the linked list structure
    @param add Character to be added
*/
void vocab_list::add_char(char add){
	
	add=tolower(add);
	if(add<32){//Quits the function for characters that are not part of the language like CR LF etc.
		return;
	}
	
	if(head==NULL){//Adds the first node to the linked list structure and assigns head to this node
		vocab_node *newNode=new vocab_node;
		newNode->character=add;
		newNode->next=NULL;
		newNode->list=NULL;
		head=newNode;
		
		return;
		
	}
	
	if(head->next==NULL){//Adds the second node to the linked list structure
		if(head->character==add){//Quits the function if the character is already added
			return;
		}
		
		vocab_node *newNode=new vocab_node;
		newNode->character=add;
		newNode->list=NULL;
		
		if(add>head->character){//Add the character after head
			newNode->next=NULL;
			head->next=newNode;
		}
		else if(add< head->character){//Add the character as the new head
			newNode->next=head;
			head=newNode;
		}
		return;
	}
	
	
	if(add<=122 && add>=97){//Check if the character is a letter
	
		if(head->character>122 || head->character<97){//Check if the head is a special character and changes to a letter if it is
			vocab_node *newNode=new vocab_node;
			newNode->character=add;
			newNode->next=head;
			newNode->list=NULL;
			head=newNode;
			return;
		}
		
		vocab_node *traverse=head;
		bool headChange=false;
		
		if(head->next!=NULL){
			if(add<traverse->character){//Check if the character should be the new head
				vocab_node *newNode=new vocab_node;
				newNode->character=add;
				newNode->next=traverse;
				newNode->list=NULL;
				head=newNode;
				headChange=true;
			}
			
			if(!headChange){
				//Go to the node the character will be added after based on alphabetical order
				while(add>traverse->next->character && traverse->next->character>=97 && traverse->next->character<=122){	
					traverse=traverse->next;
					if(traverse->next==NULL){
						break;
					}
				}
			}
		}
	
		if(traverse->next !=NULL && (traverse->character==add || traverse->next->character==add)) {//Quits the function if the character is already added
			return;
			
		}else{//Adds the character
			if(!headChange){
			vocab_node *newNode=new vocab_node;
			newNode->next=traverse->next;
			newNode->character=add;
			newNode->list=NULL;
			traverse->next=newNode;
			}
		}
	}
	
	else if(add<=57 && add>=48){//Adding a number
		vocab_node *traverse=head;
		if(head->next!=NULL){//Go to the node of the last letter
			while(traverse->next->character<=122 && traverse->next->character>=97){
				traverse=traverse->next;
				if(traverse->next==NULL){
					break;
				}
			}
		}
		
		if(traverse->next==NULL){//Adds the first numerical character
			vocab_node *newNode=new vocab_node;
			newNode->character=add;
			newNode->next=NULL;
			newNode->list=NULL;
			traverse->next=newNode;
		
			
		}else{//Add a number other than the first
			while(add>traverse->next->character && traverse->next->character>=48 && traverse->next->character<=57){//Go to the node the number will be added after
				traverse=traverse->next;
				if(traverse->next==NULL){	
						break;
				}
			}
			if(traverse->next!=NULL && (traverse->next->character==add || traverse->character==add)){//Quits the function if the character is already added
				return;
			}
			
			vocab_node *newNode=new vocab_node;
			newNode->next=traverse->next;
			newNode->character=add;
			newNode->list=NULL;
			traverse->next=newNode;
		}
		
	}
	else{//Adds a special character to the end
		
		vocab_node *traverse=head;
		while(traverse->next->character<=122 && traverse->next->character>=97){
			traverse=traverse->next;
			
			if(traverse->next==NULL){
					break;
			}
		}
		
		//Special check for the case where the first 3 inputs of the text is not a letter, 
		if(traverse->character==add){
			return;
		}
		
		//Traverse through special character and check if the character is already added
		while(traverse->next!=NULL){
			traverse=traverse->next;
			if(traverse->character==add){//Quits the function if the character is already added
				
				return;
			}	
		}
		
		vocab_node *newNode=new vocab_node;
		newNode->next=traverse->next;
		newNode->character=add;
		newNode->list=NULL;
		traverse->next=newNode;
	}
	
}

/**
    Print all vocab_Nodes
    Function for easier debugging
*/
void vocab_list::printNodes(){
	
	vocab_node* node_traverse=head;
	
	while(node_traverse!=NULL){
		if(node_traverse->character==' '){
			cout<<"node: <SP>"<<endl;
		}
		else{
			cout<<"node: "<<node_traverse->character<<endl;
		}
		node_traverse=node_traverse->next;
	}	
}

/**
        Print all occurences for a single vocab_node
        @param node Character of the vocab_node to be printed
*/

void vocab_list::printOccurences(char node){
	node=tolower(node);
	if(node<32){
		return;
	}
	vocab_node *node_traverse=head;
	
	while(node_traverse!=NULL){
		if(node_traverse->character==node){
			break;	
		}
		node_traverse=node_traverse->next;
	}
	occur_node *occur_traverse=node_traverse->list;
	while(occur_traverse!=NULL){
		if(occur_traverse->character==' '){
			cout<<"\t<<SP>,"<<occur_traverse->occurence<<">"<<endl;
		}
		else if(occur_traverse->character<32){
			cout<<"\t<<NL>,"<<occur_traverse->occurence<<">"<<endl;
		}
		else{
			cout<<"\t<"<<occur_traverse->character<<","<<occur_traverse->occurence<<">"<<endl;
		}
		occur_traverse=occur_traverse->next;
	}	
}

/**
        Prints the whole language model
*/

void vocab_list::printModel(){
	vocab_node* node_traverse=head;
	
	while(node_traverse!=NULL){
		if(node_traverse->character==' '){
			cout<<"<SP>: "<<endl;
		}
		else if(node_traverse->character<32){
			cout<<"\n: "<<endl;
		}
		else{
			cout<<node_traverse->character<<": "<<endl;
		}
		printOccurences(node_traverse->character);
		node_traverse=node_traverse->next;
	}	
}

/**
        Adds an occurence for a node character and occurence character
        @param node Character of the vocab_node
        @param occur Character of the occur_node
*/

void vocab_list::add_occurence(char node,char occur){
	node=tolower(node);
	occur=tolower(occur);
	
	if(node<32){//Quits the function if the inputs are character that are not part of the language model such as CR LF
		return;
	}
	
	vocab_node* traverse=head;
	
	while(traverse!=NULL){//Go the corresponding vocab_node for the given input
		if(traverse->character==node){
			break;	
		}
		traverse=traverse->next;
	}	

	
	occur_node *occur_traverse=traverse->list;
	
	if(occur_traverse==NULL){//Add the first occurence of the node and set the list pointer to that node and quit the function
		occur_node *new_occurence=new occur_node;
		new_occurence->character=occur;
		new_occurence->occurence=1;
		new_occurence->next=NULL;
		traverse->list=new_occurence;
		return;
	}
	
	
	while(occur_traverse->next!=NULL){//Check if the occur character is already added to the node,if added increase the occurence and quit the function
		if(occur_traverse->character==occur){
			occur_traverse->occurence++;
			return;
		}
		occur_traverse=occur_traverse->next;
	}
	
	if(occur_traverse->character==occur){//Extra check for the last occur_node,if the occur character is already added to the node,if added increase the occurence and quit the function
		occur_traverse->occurence++;
		return;
	}
	
	
	occur_node *new_occurence=new occur_node;//Add a new occur_node to the linked list structure
	new_occurence->character=occur;
	new_occurence->occurence=1;
	new_occurence->next=NULL;
	occur_traverse->next=new_occurence;
}


/**
        Gets the number of occurences of a single character
        @param node Character to determine the occurence of
        @return Number of occurences
*/

int vocab_list::get_occurence(char node){
	node=tolower(node);
	vocab_node *node_traverse=new vocab_node;
	node_traverse=head;
	while(node_traverse!=NULL){
		if(node_traverse->character==node){
			break;
		}
		node_traverse=node_traverse->next;
	}
	int result=0;
	occur_node *occur_traverse=new occur_node;
	occur_traverse=node_traverse->list;
	while(occur_traverse!=NULL){
		result+=occur_traverse->occurence;
		occur_traverse=occur_traverse->next;
	}
	return result;
}

/**
        Gets the number of co-occurences of two characters in order Character1Character2
        @param node Character1
        @param occur Character2
        @return Number of co-occurences
*/
int vocab_list::get_union_occurence(char node,char occur){
	node=tolower(node);
	occur=tolower(occur);
	vocab_node *node_traverse=new vocab_node;
	node_traverse=head;
	while(node_traverse!=NULL){
		if(node_traverse->character==node){
			break;
		}
		node_traverse=node_traverse->next;
	}
	occur_node *occur_traverse=new occur_node;
	occur_traverse=node_traverse->list;
	while(occur_traverse!=NULL && occur_traverse->character!=occur){
		occur_traverse=occur_traverse->next;
	}
	return occur_traverse->occurence;
}

/**
        Calculates the probability of the occurence Character1Character2
        @param node Character1
        @param node Character2
        @return Probability of the co-occurence
*/

double vocab_list::calculate_probability(char node,char occur){
	double result=get_union_occurence(node,occur)/(get_occurence(node)*1.0f);
	return result;
}

int main(int argc,char **argv){
	
	FILE* inputTxt=fopen(argv[1],"r");
	char add;
	char node,occur;
	
	
	vocab_list vocabularyList;
	vocabularyList.create();


	while(fscanf(inputTxt,"%c",&add)==1){
		vocabularyList.add_char(add);
	}	
		
	rewind(inputTxt);
	
	while(fscanf(inputTxt,"%c%c",&node,&occur)==2){
		vocabularyList.add_occurence(node,occur);
		fseek(inputTxt,-1,SEEK_CUR);
	}
	vocabularyList.get_occurence('j');
	if(argc==2){
		vocabularyList.printModel();
	}
	else if(argc==4){
		cout<<"Probabilty of co-occurence "<<*argv[2]<<*argv[3]<<": "<<vocabularyList.calculate_probability(*argv[2],*argv[3])<<endl;
	}
	else{
		cout<<"Wrong arguments"<<endl;
	}
	
	return EXIT_SUCCESS;
}

