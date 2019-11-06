/*@erhanonal
Erhan Önal
Date: 22.04.2019 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#define MAX_OPERATOR_SIZE 100
using namespace std;



class Operator {
		int center_x;
		int center_y;
		int op_size;
	public:
		Operator(int x, int y, int size);
		void reset(int new_x, int new_y, int new_size);

		void set_x(int new_x);
		int get_x();

		void set_y(int new_y);
		int get_y();

		void set_size(int new_size);
		int get_size();
};

class ArithmeticOperator: public Operator {
		char sign;
	public:
		ArithmeticOperator(int x, int y, int size, char sign_op);

		char get_sign();
		void printOperator();
		bool isIn(int x,int y);
};

class OperatorGrid {
		int grid_rows;
		int grid_cols;
		char **grid;
		int num_operators;
		ArithmeticOperator *operators[MAX_OPERATOR_SIZE];
	public:
		OperatorGrid(int rows, int cols);
		~OperatorGrid();

		bool place_operator(ArithmeticOperator*);
		bool move_operator(int x, int y, char direction, int move_by);
		void print_operators();
		void print_grid();
		void set_operator_positions(ArithmeticOperator*,bool);
		bool borderCheck(ArithmeticOperator*);
		bool conflictCheck(ArithmeticOperator*);

};




Operator::Operator(int x, int y, int size) {
	center_x=x;
	center_y=y;
	op_size=size;
}

void Operator::reset(int new_x, int new_y, int new_size) {
	center_x=new_x;
	center_y=new_y;
	op_size=new_size;
}

void Operator::set_x(int new_x) {
	center_x=new_x;
}

int Operator::get_x() {
	return center_x;
}

void Operator::set_y(int new_y) {
	center_y=new_y;
}

int Operator::get_y() {
	return center_y;
}

void Operator::set_size(int new_size) {
	op_size=new_size;
}

int Operator::get_size() {
	return op_size;
}



ArithmeticOperator::ArithmeticOperator(int x, int y, int size, char sign_op):Operator(x, y, size) {

	if(sign_op=='+' || sign_op=='-' || sign_op=='x' || sign_op=='/') {

		sign=sign_op;
	} else {
		sign='.';
		cout<<"SIGN parameter is invalid! "<<endl;
	}
}

char ArithmeticOperator::get_sign() {
	return sign;
}

void ArithmeticOperator::printOperator() {
	cout<<"ARITHMETIC_OPERATOR["<<get_sign()<<"], CENTER_LOCATION["<<get_x()<<","<<get_y()<<"], SIZE["<<get_size()<<"]"<<endl;
}



OperatorGrid::OperatorGrid(int rows, int cols) {
	num_operators=0;
	grid_rows=rows;
	grid_cols=cols;
	grid= new char*[grid_rows];
	for(int i=0; i<grid_rows; i++) {
		grid[i]= new char[grid_cols];
	}
	for (int i = 0; i < grid_rows; i++)
		for (int j = 0; j < grid_cols; j++)
			grid[i][j] ='.';
}

OperatorGrid::~OperatorGrid() {
	for(int i=0; i<grid_rows; i++) {
		delete[] grid[i];
	}
	delete[] grid;
	for(int i=0; i<num_operators; i++) {
		delete operators[i];
	}
	cout<<"DESTRUCTOR: GIVE BACK["<<grid_rows<<","<<grid_cols<<"] chars."<<endl;
	cout<<"DESTRUCTOR: GIVE BACK["<<num_operators<<"] Operators."<<endl;
}
bool OperatorGrid::place_operator(ArithmeticOperator *newOperator ) {
	if(newOperator->get_sign()=='.') {
		return false;
	}
	bool add=true;
	if (!borderCheck(newOperator)) {
		cout << "BORDER ERROR: Operator " << newOperator->get_sign() << " with size "
		     << newOperator->get_size() << " can not be placed on ("
		     << newOperator->get_x() << "," << newOperator->get_y() << ")."
		     << endl;
		add = false;
	}
	if (!conflictCheck(newOperator)) {
		cout << "CONFLICT ERROR: Operator " << newOperator->get_sign() << " with size "
		     << newOperator->get_size() << " can not be placed on ("
		     << newOperator->get_x() << "," << newOperator->get_y() << ")."
		     << endl;
		add = false;
	}
	if (add) {
		set_operator_positions(newOperator,false);
		cout << "SUCCESS: Operator " << newOperator->get_sign() << " with size "
		     << newOperator->get_size() << " is placed on (" << newOperator->get_x()
		     << "," << newOperator->get_y() << ")." << endl;
		ArithmeticOperator *addOperator=new ArithmeticOperator(newOperator->get_x(),newOperator->get_y(),newOperator->get_size(),newOperator->get_sign());
		operators[num_operators]=addOperator;
		num_operators++;
		return true;
	}
	return false;
}
bool ArithmeticOperator::isIn(int x,int y) {//Helper Function that checks if point x,y is in the calling ArithmeticOperator

	bool result=false;
	if(sign=='+') {
		if(x<=get_x()+get_size() && x>=get_x()-get_size() && y<=get_y()+get_size() && y>=get_y()-get_size()) {
			result=true;
		}
	} else if(sign=='-') {
		if(y<=get_y()+get_size() && y>=get_y()-get_size() && x==get_x()) {
			result=true;
		}
	} else if(sign=='x') {

		if(abs(x-get_x())==abs(y-get_y())  && abs(x-get_x())<=get_size()) {
			result=true;
		}
	} else if(sign=='/') {

		if(x-get_x()==get_y()-y && abs(x-get_x())<=get_size() && x-get_x()*y-get_y()<=0) {

			result=true;
		}
	}
	return result;
}

void OperatorGrid::set_operator_positions(ArithmeticOperator* setOperator, bool setToEmpty) {//Helper Function that sets the grid positions, for second argument true sets to empty, for false sets to the sign of setOperator

	char setTarget;
	if(setToEmpty) {
		setTarget='.';
	} else {
		setTarget=setOperator->get_sign();
	}
	switch (setOperator->get_sign()) {
		case '+':
			for (int i = 0; i <= setOperator->get_size(); i++) {
				grid[setOperator->get_x() + i - 1][setOperator->get_y()- 1] = setTarget;
				grid[setOperator->get_x() - i - 1][setOperator->get_y() - 1] = setTarget;
				grid[setOperator->get_x()- 1][setOperator->get_y() + i - 1] = setTarget;
				grid[setOperator->get_x()- 1][setOperator->get_y() - i - 1] = setTarget;
			}
			break;
		case '-':
			for (int i = 0; i <= setOperator->get_size(); i++) {
				grid[setOperator->get_x() - 1][setOperator->get_y() + i - 1] = setTarget;
				grid[setOperator->get_x() - 1][setOperator->get_y() - i - 1] = setTarget;
			}
			break;
		case 'x':
			for (int i = 0; i <= setOperator->get_size(); i++) {
				grid[setOperator->get_x() + i - 1][setOperator->get_y() + i - 1] = setTarget;
				grid[setOperator->get_x() + i - 1][setOperator->get_y() - i - 1] = setTarget;
				grid[setOperator->get_x() - i - 1][setOperator->get_y() + i - 1] = setTarget;
				grid[setOperator->get_x() - i - 1][setOperator->get_y() - i - 1] = setTarget;
			}
			break;
		case '/':
			for (int i = 0; i <= setOperator->get_size(); i++) {
				grid[setOperator->get_x() - i - 1][setOperator->get_y() + i - 1] = setTarget;
				grid[setOperator->get_x() + i - 1][setOperator->get_y() - i - 1] = setTarget;
			}
			break;
		default:
			cout << "Wrong Symbol" << endl;
			break;
	}
}
bool OperatorGrid::move_operator(int x, int y, char direction, int move_by) {

	if(grid[x-1][y-1]=='.') {
		return false;
	}
	ArithmeticOperator *targetOperator;
	for(int i=0; i<num_operators; i++) {
		if(operators[i]->isIn(x,y)) {

			targetOperator=operators[i];
			break;
		}
	}


	ArithmeticOperator checkOperator(targetOperator->get_x(),targetOperator->get_y(),targetOperator->get_size(),targetOperator->get_sign());
	if(direction=='R') {
		checkOperator.set_y(checkOperator.get_y()+move_by);
	} else if(direction=='L') {
		checkOperator.set_y(checkOperator.get_y()-move_by);
	} else if(direction=='U') {
		checkOperator.set_x(checkOperator.get_x()-move_by);
	} else if(direction=='D') {
		checkOperator.set_x(checkOperator.get_x()+move_by);
	}

	set_operator_positions(targetOperator,true);

	bool move = true;


	if (!borderCheck(&checkOperator)) {

		cout << "BORDER ERROR: " << checkOperator.get_sign() << " can not be moved from ("
		     << targetOperator->get_x() << "," << targetOperator->get_y()
		     << ") to (" << checkOperator.get_x() << "," << checkOperator.get_y()
		     << ")." << endl;
		move = false;
	}

	if (!conflictCheck(&checkOperator)) {
		cout << "CONFLICT ERROR: " << checkOperator.get_sign()
		     << " can not be moved from (" << targetOperator->get_x() << ","
		     << targetOperator->get_y() << ") to (" << checkOperator.get_x()
		     << "," << checkOperator.get_y() << ")." << endl;
		move = false;
	}

	if (!move) {
		set_operator_positions(targetOperator,false);
	}

	else {


		cout << "SUCCESS: " << checkOperator.get_sign() << " moved from ("
		     << targetOperator->get_x() << "," << targetOperator->get_y()
		     << ") to (" << checkOperator.get_x() << "," << checkOperator.get_y()
		     << ")." << endl;

		targetOperator->set_x(checkOperator.get_x());
		targetOperator->set_y(checkOperator.get_y());
		set_operator_positions(targetOperator,false);
	}

	return move;
}
bool OperatorGrid::borderCheck(ArithmeticOperator *checkOperator) {
	bool result;
	switch (checkOperator->get_sign()) {
		case '+':
		case 'x':
		case '/':
			result = (checkOperator->get_x() - checkOperator->get_size() > 0 &&
			          checkOperator->get_x() + checkOperator->get_size() <= grid_rows &&
			          checkOperator->get_y() - checkOperator->get_size() > 0 &&
			          checkOperator->get_y() + checkOperator->get_size() <= grid_cols);
			break;
		case '-':
			result = (checkOperator->get_y() - checkOperator->get_size() > 0 &&
			          checkOperator->get_y() + checkOperator->get_size() <= grid_cols &&
			          checkOperator->get_x() >0 &&
			          checkOperator->get_x() <=grid_rows);
			break;
		default:
			cout << "Wrong Symbol";
			result = false;
			break;
	}
	return result;
}

bool OperatorGrid::conflictCheck(ArithmeticOperator *checkOperator) {
	bool result = true;
	switch (checkOperator->get_sign()) {
		case '+':
			for (int i = 0; i <= checkOperator->get_size(); i++) {
				if (checkOperator->get_x() + i <= grid_rows && checkOperator->get_x() + i>0 && checkOperator->get_y()>0 && checkOperator->get_y()<=grid_cols) {
					if (grid[checkOperator->get_x() + i - 1][checkOperator->get_y() - 1] != '.') {
						result = false;
						break;
					}
				}
				if (checkOperator->get_x() - i <= grid_rows && checkOperator->get_x() - i > 0 && checkOperator->get_y()>0 && checkOperator->get_y()<=grid_cols) {
					if (grid[checkOperator->get_x() - i - 1][checkOperator->get_y() - 1]!= '.') {
						result = false;
						break;
					}
				}
				if (checkOperator->get_y() + i <= grid_cols && checkOperator->get_y() + i > 0 && checkOperator->get_x()>0 && checkOperator->get_x()<=grid_rows) {
					if (grid[checkOperator->get_x() - 1][checkOperator->get_y() + i - 1] != '.') {
						result = false;
						break;
					}
				}
				if (checkOperator->get_y() - i <= grid_cols && checkOperator->get_y() - i > 0 && checkOperator->get_x()>0 && checkOperator->get_x()<=grid_rows) {
					if (grid[checkOperator->get_x() - 1][checkOperator->get_y() - i - 1] != '.') {
						result = false;
						break;
					}
				}
			}
			break;

		case '-':

			for (int i = 0; i <= checkOperator->get_size(); i++) {
				if (checkOperator->get_y() + i <= grid_cols && checkOperator->get_y() + i > 0 && checkOperator->get_x() >0 && checkOperator->get_x()<grid_rows) {

					if (grid[checkOperator->get_x() - 1][checkOperator->get_y() + i - 1] != '.') {
						result = false;
						break;
					}
				}
				if (checkOperator->get_y() - i <= grid_cols && checkOperator->get_y() - i > 0 && checkOperator->get_x() >0 && checkOperator->get_x()<grid_rows) {

					if (grid[checkOperator->get_x() - 1][checkOperator->get_y() - i - 1] != '.') {

						result = false;
						break;
					}
				}
			}

			break;

		case 'x':
			for (int i = 0; i <= checkOperator->get_size(); i++) {
				if (checkOperator->get_x() + i <= grid_rows && checkOperator->get_x() + i >0 && checkOperator->get_y() + i <= grid_cols && checkOperator->get_y() + i > 0) {
					if (grid[checkOperator->get_x() + i - 1][checkOperator->get_y() + i - 1] !=
					        '.') {
						result = false;
						break;
					}
				}
				if (checkOperator->get_x() + i <= grid_rows && checkOperator->get_x() + i >0 && grid_rows && checkOperator->get_y() - i <= grid_cols && checkOperator->get_y() - i > 0) {
					if (grid[checkOperator->get_x() + i - 1][checkOperator->get_y() - i - 1] !=
					        '.') {
						result = false;
						break;
					}
				}
				if (checkOperator->get_x() - i > 0 && checkOperator->get_x() - i <= grid_rows && checkOperator->get_y() + i <= grid_cols && checkOperator->get_y() + i >0 ) {
					if (grid[checkOperator->get_x() - i - 1][checkOperator->get_y() + i - 1]!=
					        '.') {
						result = false;
						break;
					}
				}
				if (checkOperator->get_x() - i <=grid_rows  && checkOperator->get_x() - i > 0 && checkOperator->get_y() - i > 0 && checkOperator->get_y() - i > 0) {
					if (grid[checkOperator->get_x() - i - 1][checkOperator->get_y() - i - 1]!=
					        '.') {
						result = false;
						break;
					}
				}
			}
			break;
		case '/':
			for (int i = 0; i <= checkOperator->get_size(); i++) {
				if (checkOperator->get_x() + i <= grid_rows && checkOperator->get_x() + i >0 && checkOperator->get_y() - i <= grid_cols && checkOperator->get_y() - i > 0) {
					if (grid[checkOperator->get_x() + i - 1][checkOperator->get_y() - i - 1] !=
					        '.') {
						result = false;
						break;
					}
				}
				if (checkOperator->get_x() - i <=grid_rows  && checkOperator->get_x() - i > 0 && checkOperator->get_y() + i <= grid_cols && checkOperator->get_y() + i >0) {
					if (grid[checkOperator->get_x() - i - 1][checkOperator->get_y() + i - 1] !=
					        '.') {
						result = false;
						break;
					}
				}
			}
			break;
		default:
			cout << "Wrong Type" << endl;
			break;
	}
	return result;
}

void OperatorGrid::print_operators() {
	for(int i=0; i<num_operators; i++) {
		operators[i]->printOperator();
	}
}

void OperatorGrid::print_grid() {//Helper function for printing grid
	for(int i=0; i<grid_rows; i++) {
		for(int j=0; j<grid_cols; j++) {
			cout<<grid[i][j];
		}
		cout<<endl;
	}
}



