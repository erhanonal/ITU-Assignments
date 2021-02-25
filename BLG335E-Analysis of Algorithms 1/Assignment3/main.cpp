#include <bits/stdc++.h>
using namespace std;
enum colour {RED, BLACK};

class Node {
	public :
		int packageSize;
		int ordinalNum;
		int nodeCount;
		Node *left, *right, *parent;
		colour col;
		Node(int pSize,int oNum,int nCount) {
			packageSize=pSize;
			ordinalNum=oNum;
			nodeCount=1;
			col=RED;
			left=right=parent=NULL;
		}
		void printNode() {
			cout<<"Size: "<<packageSize<<" LeftSize: "<<left->packageSize<<" RightSize: "<<right->packageSize<<" ParentSize: "<<parent->packageSize<<endl;
		}
};

class RBTree {
	public:
		Node *TreeRoot;
		RBTree() {
			TreeRoot=NULL;
		};
		void printInorder(Node* currentRoot) {
			if(currentRoot==NULL) {
				return;
			}
			printInorder(currentRoot->left);
			cout<<currentRoot->packageSize<<"-"<<currentRoot->col<<"	";
			printInorder(currentRoot->right);
		}
		void printLevelOrder(Node *root) {
			if (root == NULL)
				return;

			std::queue<Node *> q;
			q.push(root);

			while (!q.empty()) {
				Node *temp = q.front();
				cout<<temp->packageSize<<"-"<<temp->col<<"	";
				q.pop();

				if (temp->left != NULL)
					q.push(temp->left);

				if (temp->right != NULL)
					q.push(temp->right);
			}
		}
		Node* TreeInsert(Node* currentRoot,Node *newNode);
		void RBInsert(Node *newNode);
		void leftRotate(Node* &currentRoot,Node* &newNode);
		void rightRotate(Node* &currentRoot,Node* &newNode);
};

void RBTree::leftRotate(Node* &currentRoot,Node* &newNode) {
	Node* rightChild= newNode->right;
	newNode->right = rightChild->left;

	if(newNode->right !=NULL) {
		newNode->right->parent = newNode;
	}

	rightChild->parent=newNode->parent;

	if(newNode->parent==NULL) {
		currentRoot=rightChild;
	} else if(newNode==newNode->parent->left) {
		newNode->parent->left =rightChild;
	} else {
		newNode->parent->right =rightChild;
	}
	rightChild->left=newNode;
	newNode->parent=rightChild;
}


void RBTree::rightRotate(Node* &root,Node* &newNode) {
	Node* leftChild= newNode->left;
	newNode->left = leftChild->right;

	if(newNode->left !=NULL) {
		newNode->left->parent = newNode;
	}

	leftChild->parent=newNode->parent;

	if(newNode->parent==NULL) {
		root=leftChild;
	} else if(newNode==newNode->parent->left) {
		newNode->parent->left =leftChild;
	} else {
		newNode->parent->right =leftChild;
	}
	leftChild->right=newNode;
	newNode->parent=leftChild;
}

Node* RBTree::TreeInsert(Node* currentRoot,Node *newNode) {
	if(currentRoot==NULL) {
		return newNode;
	}
	if(newNode->packageSize< currentRoot->packageSize) {
		currentRoot->left = TreeInsert(currentRoot->left,newNode);
		currentRoot->left->parent=currentRoot;
	} else if(newNode->packageSize >= currentRoot->packageSize ) {

		currentRoot->right= TreeInsert(currentRoot->right,newNode);
		currentRoot->right->parent=currentRoot;
	}
	return currentRoot;
}

void RBTree::RBInsert(Node* newNode) {
	TreeRoot=TreeInsert(TreeRoot,newNode);

	Node* parent=NULL;
	Node* grandParent=NULL;

	while((newNode!=TreeRoot) && (newNode->col !=BLACK) && (newNode->parent->col==RED)) {
		parent=newNode->parent;
		grandParent=newNode->parent->parent;
		if(parent == grandParent->left) {

			Node* aunt=grandParent->right;
			//CASE 1 RED AUNT
			if(aunt!=NULL && aunt->col ==RED) {
				grandParent->col=RED;
				parent->col=BLACK;
				aunt->col=BLACK;
				newNode=grandParent;
			} else {
				//CASE 2 LeftRotate
				if(newNode==parent->right) {

					leftRotate(TreeRoot,parent);

					newNode=parent;
					parent=newNode->parent;
				}
				//CASE 3 RightRotate

				rightRotate(TreeRoot,grandParent);
				colour temp=parent->col;
				parent->col=grandParent->col;
				grandParent->col=temp;
				newNode=parent;
			}
		} else {
			Node* aunt=grandParent->left;
			//CASE 1 Recolor
			if((aunt!=NULL && aunt->col==RED)) {
				grandParent->col=RED;
				parent->col=BLACK;
				aunt->col=BLACK;
				newNode=grandParent;
			} else {
				//Case2 rightRotate
				if(newNode==parent->left) {
					rightRotate(TreeRoot,parent);
					newNode=parent;
					parent=newNode->parent;
				}

				//CASE 3 leftRotate
				leftRotate(TreeRoot,grandParent);
				colour temp=parent->col;
				parent->col=grandParent->col;
				grandParent->col=temp;
				newNode=parent;
			}



		}
	}
	TreeRoot->col=BLACK;
}

int main() {
	RBTree tree;
	Node* newNode1=new Node(7,1,1);
	tree.RBInsert(newNode1);
	tree.printInorder(tree.TreeRoot);
	cout<<endl;

	Node* newNode2=new Node(3,1,1);
	tree.RBInsert(newNode2);
	tree.printInorder(tree.TreeRoot);
	cout<<endl;

	Node* newNode3=new Node(6,1,1);
	tree.RBInsert(newNode3);
	tree.printInorder(tree.TreeRoot);
	cout<<endl;

	Node* newNode4=new Node(2,1,1);
	tree.RBInsert(newNode4);
	tree.printInorder(tree.TreeRoot);
	cout<<endl;

	Node* newNode5=new Node(5,1,1);
	tree.RBInsert(newNode5);
	tree.printInorder(tree.TreeRoot);
	cout<<endl;

	Node* newNode6=new Node(4,1,1);
	tree.RBInsert(newNode6);
	tree.printInorder(tree.TreeRoot);
	cout<<endl;

	Node* newNode7=new Node(3,1,1);
	tree.RBInsert(newNode7);

	cout<<endl<<"Final"<<endl;
	tree.printInorder(tree.TreeRoot);
	cout<<endl;
	cout<<"Level Order: "<<endl;
	tree.printLevelOrder(tree.TreeRoot);


}
