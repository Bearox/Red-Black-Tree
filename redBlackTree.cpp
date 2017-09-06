#include <iostream>
#include <stack>
using namespace std;

enum Color
{
	red,
	black,
};

struct redBlackTreeNode
{
	Color color;
	int value;
	redBlackTreeNode *leftChild, *rightChild, *father;
};

class redBlackTree
{
public:
	redBlackTree();
	~redBlackTree();
	void addAnElement(int v);
	void deleteAnElement(int v);
	void deleteAllElement(redBlackTreeNode *(&pRoot));
	redBlackTreeNode* find(int v);
	void print();
	bool check();
private:
	redBlackTreeNode *root;

	void addAnElement(redBlackTreeNode *node, redBlackTreeNode * pNode);
	redBlackTreeNode* findAnElement(int key, redBlackTreeNode *pNode);
	void fixUp(redBlackTreeNode *node);
	void leftRotate(redBlackTreeNode *node);
	void rightRotate(redBlackTreeNode *node);
	Color getUncleColor(redBlackTreeNode *node);
	void print(redBlackTreeNode *node);
	bool check(redBlackTreeNode *root, int BlackNum, int CurBlackNum);
	redBlackTreeNode* getRealDeletedNode(redBlackTreeNode* deletedItem);
	redBlackTreeNode* getMaxNode(redBlackTreeNode *pNode);
	redBlackTreeNode* getNewNode(redBlackTreeNode *pNode);
	void deleteFix(redBlackTreeNode *pNode, redBlackTreeNode *father);
};

redBlackTree::redBlackTree()
{
	root = NULL;
}
redBlackTree::~redBlackTree()
{
	deleteAllElement(root);
}
void redBlackTree::leftRotate(redBlackTreeNode *node)
{
	redBlackTreeNode *rNode = node->rightChild;
	redBlackTreeNode *father = node->father;
	if (rNode == NULL)
	{
		cout << "Error Happend in left Roatate! The rNode is NULL!!!" << endl;
		return;
	}

	node->rightChild = rNode->leftChild;
	if (rNode->leftChild != NULL)
	{
		rNode->leftChild->father = node;
	}

	rNode->leftChild = node;
	node->father = rNode;	
	rNode->father = father;
	if (father != NULL)
	{
		if (father->leftChild == node)
		{
			father->leftChild = rNode;
		}
		else
		{
			father->rightChild = rNode;
		}
	}
	else
	{
		root = rNode;
	}

}
void redBlackTree::rightRotate(redBlackTreeNode *node)
{
	redBlackTreeNode *lNode = node->leftChild;
	redBlackTreeNode *father = node->father;
	if (lNode == NULL)
	{
		cout << "Error Happend in right Roatate! The lNode is NULL!!!" << endl;
		return;
	}

	node->leftChild = lNode->rightChild;
	if (lNode->rightChild != NULL)
	{
		lNode->rightChild->father = node;
	}

	lNode->rightChild = node;
	node->father = lNode;
	lNode->father = father;
	if (father != NULL)
	{
		if (father->leftChild == node)
		{
			father->leftChild = lNode;
		}
		else
		{
			father->rightChild = lNode;
		}
	}
	else
	{
		root = lNode;
	}
}
void redBlackTree::addAnElement(int v)
{
	if (root == NULL)
	{
		root = new redBlackTreeNode;
		root->color = black;
		root->value = v;
		root->leftChild = NULL;
		root->rightChild = NULL;
		root->father = NULL;
	}
	else
	{
		redBlackTreeNode *newNode = new redBlackTreeNode;
		newNode->color = red;
		newNode->value = v;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		addAnElement(newNode, root);
	}
}
void redBlackTree::addAnElement(redBlackTreeNode * node, redBlackTreeNode * pNode)
{
	if (pNode == NULL)
	{
		cout << "Error Happend! pNode is an empty Node!" << endl;
		delete node;
		return;
	}
	else if (pNode->value > node->value)
	{
		if (pNode->leftChild == NULL)
		{
			pNode->leftChild = node;
			node->father = pNode;
			fixUp(node);
		}
		else
		{
			addAnElement(node, pNode->leftChild);
		}
	}
	else
	{
		if (pNode->rightChild == NULL)
		{
			pNode->rightChild = node;
			node->father = pNode;
			fixUp(node);
		}
		else
		{
			addAnElement(node, pNode->rightChild);
		}
	}
}
void redBlackTree::fixUp(redBlackTreeNode *node)
{
	if (node == NULL)
		return;
	redBlackTreeNode *father = node->father;
	redBlackTreeNode *grandFather = father==NULL? NULL : father->father; 
	if (father == NULL && node->color == red)
	{
		node->color = black;
		return;
	}

	if (father == NULL || father->color == black)
		return;

	
	if (getUncleColor(node) == red)
	{
		grandFather->leftChild->color = black;
		grandFather->rightChild->color = black;
		grandFather->color = red;
		fixUp(grandFather);
	}
	else
	{
		if (node->father->leftChild == node)
		{	
			if (grandFather->leftChild == node->father)
			{
				node->father->color = black;
				grandFather->color = red;
				rightRotate(grandFather);
			}
			else
			{
				rightRotate(father);
				fixUp(father);
			}
		}
		else
		{
			if (grandFather->leftChild == node->father)
			{
				leftRotate(father);
				fixUp(father);
			}
			else
			{
				node->father->color = black;
				grandFather->color = red;
				leftRotate(grandFather);
			}
		}
	}
}
Color redBlackTree::getUncleColor(redBlackTreeNode *node)
{
	redBlackTreeNode *grandFather = node->father->father;
	redBlackTreeNode *uncle;
	uncle = (node->father == grandFather->leftChild) ? grandFather->rightChild : grandFather->leftChild;
	if (uncle == NULL)
		return black;
	else
		return uncle->color;
}
redBlackTreeNode* redBlackTree::findAnElement(int key, redBlackTreeNode *pNode)
{
	if (pNode == NULL)
		return NULL;
	else if (pNode->value == key)
		return pNode;
	else if (pNode->value > key)
		return findAnElement(key, pNode->leftChild);
	else
		return findAnElement(key, pNode->rightChild);
}
redBlackTreeNode* redBlackTree::find(int v)
{
	return findAnElement(v, root);
}
void redBlackTree::deleteAllElement(redBlackTreeNode *(&pRoot))
{
	if (pRoot == NULL)
		return;
	if (pRoot->leftChild != NULL)
	{
		deleteAllElement(pRoot->leftChild);
	}
	if (pRoot->rightChild != NULL)
	{
		deleteAllElement(pRoot->rightChild);
	}

	delete pRoot;
	pRoot = NULL;
}
void redBlackTree::print()
{
	print(root);
	cout << endl;
}
void redBlackTree::print(redBlackTreeNode *node)
{
	if (node == NULL)
		return;
	print(node->leftChild);
	cout << node->value << " ";
	print(node->rightChild);
}
bool redBlackTree::check()
{
	if (root == NULL)
		return true;
	if (root->color == red)
		return false;
	int blackCount = 0;
	int curBlackCount = 0;
	redBlackTreeNode *pNode = root;
	while (pNode != NULL)
	{
		if (pNode->color == black)
			++blackCount;
		pNode = pNode->leftChild;
	}
	return check(root, blackCount, curBlackCount);
}
bool redBlackTree::check(redBlackTreeNode *root, int BlackNum, int CurBlackNum)
{
	if (root == NULL)
		return true;
	if (root->color == red &&  root->father->color == red)//存在两个连续的红节点,根节点一定是黑的，所以红色节点一定有父节点
		return false;
	if (root->color == black)//黑节点就CurBlackNum++  
		CurBlackNum++;
	if (root->leftChild == NULL && root->rightChild == NULL)
	{
		if (CurBlackNum == BlackNum)
			return true;
		else//黑色节点不相等返回false  
			return false;
	}
	return check(root->leftChild, BlackNum, CurBlackNum)
		&& check(root->rightChild, BlackNum, CurBlackNum);//进行左右递归  
}
void redBlackTree::deleteAnElement(int value)
{
	redBlackTreeNode *deletedItem = find(value);
	if (deletedItem == NULL )
	{
		cout << "The value is not in the tree." << endl;
		return;
	}
	redBlackTreeNode *realDeletedNode = getRealDeletedNode(deletedItem);
	deletedItem->value = realDeletedNode != deletedItem ? realDeletedNode->value : deletedItem->value;
	redBlackTreeNode *father = realDeletedNode->father;
	redBlackTreeNode *newNode = getNewNode(realDeletedNode);

	//Delete the Node.
	if (newNode != NULL)
		newNode->father = father;
	if (father == NULL)
	{
		root = newNode;
	}
	else
	{
		if (father->leftChild == realDeletedNode)
			father->leftChild = newNode;
		else if (father->rightChild == realDeletedNode)
			father->rightChild = newNode;
	}
	if(realDeletedNode->color != red)
		deleteFix(newNode, father);
	delete realDeletedNode;
}
void redBlackTree::deleteFix(redBlackTreeNode *newNode, redBlackTreeNode * father)
{
	if (father == NULL)
	{
		newNode == NULL ? 1 : newNode->color = black;
		return;
	}
	redBlackTreeNode *brother = (newNode == father->leftChild) ? father->rightChild : father->leftChild;

	if (newNode != NULL && newNode->color == red)
	{
		newNode->color = black;
	}
	else
	{
		if (brother != NULL && brother->color == red)
		{
			brother->color = black;
			father->color = red;
			if (father->leftChild == newNode)
			{
				leftRotate(father);
			}
			else if (father->rightChild == newNode)
			{
				rightRotate(father);
			}
			deleteFix(newNode, father);
		}
		else
		{

			if (brother == NULL)
			{
				cout << "ERROR in 3.2.1! There is an NULL uncle!" << endl;
				return;
			}
			if ((father->color == red) &&
				(brother->leftChild == NULL || brother->leftChild->color == black) &&
				(brother->rightChild == NULL || brother->rightChild->color == black))
			{
				father->color = black;
				brother->color = red;
				if (newNode != NULL)
					newNode->color = black;
			}
			else if ((father->color == black) &&
				(brother->leftChild == NULL || brother->leftChild->color == black) &&
				(brother->rightChild == NULL || brother->rightChild->color == black))
			{
				if(newNode != NULL)
					father->color = newNode->color;
				if (newNode != NULL)
					newNode->color = black;
				brother->color = red;
				if (father->color == red)
				{
					deleteFix(father, father->father);
				}
			}
			else {

				if (father->leftChild == brother && brother->color == black && brother->leftChild != NULL && brother->leftChild->color == red)
				{
					brother->color = father->color;
					father->color = black;
					brother->leftChild->color = black;
					rightRotate(father);
				}
				else if (father->leftChild == brother && brother->color == black && brother->rightChild != NULL && brother->rightChild->color == red)
				{
					brother->rightChild->color = father->color;
					father->color = black;
					leftRotate(brother);
					rightRotate(father);
				}
				else if (father->rightChild == brother && brother->color == black && brother->rightChild != NULL && brother->rightChild->color == red)
				{
					brother->color = father->color;
					father->color = black;
					brother->rightChild->color = black;
					leftRotate(father);
				}
				else
				{
					brother->leftChild->color = father->color;
					father->color = black;
					rightRotate(brother);
					leftRotate(father);
				}
			}
		}
	}
}
redBlackTreeNode* redBlackTree::getRealDeletedNode(redBlackTreeNode* deletedItem)
{
	if (deletedItem == NULL)
	{
		cout << "Error! it's an NULL node!" << endl;
	}
	if (deletedItem->leftChild == NULL || deletedItem->rightChild == NULL)
		return deletedItem;
	else
	{
		return getMaxNode(deletedItem->leftChild);
	}

}
redBlackTreeNode* redBlackTree::getMaxNode(redBlackTreeNode *pNode)
{
	if (pNode == NULL)
	{
		cout << "ERROR in getMaxNode" << endl;
		return NULL;
	}
	while (pNode->rightChild != NULL)
		pNode = pNode->rightChild;
	return pNode;
}
redBlackTreeNode* redBlackTree::getNewNode(redBlackTreeNode *pNode)
{
	if (pNode == NULL)
	{
		cout << "Error in getNewNode. The Node is NULL!" << endl;
		return NULL;
	}
	if (pNode->leftChild == NULL && pNode->rightChild == NULL)
	{
		return NULL;
	}
	return pNode->leftChild == NULL ? pNode->rightChild : pNode->leftChild;
}

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
		tree.addAnElement(x);
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
		tree.deleteAnElement(x);
		if (!tree.check())
			cout << "ERROR! It is not a red black tree!" << endl;
	}
	tree.print();
	return 0;
}
