#include <stdio.h>
#include <stdlib.h>
#include <string>

std::string output;

typedef struct node {
    int val;
    int size;
    node *left;
    node *parent;
    node *right;
} node;

struct BST{
	node * root;
	int size;
};

node* newNode (int data, node* parent){
    node *temp = new node;
    temp->val = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = parent;
    return temp;
}

void inorder_traverse(node *root){ // try to return std::string
	if(root == NULL) return;
	inorder_traverse(root->left);
	output += std::to_string(root->val) + " ";
	inorder_traverse(root->right);
}

void rotate_right(node *tnode){
	node* n = tnode->left;
	int temp = n->val; n->val = tnode->val; tnode->val = temp;
	tnode->left = n->left;
	n->left = n->right;
	n->right = tnode->right;
	tnode->right = n;
	if(tnode->left)tnode->left->parent = tnode;
	if(n->right)n->right->parent = n;
}

void rotate_left(node *tnode){
	node* n = tnode->right;
	int temp = n->val; n->val = tnode->val; tnode->val = temp;
	tnode->right = n->right;
	n->right = n->left;
	n->left = tnode->left;
	tnode->left = n;
	if(tnode->right) tnode->right->parent = tnode;
	if(n->left) n->left->parent = n;
}

int height(node *n){
	if(!n) return 0;
	else{
		int one = 1+height(n->left);
		int two = 1+height(n->right);
		if(one >= two) return one;
		else return two;
	}
}

int heightTree(BST* tree){
	return height(tree->root);
}

void rebalance(node *n){
	if(height(n->left) > height(n->right)){
		if(height(n->left->left) >= height(n->left->right)){
			rotate_right(n);
		}
		else{
			rotate_left(n->left);
			rotate_right(n);
		}
	}
	else{
		if(height(n->right->right) >= height(n->right->left)){
			rotate_left(n);
		}
		else{
			rotate_right(n->right);
			rotate_left(n);
		}
	}
}

node* add_rec(node* tnode, int val, node* parent){
	if(!tnode && !parent){
		parent = newNode(val, NULL);
		return parent;
	}
	else if(!tnode) return newNode(val, parent);
	else if(val<tnode->val) tnode->left = add_rec(tnode->left, val, parent);
	else tnode->right = add_rec(tnode->right, val, parent);
	if(abs(height(tnode->left) - height(tnode->right)) >= 2) rebalance(tnode);
	return tnode;
}

void add(BST * tree, int val){
	tree->root = add_rec(tree->root, val, tree->root);
	tree->size++;
}

bool contains_rec(node* n, int val){
	if(!n) return false;
	else if(val < n->val) return contains_rec(n->left, val);
	else if(val > n->val) return contains_rec(n->right, val);
	else return true;
}

bool contains(BST * tree, int val){
	return contains_rec(tree->root, val);
}

int n, j;

int main(){
	BST *tree = new BST();
	scanf("%d", &n);
	for(int i = 0; i<n; ++i){
		scanf("%d", &j);
		add(tree, j);
	}
	printf("%d", tree->root->val);
	return 0;
}

