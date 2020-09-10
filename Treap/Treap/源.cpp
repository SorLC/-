#include <iostream>
#include <time.h>
#include "Treap.h"
#include "BinarySearchTree.h"
using namespace std;

int RandInt(int i, int j) //随机生成i,j之间的一个数
{
	return rand() % (j - i + 1) + i;
}

void swap(int &a, int &b) //交换
{
	int temp = a;
	a = b;
	b = temp;
}
void Rand_sort(int *a,int n) //随机排序
{
	for (int i = 1; i < n; i++)
	{
		swap(a[i], a[RandInt(0, i)]);
	}
}
int main()
{
	clock_t start, finish;
	int n;
	cout << "普通搜索树" << '\t' <<'\t' << "随机搜索树" << '\t' <<'\t'<< "Treap" << endl;
	while (cin >> n)
	{
		srand((int)time(0));
		double H_Src[10], H_Rand[10], H_Treap[10];
		double T_Src[10], T_Rand[10], T_Treap[10];
		for (int i = 0; i < 10; i++)
		{
			Treap<int, int> _treap;
			BinarySearchTree<int, int> _search;
			BinarySearchTree<int, int> Rand_search;
			pair<int, int> temp;
			int *test = new int[n];
			for (int i = 0; i < n; i++)
			{
				test[i] = rand();
			}
			//普通搜索树插入
			start = clock();
			for (int i = 0; i < n; i++)
			{
				temp.first = temp.second = test[i];
				_search.insert(temp);
			}
			finish = clock();
			T_Src[i] = (double)(finish - start) / CLOCKS_PER_SEC;
			//Treap插入
			start = clock();
			for (int i = 0; i < n; i++)
			{
				temp.first = temp.second = test[i];
				_treap.insert(temp);
			}
			finish = clock();
			T_Treap[i] = (double)(finish - start) / CLOCKS_PER_SEC;
			//Rand_Src插入		
			start = clock();
			Rand_sort(test, n);
			for (int i = 0; i < n; i++)
			{
				temp.first = temp.second = test[i];
				Rand_search.insert(temp);
			}
			finish = clock();
			//统计
			T_Rand[i] = (double)(finish - start) / CLOCKS_PER_SEC;
			H_Src[i] = (double)_search.height();
			H_Treap[i] = (double)_treap.height();
			H_Rand[i] = (double)Rand_search.height();
			delete[]test;
		}
		pair<double, double> theSrc(0,0), theTreap(0,0), theRand(0,0);
		for (int i = 0; i < 10; i++)
		{
			theSrc.first += H_Src[i];
			theSrc.second += T_Src[i];
			theTreap.first += H_Treap[i];
			theTreap.second += T_Treap[i];
			theRand.first += H_Rand[i];
			theRand.second += T_Rand[i];
		}
		cout << (double)theSrc.first / 10 << " " << theSrc.second / 10 << "(s)" << '\t' <<'\t'<< (double)theRand.first / 10 << " " << theRand.second / 10 << "(s)" << '\t' <<'\t'<< (double)theTreap.first / 10 << " " << theTreap.second / 10 << "(s)" << endl;
	}
	return 0;
}