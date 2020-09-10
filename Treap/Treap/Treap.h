#ifndef TREAP_H
#define TREAP_H

#include<iostream>
#include <stack>
#include <queue>
#include <time.h>
#include <string>
using namespace std;

template <class K, class E>
struct TreapNode  //声明并定义Treap结构的节点
{
	pair<const K, E> value;  //元素
	TreapNode<K, E> *leftChild, *rightChild; //左右孩子指针
	int priority; //随机分配优先级
	TreapNode(pair<const K, E> thePair);
	TreapNode(pair<const K, E> thePair, TreapNode<K, E> *theLeft, TreapNode<K, E> *theRight);
};
template <class K, class E>
TreapNode<K, E>::TreapNode(pair<const K, E> thePair) :value(thePair)
{
	leftChild = rightChild = nullptr;
	priority = rand();
}
template <class K, class E>
TreapNode<K, E>::TreapNode(pair<const K, E> thePair, TreapNode<K, E> *theLeft, TreapNode<K, E> *theRight) :value(thePair)
{
	leftChild = theLeft;
	rightChild = theRight;
	priority = rand();
}

template <class K, class E>
class Treap  //treap结构
{
private:
	TreapNode<K, E> *root;
	static void levelOrder(TreapNode<K, E>*, void(*visit)(TreapNode<K, E> *) = output); //层次遍历节点
	static void postOrder(TreapNode<K, E>*, void(*visit)(TreapNode<K, E> *) = output); //后序遍历
	static void output(TreapNode<K, E> *t); //输出节点t的值
	static int heightOnT(TreapNode<K, E>*t); //计算以t为根的树的高度
	static void release(TreapNode<K, E>*t) { delete t; } //释放节点t
	static void _output(TreapNode<K, E> *t, bool left, string const& indent); //图形化输出结构
public:
	Treap() { 
		root = nullptr;
	}
	~Treap()
	{
		erase_all();
	}
	void level_output(); //层次输出
	void erase_all() { postOrder(root, release); }
	pair<const K, E> find(const K theKey); //返回指向指定关键字的数对的指针，若无，则返回空指针
	void insert(pair<const K, E> thePair); //插入数对
	void erase(const K ); //删除指定关键字的数对
	int height(); //返回树的高度
	void _output()
	{
		if (root->rightChild)
		{
			_output(root->rightChild, false, "");
		}
		cout << root->value.second << endl;
		if (root->leftChild)
		{
			_output(root->leftChild, true, "");
		}
	}
};

template <class K, class E>
void Treap<K, E>::levelOrder(TreapNode<K, E>*t, void(*visit)(TreapNode<K, E> *))
{
	queue<TreapNode<K, E>* > p; //存放所有节点
	while (t != nullptr)
	{
		visit(t);
		if (t->leftChild != nullptr) p.push(t->leftChild);
		if (t->rightChild != nullptr) p.push(t->rightChild);
		if (!p.empty())
		{
			t = p.front();
			p.pop();
		}
		else break;
	}
}

template <class K, class E>
void Treap<K, E>::postOrder(TreapNode<K, E>* t, void(*visit)(TreapNode<K, E> *))
{
	if (t != nullptr)
	{
		postOrder(t->leftChild, visit);
		postOrder(t->rightChild, visit);
		visit(t);
	}
}
template <class K, class E>
void Treap<K, E>::output(TreapNode<K, E> *t)  //输出节点的内容
{ 
	cout << t->value.second << "(" << t->priority << ")" << " ";
}

template <class K, class E>
int Treap<K, E>::heightOnT(TreapNode<K, E>*t) //计算指定节点为根的树的高度 
{
	if (t == nullptr) return 0;
	else {
		int hl = heightOnT(t->leftChild);
		int hr = heightOnT(t->rightChild);
		return hl > hr ? hl + 1 : hr + 1;
	}
}

template <class K, class E> //计算树的高度
int Treap<K, E>::height() { return heightOnT(root); }

template <class K, class E>
void Treap<K, E>::level_output() //层次输出
{
	levelOrder(root, output);
	cout << endl;
}

template <class K, class E>
void Treap<K, E>::_output(TreapNode<K, E> *t, bool left, string const& indent)
{
	if (t->rightChild)
	{
		_output(t->rightChild, false, indent + (left ? "|     " : "      "));
	}
	cout << indent;
	cout << (left ? '\\' : '/');
	cout << "-----";
	cout << t->value.second << endl;
	if (t->leftChild)
	{
		_output(t->leftChild, true, indent + (left ? "      " : "|     "));
	}
}

template <class K, class E>
pair<const K,E> Treap<K, E>::find(const K theKey)
{
	TreapNode<K, E>* cur = root;
	while (cur != nullptr && cur->value.first != theKey)
	{
		if (theKey < cur->value.first) cur = cur->leftChild;
		else cur = cur->rightChild;
	}
	return cur->value;
}
template <class K, class E>
void Treap<K, E>::insert(pair<const K, E> thePair)
{//插入数对，若关键字已经存在，则覆盖旧值
	TreapNode<K, E> *cur = root;
	TreapNode<K, E> *fp = nullptr;
	stack<TreapNode<K, E>* > f;
	while (cur != nullptr) //按关键字遍历二叉树，找到新节点应插入的位置
	{
		fp = cur; //保存cur的父节点
		f.push(fp); //记录所有父节点
		if (cur->value.first > thePair.first) { //若此节点关键字小于待插入节点，则移至左孩子
			cur = cur->leftChild;
		}
		else if (cur->value.first < thePair.first) { //若关键字大于待插入节点，则移至右孩子
			cur = cur->rightChild;
		}
		else { //若等于待插入节点关键字，则覆盖旧值
			cur->value.second = thePair.second;
			break;
		}
	}
	TreapNode<K, E> *newNode = new TreapNode<K, E>(thePair);
	//output(newNode);
	if (root == NULL) //若根为空，则直接接在根上,并结束
	{
		root = newNode;
		return;
	}
	else { //根不为空，找到应插入左孩子还是右孩子
		if (newNode->value.first < fp->value.first)
		{
			fp->leftChild = newNode;
		}
		else fp->rightChild = newNode;
	}
	//依照优先级调整结构
	cur = newNode;
	fp = f.top();
	f.pop();
	while (cur != root && cur->priority > fp->priority)
	{
		if (cur == fp->leftChild) //若cur为fp的左孩子，则右旋
		{
			TreapNode<K, E> *ffp = nullptr;
			TreapNode<K, E> *temp = cur->rightChild; //cur的右孩子连接到fp的右孩子，fp变为cur的右孩子
			fp->leftChild = temp;
			cur->rightChild = fp;
			if (f.empty()) //若cur的父节点为根节点
			{
				root = cur;
			}
			else {
				ffp = f.top(); //将cur接到原来fp的位置
				f.pop();
				if (fp == ffp->leftChild) {
					ffp->leftChild = cur;
				}
				else ffp->rightChild = cur;
			}
			fp = ffp;
		}
		else //cur为fp的右孩子，则左旋
		{
			TreapNode<K, E> *ffp = nullptr;
			TreapNode<K, E> *temp = cur->leftChild;
			fp->rightChild = temp;
			cur->leftChild = fp;
			if (f.empty()) //若cur的父节点为根节点
			{
				root = cur;
			}
			else {
				ffp = f.top();
				f.pop();
				if (fp == ffp->leftChild) {
					ffp->leftChild = cur;
				}
				else ffp->rightChild = cur;
			}
			fp = ffp;
		}
	}
}

template <class K,class E>
void Treap<K, E>::erase(const K theKey) //删除指定关键字的数对
{
	TreapNode<K, E>* cur = root; //从根节点开始找到要删除的节点
	TreapNode<K, E>* fp;
	while (cur != nullptr && cur->value.first != theKey)
	{
		fp = cur; //保存cur的父节点
		if (theKey < cur->value.first) cur = cur->leftChild;
		else cur = cur->rightChild;
	}
	if (cur == nullptr) //若不存在，则结束
	{
		//cout << "不存在此关键字的数对" << endl;
		return;
	}
	//把要删除的cur节点旋转至叶节点
	TreapNode<K, E>* left = cur->leftChild;
	TreapNode<K, E>* right = cur->rightChild;
	while (left != nullptr || right != nullptr) //只要存在孩子，就进行旋转操作
	{
		if (left == nullptr) {//若左孩子为空,则把右孩子左旋
			TreapNode<K, E> *temp = right->leftChild;
			if (cur == root) {
				root = right;
			}
			else {
				if (cur == fp->leftChild) fp->leftChild = right;
				else fp->rightChild = right;
			}
			right->leftChild = cur;
			cur->rightChild = temp;
			fp = right;
		}
		else if (right == nullptr) {//若右孩子为空
			TreapNode<K, E> *temp = left->rightChild;
			if (cur == root) {
				root = left;
			}
			else {
				if (cur == fp->leftChild) fp->leftChild = left;
				else fp->rightChild = left;
			}
			left->rightChild = cur;
			cur->leftChild = temp;
			fp = left;
		}
		else //若两个孩子均不为空
		{
			int R = right->priority, L = left->priority;
			//将优先级大的孩子上旋
			if (L > R) { //左孩子上旋
				TreapNode<K, E> *temp = left->rightChild;
				if (cur == root) {
					root = left;
				}
				else {
					if (fp->leftChild == cur) fp->leftChild = left;
					else fp->rightChild = left;
				}
				left->rightChild = cur;
				cur->leftChild = temp;
				fp = left;
			}
			else { //右孩子上旋
				TreapNode<K, E> *temp = right->leftChild;
				if (cur == root) {
					root = right;
				}
				else {
					if (fp->leftChild == cur) fp->leftChild = right;
					else fp->rightChild = right;
				}
				right->leftChild = cur;
				cur->rightChild = temp;
				fp = right;
			}
		}
		left = cur->leftChild;
		right = cur->rightChild;
	}
	if (cur == root) { root = nullptr; }
	else {
		if (cur == fp->leftChild) fp->leftChild = nullptr;
		else fp->rightChild = nullptr;
	}
	delete cur;
}


#endif // !TREAP_H
