#include <iostream>
using namespace std;
struct Node
{
	int key;
	Node* left, * right;
};
void Init(Node*& root)
{
	root = NULL;
}
void InsertNode(Node*& p, int key)
{
	if (p != NULL)
	{
		if (p->key == key)
			return;
		if (p->key > key)
			InsertNode(p->left, key);
		else
			InsertNode(p->right, key);
	}
	else
	{
		p = new Node;
		p->key = key;
		p->left = NULL;
		p->right = NULL;
	}
}
void Input(Node*& root)
{
	int n, key;
	cout << "\nNhap vao so phan tu can them: ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "\nNhap vao phan tu thu " << i << ": ";
		cin >> key;
		InsertNode(root, key);
	}
}
void OutputLNR(Node* p)
{
	if (p != NULL)
	{
		OutputLNR(p->left);
		cout << p->key << " ";
		OutputLNR(p->right);
	}
}
Node* NodeMinOnTheTree(Node* p)
{
	if (p == NULL)
		return NULL;
	if (p->left != NULL)
	{
		return NodeMinOnTheTree(p->left);
	}
	else
		return p;
}
Node* NodeMaxOnTheTree(Node* p)
{

	if (p == NULL)
		return NULL;
	if (p->right != NULL)
	{
		return NodeMaxOnTheTree(p->right);
	}
	else
		return p;
}

int DegreeOfNode(Node* p)
{
	if (p == NULL)
		return -1;
	if (p->left != NULL && p->right != NULL)
		return 2;
	if (p->left == NULL && p->right == NULL)
		return 0;
	return 1;
}

void DegreeOfTree(Node* p, int& dmax)
{
	if (p == NULL)
		return;
	dmax = DegreeOfNode(p);
	if (p->left != NULL)
	{
		if (dmax < DegreeOfNode(p->left))
		{
			DegreeOfTree(p->left, dmax);
		}
	}
	if (p->right != NULL)
	{
		if (dmax < DegreeOfNode(p->right))
		{
			DegreeOfTree(p->right, dmax);
		}
	}
}
int CountNode(Node* p)
{
	if (p != NULL)
	{
		return 1 + CountNode(p->left) + CountNode(p->right);
	}
	else
		return 0;
}
int CountNodeLeaf(Node* p)
{
	if (p == NULL)
	{
		return 0;
	}
	if (p->left == NULL && p->right == NULL)
	{
		return 1 + CountNodeLeaf(p->left) + CountNodeLeaf(p->right);
	}
	else
	{
		int _countleft = 0, _countright = 0;
		if (p->left != NULL)
			_countleft = CountNodeLeaf(p->left);
		if (p->right != NULL)
			_countright = CountNodeLeaf(p->right);

		return  _countleft + _countright;
	}
}

void main()
{
	Node* root;
	Init(root);
	Input(root);
	OutputLNR(root);

	Node* _min = NodeMinOnTheTree(root);
	Node* _max = NodeMaxOnTheTree(root);

	if (_min != NULL)
		cout << "\nGia tri nho nhat tren cay la = " << _min->key;
	if (_max != NULL)
		cout << "\nGia tri lon nhat tren cay la = " << _max->key;

	int dmax = 0;
	DegreeOfTree(root, dmax);
	cout << "\nBac cua cay la: " << dmax;

	int _count = CountNode(root);
	cout << "\nSo nut trong cay la: " << _count;

	int _countleaf = CountNodeLeaf(root);
	cout << "\nSo nut LA trong cay la: " << _countleaf;

	int _countInnerNode = _count - 1 - _countleaf;
	cout << "\nSo nut TRONG trong cay la: " << _countInnerNode;

}
nt HeightOfTree(Node* p)
{
	if (p == NULL)
		return 0;

	int left = HeightOfTree(p->left);
	int right = HeightOfTree(p->right);
	if (left > right)
		return 1 + left;
	else
		return 1 + right;


}