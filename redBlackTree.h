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
private:
	redBlackTreeNode *root;

public:
	redBlackTree();
	~redBlackTree();
	void add(int v);
	void erase(int v);
	void clear();
	redBlackTreeNode* find(int v);
	void print();
	bool check();

private:
	void deleteAllElements(redBlackTreeNode *(&pRoot));
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