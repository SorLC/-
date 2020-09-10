#ifndef BinarySearchTree_H
#define BinarySearchTree_H
#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>
#include <string>
using namespace std;

template <class K,class E>
struct TreeNode //��ͨ�����������Ľڵ�ṹ
{
	pair<const K, E> element; //Ԫ����
	TreeNode<K, E> *leftChild, *rightChild;  //���Һ��ӵ�ָ��
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
	TreeNode<K, E> *root; //�����������ĸ��ڵ�
	static void levelOrder(TreeNode<K, E> *t, void(*visit)(TreeNode<K, E> *t));
	static void PostOrder(TreeNode<K, E> *t, void(*visit)(TreeNode<K, E> *t));
	static void outPut(TreeNode<K, E> *t);  //���һ���ڵ������
	static void release(TreeNode<K, E> *t); //�ͷ�һ���ڵ������
	static int height(TreeNode<K, E> *t); //������tΪ�������ĸ߶�
	static void _output(TreeNode<K, E> *t, bool left, string const& indent);
public:
	BinarySearchTree() { root = nullptr; }
	~BinarySearchTree()
	{
		erase_all();
	}
	void level_output(); //�������
	pair<const K, E>* find(const K theKey); //�ҵ�ָ���ؼ��ֵ����� 
	void insert(pair<const K, E> thePair);  //����������
	void erase(const K theKey); //ɾ��ָ���ؼ��ֵ�����
	void erase_all(); //�����
	int height() { return height(root); } //���ظ����ĸ߶�
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
	cout << t->element.first << "��" << t->element.second << " ";
}
template <class K,class E>
void BinarySearchTree<K, E>::release(TreeNode<K, E>*t)
{
	delete t;
}
template <class K,class E>
int BinarySearchTree<K, E>::height(TreeNode<K, E>*t) //������tΪ�������ĸ߶�
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
void BinarySearchTree<K, E>::level_output() //�������
{
	levelOrder(root, outPut);
	cout << endl;
}
template <class K, class E>
void BinarySearchTree<K, E>::erase_all() //���
{
	PostOrder(root, release);
}
template <class K,class E>
pair<const K, E>* BinarySearchTree<K, E>::find(const K theKey)
{
	TreeNode<K, E>* cur = root;
	while (cur != nullptr) //�Ӹ��ڵ㿪ʼ������������
	{
		if (cur->element.first == theKey) break;
		else if (theKey < cur->element.first) cur = cur->leftChild;
		else cur = cur->rightChild;
	}
	pair<const K, E> *ans = nullptr; 
	if (cur != nullptr) ans = cur->element; //��δ�ҵ������ؿ�ָ�룻���򷵻�ָ�����Ե�ָ��
	return ans;
}

template <class K,class E>
void BinarySearchTree<K, E>::insert(pair<const K, E> thePair) 
{  //���������ԣ����ؼ����Ѵ��ڣ��򸲸Ǿ�ֵ
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
	//��Ҷ�ڵ������ֵ
	TreeNode<K, E>* newNode = new TreeNode<K, E>(thePair);
	if (cur == root) root = newNode; //��Ϊ���ڵ㣬ֱ�Ӳ���
	else { //�����ж�����
		if (thePair.first < fp->element.first) fp->leftChild = newNode;
		else fp->rightChild = newNode;
	}
}

template <class K,class E>
void BinarySearchTree<K, E>::erase(const K theKey) //ɾ��ָ���ؼ��ֵ�����
{
	TreeNode<K, E>* cur = root;
	TreeNode<K, E>*fp = nullptr;
	while (cur != nullptr && cur->element.first != theKey)
	{ //�ҵ�Ҫɾ���Ľڵ㼰�丸�ڵ�
		fp = cur;
		if (theKey < cur->element.first) cur = cur->leftChild;
		else cur = cur->rightChild;
	}
	if (cur == nullptr) {
		cout << "û�д˹ؼ���" << endl;
		return;
	}
	else {
		if (cur->leftChild && cur->rightChild) //���˽ڵ�����������
		{//�ҵ��������������Ľڵ㣬���汻ɾ���Ľڵ�
			TreeNode<K, E> *Lmax = cur->leftChild,
				*Lfp = cur;
			while (Lmax->rightChild != nullptr) Lfp = Lmax, Lmax = Lmax->rightChild;
			TreeNode<K, E>* temp = new TreeNode<K, E>(Lmax->element, cur->leftChild, cur->rightChild);
			if (cur == root) root = temp; //��ɾ�����ڵ�
			else { //����ȷ���滻Ϊ����������������
				if (cur == fp->leftChild) fp->leftChild = temp;
				else fp->rightChild = temp;
			}
			//ɾ��Lmax�ڵ�
			if (Lfp == cur) fp = temp;
			else fp = Lfp;
			delete cur;
			cur = Lmax;
		}
		//cur�ڵ���һ�����ӻ���û��
		TreeNode<K, E> *child = nullptr; //������ڵĺ��ӻ�սڵ�
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
