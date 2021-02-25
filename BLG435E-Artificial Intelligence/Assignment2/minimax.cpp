#include <bits/stdc++.h>


using namespace std;



void printState(vector<vector<int>> grid){
	for(int i = 0; i<9; i++){
		for(int j = 0; j<9 ; j++){
			cout<<grid[i][j]<<" ";
		}
		cout<<endl;
	} 
	cout<<endl<<endl<<"-------------------------------------------------------"<<endl<<endl;
}



bool validLocation(vector<vector<int>> *grid, int row, int col, int val){
	for(int i = 0; i<9; i++){
		if((*grid)[row][i] == val){
			return false;
		}
	}
	for(int i = 0; i<9; i++){
		if((*grid)[i][col] == val){
			return false;
		}
	}
	for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
        	if ((*grid)[i + row - row % 3 ][j + col - col%3] == val){
        		return false;	
			}  
		} 
	}
	return true;
}


bool maxValue(vector<vector<int>> *state, bool turn, int* callCount);

	

bool minValue(vector<vector<int>> *state, bool turn, int* callCount){
	*callCount +=1;
//	cout<<*callCount<<endl;
	bool moveMade = false;
	int v = 2;
	for(int i = 0; i<9; i++){
		for(int j = 0; j<9 ; j++){
			if((*state)[i][j] == 0){
				for(int val = 1; val<10; val++){
					if(validLocation(state, i, j, val)){
						moveMade = true;
						vector<vector<int>> newState = *state;
						newState[i][j] = val ;
						v = min(v, int(maxValue(&newState, !turn, callCount)));
					}
				}
			}
		}
	}
	if(!moveMade){
		return turn;
	} 
	
	return v;
}


bool maxValue(vector<vector<int>> *state, bool turn, int* callCount){
	*callCount +=1;
	bool moveMade = false;
	int v = -1;
	for(int i = 0; i<9; i++){
		for(int j = 0; j<9 ; j++){
			if((*state)[i][j] == 0){
				for(int val = 1; val<10; val++){
					if(validLocation(state, i, j, val)){
						moveMade = true;
						vector<vector<int>> newState = *state;
						newState[i][j] = val ;
						v = max(v, int( minValue(&newState, !turn, callCount)));
					}
				}
			}
		}
	}
	if(!moveMade){
		return turn;
	} 
	 
	return v;
}



int main(int argc, char *argv[]){

	ifstream inputFile(argv[1]);
	vector<vector<int>> grid;
	for(int i = 0; i<9; i++){
		vector<int> rowData;
		for(int j = 0; j<9 ; j++){
			int val;
			inputFile >> val;
			rowData.push_back(val);
		}
		grid.push_back(rowData);
	} 
	int callCount = 0;

	if(maxValue(&grid, false, &callCount)){
		cout<<"1"<<endl;
	}else{
		cout<<"2"<<endl;
	}
//	cout<<callCount<<endl;
	
	return 0;

}
