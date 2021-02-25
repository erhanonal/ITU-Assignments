//Erhan Önal 150170713

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
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
		sort(arr, first, mid);
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
