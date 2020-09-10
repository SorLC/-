#ifndef TREAP_H
#define TREAP_H

#include<iostream>
#include <stack>
#include <queue>
#include <time.h>
#include <string>
using namespace std;

template <class K, class E>
struct TreapNode  //����������Treap�ṹ�Ľڵ�
{
	pair<const K, E> value;  //Ԫ��
	TreapNode<K, E> *leftChild, *rightChild; //���Һ���ָ��
	int priority; //����������ȼ�
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
class Treap  //treap�ṹ
{
private:
	TreapNode<K, E> *root;
	static void levelOrder(TreapNode<K, E>*, void(*visit)(TreapNode<K, E> *) = output); //��α����ڵ�
	static void postOrder(TreapNode<K, E>*, void(*visit)(TreapNode<K, E> *) = output); //�������
	static void output(TreapNode<K, E> *t); //����ڵ�t��ֵ
	static int heightOnT(TreapNode<K, E>*t); //������tΪ�������ĸ߶�
	static void release(TreapNode<K, E>*t) { delete t; } //�ͷŽڵ�t
	static void _output(TreapNode<K, E> *t, bool left, string const& indent); //ͼ�λ�����ṹ
public:
	Treap() { 
		root = nullptr;
	}
	~Treap()
	{
		erase_all();
	}
	void level_output(); //������
	void erase_all() { postOrder(root, release); }
	pair<const K, E> find(const K theKey); //����ָ��ָ���ؼ��ֵ����Ե�ָ�룬���ޣ��򷵻ؿ�ָ��
	void insert(pair<const K, E> thePair); //��������
	void erase(const K ); //ɾ��ָ���ؼ��ֵ�����
	int height(); //�������ĸ߶�
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
	queue<TreapNode<K, E>* > p; //������нڵ�
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
void Treap<K, E>::output(TreapNode<K, E> *t)  //����ڵ������
{ 
	cout << t->value.second << "(" << t->priority << ")" << " ";
}

template <class K, class E>
int Treap<K, E>::heightOnT(TreapNode<K, E>*t) //����ָ���ڵ�Ϊ�������ĸ߶� 
{
	if (t == nullptr) return 0;
	else {
		int hl = heightOnT(t->leftChild);
		int hr = heightOnT(t->rightChild);
		return hl > hr ? hl + 1 : hr + 1;
	}
}

template <class K, class E> //�������ĸ߶�
int Treap<K, E>::height() { return heightOnT(root); }

template <class K, class E>
void Treap<K, E>::level_output() //������
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
{//�������ԣ����ؼ����Ѿ����ڣ��򸲸Ǿ�ֵ
	TreapNode<K, E> *cur = root;
	TreapNode<K, E> *fp = nullptr;
	stack<TreapNode<K, E>* > f;
	while (cur != nullptr) //���ؼ��ֱ������������ҵ��½ڵ�Ӧ�����λ��
	{
		fp = cur; //����cur�ĸ��ڵ�
		f.push(fp); //��¼���и��ڵ�
		if (cur->value.first > thePair.first) { //���˽ڵ�ؼ���С�ڴ�����ڵ㣬����������
			cur = cur->leftChild;
		}
		else if (cur->value.first < thePair.first) { //���ؼ��ִ��ڴ�����ڵ㣬�������Һ���
			cur = cur->rightChild;
		}
		else { //�����ڴ�����ڵ�ؼ��֣��򸲸Ǿ�ֵ
			cur->value.second = thePair.second;
			break;
		}
	}
	TreapNode<K, E> *newNode = new TreapNode<K, E>(thePair);
	//output(newNode);
	if (root == NULL) //����Ϊ�գ���ֱ�ӽ��ڸ���,������
	{
		root = newNode;
		return;
	}
	else { //����Ϊ�գ��ҵ�Ӧ�������ӻ����Һ���
		if (newNode->value.first < fp->value.first)
		{
			fp->leftChild = newNode;
		}
		else fp->rightChild = newNode;
	}
	//�������ȼ������ṹ
	cur = newNode;
	fp = f.top();
	f.pop();
	while (cur != root && cur->priority > fp->priority)
	{
		if (cur == fp->leftChild) //��curΪfp�����ӣ�������
		{
			TreapNode<K, E> *ffp = nullptr;
			TreapNode<K, E> *temp = cur->rightChild; //cur���Һ������ӵ�fp���Һ��ӣ�fp��Ϊcur���Һ���
			fp->leftChild = temp;
			cur->rightChild = fp;
			if (f.empty()) //��cur�ĸ��ڵ�Ϊ���ڵ�
			{
				root = cur;
			}
			else {
				ffp = f.top(); //��cur�ӵ�ԭ��fp��λ��
				f.pop();
				if (fp == ffp->leftChild) {
					ffp->leftChild = cur;
				}
				else ffp->rightChild = cur;
			}
			fp = ffp;
		}
		else //curΪfp���Һ��ӣ�������
		{
			TreapNode<K, E> *ffp = nullptr;
			TreapNode<K, E> *temp = cur->leftChild;
			fp->rightChild = temp;
			cur->leftChild = fp;
			if (f.empty()) //��cur�ĸ��ڵ�Ϊ���ڵ�
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
void Treap<K, E>::erase(const K theKey) //ɾ��ָ���ؼ��ֵ�����
{
	TreapNode<K, E>* cur = root; //�Ӹ��ڵ㿪ʼ�ҵ�Ҫɾ���Ľڵ�
	TreapNode<K, E>* fp;
	while (cur != nullptr && cur->value.first != theKey)
	{
		fp = cur; //����cur�ĸ��ڵ�
		if (theKey < cur->value.first) cur = cur->leftChild;
		else cur = cur->rightChild;
	}
	if (cur == nullptr) //�������ڣ������
	{
		//cout << "�����ڴ˹ؼ��ֵ�����" << endl;
		return;
	}
	//��Ҫɾ����cur�ڵ���ת��Ҷ�ڵ�
	TreapNode<K, E>* left = cur->leftChild;
	TreapNode<K, E>* right = cur->rightChild;
	while (left != nullptr || right != nullptr) //ֻҪ���ں��ӣ��ͽ�����ת����
	{
		if (left == nullptr) {//������Ϊ��,����Һ�������
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
		else if (right == nullptr) {//���Һ���Ϊ��
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
		else //���������Ӿ���Ϊ��
		{
			int R = right->priority, L = left->priority;
			//�����ȼ���ĺ�������
			if (L > R) { //��������
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
			else { //�Һ�������
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
