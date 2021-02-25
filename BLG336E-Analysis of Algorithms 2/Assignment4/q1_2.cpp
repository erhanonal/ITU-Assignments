//Erhan Önal 150170713
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include<bits/stdc++.h> 
using namespace std;

void print_arr(vector<int>& arr, int first, int last)
{
	for (int i = first; i <= last; i++)
	{
		string if_eol = (i == last) ? "\n" : ", ";

		cout << arr[i] << if_eol;
	}
}

void merge(vector<int>& arr, int first, int mid, int last){
	int i = first;
	int j = mid + 1;
	int k = 0;
	vector<int> temp = arr;
	while(i <= mid && j <= last){
		if(arr[i] < arr[j]){
			temp[k++] = arr[i++];
		}else{
			temp[k++] = arr[j++];
		}
	}
	while(i <= mid){
		temp[k++] = arr[i++];
	}
	while(j <= last){
		temp[k++] = arr[j++];
	}
	
	i = first;
	j = 0;
	while(i <= last){
		arr[i] = temp[j];
		i++;
		j++;
	} 
}

void func(vector<int>& arr, int first, int last){
	int m = 0;
	int k = first;
	int temp;
	while(k < last){
		if(arr[k] > arr[k+1]){
			temp = arr[k];
			arr[k] = arr[k+1];
			arr[k+1] = temp;
		}
		k += 2;
	}
	vector<int> A = arr;
	k = first + 1;
	while(k <= last){
		A[m] = arr[k];
		m++;
		k += 2;
	}
	int x = first;
	k = first;
	while(k <= last){
		arr[x] = arr[k];
		x++;
		k += 2;
	}
	k = 0;
	while(k < m){
		arr[x] = A[k];
		x++;
		k++;
	}
	
}


pair<int, int> minMax(vector<int>& arr, int first, int last)
{	
	if(last == first){
		pair<int, int> result ;
		result.first = arr[first];
		result.second = arr[first];

		return  result;
	}else if(last - first == 1){
		pair<int, int> result;
		result.first = min(arr[first], arr[last]);
		result.second = max(arr[first], arr[last]);

		return  result;
	}else{
		int mid = (first + last) / 2;	
		pair<int, int> resultLeft;
		pair<int, int> resultRight;
		resultLeft = minMax(arr,first, mid);
		resultRight = minMax(arr, mid + 1, last);
		/*cout<<"Min: "<<resultLeft.first;
		cout<<" Max: "<<resultLeft.second<<endl;
		cout<<"Min: "<<resultRight.first;
		cout<<" Max: "<<resultRight.second<<endl;*/
		pair<int, int> result;
		result.first = min(resultLeft.first, resultRight.first);
		result.second = max(resultLeft.second, resultRight.second);
		return result;
	}
}


void sort(vector<int>& arr, int first, int last)
{
	int n = last + first + 1;
	if(n <= 1){
		return;
	}
	if(first != last){
		print_arr(arr, first, last);
	}
	if(first < last){
		func(arr, first, last);
		int mid = (first + last) / 2;
		cout<<"Min_max unsorted: ";
		print_arr(arr, first, mid);
		for(int i = 0; i <= (mid - first)/2; i++){
			pair<int, int> resultLeft = minMax(arr, first+i, mid-i);
			if(first+i != mid-i){
				cout<<"Min: "<<resultLeft.first;
				cout<<" Max: "<<resultLeft.second<<endl;
			}

			vector<int>::iterator itMin = std::find(arr.begin(), arr.end(), resultLeft.first); 
			int temp = arr[itMin- arr.begin()];
			arr[itMin- arr.begin()] = arr[first+i];
			arr[first+i] = temp;
	
			vector<int>::iterator itMax = std::find(arr.begin(), arr.end(), resultLeft.second);
			temp = arr[itMax - arr.begin()];
			arr[itMax - arr.begin()] = arr[mid-i];
			arr[mid-i] = temp;	
		}
		
		cout<<"Min_max sorted: ";
	
		print_arr(arr, first, mid);
	
		
		sort(arr, mid + 1, last);
		merge(arr, first, mid, last);
	}
	return;
}




int main(int argc, char *argv[])
{

	vector<int> all_values;


	try {
		
		ifstream myfile(argv[1]);

		
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				int number = stoi(line);
				all_values.push_back(number);
			}

			sort(all_values, 0, all_values.size() - 1);

			print_arr(all_values, 0, all_values.size() - 1);
		}
		else
		{
			cout << "File is not available." << endl;
			throw;
		}

	}
	catch (const ifstream::failure& e)
	{
		cerr << "Exception opening the file!" << endl;
		return -1;
	}
	catch (...)
	{
		cerr << "Something's wrong!" << endl;
		return -1;
	}



	return 0;
}
