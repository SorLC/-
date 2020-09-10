#ifndef BinarySearchTree_H
#define BinarySearchTree_H
#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>
#include <string>
using namespace std;

template <class K,class E>
struct TreeNode //普通二叉搜索树的节点结构
{
	pair<const K, E> element; //元素域
	TreeNode<K, E> *leftChild, *rightChild;  //左右孩子的指针
	TreeNode(pair<const K, E> thePair):element(thePair)
	{
		leftChild = rightChild = nullptr;
	}
	TreeNode(pair<const K, E> thePair, TreeNode<K, E>* left, TreeNode<K, E>*right):element(thePair)
	{
		leftChild = left;
		rightChild = right;
	}
};

template <class K,class E>
class BinarySearchTree
{
private:
	TreeNode<K, E> *root; //二叉搜索树的根节点
	static void levelOrder(TreeNode<K, E> *t, void(*visit)(TreeNode<K, E> *t));
	static void PostOrder(TreeNode<K, E> *t, void(*visit)(TreeNode<K, E> *t));
	static void outPut(TreeNode<K, E> *t);  //输出一个节点的内容
	static void release(TreeNode<K, E> *t); //释放一个节点的内容
	static int height(TreeNode<K, E> *t); //计算以t为根的树的高度
	static void _output(TreeNode<K, E> *t, bool left, string const& indent);
public:
	BinarySearchTree() { root = nullptr; }
	~BinarySearchTree()
	{
		erase_all();
	}
	void level_output(); //层序输出
	pair<const K, E>* find(const K theKey); //找到指定关键字的数对 
	void insert(pair<const K, E> thePair);  //插入新数对
	void erase(const K theKey); //删除指定关键字的数对
	void erase_all(); //清空树
	int height() { return height(root); } //返回该树的高度
	void _output()
	{
		if (root->rightChild)
		{
			_output(root->rightChild, false, "");
		}
		cout << root->element.second << endl;
		if (root->leftChild)
		{
			_output(root->leftChild, true, "");
		}
	}
};

template <class K,class E>
void BinarySearchTree<K, E>::outPut(TreeNode<K, E>*t)
{
	cout << t->element.first << "→" << t->element.second << " ";
}
template <class K,class E>
void BinarySearchTree<K, E>::release(TreeNode<K, E>*t)
{
	delete t;
}
template <class K,class E>
int BinarySearchTree<K, E>::height(TreeNode<K, E>*t) //计算以t为根的树的高度
{
	if (t == nullptr) return 0;
	else {
		int hl = height(t->leftChild);
		int hr = height(t->rightChild);
		return hl > hr ? hl + 1 : hr + 1;
	}
}
template <class K,class E>
void BinarySearchTree<K, E>::PostOrder(TreeNode<K, E>*t, void(*visit)(TreeNode<K, E>*t))
{
	if (t != nullptr)
	{
		PostOrder(t->leftChild, visit);
		PostOrder(t->rightChild, visit);
		visit(t);
	}
}
template <class K,class E>
void BinarySearchTree<K, E>::levelOrder(TreeNode<K, E>*t, void(*visit)(TreeNode<K, E>*t))
{
	queue<TreeNode<K, E>*> q;
	while (t != nullptr)
	{
		visit(t);
		if (t->leftChild) q.push(t->leftChild);
		if (t->rightChild) q.push(t->rightChild);
		if (!q.empty())
		{
			t = q.front();
			q.pop();
		}
		else break;
	}
}
template <class K,class E>
void BinarySearchTree<K, E>::level_output() //层序输出
{
	levelOrder(root, outPut);
	cout << endl;
}
template <class K, class E>
void BinarySearchTree<K, E>::erase_all() //清空
{
	PostOrder(root, release);
}
template <class K,class E>
pair<const K, E>* BinarySearchTree<K, E>::find(const K theKey)
{
	TreeNode<K, E>* cur = root;
	while (cur != nullptr) //从根节点开始，遍历搜索树
	{
		if (cur->element.first == theKey) break;
		else if (theKey < cur->element.first) cur = cur->leftChild;
		else cur = cur->rightChild;
	}
	pair<const K, E> *ans = nullptr; 
	if (cur != nullptr) ans = cur->element; //若未找到，返回空指针；否则返回指定数对的指针
	return ans;
}

template <class K,class E>
void BinarySearchTree<K, E>::insert(pair<const K, E> thePair) 
{  //插入新数对，若关键字已存在，则覆盖旧值
	TreeNode<K, E> *cur = root;
	TreeNode<K, E>*fp = nullptr;
	while (cur != nullptr )
	{
		fp = cur;
		if (thePair.first < cur->element.first) cur = cur->leftChild;
		else if (thePair.first > cur->element.first) cur = cur->rightChild;
		else {
			cur->element.second = thePair.second;
			return;
		}
	}
	//在叶节点插入新值
	TreeNode<K, E>* newNode = new TreeNode<K, E>(thePair);
	if (cur == root) root = newNode; //若为根节点，直接插入
	else { //否则判断左右
		if (thePair.first < fp->element.first) fp->leftChild = newNode;
		else fp->rightChild = newNode;
	}
}

template <class K,class E>
void BinarySearchTree<K, E>::erase(const K theKey) //删除指定关键字的数对
{
	TreeNode<K, E>* cur = root;
	TreeNode<K, E>*fp = nullptr;
	while (cur != nullptr && cur->element.first != theKey)
	{ //找到要删除的节点及其父节点
		fp = cur;
		if (theKey < cur->element.first) cur = cur->leftChild;
		else cur = cur->rightChild;
	}
	if (cur == nullptr) {
		cout << "没有此关键字" << endl;
		return;
	}
	else {
		if (cur->leftChild && cur->rightChild) //若此节点有两个孩子
		{//找到其左子树中最大的节点，顶替被删除的节点
			TreeNode<K, E> *Lmax = cur->leftChild,
				*Lfp = cur;
			while (Lmax->rightChild != nullptr) Lfp = Lmax, Lmax = Lmax->rightChild;
			TreeNode<K, E>* temp = new TreeNode<K, E>(Lmax->element, cur->leftChild, cur->rightChild);
			if (cur == root) root = temp; //若删除根节点
			else { //否则确定替换为左子树还是右子树
				if (cur == fp->leftChild) fp->leftChild = temp;
				else fp->rightChild = temp;
			}
			//删除Lmax节点
			if (Lfp == cur) fp = temp;
			else fp = Lfp;
			delete cur;
			cur = Lmax;
		}
		//cur节点有一个孩子或者没有
		TreeNode<K, E> *child = nullptr; //保存存在的孩子或空节点
		if (cur->leftChild) child = cur->leftChild;
		else child = cur->rightChild;
		if (cur == root) root = child;
		else {
			if (cur == fp->leftChild) fp->leftChild = child;
			else fp->rightChild = child;
		}
		delete cur;
	}
}

template <class K,class E>
void BinarySearchTree<K, E>::_output(TreeNode<K, E> *t, bool left, string const& indent)
{
	if (t->rightChild)
	{
		_output(t->rightChild, false, indent + (left ? "|     " : "      "));
	}
	cout << indent;
	cout << (left ? '\\' : '/');
	cout << "-----";
	cout << t->element.second << endl;
	if (t->leftChild)
	{
		_output(t->leftChild, true, indent + (left ? "      " : "|     "));
	}
}

#endif // !BinarySearchTree_H
