//Erhan Önal 150170713
#include <bits/stdc++.h>
using namespace std;

/*****
*Helper Function to print adjacency Matrix for debugging
*
*/
void printAdjMatrix(vector <vector<int> > &adjMatrix) {
	for(int i=0; i<adjMatrix.size(); i++) {
		for(int j=0; j<adjMatrix.size(); j++) {
			cout<<adjMatrix[i][j]<<" ";
		}
		cout<<endl;
	}
}

/*****
*Function to determine the node with minimum distance value
*
*/
int minDistance(vector<int> &distance, vector<bool> &set) {
	int min = INT_MAX;
	int minIndex;

	for(int i=0; i<distance.size(); i++) {
		if(set[i]==false && distance[i] <= min) {
			min= distance[i];
			minIndex=i;
		}
	}
	return minIndex;
}

/*****
*Helper Function to print the path from a given node. Used for debugging
*
*/
void printPath(vector<int> &parent, int node) {
	if(parent[node]==-1) {
		return;
	}
	printPath(parent, parent[node]);
	cout<<node<<" ";
}

/*****
*A function to store the path information in a vector containing node Number and distance
*
*/
void savePath(vector<int> &distance,vector<int> &parent,vector<pair<int,int> > &path,int node,int forwardTime) {
	if(parent[node]==-1) {
		return;
	}
	savePath(distance,parent,path,parent[node],forwardTime);
	path.push_back(make_pair(node,distance[node]+forwardTime));
}


/*****
*Helper Function to print a vector holding path information
*
*/
void printResult(vector<pair<int,int> > path) {
	for(int i=0; i<path.size(); i++) {
		cout<<"Node: "<<path[i].first<<" Time"<<path[i].second<<endl;
	}
}

/*****
*Djikstra's shortest path algorithm modified for the assignment
*@param adjMatrix : Holds the graph structure
*@param sourceNode: Number of the starting Node
*@param destNode: Number of the ending Node
*@param forwardTime: Integer value for completion time of trip from hotel to destination plus 30 minutes waiting time, set to 0 when function is called for the trip to destination
*@return : returns vector of pairs with <int: nodeNumber, int: time>. Contains the shortest path found by the algorithm.
*/
vector<pair<int,int> > shortestPath(vector <vector<int> > &adjMatrix, int sourceNode,int destNode,int forwardTime) {
	vector<int> distance; //Stores distances of nodes
	vector<bool> set;	//Saves visited nodes
	vector<int> parent; //Saves parent information of nodes

	for(int i=0; i<adjMatrix.size(); i++) {
		parent.push_back(-1);
		set.push_back(false);
		distance.push_back(INT_MAX);
	}
	distance[sourceNode]=0;

	for(int i=0; i< adjMatrix.size()-1; i++) {
		int closestIndex = minDistance(distance,set);
		set[closestIndex]=true;

		for(int j=0 ; j<adjMatrix.size() ; j++) {
			if(!set[j] && adjMatrix[closestIndex][j] && distance[closestIndex] != INT_MAX && distance[closestIndex] + adjMatrix[closestIndex][j] < distance[j]) {
				distance[j] = distance[closestIndex] + adjMatrix[closestIndex][j];
				parent[j] = closestIndex;
			}
		}
	}

	vector<pair<int,int> > path;
	path.push_back(make_pair(sourceNode,0+forwardTime));//First point of path is sourceNode
	savePath(distance,parent,path,destNode,forwardTime);//This function extracts the path info from parent and distance vectors and stores in the path vector of pairs
	return path;

}
/*****
*Checks if there is a collision between two paths
*@param forwardTrip: flag used for doing additional checks if the trip is from hotel to destination
*/
int checkCollision(vector<pair<int,int> > josephPath,vector<pair<int,int> > lucyPath,bool forwardTrip) {
	for(int i =0; i<josephPath.size(); i++) {
		for(int j =0; j<lucyPath.size(); j++) {
			if(josephPath[i].first == lucyPath[j].first && (josephPath[i].second == lucyPath[j].second
			        || (forwardTrip && (i == josephPath.size()-1 && (josephPath[i].second <= lucyPath[j].second && josephPath[i].second +30 >= lucyPath[j].second))
			            || (j == lucyPath.size()-1 && (lucyPath[j].second <= josephPath[i].second && lucyPath[j].second +30 >= josephPath[i].second))))) {
				return josephPath[i].first;
			}
		}
	}
	return -1;
}
int main(int argc, char** argv) {
	ifstream file;
	file.open(argv[1]);
	int nodeCount,JH,JD,LH,LD;
	file>>nodeCount>>JH>>JD>>LH>>LD;
	vector <vector<int> > adjMatrix;

	for(int i=0; i<nodeCount; i++) {
		vector<int> vect;
		for(int j=0; j<nodeCount; j++) {
			vect.push_back(0);
		}
		adjMatrix.push_back(vect);
	}

	while(!file.eof()) {//Form the adjacencyMatrix
		int sourceNode,targetNode,weight;
		file>>sourceNode>>targetNode>>weight;
		adjMatrix[sourceNode][targetNode]=weight;
	}

	vector<pair<int,int> > josephPathForward = shortestPath(adjMatrix,JH,JD,0);//Create paths for forward trips
	
	vector<pair<int,int> > lucyPathForward = shortestPath(adjMatrix,LH,LD,0);

	if(josephPathForward[josephPathForward.size()-1].first!=JD || lucyPathForward[lucyPathForward.size()-1].first!=LD) {//If trips are not possible stop the program
		cout<<"No Solution"<<endl;
		return 0;
	}
	vector<pair<int,int> > newJosephPathForward,newLucyPathForward ;
	int check=checkCollision(lucyPathForward,josephPathForward,true);
	if(check>=0) {//If there is a collision between paths, find new paths
		vector <vector<int> > newAdjMatrix=adjMatrix;
		for(int i=0; i<adjMatrix.size(); i++) {//Remove edges to the vertex causing collision
			newAdjMatrix[i][check]=0;
		}
		newJosephPathForward = shortestPath(newAdjMatrix,JH,JD,0);//Form new paths
		int josephPathLength=INT_MAX;
		int lucyPathLength = INT_MAX;
		if(newJosephPathForward[newJosephPathForward.size()-1].first==JD) {
			josephPathLength=newJosephPathForward[newJosephPathForward.size()-1].second;
		}
		newLucyPathForward = shortestPath(newAdjMatrix,LH,LD,0);
		if(newLucyPathForward[newLucyPathForward.size()-1].first==LD) {
			lucyPathLength=newLucyPathForward[newLucyPathForward.size()-1].second;
		}
		if(lucyPathLength==INT_MAX && josephPathLength==INT_MAX) {//If new paths are not possible, stop program
			cout<<"No Solution!"<<endl;
			return 0;
		} else if(lucyPathLength>josephPathLength) {//Else select the path with lowest time
			josephPathForward=newJosephPathForward;
		} else {
			lucyPathForward=newLucyPathForward;
		}
	}

/********************************
*Similar steps for backwards trip
********************************/	
	vector<pair<int,int> > josephPathBackward = shortestPath(adjMatrix,JD,JH,josephPathForward[josephPathForward.size()-1].second+30);
	vector<pair<int,int> > lucyPathBackward = shortestPath(adjMatrix,LD,LH,lucyPathForward[lucyPathForward.size()-1].second+30);

	check=checkCollision(lucyPathBackward,josephPathBackward,false);
	vector<pair<int,int> > newJosephPathBackward,newLucyPathBackward ;
	if(check>=0) {
		vector <vector<int> > newAdjMatrix=adjMatrix;
		for(int i=0; i<adjMatrix.size(); i++) {
			newAdjMatrix[i][check]=0;
		}
		newJosephPathBackward = shortestPath(newAdjMatrix,JD,JH,josephPathForward[josephPathForward.size()-1].second+30);
		int josephPathLength=INT_MAX;
		int lucyPathLength = INT_MAX;
		if(newJosephPathBackward[newJosephPathBackward.size()-1].first==JH) {
			josephPathLength=newJosephPathBackward[newJosephPathBackward.size()-1].second;
		}


		newLucyPathBackward = shortestPath(newAdjMatrix,LD,LH,lucyPathForward[lucyPathForward.size()-1].second+30);
		if(newLucyPathBackward[newLucyPathBackward.size()-1].first==LH) {
			lucyPathLength=newLucyPathBackward[newLucyPathBackward.size()-1].second;
		}
		if(lucyPathLength==INT_MAX && josephPathLength==INT_MAX) {
			cout<<"No Solution!"<<endl;
			return 0;
		} else if(lucyPathLength>josephPathLength) {
			josephPathBackward=newJosephPathBackward;
		} else {
			lucyPathBackward=newLucyPathBackward;
		}
	}

	//Print the result
	cout<<"Joseph's Path, duration: "<<josephPathBackward[josephPathBackward.size()-1].second<<endl;
	for(int i=0; i<josephPathForward.size(); i++) {
		cout<<"Node: "<<josephPathForward[i].first<<" Time: "<<josephPathForward[i].second<<endl;
	}
	cout<<"-- return --"<<endl;


	for(int i=0; i<josephPathBackward.size(); i++) {
		cout<<"Node: "<<josephPathBackward[i].first<<" Time: "<<josephPathBackward[i].second<<endl;
	}
	cout<<endl;

	cout<<"Lucy's Path, duration: "<<lucyPathBackward[lucyPathBackward.size()-1].second<<endl;
	for(int i=0; i<lucyPathForward.size(); i++) {
		cout<<"Node: "<<lucyPathForward[i].first<<" Time: "<<lucyPathForward[i].second<<endl;
	}
	cout<<"-- return --"<<endl;
	for(int i=0; i<lucyPathBackward.size(); i++) {
		cout<<"Node: "<<lucyPathBackward[i].first<<" Time: "<<lucyPathBackward[i].second<<endl;
	}
	return 0;


}
