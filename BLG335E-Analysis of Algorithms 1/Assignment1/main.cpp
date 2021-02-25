//Erhan �nal 150170713

#include <stdlib.h>
#include <iostream>	
#include <time.h>
using namespace std;

int main(){
	int n;
	cin>>n;
	srand(time(0)); 
	int array[n];
	for(int i=0;i<n;i++){
		array[i]=rand()%n+1;
	}
	cout<<"ARRAY:"<<endl;
	for(int i=0;i<n;i++){
		cout<<array[i]<<"\t";
		if(i%10==9){
			cout<<endl;
		}
	}
	cout<<endl;
	cout<<"EXPECTED NUMBER OF DUPLICATIONS = "<<(n-1)/2<<endl<<endl;
	int counter=0;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(array[j]==array[i]){
				cout<<"("<<i+1<<","<<j+1<<") ";
				counter++;
			}
		}	
	}
	cout<<endl<<endl;
	cout<<"ENCOUNTERED NUMBER OF DUPLICATIONS = "<<counter<<endl;
}
