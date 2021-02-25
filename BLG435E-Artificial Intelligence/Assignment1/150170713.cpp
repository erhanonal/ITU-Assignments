//Erhan Önal 150170713

#include <bits/stdc++.h>
#include <iostream>	
#include <fstream>

using namespace std;

struct Node{
	pair<int, int> *agentCoordinates;
	pair<int, int> *goalCoordinates;
	Node* parent;
	string action;
	int depth;
};


void printMaze(vector<vector<string>> &maze){
	for(int i = 0; i< maze.size(); i++){
		for(int j = 0; j< maze[0].size() ; j++){
			cout<< maze[i][j]<<"\t";
		}
		cout<<endl;
	}
}

pair<int, int> *getNewAgentCoordinates(vector<vector<string>> &maze, pair<int, int> *agentCoordinates, string action){
	int agentCount = action.length();
//	cout<<"count "<<agentCount<<endl;
//	cout<<"Getting new Coordinates for : "<<action<<endl;
	pair<int, int> *newAgentCoordinates = new pair<int, int>[agentCount];
	for(int i = 0; i < agentCount; i++){
		switch(action[i]){
			case 'R':
			//	cout<<"case R"<<endl;
				if(maze[agentCoordinates[i].first][agentCoordinates[i].second + 1].compare("W") == 0 ){
					newAgentCoordinates[i] = make_pair(0, 0);
					break;
				}else{
					newAgentCoordinates[i] = make_pair(agentCoordinates[i].first, agentCoordinates[i].second  + 1);
				}
				break;
					
			case 'U':
		//		cout<<maze[agentCoordinates[i].first][agentCoordinates[i].second + 1]<<endl;
			//	cout<<"case U"<<endl;
				if(maze[agentCoordinates[i].first - 1][agentCoordinates[i].second].compare("W") == 0){
					newAgentCoordinates[i] = make_pair(0, 0);
					break;
				}else{
					newAgentCoordinates[i] = make_pair(agentCoordinates[i].first - 1, agentCoordinates[i].second );
				}
				break;
				
				
			case 'L':
			//	cout<<"case L"<<endl;
				if(maze[agentCoordinates[i].first][agentCoordinates[i].second - 1].compare("W") == 0 ){
					newAgentCoordinates[i] = make_pair(0, 0);
					break;
				}else{
					newAgentCoordinates[i] = make_pair(agentCoordinates[i].first , agentCoordinates[i].second  - 1);
				}
				break;
				
			case 'D':
			//	cout<<"case D"<<endl;
				if(maze[agentCoordinates[i].first + 1][agentCoordinates[i].second ].compare("W") == 0 ){
					newAgentCoordinates[i] = make_pair(0, 0);
					break;
				}else{
					newAgentCoordinates[i] = make_pair(agentCoordinates[i].first + 1, agentCoordinates[i].second );
				}
				break;
			
			case 'P':
			//	cout<<"P"<<endl;
				newAgentCoordinates[i] = make_pair(agentCoordinates[i].first, agentCoordinates[i].second );
				break;
			}
		}
		set<pair<int, int>> temp;
		for(int i = 0; i < agentCount; i++){
			if(temp.count(newAgentCoordinates[i]) == 0){
				temp.insert(newAgentCoordinates[i]);
			}else{
				newAgentCoordinates[i] = make_pair(0, 0); 
			}
		}
		for(int i = 0; i < agentCount; i++){
			for(int j = i + 1; j < agentCount; j++){
				if(newAgentCoordinates[i].first == agentCoordinates[j].first && newAgentCoordinates[i].second == agentCoordinates[j].second){
					newAgentCoordinates[i] = make_pair(0, 0); 
				} 
			}	
		}
			
	
		return newAgentCoordinates;
		
		
	}
	

	
	




Node* bfs(Node*  rootNode,int agentCount, vector<vector<string>> &maze){
	queue<Node*> nodes;
	nodes.push(rootNode);
	vector<pair<int, int>*> visitedNodes;
	int maxNodes = 0;
	string moves  = "RULDP";
	vector<string> actions;
	
	for(int i = 0; i < 5; i++){
		string s;
		actions.push_back(s + moves[i]);	
	}

	vector<string> newActions;
	for(int agents = 0; agents<agentCount-1; agents++){
		for(int i = 0; i < actions.size(); i++){
			for(int j = 0; j < 5; j++){
				newActions.push_back(actions[i] + moves[j]);
			}
		}
		actions = newActions;
	}
/*	for(int i = 0; i < actions.size(); i++){
		cout<<actions[i]<<" ";	
	}*/

	bool cont = true;
	Node* currentNode;
	

	int genCounter = 1;
	int exCounter = 0;
	while(cont){
		currentNode = nodes.front();
		if(nodes.size()> maxNodes){
			maxNodes = nodes.size();
		}
		nodes.pop();
		bool eval = true;
		for(int j = 0; j < visitedNodes.size(); j++){
			bool tmp = true;
			for(int k = 0; k< agentCount; k++){
				if(visitedNodes[j][k].first != currentNode-> agentCoordinates[k].first || visitedNodes[j][k].second != currentNode->agentCoordinates[k].second){
					tmp = false;
					break;
				}
			}
			if(tmp){
				eval = false;
				
				break;
			}
		}
		
		if(eval){
			exCounter++;	
		
			pair<int, int>* visitedNode = new pair<int, int>[agentCount];
			for(int j = 0; j< agentCount; j++){
				visitedNode[j].first = currentNode->agentCoordinates[j].first;	
				visitedNode[j].second = currentNode->agentCoordinates[j].second;	
			}
			visitedNodes.push_back(visitedNode);
			for(int i = 0; i < actions.size(); i++){
				
				pair<int, int> *newAgentCoordinates = getNewAgentCoordinates(maze, currentNode->agentCoordinates, actions[i]);
			//	cout<<"erhan"<<endl;
				bool validMove = true;
		
				for(int j = 0; j< agentCount; j++){
			//		cout<<"Agent "<<j<<" Depth "<< currentNode->depth +1 << " : "<<newAgentCoordinates[j].first << " --- "<<newAgentCoordinates[j].second<< " --- "<<actions[i]<<endl;
					if((newAgentCoordinates[j].first == 0) || (newAgentCoordinates[j].second == 0)){
						validMove = false;
			//			cout<<"   Nonvalid"<<endl;
						break;
					}
				}
				if(validMove){
					bool visited = false;
					for(int j = 0; j < visitedNodes.size(); j++){
						bool tmp = true;
						for(int k = 0; k< agentCount; k++){
							if(visitedNodes[j][k].first != newAgentCoordinates[k].first || visitedNodes[j][k].second != newAgentCoordinates[k].second){
								tmp = false;
								break;
							}
						}
						if(tmp){
							visited = true;
							
							break;
						}
					}
					
					if(!visited){
						struct Node* newNode = new Node{newAgentCoordinates, currentNode->goalCoordinates, currentNode, actions[i], currentNode->depth + 1};
						cout<<"Node not Visited: "<< actions[i]<<endl;
						nodes.push(newNode);
						genCounter++;
					}else{
						cout<<"Node visited: "<< actions[i]<<endl;
					}
					
					
		//		cout<<"   Valid"<<endl;
				}
			}	
		

	
		}

		bool foundSolution = true;
		cout<<"Checking locations for depth "<<currentNode->depth<<" move : "<<currentNode->action<<endl;
		for(int j = 0; j< agentCount; j++){

			cout<<currentNode->agentCoordinates[j].first<<" "<<currentNode -> agentCoordinates[j].second<< " --- "<< currentNode -> goalCoordinates[j].first<<" "<< currentNode -> goalCoordinates[j].second<<endl;
			if(currentNode->agentCoordinates[j].first != currentNode -> goalCoordinates[j].first || currentNode->agentCoordinates[j].second != currentNode -> goalCoordinates[j].second){
				foundSolution = false;
				break;
			}
		}
		if(foundSolution){
			cont = false;
		}
		cout<<"ex "<<exCounter<<endl;
		cout<<"gen:"<<genCounter<<endl;
	}
	cout<<"bfs end "<<maxNodes<<endl;
	return currentNode;
}



Node* dfs(Node*  rootNode,int agentCount, vector<vector<string>> &maze){
	stack<Node*> nodes;
	nodes.push(rootNode);
	int maxNodes = 0;
	vector<pair<int, int>*> visitedNodes;

	string moves  = "RULDP";
	vector<string> actions;
	
	for(int i = 0; i < 5; i++){
		string s;
		actions.push_back(s + moves[i]);	
	}

	vector<string> newActions;
	for(int agents = 0; agents<agentCount-1; agents++){
		for(int i = 0; i < actions.size(); i++){
			for(int j = 0; j < 5; j++){
				newActions.push_back(actions[i] + moves[j]);
			}
		}
		actions = newActions;
	}
/*	for(int i = 0; i < actions.size(); i++){
		cout<<actions[i]<<" ";	
	}*/

	bool cont = true;
	Node* currentNode;
	

	int genCounter = 1;
	int exCounter = 0;
	while(cont){
		currentNode = nodes.top();
		if(nodes.size()> maxNodes){
			maxNodes = nodes.size();
		}
		nodes.pop();
		bool eval = true;
		for(int j = 0; j < visitedNodes.size(); j++){
			bool tmp = true;
			for(int k = 0; k< agentCount; k++){
				if(visitedNodes[j][k].first != currentNode-> agentCoordinates[k].first || visitedNodes[j][k].second != currentNode->agentCoordinates[k].second){
					tmp = false;
					break;
				}
			}
			if(tmp){
				eval = false;
				
				break;
			}
		}
		
		if(eval){
				
			exCounter++;
			pair<int, int>* visitedNode = new pair<int, int>[agentCount];
			for(int j = 0; j< agentCount; j++){
				visitedNode[j].first = currentNode->agentCoordinates[j].first;	
				visitedNode[j].second = currentNode->agentCoordinates[j].second;	
			}
			visitedNodes.push_back(visitedNode);
			for(int i = 0; i < actions.size(); i++){
				
				pair<int, int> *newAgentCoordinates = getNewAgentCoordinates(maze, currentNode->agentCoordinates, actions[i]);
			//	cout<<"erhan"<<endl;
				bool validMove = true;
		
				for(int j = 0; j< agentCount; j++){
			//		cout<<"Agent "<<j<<" Depth "<< currentNode->depth +1 << " : "<<newAgentCoordinates[j].first << " --- "<<newAgentCoordinates[j].second<< " --- "<<actions[i]<<endl;
					if((newAgentCoordinates[j].first == 0) || (newAgentCoordinates[j].second == 0)){
						validMove = false;
			//			cout<<"   Nonvalid"<<endl;
						break;
					}
				}
				if(validMove){
					bool visited = false;
					for(int j = 0; j < visitedNodes.size(); j++){
						bool tmp = true;
						for(int k = 0; k< agentCount; k++){
							if(visitedNodes[j][k].first != newAgentCoordinates[k].first || visitedNodes[j][k].second != newAgentCoordinates[k].second){
								tmp = false;
								break;
							}
						}
						if(tmp){
							visited = true;
							
							break;
						}
					}
					
					if(!visited){
						struct Node* newNode = new Node{newAgentCoordinates, currentNode->goalCoordinates, currentNode, actions[i], currentNode->depth + 1};
						cout<<"Node not Visited: "<< actions[i]<<endl;
						nodes.push(newNode);
						genCounter++;
					}else{
						cout<<"Node visited: "<< actions[i]<<endl;
					}
					
					
		//		cout<<"   Valid"<<endl;
				}
			}	
		

	
		}

		bool foundSolution = true;
		cout<<"Checking locations for depth "<<currentNode->depth<<" move : "<<currentNode->action<<endl;
		for(int j = 0; j< agentCount; j++){

			cout<<currentNode->agentCoordinates[j].first<<" "<<currentNode -> agentCoordinates[j].second<< " --- "<< currentNode -> goalCoordinates[j].first<<" "<< currentNode -> goalCoordinates[j].second<<endl;
			if(currentNode->agentCoordinates[j].first != currentNode -> goalCoordinates[j].first || currentNode->agentCoordinates[j].second != currentNode -> goalCoordinates[j].second){
				foundSolution = false;
				break;
			}
		}
		if(foundSolution){
			cont = false;
		}
		cout<<"ex: "<<exCounter<<endl;

		cout<<"GenCount :"<<genCounter<<endl;
	}

	cout<<"dfs end "<<maxNodes<<endl;
	return currentNode;
}



int main(int argc, char *argv[]){

	ifstream inputFile(argv[1]);
	
	int row, col, agentCount;
	inputFile >> row >> col >> agentCount;
	vector<vector<string>> maze;
	pair<int, int> agentCoordinates[agentCount];
	pair<int, int> goalCoordinates[agentCount];
	for(int i = 0; i< row; i++){
		vector<string> rowData;
		for(int j = 0; j< col ; j++){
			string input;
			inputFile >> input;
			if(input[0] == 'A'){
				agentCoordinates[input[1] - '0' - 1] = make_pair(i, j);
				rowData.push_back("E");
			}else if(input[0] == 'G'){
				goalCoordinates[input[1] - '0' - 1] = make_pair(i, j);
				rowData.push_back("E");
			}
			else{
				rowData.push_back(input);
			}
		}
		maze.push_back(rowData);
	}
	for(int i = 0; i< agentCount; i++){
		cout<<agentCoordinates[i].first<<" "<<agentCoordinates[i].second<< " ---"<< goalCoordinates[i].first<<" "<<goalCoordinates[i].second<<endl;
	}
	printMaze(maze);
	cout<< "---------------------------------------------"<<endl;
/*	pair<int, int> *newAgentCoordinates = getNewAgentCoordinates(maze, agentCoordinates, "DR");
	for(int i = 0; i< agentCount; i++){
		cout<<newAgentCoordinates[i].first<<" "<<newAgentCoordinates[i].second<< " ---"<< goalCoordinates[i].first<<" "<<goalCoordinates[i].second<<endl;
	}*/
	
	struct Node* root = new Node{agentCoordinates, goalCoordinates, NULL, "", 0};
	ofstream myfile;
	if(argc == 3){
		myfile.open (argv[2]);
	}else{
		myfile.open("output.txt");
	}
	 


/////////////////////////////////////////////////////	
	
	Node* solution = bfs(root, agentCount, maze);
//	Node* solution = dfs(root, agentCount, maze);

////////////////////////////////////////////////////////////////////////
	myfile<<solution->depth<<" "<<agentCount;
	Node* traverse;
	traverse=solution;
	stack<string> output;
	while(traverse){
		output.push(traverse->action);
		traverse= traverse->parent;
	}
	while(!output.empty()){
		myfile<<output.top()<<endl;
		output.pop();
	}
	myfile.close();
	return 0;
}
