/*
**	Erhan Önal 150170713
*/
#include <bits/stdc++.h>

using namespace std;

int calculateDistance(vector<pair<int, int> > a, vector<pair<int, int> > b) {//Modified version Levenshtein Distance Algorithm for number sequences
	int array[a.size()+1][b.size()+1];

	for(int i = 0; i< a.size() + 1; i++) {
		for(int j = 0; j< b.size() +1 ; j++) {
			if(i == 0) {
				array[i][j] = j;// If the first sequence is empty, distance is equal to second sequnce length
			} else if(j == 0) {
				array[i][j] = i;// If the second sequence is empty, distance is equal to first sequnce length
			} else if(a[i-1].second == b[j-1].second) {
				array[i][j] = array[i-1][j-1];// If the last elements are equal, distance is equal to the subproblem without these elements
			} else {
				array[i][j] = 1 + min(array[i][j-1], min(array[i-1][j], array[i-1][j-1]));// Else get the minimum subproblem for insertion, removal or replacement 
			}
		}
	}
	return array[a.size()][b.size()];
}

vector<int> testSuiteSelection(int maxTime, int testCount, vector<int> times, vector<int> bugs) {// Weighted Knapsack algorithm
	int array[testCount+1][maxTime+1];
	for(int i=0; i< maxTime+1; i++) {
		array[0][i] = 0;//Initialize first row with 0 
	}
	for(int i=1; i < testCount+1; i++) {//Loop through 2d array
		for(int j = 0; j<maxTime+1; j++)
			if(times[i-1] > j) {
				array[i][j] = array[i-1][j];//If the time is bigger than the maxTime, we can't insert this test. Get the value from the subproblem before this test case
			} else {
				array[i][j] = max(array[i-1][j], array[i-1][j-times[i-1]]+ bugs[i-1]);//Else we may insert this test or not. Get the max value from insertion and not insertion
			}
	}
	vector<int> selectedIndex;//Store the selected indices
	int i=testCount;//Start from the last coordinates of 2d matrix, which is the solution to our problem
	int j=maxTime;
	while(i>0) {
		if(array[i][j] != array[i-1][j]) {//If the value of subproblem without this test is not equal to the value of this coordinates, we have selected this test
			selectedIndex.push_back(i);//Store the index
			j-=times[i-1];//Update the weight to move to the correct subproblem
			i--;//Move the subproblem without this test
		} else {
			i--;//Move the subproblem without this test
		}
	}
	return selectedIndex;
}

int main(int argc, char** argv) {
	//Read Data from file
	if(argc != 2){
		cout<<"Wrong Arguments"<<endl;
		return -1;
	}
	vector<int> bugs;
	vector<int> times;
	vector<string> names;
	vector<vector<string> > freqProfiles;//Store frequencies as a vector of vector holding strings
	ifstream file;
	file.open(argv[1]);
	string tmp;
	file>>tmp>>tmp>>tmp>>tmp;
	int maxTime ;
	file>>maxTime;
	file>>tmp>>tmp>>tmp>>tmp;
	string testSuiteData;
	getline(file, tmp);
	while(!file.eof()) {//Read test suites until end of file
		getline(file, testSuiteData);
		if(!testSuiteData.empty()) {
			stringstream dataStream(testSuiteData);//Convert the line of a test suite to stringstream
			string name;
			int bug;
			int runTime;
			dataStream>>name>>bug>>runTime;//Read test suite name, bug count and runtime
			names.push_back(name);
			bugs.push_back(bug);
			times.push_back(runTime);
			vector<string> freqs;//Vector to hold frequencies of a single test suite
			while(!dataStream.eof()) {//Read frequencies until the end of test suite
				string freq;
				dataStream>>freq;
				freqs.push_back(freq);//Store the frequencies in the vector
			}
			freqProfiles.push_back(freqs);//Store the frequency vectors in vector of vectors
		}
	}
	/*
	for(int i=0; i<freqProfiles.size();i++){
		cout<<"FreqProfiles for: "<<i<<endl;
		for(int j=0;j<freqProfiles[i].size();j++){
			cout<<freqProfiles[i][j]<<" ";
		}
		cout<<endl;
	}*/
	int testCount = bugs.size();
	vector<int> selectedIndex = testSuiteSelection(maxTime, testCount, times, bugs);//Get the test suite selection with Knapsack algorithm
	reverse(selectedIndex.begin(), selectedIndex.end());//Reverse the ordering to order suites in the same order they appear in input txt
	cout<<"Total amount of runnning time: "<<maxTime<<endl<<endl;
	cout<<"Selected Test Suites and number of previously discovered bugs"<<endl;
	int totalBugCount=0;
	for(int i = 0; i <selectedIndex.size(); i++) {
		cout<<names[selectedIndex[i]-1]<<" Bug Count: "<<bugs[selectedIndex[i]-1]<<endl;
		totalBugCount+=bugs[selectedIndex[i]-1];
	}
	cout<<"Total Bug Count: "<<totalBugCount<<endl<<endl;
	
//*****************         PART 2              **********************************
	
	cout<<"Test Suites and Test Case Orders"<<endl;
	for(int i = 0; i < selectedIndex.size(); i++) {//Loop through selected test suites
		int index = selectedIndex[i];
		cout<<names[index-1]<<" ";//Print the name of the selected test suite
		vector<int> coverages;//Vector to store coverage rates of individual test cases
		vector<vector<pair<int, int> > > freqVectors;//Convert the frequencies from string to vectors of integer pairs. First data of the pair is the value, second data of the pair is the index
		for(int j = 0; j<freqProfiles[index-1].size(); j++) {//Loop through frequency profiles of a single test case
			string freq = freqProfiles[index-1][j];//A single frequency profile is stored to string freq
			vector<pair<int, int> > tokens;//Vector to hold individual values in a frequency profile
			stringstream freqStream(freq);
			string read;
			int ind = 1;
			while(getline(freqStream, read, '-')) {//Tokenize a frequency profile to extract individual frequency value
				stringstream readStream(read);
				int readInt;
				readStream>>readInt;
				tokens.push_back(make_pair(readInt, ind));//Store the value of token in first location of pair and the index of token in the second location of pair
				ind++;
			}
			int coverage = 0;
			for(int k = 0; k < tokens.size(); k++) {//Loop through the tokens of a single frequency profile
				if(tokens[k].first != 0) {
					coverage++;//Calculate the coverage of a single frequency profile
				}
			}
			sort(tokens.begin(), tokens.end());//Sort the tokens based on their value stored in the first location of pair, indices are not lost since they are saved in second location of pair
			
			if(!tokens.empty()){
				freqVectors.push_back(tokens);//Store the tokens of single frequency profile to freqVectors
			}
			
			coverages.push_back(coverage);//Store the coverages in the vector
		}

		/*
		for(int a =0 ;a<freqVectors.size();a++){
			cout<<"FreqVector"<<endl;
			for(int b =0; b<freqVectors[a].size();b++){
				cout<<freqVectors[a][b].second<<"-"<<freqVectors[a][b].first<<" ";
			}
			cout<<endl;
		}*/

		vector<int>::iterator result = max_element(coverages.begin(), coverages.end());//Get an iterator to the frequency profile with most coverage
		int maxIndex = distance(coverages.begin(), result);//Get the index of the frequency profile with most coverage
		vector<pair<int, int> > distances;//Distance vector to store distance data
		for(int j = 0 ; j<freqVectors.size(); j++) {//Loop through frequency profiles
			distances.push_back(make_pair(calculateDistance(freqVectors[j],freqVectors[maxIndex]),j));//Calculate the distances between the freqProfile with most coverage and all other freqProfiles and store with index
		}
		
		
		/*cout<<"Distances: ";
		for(int j = 0 ; j<freqVectors.size(); j++) {//Loop through frequency profiles
			cout<<distances[j].first<<" ";
		}
		cout<<endl<<"Ordered: ";
		*/
		
		sort(distances.begin(), distances.end());//Sort the distances based on their value
		cout<<distances[0].second + 1<<" ";//Print the index of the freqProfile with lowest distance which is freqProfile with most coverage since we compared it to itself and distance is 0
		reverse(distances.begin(), distances.end());//Reverse the ordering of distances to get most distant freqProfiles to the front 
		for(int j = 0 ; j<freqVectors.size() - 1; j++) {//Loop through profiles excluding last element since we have already printed that value 
			cout<<distances[j].second + 1<<" ";//Print the indexes of freqProfiles
		}
		cout<<endl;

	}

	return 0;
}
