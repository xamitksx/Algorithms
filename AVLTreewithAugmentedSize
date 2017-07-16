#if 1
/*
  This code is AVL tree implementation with Augmented size. 
  I wrote this for https://www.hackerrank.com/challenges/median/problem
*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <iomanip>
#include <assert.h>

using namespace std;
#define MSIZE 100005
typedef struct tr {
	struct tr * left;
	struct tr * right;
	int data;
	int size; /// total no of nodes in subtree rooted here 1 + size[left] + size[rt];
	int height;  // max depth of leaf
} TNODE;
#define MAX(a,b) (((a)>(b))?(a):(b))

inline int getSize(TNODE * root)
{
	if (root == NULL) return 0;
	else return root->size;
}
inline int getHeight(TNODE * root)
{
	if (root == NULL) return 0;
	else return root->height;
}
inline int getBalanceFactor(TNODE * root)
{
	if (root == NULL) return 0;
	else
		//return root->left->height - root->right->height;
		return getHeight(root->left) - getHeight(root->right);
}


void leftRotate(TNODE ** root)
{
	TNODE * ROOT = *root;
	TNODE * newROOT = ROOT->right;
	ROOT->right = newROOT->left;
	newROOT->left = ROOT;
	*root = newROOT;
	// update height
	ROOT->height = 1 + MAX(getHeight(ROOT->left), getHeight(ROOT->right));
	newROOT->height = 1 + MAX(getHeight(newROOT->left), getHeight(newROOT->right));
	// update size
	ROOT->size = 1 + getSize(ROOT->left) + getSize(ROOT->right);
	newROOT->size = 1 + getSize(newROOT->left) + getSize(newROOT->right);
}
void rightRotate(TNODE ** root)
{
	TNODE * ROOT = *root;
	TNODE * newROOT = ROOT->left;
	ROOT->left = newROOT->right;
	newROOT->right = ROOT;
	*root = newROOT;
	// update height
	ROOT->height = 1 + MAX(getHeight(ROOT->left), getHeight(ROOT->right));
	newROOT->height = 1 + MAX(getHeight(newROOT->left), getHeight(newROOT->right));
	/// update size
	ROOT->size = 1 + getSize(ROOT->left) + getSize(ROOT->right);
	newROOT->size = 1 + getSize(newROOT->left) + getSize(newROOT->right);
}
bool insertinAVL(TNODE ** root, int data)
{
	bool status = false;
	TNODE *ROOT = *root;
	if (ROOT == NULL)
	{
		ROOT = (TNODE *)calloc(1, sizeof(TNODE));
		ROOT->data = data;
		ROOT->size = 1;
		ROOT->height = 1;
		*root = ROOT;
		return true;
	}
	else
	{
		if (data > ROOT->data)
		{
			status = insertinAVL(&ROOT->right, data);
		}
		else
		{
			status = insertinAVL(&ROOT->left, data);
		}
		++ROOT->size; // update size of subtree 
		ROOT->height = 1 + MAX(getHeight(ROOT->left), getHeight(ROOT->right)); // update height of subtree
	////// Do balncing 
#if 1
		int balanceFactor = getBalanceFactor(ROOT);
		if (balanceFactor > 1) /// left side is heavy
		{
			int balanceFactorLeft = getBalanceFactor(ROOT->left);
			if (balanceFactorLeft > 0) // single Rotation left left case
			{
				rightRotate(root);
			}
			else  // two rotations  left right case
			{
				leftRotate(&ROOT->left);
				rightRotate(root);
			}
		}
		else if (balanceFactor < -1) // right side heavy 
		{
			int balanceFactorRight = getBalanceFactor(ROOT->right);
			if (balanceFactorRight < 0) // single Rotation right right case
			{
				leftRotate(root);
			}
			else  // two rotations 
			{
				rightRotate(&ROOT->right);
				leftRotate(root);
			}
		}
#endif
	}

	return status;
}
bool removefrmAVL(TNODE ** root, int data);
void DelInOrderSucc(TNODE * ROOT)
{
	TNODE * toCopy = ROOT->right;
	TNODE * parent = ROOT;
	while (toCopy->left)
	{
		parent = toCopy;
		toCopy = toCopy->left;
	}
	ROOT->data = toCopy->data;
	removefrmAVL(&ROOT->right, toCopy->data); /// this will take care of all augment data update
}

bool removefrmAVL(TNODE ** root, int data)
{
	bool status = false;
	TNODE *ROOT = *root;
	if (ROOT == NULL)  // this is required since we have query for non existing no ...
		return false;

	if (data > ROOT->data)
	{
		status = removefrmAVL(&ROOT->right, data);
		if (status == true) /// we need to decrement only if no was found and deleted 
		{
			--ROOT->size;
			ROOT->height = 1 + MAX(getHeight(ROOT->left), getHeight(ROOT->right));
		}
	}
	else if (data < ROOT->data)
	{
		status = removefrmAVL(&ROOT->left, data);
		if (status == true) /// we need to decrement only if no was found and deleted 
		{
			--ROOT->size;
			ROOT->height = 1 + MAX(getHeight(ROOT->left), getHeight(ROOT->right));
		}

	}
	else if (ROOT->data == data)
	{
		status = true;
		// no child
		if (ROOT->left == NULL && ROOT->right == NULL)
		{
			free(ROOT);
			*root = NULL;
		}
		// single child
		else if (ROOT->left == NULL)
		{
			*root = ROOT->right;
			free(ROOT);
		}
		else if (ROOT->right == NULL)
		{
			*root = ROOT->left;
			free(ROOT);
		}
		else
		{  // BOTH child case inorder Successor go right and then leftest
			DelInOrderSucc(ROOT);
			--ROOT->size;  // other i.e right branch  will be updaed in recursion.
		}
	}
#if 1  // balance Tree
	TNODE *ROOT = *root;
	int balanceFactor = getBalanceFactor(ROOT);
	if (balanceFactor > 1) /// left side is heavy
	{
		int balanceFactorLeft = getBalanceFactor(ROOT->left);
		if (balanceFactorLeft > 0) // single Rotation left left case
		{
			rightRotate(root);
		}
		else  // two rotations  left right case
		{
			leftRotate(&ROOT->left);
			rightRotate(root);
		}
	}
	else if (balanceFactor < -1) // right side heavy 
	{
		int balanceFactorRight = getBalanceFactor(ROOT->right);
		if (balanceFactorRight < 0) // single Rotation right right case
		{
			leftRotate(root);
		}
		else  // two rotations    right left case
		{
			rightRotate(&ROOT->right);
			leftRotate(root);
		}
	}
#endif

	return status;
}
/*kth smallest node from total N nodes */
int gerKsmallestinBST(TNODE * root, int k)
{
	assert(root != NULL);
	int nodeCntTillHere = 1;
	if (root->left)
		nodeCntTillHere = nodeCntTillHere + root->left->size;
	if (nodeCntTillHere == k)
		return root->data;
	int data = 0;
	if (nodeCntTillHere > k) // go left
	{
		assert(root->left != NULL);
		data = gerKsmallestinBST(root->left, k);
	}
	else   // go right
	{
		assert(root->right != NULL);
		data = gerKsmallestinBST(root->right, k - nodeCntTillHere);
	}
	return data;
}
double  getMedian(TNODE * root, int totalNodes)
{
	double res = 0;
	int half = totalNodes / 2;
	if (totalNodes % 2 == 0)
	{
		long long a = gerKsmallestinBST(root, half);
		long long b = gerKsmallestinBST(root, half + 1);
		res = (double)(a + b) / 2.0;
	}
	else
	{
		res = gerKsmallestinBST(root, half + 1);
	}
	return res;
}
void deleteAVLTree(TNODE ** root)
{
	TNODE *ROOT = *root;
	if (ROOT != NULL)
	{
		deleteAVLTree(&ROOT->left);
		deleteAVLTree(&ROOT->right);
		free(ROOT);
		*root = NULL;
	}
}
void inorder(TNODE * root)
{
	if (root != NULL)
	{
		inorder(root->left);
		cout << root->data << ", ";
		inorder(root->right);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
#ifdef _WIN32
	freopen("input.txt", "r", stdin);
	freopen("Text.txt", "w", stdout);
	int T;
	//	cin >> T;
	//while (T--)
	{
#endif
		int N;
		cin >> N;
		TNODE * root = NULL;
		int totalNode = 0;
		for (int i = 0; i < N; i++)
		{
			int val;
			char ch;
			cin >> ch >> val;
			bool status = false;
			if (ch == 'a')
			{
				status = insertinAVL(&root, val);
				++totalNode;
			}
			else
			{
				status = removefrmAVL(&root, val);
				if (status == true)
					--totalNode;
			}

			if (status == true && totalNode>0)
			{
#if 0
				cout << "Total Node-" << totalNode << ": ";
				inorder(root);
				cout << endl;
#endif
				double ans = getMedian(root, totalNode);
				long long a = floor(ans * 10);
				if (a % 10 == 0)
					cout << (int)ans << endl;
				else
					cout << fixed << std::setprecision(1) << ans << endl;
			}
			else
				cout << "Wrong!" << endl;
		}
		//deleteAVLTree(&root);
#ifdef _WIN32
	}
#endif

	return 0;
}
#endif
