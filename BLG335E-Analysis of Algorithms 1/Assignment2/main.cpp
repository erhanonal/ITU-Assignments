/* @erhanonal
* Erhan �nal
* Date: 12.12.2019 */

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
using namespace std;

enum EventType {START, END};

/*****************************************************************
* Class for Event objects*
*****************************************************************/

class Event {
	public :
		int time;
		string name;
		EventType type;

		Event(int inputTime,string inputName,EventType inputType) {
			time=inputTime;
			name=inputName;
			type=inputType;
		}
		void printEvent() {
			cout<<name<<" "<<type<<" "<<time<<endl;
		}
};

/*****************************************************************
* Function Name: minHeapify *
* Ensures heap property for the input array from the index i up *
* Parameters: eventsArray,index i *
* Return: void *
* Algorithm: Function is called recursively *
*****************************************************************/

void minHeapify(vector<Event> &eventsArray,int i) {
	int l=2*i+1;
	int r=2*i+2;
	int smallest=i;
	if(l<eventsArray.size() && eventsArray[l].time < eventsArray[i].time) {
		smallest=l;
	}
	if(r<eventsArray.size() && eventsArray[r].time < eventsArray[smallest].time) {
		smallest=r;
	}
	if(smallest!=i) {
		Event tempEvent= eventsArray[i];
		eventsArray[i]=eventsArray[smallest];
		eventsArray[smallest]=tempEvent;
		minHeapify(eventsArray,smallest);
	}
}

/*****************************************************************
* Function Name: buildMinHeap *
* Transforms the given array into a heap structure *
* Parameters: eventsArray *
* Return: void *
* Algorithm: minHeapify called iteratively for half of the array *
*****************************************************************/
void buildMinHeap(vector<Event> &eventsArray) {
	int length=eventsArray.size();
	for(int i=(length/2-1); i>=0; i--) {
		minHeapify(eventsArray,i);
	}
}

/*****************************************************************
* Function Name: removeMinEvent *
* Removes the smallest element from the heap and restores heap structure *
* Parameters: eventsArray *
* Return: void *
*****************************************************************/
void removeMinEvent(vector<Event> &eventsArray) {
	int length=eventsArray.size();
	if(length<1) {
		cout<<"Error: Heap UnderFlow"<<endl;
	} else {
		eventsArray[0]=eventsArray[length-1];
		eventsArray.pop_back();
		minHeapify(eventsArray,0);
	}
}
int main(int argc, char **argv) {
	if(argc!=2) {
		cout<<"Insufficient arguments"<<endl;
		return 1;
	}

	ifstream events;
	events.open(argv[1]);
	vector<Event> eventsArray;
	while(!events.eof()) {
		string name;
		int startTime;
		int endTime;
		events>>name>>startTime>>endTime;
		Event newEvent=Event(startTime,name,START);
		eventsArray.push_back(newEvent);
		newEvent=Event(endTime,name,END);
		eventsArray.push_back(newEvent);
	}

	buildMinHeap(eventsArray);
	int time=1;
	bool removed=false;
	while(!eventsArray.empty()) {
		if(eventsArray[0].time==time) {
			if(eventsArray[0].type==0) {
				cout<<"TIME "<<time<<":"<<eventsArray[0].name<<" STARTED"<<endl;
			} else {
				cout<<"TIME "<<time<<":"<<eventsArray[0].name<<" ENDED"<<endl;
			}
			removeMinEvent(eventsArray);
			removed=true;
		} else if(removed) {
			time++;
			removed=false;
		} else {
			cout<<"TIME "<<time<<":"<<"NO EVENT"<<endl;
			time++;
		}


	}
	cout<<"TIME """<<time<<":"<<"NO MORE EVENTS, SCHEDULER EXITS"<<endl;

}

