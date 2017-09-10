#include <iostream>
#include "redBlackTree.h"
using namespace std;

int main()
{
	redBlackTree tree;
	int n;
	cout << "Please enter the number of the tree nodes: ";
	cin >> n;
	cout << "Please enter the tree nodes' value: " << endl;
	for (int i = 0; i < n; ++i)
	{
		int x;
		cin >> x;
		tree.add(x);
	}
	tree.print();
	if (tree.check())
		cout << "It is a red black tree!" << endl;
	else
		cout << "It is not a red black tree!" << endl;

	cout << "Please enter the number of delete nodes: ";
	cin >> n;
	cout << "Please enter the deleted value: " << endl;
	for (int i = 0; i < n; ++i)
	{
		int x;
		cin >> x;
		tree.erase(x);
		if (!tree.check())
			cout << "ERROR! It is not a red black tree!" << endl;
	}
	tree.print();
	return 0;
}