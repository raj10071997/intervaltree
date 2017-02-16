#include<bits/stdc++.h>
using namespace std;
struct intrvl
{
	int low, high;
};

struct Node
{
	intrvl *i;
	int max;
	Node *left, *right, *parent;
};

intrvl *newintrvl(int low, int high)
{
	intrvl *i = new intrvl();
	i->low = low;
	i->high = high;
	return i;
}

class intrvlTree
{
private :
	Node *root;

public:
	intrvlTree(intrvl *i)
	{
		root = new Node();
		root->i = i;
		root->max = max(i->low, i->high);
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
	}
	
	Node* newNode(intrvl *i)
	{
		Node *node = new Node();
		node->i = i;
		node->max = max(i->low, i->high);
		node->left = NULL;
		node->right = NULL;
		return node;
	}

	void insert(intrvl *i)
	{
		Node *crntnode = newNode(i);
		insert(root, crntnode);
	}

	void insert(Node *root, Node *crntnode)
	{
		// tree==null
		if (!this->root){
			this->root = crntnode;
			this->root->parent = NULL;
		}else{
			root->max = max(root->max, crntnode->max);     //update max 
			// left for insertion
			if (crntnode->i->low < root->i->low){
				// if left node == NULL,  just insert it
				if (!root->left){
					root->left = crntnode;
					crntnode->parent = root;
				}else{
					insert(root->left, crntnode);
				}
			}else{// right for insertion
				// if right node == NULL, just insert it
				if(!root->right){
					root->right = crntnode;
					crntnode->parent = root;
				}else{
					insert(root->right, crntnode);
				}
			}
		}
	}

	bool checkoverlap(intrvl *a, intrvl *b)
	{
		if (a->low == b->low && a->high == b->high)
			return true;
		return false;
	}

	void deleteYourDesiredNode(intrvl *i)
	{
		deleteYourDesiredNode(root, i);
	}

	bool isItTheLeftChild(Node *t)
	{
		if (t->parent->left == t)
			return true;
		return false;
	}

	void deleteYourDesiredNode(Node *root, intrvl *i)
	{
		if(!root)
		{
			cout<<"No such interval exists"<<endl;
			return;
		}

		if (checkoverlap(root->i, i))
		{
			
			if (root->right)
			{//if match is FOUND and look in the right subtree
				Node *replaceWith = root;
				Node *temp = root->right;
				while(temp)
				{
					replaceWith = temp;
					temp = temp->left;
				}
				//delete replaceWith
				if (isItTheLeftChild(replaceWith))
				{
					replaceWith->parent->left = replaceWith->right;
					if (replaceWith->right) replaceWith->right->parent = replaceWith->parent;
				}else
				{
					replaceWith->parent->right = replaceWith->right;
					if (replaceWith->right) replaceWith->right->parent = replaceWith->parent;
				} 
				
				temp = replaceWith->parent;
				while(temp!=root)
				{
					if (temp->left) temp->max = root->left->max;
					if (temp->right) temp->max = max(root->max, root->right->max);
					temp = temp->parent;
				}
				
				root->i = replaceWith->i;
				root->max = replaceWith->max;
				if (root->left) root->max = max(root->max, root->left->max);
				if (root->right) root->max = max(root->max, root->right->max);
			}else{//if right subtree is empty
				if (isItTheLeftChild(root)){
					root->parent->left = root->left;
					if (root->left) root->left->parent = root->parent;
				}else
				{
					root->parent->right = root->left;
					if (root->left) root->left->parent = root->parent;
				} 
			}

			//updating max till root starting from the match's parent 
			Node *temp = root->parent;
			while(temp != NULL){
				temp->max = temp->i->high;
				if (temp->left) temp->max = max(temp->left->max, temp->max);
				if (temp->right) temp->max = max(temp->right->max, temp->max);
				temp = temp->parent;
			}

		}else{
			if (i->low < root->i->low)
				deleteYourDesiredNode(root->left, i);
			else deleteYourDesiredNode(root->right, i);
		}

	}

	bool dooverlap(intrvl *a, intrvl *b){
		if (a->high < b->low || a->low > b->high)
			return false;
		return true;
	}

	intrvl* srchovrlap(intrvl *i){
		return srchovrlap(root, i);
	}

	intrvl* srchovrlap(Node *root, intrvl *i){
		if (!root)
			return NULL;

		if (dooverlap(root->i, i))
			return root->i;

		if (root->left && i->low <= root->left->max)
			return srchovrlap(root->left, i);
		else return srchovrlap(root->right, i);
	}

	void inordertraverseTree(){
		inordertraverseTree(root);
	}

	void inordertraverseTree(Node *root){
		if (!root)
			return;
		inordertraverseTree(root->left);
		cout<<"("<<root->i->low<<","<<root->i->high<<",["<<root->max<<"]"<<")"<<"  ";
		inordertraverseTree(root->right);
	}
	
};

int main(){
	intrvlTree IT(newintrvl(15,20));
	intrvl ints[] = {{15,20}, {10, 30}, {17, 19},
        {5, 20}, {12, 15}, {16, 40}
    };
    int n = sizeof(ints)/sizeof(ints[0]);
    
    for (int i = 0; i < n; i++)
		IT.insert(newintrvl(ints[i].low, ints[i].high));

	IT.inordertraverseTree();
	
	intrvl *match = IT.srchovrlap(newintrvl(14, 19));
	if(match)
		cout<<"overlaps with ("<<match->low<<","<<match->high<<")"<<endl;
	else cout<<"no overlap";
	
	match = IT.srchovrlap(newintrvl(21, 23));
	if(match)
		cout<<"overlaps with ("<<match->low<<","<<match->high<<")"<<endl;
	else cout<<"no overlap";

	cout<<"enter the interval you want to delete"<<endl	;
	intrvl x;
	cin>>x.low>>x.high;
	IT.deleteYourDesiredNode(newintrvl(x.low,x.high));

	IT.inordertraverseTree();

	return 0;
}


