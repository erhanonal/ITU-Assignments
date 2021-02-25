/*
 * Erhan Önal 150170713 
 * 
 *******************/
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <chrono>
#include <fstream>
#include <sstream>


using namespace std;
class Attack {
	private:
		string name;
		int PP;
		int accuracy;
		int damage;
		int firstUsage;
	public:
		Attack(string inputName, int inputPP, int inputAcc, int inputDamage, int inputFirstUsage) {
			name = inputName;
			PP = inputPP;
			accuracy = inputAcc;
			damage = inputDamage;
			firstUsage = inputFirstUsage;
		}
		string getName() {
			return name;
		}
		int getPP() {
			return PP;
		}
		int getAccuracy() {
			return accuracy;
		}
		int getDamage() {
			return damage;
		}
		int getFirstUsage() {
			return firstUsage;
		}
		static vector<Attack> createAttacks(string fileName) {
			vector<Attack> result;
			ifstream attackFile;
			attackFile.open(fileName);
			string line;
			getline(attackFile,line);
			while(getline(attackFile,line)){
				string i_name;
				int i_PP;
				int i_accuracy;
				int i_damage;
				int i_firstUsage;
				stringstream input(line);
				getline(input, i_name, ',');
				
				string attribute;
				getline(input, attribute, ',');
				stringstream in_stream1(attribute);
				in_stream1 >> i_PP;
				
				getline(input, attribute, ',');
				stringstream in_stream2(attribute);
				in_stream2 >> i_accuracy;
				
				getline(input, attribute, ',');
				stringstream in_stream3(attribute);
				in_stream3 >> i_damage;
				
				getline(input, attribute, ',');
				stringstream in_stream4(attribute);
				in_stream4 >> i_firstUsage;
				result.push_back(Attack(i_name,i_PP,i_accuracy,i_damage,i_firstUsage));
				
			}
			return result;
		}
		void printAttack() {
			cout<<name<<" "<<PP<<" "<<accuracy<<" "<<damage<<" "<<firstUsage<<endl;
		}
};


enum Turn {P,B};
class Node {
	private:
		int pikaHP;
		int blasHP;
		int pikaPP;
		int blasPP;
		double prob;
		int level;
		bool isLeaf;
		Turn turn;
		Node* parent;
		Attack* move;
		bool moveSuccess;
		vector<Node> children;
	public:
		Node(int pHP, int pPP, int bHP, int bPP, double pr, int lev,bool leaf,Turn t,Node* par,Attack* mov,bool movSuc) {
			pikaHP = pHP;
			blasHP = bHP;
			pikaPP = pPP;
			blasPP = bPP;
			prob = pr;
			level = lev;
			isLeaf =leaf;
			turn = t;
			parent=par;
			move=mov;
			moveSuccess=movSuc;
		}
		int get_pikaHP() {
			return pikaHP;
		}
		int get_blasHP() {
			return blasHP;
		}
		int get_pikaPP() {
			return pikaPP;
		}
		int get_blasPP() {
			return blasPP;
		}
		double get_prob() {
			return prob;
		}
		int get_level() {
			return level;
		}
		bool get_isLeaf() {
			return isLeaf;
		}
		Turn get_turn() {
			return turn;
		}
		vector<Node> *get_children() {
			return &children;
		}
		Node* get_parent(){
			return parent;
		}
		Attack* get_move(){
			return move;
		}
		bool get_moveSuccess(){
			return moveSuccess;
		}
		void set_isLeaf(bool input) {
			isLeaf=input;
		}
		void printNode() {
			cout<<"P_HP:"<<pikaHP<<" P_PP:"<<pikaPP<<" B_HP:"<<blasHP<<" B_PP:"<<blasPP<<" PROB:"<<prob<<" LVL:"<<level<<endl;
		}
		void printChildren() {
			for(int i=0; i<children.size(); i++) {
				//	cout<<"child printed"<<endl;
				children[i].printNode();
			}
		}
};

class Graph {
	private:
		Node* root;
		int start_pHP ;
		int start_pPP = 100;
		int start_bHP ;
		int start_bPP = 100;
		Turn start_t = P;
		double start_pr = 1;
		int start_lvl =0;
		bool start_leaf = true;
		Node* start_parent=NULL;
		Attack* start_move=NULL;
		bool start_moveSuccess=true;
	public:
		Graph(int s_pHP=273,int s_bHP=361) {
			start_pHP=s_pHP;
			start_bHP=s_bHP;
			root = new Node(s_pHP, start_pPP, s_bHP, start_bPP, start_pr, start_lvl, start_leaf, start_t,start_parent,start_move,start_moveSuccess);
		}
		Node* get_root() {
			return root;
		}
		void printLastLayer(Node* currentNode,int maxLevel) {
			if(currentNode->get_level()==maxLevel) {
				currentNode->printNode();
			}
			for(int i=0; i<currentNode->get_children()->size(); i++) {
				//	cout<<"child printed"<<endl;
				printLastLayer(&currentNode->get_children()->at(i),maxLevel);
			}
		}
		void bfs(int &nodeCount){
			queue<Node> nodes;
			nodes.push(*root);
			while(!nodes.empty()){
				//nodes.front().printNode();
				nodeCount++;
				vector<Node> *children = nodes.front().get_children();
				for(int i=0;i<children->size();i++){
					nodes.push(children->at(i));
				}
				nodes.pop();
			}
		}
		
		void dfs(Node* node,int &nodeCount){
			//node->printNode();
			nodeCount++;
			for(int i=0;i<node->get_children()->size();i++){
					dfs(&node->get_children()->at(i),nodeCount);
				}
		}
		void createGraph(Node* currentNode,vector<Attack> &pikaAttacks, vector<Attack> &blasAttacks,int maxLevel) {
			if(currentNode->get_turn()==B) {
				int legalAttackCount=0;
				for(int i=0; i<blasAttacks.size(); i++) {
					Attack attack=blasAttacks[i];
					if((attack.getFirstUsage()<= currentNode->get_level()) && currentNode->get_blasPP()>= (-1)*attack.getPP()
					        && currentNode->get_pikaHP()>0 && currentNode->get_blasHP()>0 && currentNode->get_level()<maxLevel) {
						legalAttackCount++;
					}
				}
				//	cout<<legalAttackCount<<endl;
				for(int i=0; i<blasAttacks.size(); i++) {
					Attack attack=blasAttacks[i];
					Attack* attackPointer=&blasAttacks[i];
					if((attack.getFirstUsage()<= currentNode->get_level()) && currentNode->get_blasPP()>= (-1)*attack.getPP()
					        && currentNode->get_pikaHP()>0 && currentNode->get_blasHP()>0 && currentNode->get_level()<maxLevel) {
						if(attack.getAccuracy()==100) {
							currentNode->get_children()->push_back(Node(currentNode->get_pikaHP()-attack.getDamage(),currentNode->get_pikaPP(),currentNode->get_blasHP(),
							                                       currentNode->get_blasPP() + attack.getPP(), currentNode->get_prob()/legalAttackCount,currentNode->get_level()+1,true,P,currentNode,attackPointer,true));
						} else {
							currentNode->get_children()->push_back(Node(currentNode->get_pikaHP()-attack.getDamage(),currentNode->get_pikaPP(),currentNode->get_blasHP(),
							                                       currentNode->get_blasPP() + attack.getPP(), (currentNode->get_prob()/legalAttackCount)*(attack.getAccuracy()/100.0),currentNode->get_level()+1,true,P,currentNode,attackPointer,true));
							currentNode->get_children()->push_back(Node(currentNode->get_pikaHP(),currentNode->get_pikaPP(),currentNode->get_blasHP(),currentNode->get_blasPP() + attack.getPP(),
							                                       (currentNode->get_prob()/legalAttackCount)*((100-attack.getAccuracy())/100.0),currentNode->get_level()+1,true,P,currentNode,attackPointer,false));
						}
					}
				}
			} else {
				int legalAttackCount=0;
				for(int i=0; i<pikaAttacks.size(); i++) {
					Attack attack=pikaAttacks[i];
					if((attack.getFirstUsage() <= currentNode->get_level()) && currentNode->get_pikaPP()>= (-1)*attack.getPP()
					        && currentNode->get_pikaHP()>0 && currentNode->get_blasHP()>0 && currentNode->get_level()<maxLevel) {
						legalAttackCount++;
					}
				}
				for(int i=0; i<pikaAttacks.size(); i++) {
					Attack attack=pikaAttacks[i];
					Attack* attackPointer=&pikaAttacks[i];
					if((attack.getFirstUsage() <= currentNode->get_level()) && currentNode->get_pikaPP()>= (-1)*attack.getPP()
					        && currentNode->get_pikaHP()>0 && currentNode->get_blasHP()>0 && currentNode->get_level()<maxLevel) {
						if(attack.getAccuracy()==100) {
							currentNode->get_children()->push_back(Node(currentNode->get_pikaHP(),currentNode->get_pikaPP() + attack.getPP(),currentNode->get_blasHP()-attack.getDamage(),
							                                       currentNode->get_blasPP(), currentNode->get_prob()/legalAttackCount,currentNode->get_level()+1,true,B,currentNode,attackPointer,true));
						} else {
							currentNode->get_children()->push_back(Node(currentNode->get_pikaHP(),currentNode->get_pikaPP() + attack.getPP(),currentNode->get_blasHP()-attack.getDamage(), currentNode->get_blasPP(),
							                                       (currentNode->get_prob()/legalAttackCount)*(attack.getAccuracy()/100.0),currentNode->get_level()+1,true,B,currentNode,attackPointer,true));
							currentNode->get_children()->push_back(Node(currentNode->get_pikaHP(),currentNode->get_pikaPP() + attack.getPP(),currentNode->get_blasHP(), currentNode->get_blasPP(),
							                                       (currentNode->get_prob()/legalAttackCount)*((100-attack.getAccuracy())/100.0),currentNode->get_level()+1,true,B,currentNode,attackPointer,false));
						}
					}
				}

			}
			currentNode->set_isLeaf(false);
			for(int i=0; i<currentNode->get_children()->size(); i++) {
				createGraph(&currentNode->get_children()->at(i),pikaAttacks,blasAttacks,maxLevel);
			}
		}
		void easiestPath(string pokeName){
			
				int nodeCount;
				queue<Node> nodes;
				nodes.push(*root);
				Node* found;
				while(!nodes.empty()){
					if(pokeName=="pikachu"){
						if(nodes.front().get_blasHP()<=0){
							found=&nodes.front();
							break;
						}
					}else{
						if(nodes.front().get_pikaHP()<=0){
							found=&nodes.front();
							break;
						}
					}
					nodeCount++;
					vector<Node> *children = nodes.front().get_children();
					for(int i=0;i<children->size();i++){
						nodes.push(children->at(i));
					}
					nodes.pop();
				}
				Node* traverse= found;
				stack<Node*> steps;
				while(traverse){
					steps.push(traverse);
					traverse= traverse->get_parent();
					
				}
				steps.pop();
				while(!steps.empty()){
					//steps.top()->printNode();
					if(steps.top()->get_turn()==P){
						cout<<"Blastoise ";
					}else{
						cout<<"Pikachu ";
					}
					
					cout<<"used "<<(steps.top()->get_move())->getName()<<". ";
					
					if(steps.top()->get_moveSuccess()){
						cout<<"It's effective."<<endl;
					}else{
						cout<<"It's noneffective."<<endl;
					}
					steps.pop();
				}
				cout<<endl;
				cout<<"Level Count: "<<found->get_level()<<endl;
				cout<<"Probability: "<<found->get_prob()<<endl;
			
		}

};

int main(int argc, char* argv[]) {
	
	vector<Attack> pikaAttacks;
	pikaAttacks=Attack::createAttacks("pikachu.txt");
	vector<Attack> blasAttacks;
	blasAttacks=Attack::createAttacks("blastoise.txt");
	if(strcmp(argv[1],"part1")==0){
		Graph newGraph;
		newGraph.createGraph(newGraph.get_root(),pikaAttacks,blasAttacks,stoi(argv[2]));
		newGraph.printLastLayer(newGraph.get_root(),stoi(argv[2]));
	}else if(strcmp(argv[1],"part2")==0){
		Graph newGraph;
		newGraph.createGraph(newGraph.get_root(),pikaAttacks,blasAttacks,stoi(argv[2]));
		if(strcmp(argv[3],"bfs")==0){
			int nodeCount=0;
			auto start = chrono::high_resolution_clock::now();
			newGraph.bfs(nodeCount);
			auto stop = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start ).count();
			cout <<"Node Count: "<<nodeCount<<" Running Time: "<<duration<<" ms"<<endl;	
		}else if(strcmp(argv[3],"dfs")==0){
			int nodeCount=0;
			auto start = chrono::high_resolution_clock::now();
			newGraph.dfs(newGraph.get_root(),nodeCount);
			auto stop = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start ).count();
			cout <<"Node Count: "<<nodeCount<<" Running Time: "<<duration<<" ms"<<endl;	
		}else{
			cout <<"Invalid Argument"<<endl;
		}
	}else if(strcmp(argv[1],"part3")==0){
		if((strcmp(argv[2],"pikachu") != 0) && (strcmp(argv[2],"blastoise") != 0)){
			cout<<"Invalid input"<<endl;
			return -1;
		}
		Graph newGraph(200,200);
		newGraph.createGraph(newGraph.get_root(),pikaAttacks,blasAttacks,8);
		newGraph.easiestPath(argv[2]);
	}
	

    return 0;
}
