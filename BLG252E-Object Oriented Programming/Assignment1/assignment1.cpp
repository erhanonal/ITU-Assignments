/*@erhanonal
Erhan Önal
Date: 25.03.2019

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "Polynomial.h"
#include "Vector.h"
using namespace std;

/*Constructor for Vector Class
int s: Size of the vector
int* vals: Pointer to the array of vector values
*/ 
Vector::Vector(int s,int* vals){
	size=s;
	values=new int[size];
	for(int i=0;i<size;i++){
		values[i]=vals[i];
	}
}  

Vector::Vector(const Vector &objectIn){//Copy constructor for Vector Class
	size=objectIn.size;
	values=new int[size];
	for(int i=0;i<size;i++){
		values[i]=objectIn.values[i];
	}
}

Vector::~Vector(){//Destructor for Vector Class
	delete[] values;
}

/*Overloaded addition operator for Vector class
returns a vector with size 0 for an invalid operation between vectors of different sizes
*/
Vector Vector::operator+(const Vector &objectIn)const{
	if(size==objectIn.size){
		int sumValues[size];
		for(int i=0;i<size;i++){
			sumValues[i]=values[i]+objectIn.values[i];
		}
		return Vector(size,sumValues);
	}else{
		cout<<"Can't add vectors with different sizes"<<endl;
		return Vector(0,NULL);
	}
}

Vector Vector::operator*(int scalar)const {//Overloaded multiplication operator for scalar multiplication
	int resultValues[size];
	for(int i=0;i<size;i++){
		resultValues[i]=values[i]*scalar;
	}
	return Vector(size,resultValues);
}

/*Overloaded multiplication operator for dot product
returns 0 for invalid operation with different sizes*/
int Vector::operator*(const Vector &objectIn)const{
	if(size==objectIn.size){
		int result=0;
		for(int i=0;i<size;i++){
			result+=values[i]*objectIn.values[i];
		}
		return result;
	}else{
		cout<<"Can't perform dot product on vectors with different sizes"<<endl;
		return 0;
	}
}

const Vector& Vector::operator=(const Vector &objectIn){//Overloaded assignment operator for Vector Class
	size=objectIn.size;
	delete[] values;
	values=new int[size];
	for(int i=0;i<size;i++){
		values[i]=objectIn.values[i];
	}
	return *this;
}



ostream& operator<<(ostream& os,const Vector& objectIn){//Function for printing a vector
	
	os<<"(";
	for(int i=0;i<objectIn.size;i++){
		os<<objectIn.values[i];
		if(i!=objectIn.size-1){
			os<<", ";
		}
	}
	os<<")";
	return os;
}


Polynomial::Polynomial(int d ,int* values_array){//Constuctor for Polynomial Class. int d : degree , int* values_array: array of coefficients
	degree=d;
	values=new int[degree+1];
	for(int i=0;i<degree+1;i++){
		values[i]=values_array[i];
	}
}

Polynomial::Polynomial(const Polynomial &objectIn){//Copy constructor for polynomial class
	degree=objectIn.degree;
	values=new int[degree+1];
	for(int i=0;i<degree+1;i++){
		values[i]= objectIn.values[i];
	}
}
Polynomial::~Polynomial(){//Destructor for Polynomial Class
	delete[] values;
}
Polynomial Polynomial::operator+(const Polynomial& objectIn)const{//Overloaded addition operator for polynomials
	if(degree>=objectIn.degree){
		int sumValues[degree+1];
		int i;
		for(i=0;i<degree-objectIn.degree;i++){
			sumValues[i]=values[i];
		}
		for(int j=0;j<objectIn.degree+1;j++){
			sumValues[i]=values[i]+objectIn.values[j];
			i++;
		}
			Polynomial sum(degree,sumValues);
			return sum;
		
	}else{
	
		int sumValues[objectIn.degree+1];
		int i;
		for(i=0;i<objectIn.degree-degree;i++){
			sumValues[i]=objectIn.values[i];
		}
		for(int j=0;j<degree+1;j++){
			sumValues [i]=objectIn.values[i]+values[j];
			i++;
		}
			Polynomial sum(objectIn.degree,sumValues);
			return sum;
	}

} 
Polynomial Polynomial::operator*(const Polynomial& objectIn) const{//Overloadad multiplication operator for polynomials
	int multiValues[degree+objectIn.degree+1];
	for(int i=0;i<degree+objectIn.degree+1;i++){
		multiValues[i]=0;
	}
	for(int i=0;i<degree+1;i++){
		for(int j=0;j<objectIn.degree+1;j++){
			multiValues[i+j]+=values[i]*objectIn.values[j];
		}
	}
	Polynomial multi(degree+objectIn.degree,multiValues);
	return multi;
}
const Polynomial& Polynomial::operator=(const Polynomial& objectIn){//Overloaded assignment operator for polynomials
	degree=objectIn.degree;
	delete[] values;
	values=new int[degree+1];
	for(int i=0;i<degree+1;i++){
		values[i]=objectIn.values[i];
	}
	return *this;
}
ostream& operator<<(ostream& os,const Polynomial& objectIn){//Function for printing a polynomial
	for(int i=0;i<objectIn.degree+1;i++){
		
		if(objectIn.values[i]<0){
			os<<" - ";		
		}else if(objectIn.values[i]>0 && i!=0){
			os<<" + ";
		}
		if((abs(objectIn.values[i])!=1 || i==objectIn.degree) && objectIn.values[i]!=0){
			os<<abs(objectIn.values[i]);
		}
		if(objectIn.values[i]!=0 && i!=objectIn.degree){
			os<<"x";
		}
		if(objectIn.values[i]!=0 && i!=objectIn.degree && i!=objectIn.degree-1){
			os<<"^"<<objectIn.degree-i;
		}
	}

	return os;
}

int Polynomial::getDegree(){
	return degree;
}

int* Polynomial::getValues(){
	return values;
}

int Vector::getSize(){
	return size;
}

int* Vector::getValues(){
 	return values;
 }

void printAllPolynomials(int polyCount,vector<Polynomial> &polynomials){//Prints all Polynomials
	cout<<"Polynomials: "<<endl;
	for(int i=0;i<polyCount;i++){
		cout<<i+1<<". "<<polynomials[i];
		cout<<endl;
	}
	cout<<endl;

}

void printAllVectors(int vectorCount,vector<Vector> &vectors){//Prints all Vectors
	cout<<"Vectors:"<<endl;
	for(int i=0;i<vectorCount;i++){
		cout<<i+1<<". "<<vectors[i];
		cout<<endl;
	}
	cout<<endl;
}

void printOptions(){
	
	cout<<"Possible Actions"<<endl;
	cout<<"1. Print Polynomial and Vector lists"<<endl;
	cout<<"2. Do a polynomial operation"<<endl;
	cout<<"3. Do a vector operation"<<endl;
	cout<<"4. Help: Print possible actions"<<endl;
	cout<<"0. Exit the program"<<endl<<endl;
}

int main(){
	ifstream polyFile;
	polyFile.open("Polynomial.txt");
	if(!polyFile){
		cout<<"Could not open Polynomial file"<<endl;
		return 1;
	}
	
	int polyCount;
	polyFile>>polyCount;
	vector<Polynomial> polynomials;
	for(int i=0;i<polyCount;i++){
		int degree;
		polyFile>>degree;
		int polyArray[degree+1];
		for(int j=0;j<degree+1;j++){
			int coeff;
			polyFile>>coeff;
			polyArray[j]=coeff;
		}
		Polynomial newPolynomial(degree,polyArray);
		polynomials.push_back(newPolynomial);
	}
	
	ifstream vectorFile;
	vectorFile.open("Vector.txt");
	if(!vectorFile){
		cout<<"Could not open Vector.txt"<<endl;
		return 1;
	}
	int vectorCount;
	vectorFile>>vectorCount;
	vector<Vector> vectors;
	for(int i=0;i<vectorCount;i++){
		int size;
		vectorFile>>size;
		int vectorArray[size];
		for(int j=0;j<size;j++){
			int value;
			vectorFile>>value;
			vectorArray[j]=value;
		}
		Vector newVector(size,vectorArray);
		vectors.push_back(newVector);
	}
	cout<<"Polynomial and Vector List Program!"<<endl;
	cout<<"Polynomials and Vectors are read from text files!"<<endl<<endl;
    printOptions();
	
	bool finish =false;
	while(!finish){
		cout<<"Enter an option: ";
		int selection;
		cin>>selection;
		if(selection==1){
			printAllVectors(vectorCount,vectors);
			printAllPolynomials(polyCount,polynomials);
		}
		else if(selection==2){
			cout<<"Which polynomial operation would you like to do (+:addition, *:multiplication):"<<endl;
			int operand1,operand2;
			char operation;
			cin>>operand1>>operation>>operand2;
			if(operation=='+'){
				if(operand1<1 || operand1>polyCount || operand2<1 || operand2>polyCount){
					cout<<"Polynomial doesn't exist"<<endl;
				}else{
					cout<<"("<<polynomials[operand1-1]<<") + ("<<polynomials[operand2-1]<<") = "<<polynomials[operand1-1]+polynomials[operand2-1]<<endl;
				}
			}else if(operation=='*'){
				if(operand1<1 || operand1>polyCount || operand2<1 || operand2>polyCount){
					cout<<"Polynomial doesn't exist"<<endl;
				}else{
					cout<<"("<<polynomials[operand1-1]<<") * ("<<polynomials[operand2-1]<<") = "<<polynomials[operand1-1]*polynomials[operand2-1]<<endl;
				}
			}else {
				cout<<"Unknown operation, try again"<<endl;
			}
		}
		else if(selection==3){
			cout<<"Which vector operation would you like to do (+:addition, *: scalar multiplication, .: dot product):"<<endl;
			int operand1,operand2;
			char operation;
			cin>>operand1>>operation>>operand2;
			if(operation=='+'){
				if(operand1<1 || operand1>vectorCount || operand2<1 || operand2>vectorCount){
					cout<<"Vector doesn't exist"<<endl;
				}else{
					cout<<vectors[operand1-1]<<" + "<<vectors[operand2-1]<<" = "<<vectors[operand1-1]+vectors[operand2-1]<<endl;
				}
			}else if(operation=='*'){
				if(operand1<1 || operand1>vectorCount ){
					cout<<"Vector doesn't exist"<<endl;
				}else{
					cout<<vectors[operand1-1]<<" * "<<operand2<<" = "<<vectors[operand1-1]*operand2<<endl;
				}
			}else if(operation=='.'){
				if(operand1<1 || operand1>vectorCount || operand2<1 || operand2>vectorCount){
					cout<<"Vector doesn't exist"<<endl;
				}else{
					cout<<vectors[operand1-1]<<" . "<<vectors[operand2-1]<<" = "<<vectors[operand1-1]*vectors[operand2-1]<<endl;
				}
			}else{
				cout<<"Unknown operation, try again"<<endl;
			}
		}else if(selection==4){
			printOptions();
		}else if(selection==0){
			finish =true;
			return 0;
		}else{
			cout<<"Unknown command,try again "<<endl;
		}
	}
    
    
	return 0;
}


