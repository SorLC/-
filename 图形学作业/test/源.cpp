#include <iostream>
#include <set>
using namespace std;

struct point
{
	int x, y;
	point(int _x, int _y):x(_x),y(_y)
	{}
	bool operator < (point &b) const
	{
		if (x == b.x)
		{
			return y < b.y;
		}
		return x < b.x;
	}
};
set<point> Myset;
int main()
{
	Myset.insert(1,2);
	Myset.insert(2,3);
	set<point> ::iterator iter = Myset.begin();
	while (iter != Myset.end())
	{
		cout << (point*)(*iter).x << endl;
	}
}