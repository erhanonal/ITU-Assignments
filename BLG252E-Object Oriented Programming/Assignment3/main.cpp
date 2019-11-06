/*erhanonal
Erhan Önal
Date: 09.05.2019 */

#include <iostream>
#include <cstring>
#include <string>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <stdio.h>


using namespace std;

class Ingredient {
	protected:
		string name;
		Ingredient(string inputName) {
			name=inputName;
		}

	public:
		virtual void use(int)=0;
		virtual bool checkStock(int)=0;
		virtual float calculatePrice()=0;
		virtual string getName()=0;
		virtual int getNum()=0;
		virtual float getPrice()=0;
		virtual string printStock()=0;
};

class Type1 : public Ingredient {
	private:
		int weight;
		float gramPrice;
	public:
		Type1(string inputName, int inputWeight, float inputPrice):Ingredient(inputName) {
			weight=inputWeight;
			gramPrice=inputPrice;
		}
		virtual string printStock() {
			return name+"\t1\t"+to_string(weight)+"\t"+to_string(gramPrice);
		}
		virtual void use(int usedGram) {
			weight-=usedGram;
		}
		virtual bool checkStock(int checkGram) {
			return weight>=checkGram;
		}
		virtual float calculatePrice() {
			return weight*gramPrice;
		}
		virtual string getName() {
			return name;
		}
		virtual int getNum() {
			return weight;
		}
		float getPrice() {
			return gramPrice;
		}
};

class Type2 : public Ingredient {
	private:
		int unitNumber;
		float unitPrice;
	public:
		Type2(string inputName,int inputUnit, float inputPrice):Ingredient(inputName) {
			unitNumber=inputUnit;
			unitPrice=inputPrice;
		}

		virtual string printStock() {
			return name+"\t2\t"+to_string(unitNumber)+"\t"+to_string(unitPrice);
		}
		virtual void use(int usedUnit) {
			unitNumber-=usedUnit;
		};
		virtual bool checkStock(int checkUnit) {
			return unitNumber>=checkUnit;
		};
		virtual float calculatePrice() {
			return unitNumber*unitPrice;
		}
		string getName() {
			return name;
		}
		int getNum() {
			return unitNumber;
		}
		float getPrice() {
			return unitPrice;
		}
};

class Type3 : public Ingredient {
	private:
		int ml;
		float mlPrice;
	public:
		Type3(string inputName,int inputMl,float inputPrice):Ingredient(inputName) {
			ml=inputMl;
			mlPrice=inputPrice;
		}
		virtual string printStock() {
			return name+"\t3\t"+to_string(ml)+"\t"+to_string(mlPrice);
		}
		virtual void use(int usedMl) {
			ml-=usedMl;
		};
		virtual bool checkStock(int checkMl) {
			return ml>=checkMl;
		};
		virtual float calculatePrice() {
			return ml*mlPrice;
		}
		string getName() {
			return name;
		}
		int getNum() {
			return ml;
		}
		float getPrice() {
			return mlPrice;
		}
};

class Dish {
	private:
		float dishPrice;
		string dishName;
		vector<Ingredient*> requiredIng;
	public:

		string getName() {
			return dishName;
		}

		float getPrice() {
			return dishPrice;
		}
		Dish(string inputName,vector<Ingredient*> &inputIng) {
			dishName=inputName;
			dishPrice=0;
			for(int i=0; i<inputIng.size(); i++) {

				dishPrice+=inputIng[i]->calculatePrice();
				requiredIng.push_back(inputIng[i]);

			}

		}
		bool checkDish(vector<Ingredient*> &stock,int dishCount) {
			bool inStock=true;
			for(int i=0; i<requiredIng.size(); i++) {
				if(!stock[i]->checkStock(dishCount*requiredIng[i]->getNum())) {
					inStock=false;
				}
			}
			return inStock;
		}

		void serveDish(vector<Ingredient*> &stock) {
			for(int i=0; i<requiredIng.size(); i++) {
				for(int j=0; j<stock.size(); j++) {
					if(requiredIng[i]->getName()==stock[j]->getName()) {
						stock[j]->use(requiredIng[i]->getNum());
					}

				}

			}
		}

		void printDish() {
			cout<<"Dishname :"<<dishName<<endl;
			cout<<"Ingredients: "<<endl;
			for(int i=0; i<requiredIng.size(); i++) {
				cout<<requiredIng[i]->getNum()<<" "<<requiredIng[i]->getName()<<" Unit Price: "<<requiredIng[i]->getPrice()<<endl;
			}
			cout<<"Price: "<<dishPrice<<endl;
		}
};
int main() {
	const int MAX_ING=100;
	vector<Ingredient*> stock;

	fstream stockFile("stock.txt");
	if(stockFile.is_open()) {
		string line;

		getline(stockFile,line);
		while(getline(stockFile,line)) {
			char lineArray[line.length()+1];
			strcpy(lineArray, line.c_str());
			vector<string> tokens;
			char* token ;
			token=strtok(lineArray," \t");
			while(token!=NULL) {
				string tokenString(token);
				tokens.push_back(tokenString);
				token=strtok(NULL," \t");
			}

			if(tokens[1]!="1" && tokens[1]!="2" && tokens[1]!="3") {
				tokens[0]=tokens[0]+" "+tokens[1];
				tokens[1]=tokens[2];
				tokens[2]=tokens[3];
				tokens[3]=tokens[4];
			}

			Ingredient* newIng;
			if(tokens[1]=="1") {

				newIng=new Type1(tokens[0],stoi(tokens[2]),stof(tokens[3]));
			} else if(tokens[1]=="2") {
				newIng=new Type2(tokens[0],stoi(tokens[2]),stof(tokens[3]));
			} else if(tokens[1]=="3") {
				newIng=new Type3(tokens[0],stoi(tokens[2]),stof(tokens[3]));
			} else {
				cout<<"Wrong Type of Ingredient"<<endl;
			}
			stock.push_back(newIng);
		}
	}

	fstream menuFile("menu.txt");
	vector<Dish*> menu;
	if(menuFile.is_open()) {
		string line;
		getline(menuFile,line);
		while(getline(menuFile,line)) {
			string dishName;
			char lineArray[line.length()+1];
			strcpy(lineArray,line.c_str());
			char* token;
			token=strtok(lineArray,"\t");
			string tokenString(token);
			dishName=tokenString;
			vector<Ingredient*> ingInput;
			size_t found=line.find("\t");
			line.erase(0,found);
			char remainingArray[line.length()+1];
			strcpy(remainingArray,line.c_str());
			char* endToken;
			token=strtok_r(remainingArray,",",&endToken);

			while(token!=NULL) {

				string tokenString(token);
				char tokenArray[tokenString.length()+1];
				strcpy(tokenArray,tokenString.c_str());
				char* subEndToken;
				char* subToken=strtok_r(tokenArray," \t",&subEndToken);


				vector<string> ingSubTokens;
				while(subToken!=NULL) {
					string subTokenString(subToken);
					ingSubTokens.push_back(subTokenString);
					subToken=strtok_r(NULL," \t",&subEndToken);
				}
				float price=1;

				if(ingSubTokens[0][0]=='N' && ingSubTokens[0][1]=='/' && ingSubTokens[0][2]=='A') {

					for(int i=0; i<stock.size(); i++) {
						if(stock[i]->getName()==dishName) {
							price=stock[i]->getPrice();
						}
					}
					Ingredient* newIngredient=new Type2(dishName,1,price);

					ingInput.push_back(newIngredient);


				} else if((ingSubTokens[1]=="gram" || ingSubTokens[1]=="ml") && ingSubTokens.size()!=3) {
					ingSubTokens[2]=ingSubTokens[2]+" "+ingSubTokens[3];
				} else if((ingSubTokens[1]!="gram" && ingSubTokens[1]!="ml") && ingSubTokens.size()!=2) {
					ingSubTokens[1]=ingSubTokens[1]+" "+ingSubTokens[2];
				}

				if(ingSubTokens[0][0]!='N' || ingSubTokens[0][1]!='/' || ingSubTokens[0][2]!='A') {
					if(ingSubTokens[1]=="gram") {
						for(int i=0; i<stock.size(); i++) {
							if(stock[i]->getName()==ingSubTokens[2]) {
								price=stock[i]->getPrice();
							}
						}
						Ingredient* newIngredient=new Type1(ingSubTokens[2],stoi(ingSubTokens[0]),price);
						ingInput.push_back(newIngredient);
					} else if(ingSubTokens[1]=="ml") {
						for(int i=0; i<stock.size(); i++) {
							bool found=true;
							for(int j=0; j<stock[i]->getName().length(); j++) {

								if(stock[i]->getName()[j]!=ingSubTokens[2][j]) {
									found=false;
									break;
								}

							}
							if(found) {
								price=stock[i]->getPrice();
								break;
							}
						}


						Ingredient* newIngredient=new Type3(ingSubTokens[2],stoi(ingSubTokens[0]),price);
						ingInput.push_back(newIngredient);
					} else {
						for(int i=0; i<stock.size(); i++) {
							if(stock[i]->getName()==ingSubTokens[1]) {
								price=stock[i]->getPrice();
							}
						}
						Ingredient* newIngredient=new Type2(ingSubTokens[1],stoi(ingSubTokens[0]),price);
						ingInput.push_back(newIngredient);
					}
				}
				token=strtok_r(NULL,",",&endToken);
			}
			Dish *newDish=new Dish(dishName,ingInput);
			menu.push_back(newDish);
		}
	}

	fstream orderFile("order.txt");
	if(orderFile.is_open()) {
		string line;
		while(getline(orderFile,line)) {
			cout<<"Table"<<line[5]<<" ordered:"<<endl;
			float totalCost=0;
			getline(orderFile,line);
			int orderCount=stoi(line);
			for(int i=0; i<orderCount; i++) {
				getline(orderFile,line);
				char lineArray[line.length()+1];
				strcpy(lineArray,line.c_str());
				vector<string> tokens;
				char* token ;
				token=strtok(lineArray," ");
				while(token!=NULL) {
					string tokenString(token);
					tokens.push_back(tokenString);
					token=strtok(NULL," ");
				}
				if(tokens.size()!=2) {
					tokens[1]=tokens[1]+" "+tokens[2];
				}
				string dishName=tokens[1];
				int dishCount=stoi(tokens[0]);
				for(int i=0; i<menu.size(); i++) {
					bool found=true;
					for(int j=0; j<menu[i]->getName().length(); j++) {
						if(menu[i]->getName()[j]!=dishName[j]) {
							found=false;
							break;
						}
					}

					if(found) {
						if(!menu[i]->checkDish(stock,dishCount)) {
							cout<<"We don't have enough "<<menu[i]->getName()<<endl;
							int served=0;
							for(int j=0; j<dishCount; j++) {
								if(menu[i]->checkDish(stock,1)) {
									served++;
									menu[i]->serveDish(stock);
								}
							}
							if(served!=0) {
								cout<<served<<" "<<menu[i]->getName()<<" cost = "<<served*menu[i]->getPrice()<<endl;
								totalCost+=served*menu[i]->getPrice();
							}
						} else {
							for(int j=0; j<dishCount; j++) {
								if(menu[i]->checkDish(stock,1)) {
									menu[i]->serveDish(stock);

								}

							}
							cout<<dishCount<<" "<<menu[i]->getName()<<" cost = "<<dishCount*menu[i]->getPrice()<<endl;
							totalCost+=dishCount*menu[i]->getPrice();
						}
					}
				}
			}
			cout<<"Tip is "<<0.15*totalCost<<endl;
			cout<<"Total cost: "<<1.23*totalCost<<" TL"<<endl;
		}

		ofstream stockUpdate;
		stockUpdate.open("stock.txt",ofstream::out | ofstream::trunc);
		if(stockUpdate.is_open()) {
			stockUpdate<<"Name\tType\tItemCount\tPrice";
			for(int i=0; i<stock.size(); i++) {
				stockUpdate<<"\n"<<stock[i]->printStock();
			}
		}


		for(int i=0; i<stock.size(); i++) {
			delete stock[i];
		}
		for(int i=0; i<menu.size(); i++) {
			delete menu[i];
		}
	}
	return 0;
}

