#include <iostream>
#include "KDTree.h"
#include "readcsv.h"
#include <vector>
#include <string>

using namespace std;


int main()
{
  int k = 2;
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

  vector<vector<int>> csv = readCSV("file.csv");

	return 0;
}
