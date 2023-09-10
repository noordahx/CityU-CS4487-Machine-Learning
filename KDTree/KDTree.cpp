// O(k log n)
// n - number of points in the tree
#include<iostream>

using namespace std;

const int k = 2;

struct Node 
{
	int point[k];
	Node *left;
	Node *right;
};

struct Node* newNode(int arr[])
{
	struct Node* temp = new Node;
	
	for (int i = 0; i < k; i++)
		temp->point[i] = arr[i];

	temp->left = temp->right = NULL;
	return temp;
}

// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
Node *insertRec(Node *root, int point[], unsigned depth)
{
	if (root == NULL)
		return newNode(point);

	unsigned cd = depth % k;

	if (point[cd] < (root->point[cd]))
		root->left = insertRec(root->left, point, depth + 1);
	else
		root->right = insertRec(root->right, point, depth + 1);
	
	return root;
}

// Function to insert a new point with given point in
// KD Tree and return new root. It mainly uses above recursive
// function "insertRec()"
Node* insert(Node *root, int point[])
{
	return insertRec(root, point, 0);
}

// A utility method to determine if two Points are same
// in K Dimensional space
bool arePointsSame(int point1[], int point2[])
{
	for (int i = 0; i < k; ++i)
		if (point1[i] != point2[i])
			return false;
	
	return true;
}

// Searches a Point represented by "point[]" in the K D tree.
// The parameter depth is used to determine current axis.
bool searchRec(Node* root, int point[], unsigned depth)
{
	if (root == NULL)
		return false;
	if (arePointsSame(root->point, point))
		return true;

	unsigned cd = depth % k;

	if (point[cd] < root->point[cd])
		return searchRec(root->left, point, depth + 1);

	return searchRec(root->right, point, depth + 1);

}

// Searches a Point in the K D tree. It mainly uses
// searchRec()
bool search(Node* root, int point[])
{
	return searchRec(root, point, 0);
}

// A utility function to find minimum of three integers
int min (int x, int y, int z)
{
	return min(x, min(y,z));
}

// A utility function to find minimum of three integers
Node *minNode(Node *x, Node *y, Node *z, int d)
{
	Node *res = x;
	if (y != NULL && y->point[d] < res->point[d])
       		res = y;
	if (z != NULL && z->point[d] < res->point[d])
		res = z;
    	return res;
}

// Recursively finds minimum of d'th dimension in KD tree
// The parameter depth is used to determine current axis.
Node *findMinRec(Node* root, int d, unsigned depth)
{
	if (root == NULL)
		return NULL;
  
  	unsigned cd = depth % k;

  	if (cd == d) {
		  if (root->left == NULL)
		  	return root;
	  	return findMinRec(root->left, d, depth + 1);
  	}

	return minNode(root,
			findMinRec(root->left, d, depth + 1),
			findMinRec(root->right, d, depth + 1), d);
}

Node *findMin(Node* root, int d)
{
	return findMinRec(root, d, 0);
}	

// Copies point2 to point1
void copyPoint(int point1[], int point2[])
{
	for (int i = 0; i < k; i++)
		point1[i] = point2[i];
}

// Function to delete a given point 'point[]' from tree with root
// as 'root'.  depth is current depth and passed as 0 initially.
// Returns root of the modified tree.
Node *deleteNodeRec(Node* root, int point[], int depth)
{
	if (root == NULL)
		return NULL;

	int cd = depth % k;

	if (arePointsSame(root->point, point))
	{
		if (root->right != NULL)
		{
			Node *min = findMin(root->right, cd);
			
			copyPoint(root->point, min->point);

			root->right = deleteNodeRec(root->right, min->point, depth + 1);
		}
		else if (root->left != NULL)
		{
			Node *min = findMin(root->left, cd);
			copyPoint(root->point, min->point);
			root->right = deleteNodeRec(root->left, min->point, depth + 1);
		}
		else
		{
			delete root;
			return NULL;
		}
		return root;
	}
	if (point[cd] < root->point[cd])
		root->left = deleteNodeRec(root->left, point, depth + 1);
	else
		root->right = deleteNodeRec(root->right, point, depth + 1);
	return root;
}

Node* deleteNode(Node *root, int point[])
{
	return deleteNodeRec(root, point, 0);
}

int main()
{
	struct Node *root = NULL;
	int points[][k] = { { 30, 40 }, { 5, 25 },
      			{ 70, 70 }, { 10, 12 }, { 50, 30 }, { 35, 45 } };

	int n = sizeof(points)/sizeof(points[0]);

	for (int i = 0; i < n; i++)
		root = insert(root, points[i]);

	int point1[] = {10, 19};
	(search(root, point1))? cout << "Found\n": cout << "Not Found\n";

	int point2[] = {12, 19};
	(search(root, point2))? cout << "Found\n": cout << "Not Found\n";

	cout << "Minimum of 0'th dimension is " << findMin(root, 0) << endl;
    	cout << "Minimum of 1'th dimension is " << findMin(root, 1) << endl;

	root = deleteNode(root, points[0]);

	cout << "Root after deletion of (30, 40)\n";
	cout << root->point[0] << ", " << root->point[1] << endl;

	return 0;
}
