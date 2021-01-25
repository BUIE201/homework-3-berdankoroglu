#include <iostream>
#include <vector>
using namespace std;

struct Node
{
	int i;
	Node* pLeft;
	Node* pRight;
	bool flag;
	Node(int iIn) : i(iIn), pLeft(nullptr), pRight(nullptr) {}
};

void InsertToTree(Node*& pRoot, Node* pNew)
{
	if (!pRoot)
	{
		pRoot = pNew;
		return;
	}

	if (pNew->i <= pRoot->i)
		InsertToTree(pRoot->pLeft, pNew);
	else
		InsertToTree(pRoot->pRight, pNew);
}

void DeleteNodeWithTwoChildren(Node*& q, Node*& p)
{
	if (p->pRight)
	{
		DeleteNodeWithTwoChildren(q, p->pRight);
		return;
	}

	p->i = q->i;
	q = p;
	p = p->pLeft;
}

void DeleteNodeFromTree(Node*& pRoot, int i)
{
	if (!pRoot)
		return;

	if (pRoot->i < i)
	{
		DeleteNodeFromTree(pRoot->pRight, i);
		return;
	}

	if (pRoot->i > i)
	{
		DeleteNodeFromTree(pRoot->pLeft, i);
		return;
	}

	Node* q = pRoot;
	if (!q->pRight)
		pRoot = q->pLeft;
	else if (!q->pLeft)
		pRoot = q->pRight;
	else
		DeleteNodeWithTwoChildren(q, q->pLeft);

	delete q;
}

void PrintTree(Node* pRoot, int Level)
{
	if (!pRoot)
		return;

	PrintTree(pRoot->pRight, Level + 1);

	for (int i = 0; i < Level; i++)
		cout << "  ";
	cout << pRoot->i << endl;

	PrintTree(pRoot->pLeft, Level + 1);
}

void Insert(Node*& pRoot, Node* pNewNode)
{
	if (!pRoot)
		pRoot = pNewNode;
	else
	{
		if (pNewNode->i < pRoot->i)
			Insert(pRoot->pLeft, pNewNode);
		else
			Insert(pRoot->pRight, pNewNode);
	}
}


int LargestBranchSum(Node* pRoot)
{
	if (pRoot == nullptr) {
		return 0;
	}
	int pLeft = LargestBranchSum(pRoot->pLeft);
	int pRight = LargestBranchSum(pRoot->pRight);
	if (pLeft > pRight)					//we take the child with largest value
	{
		pRoot->flag = 0;
		return pLeft + pRoot->i;
	}
	else
	{
		pRoot->flag = 1;
		return pRight + pRoot->i;
	}

}
void print_max_road(Node* pRoot)
{
	if (pRoot == nullptr)
		return;
	cout << pRoot->i << ' ';
	if (pRoot->flag == 0)
		print_max_road(pRoot->pLeft);
	else
		print_max_road(pRoot->pRight);
}
void findLargestBranch(Node* pRoot)
{
	vector<vector<int> > branches;
	vector <int> branch;
	int max_sum = LargestBranchSum(pRoot);
	cout << " Branch with the largest sum is :";
	print_max_road(pRoot);
	cout <<"->SUM ="<< max_sum << endl;
}
int main()
{
	int i;

	Node* pRoot = nullptr;
	while (true)
	{
		cin >> i;
		if (i == 99)
			break;

		Node* p = new Node(i);
		InsertToTree(pRoot, p);
	}

	PrintTree(pRoot, 1);
	findLargestBranch(pRoot);
	return 0;
}