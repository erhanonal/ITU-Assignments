/* @erhanonal
* Erhan Önal
* Date: 03.12.2018 */

#include <stdlib.h>
#include <iostream>
using namespace std;
/**
        Structure for one node of the Stack ,which holds decks
        @value Number on the card
        @next Pointer for card in the deck
*/
struct Node{
	int value;
	Node *next;
};

/**
        Structure for a deck
        @topNode Pointer to the top card of the deck
        @cardCount Number of Cards in the deck
        @push Adds a card to the top of the deck
        @fillStack Fills the deck with card according to the input file
        @printStack Prints all of the cards in the deck
        @create Creates a deck
        @pop Draws the top card of the deck and returns the number on the card
        @isEmpty returns true if the deck is empty
*/
struct Stack{
	Node *topNode;
	int cardCount;
	void push(int);
	void fillStack(int,FILE*);
	void printStack();
	void create();
	int pop();
	bool isEmpty();	
};

/**
        Structure for the game
        @player1Deck Deck of the Player 1
        @player2Deck Deck of the Player 2
        @tableDeck Deck on the table
        @nextPlayer Number of the player to draw on the next round
        @binCount Number of cards thrown in the bin
        @playRound Plays one round of the game
        @printDecks Prints all 3 decks
*/
struct Game{
	Stack player1Deck,player2Deck,tableDeck;
	int nextPlayer;
	int binCount;
	void playRound();
	void create();
	void printDecks();

};

/**
        Funtion for creating the deck
*/

void Stack::create(){
	topNode=NULL;
	cardCount=0;
}
/**
    	Function for pushing a card to the deck
    	@param value Number on the card to push
*/
void Stack::push(int value){
	Node *newNode=new Node;
	newNode->value=value;
	if(topNode==NULL){
		newNode->next=NULL;
	}else{
		newNode->next=topNode;
	}
	topNode=newNode;
	cardCount++;
}
/**
    	Function for drawing a card from the top of the deck
    	@return Number on the card drawn
*/

int Stack::pop(){
	int result=topNode->value;
	Node *deleteNode=topNode;
	topNode=topNode->next;
	delete(deleteNode);
	cardCount--;
	return result;
}
/**
    	Function for checking if the deck is empty
    	@return Returns true if the deck is empty
*/
bool Stack::isEmpty(){
	if(topNode==NULL){
		return true;
	}else{
		return false;
	}
}
/**
    	Function for filling a deck with card according to the input file
    	@param inputCount Number of inputs to be read
    	@param inputTxt Pointer to the input text file
*/

void Stack::fillStack(int inputCount,FILE* inputTxt){
	for(int i=0;i<inputCount;i++){
		int input;
		if(fscanf(inputTxt,"%d",&input)==1){
			push(input);
		}
		else{
			return;
		}
	}
}

/**
    	Function for printing a deck
*/
void Stack::printStack(){
	Node* traverse=topNode;
	while(traverse!=NULL){
		cout<<traverse->value<<endl;
		traverse=traverse->next;
	}
	cout<<endl;
}

/**
    	Function for printing all 3 decks
*/

void Game::printDecks(){
	cout<<"printing table Deck"<<endl;
	tableDeck.printStack();
	
	cout<<"printing  Deck 1"<<endl;
	player1Deck.printStack();
	
	cout<<"printing Deck2"<<endl;
	player2Deck.printStack();
}
/**
    	Function for creating a game
*/

void Game::create(){
	player1Deck.create();
	player2Deck.create();
	tableDeck.create();
	nextPlayer=1;
	binCount=0;
}

/**
    	Function for playing one round of the game
*/

void Game::playRound(){
	
	int tableCard=tableDeck.pop();
	
	if(nextPlayer==1){
		
		if(tableCard>0){
			
			for(int i=0;i<tableCard;i++){
				if(player2Deck.isEmpty()){
					break;
				}
				int takersCard=player1Deck.pop();
				player1Deck.push(takersCard);	
				int giversCard=player2Deck.pop();
				if(giversCard>takersCard){
					player1Deck.push(giversCard);
				}else{
					binCount++;
				}
			}
		}
		else{
			
			for(int i=0;i<tableCard*(-1);i++){
				if(player1Deck.isEmpty()){
					break;
				}
				int takersCard=player2Deck.pop();
				player2Deck.push(takersCard);
				int giversCard=player1Deck.pop();
				if(giversCard>takersCard){
					player2Deck.push(giversCard);
				}else{
					binCount++;
				}
			}                                 			
		}
		nextPlayer=2;
	}else{
		if(tableCard>0){
		
			for(int i=0;i<tableCard;i++){
				if(player1Deck.isEmpty()){
					break;
				}
				int takersCard=player2Deck.pop();
				player2Deck.push(takersCard);
				int giversCard=player1Deck.pop();
				if(giversCard>takersCard){
					player2Deck.push(giversCard);
				}else{
					binCount++;
				}
			}
		}
		else{
			
			for(int i=0;i<tableCard*(-1);i++){
				if(player1Deck.isEmpty()){
					break;
				}
				int takersCard=player1Deck.pop();
				player1Deck.push(takersCard);
				int giversCard=player2Deck.pop();
				if(giversCard>takersCard){
					player1Deck.push(giversCard);
				}else{
					binCount++;
				}
			}
		}
		nextPlayer=1;
	}
}



int main(int argc,char **argv){
	if(argc!=2){
		return EXIT_FAILURE;
	}
	Game newGame;
	newGame.create();
	int tableDeckCount,playerDeckCount;
	FILE* inputTxt=fopen(argv[1],"r");
	
	if(fscanf(inputTxt,"%d %d",&tableDeckCount,&playerDeckCount)!=2){
		cout<<"Wrong Input"<<endl;
		return 1;
	}
	
	newGame.tableDeck.fillStack(tableDeckCount,inputTxt);
	newGame.player1Deck.fillStack(playerDeckCount,inputTxt);
	newGame.player2Deck.fillStack(playerDeckCount,inputTxt);
	bool continuePlaying=true;
	while(continuePlaying){
		if(newGame.player1Deck.cardCount<1 || newGame.player2Deck.cardCount<1  || newGame.tableDeck.cardCount<1){
			continuePlaying=false;
			break;
		}
		newGame.playRound();
	}
	cout<<newGame.binCount<<endl;
	return EXIT_SUCCESS;
}
