#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int a, b, c;
int gcd(int a, int b) //求解a、b的最大公约数
{
	if (a > b) swap(a, b);
	while (a != 0) {
		int temp = b % a;
		b = a;
		a = temp;
	}
	return b;
}
const string Move[] = {
	"装满A桶",
	"装满B桶",
	"清空A桶",
	"清空B桶",
	"A桶水倒入B桶",
	"B桶水倒入A桶",
	"得出结果"
};
int main()
{
	bool flag = false;
	while (!flag)
	{
		cout << "输入两个桶A、B的体积和目标体积C：";
		cin >> a >> b >> c;
		if (a <= 0 || b <= 0 || c <= 0) {
			cout << "输入的体积应为正整数" << endl;
		}
		else if (c > a && c > b) {
			cout << "目标体积应该小于桶体积" << endl;
		}
		else {
			flag = true;
		}
	}
	vector<string> ans;
	int cur_A = 0, cur_B = 0;//当前桶内的水
	if (c % gcd(a, b) == 0)
	{
		char temp[30];
		while (true) {
			if (cur_A == c) break;
			if (cur_A == 0)//A桶空则装满水
			{
				cur_A = a;
				sprintf(temp, "   A:%d, B:%d\n", cur_A, cur_B);
				ans.push_back(Move[0]+temp);
			}
			else 
			{
				if (cur_A > (b - cur_B)) //A桶倒入B桶有剩余
				{
					if (cur_B == b)//B桶满了,则清空B桶
					{
						cur_B = 0;
						sprintf(temp, "   A:%d, B:%d\n", cur_A, cur_B);
						ans.push_back(Move[3] + temp);
					}
					else { //A倒入B桶，B桶满，A桶有剩余
						int rest_B = b - cur_B;
						cur_A -= rest_B;
						cur_B = b;
						sprintf(temp, "   A:%d, B:%d\n", cur_A, cur_B);
						ans.push_back(Move[4] + temp);
					}
				}
				else {//A桶可以全部倒入B桶
					cur_B += cur_A;
					cur_A = 0;
					sprintf(temp, "   A:%d, B:%d\n", cur_A, cur_B);
					ans.push_back(Move[4] + temp);
				}
			}
		}
	}
	else {
		cout << "无解" << endl;
	}
	vector<string>::iterator iter = ans.begin();
	while (iter != ans.end())
	{
		cout << *iter;
		iter++;
	}
}