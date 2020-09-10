#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int a, b, c;
int gcd(int a, int b) //���a��b�����Լ��
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
	"װ��AͰ",
	"װ��BͰ",
	"���AͰ",
	"���BͰ",
	"AͰˮ����BͰ",
	"BͰˮ����AͰ",
	"�ó����"
};
int main()
{
	bool flag = false;
	while (!flag)
	{
		cout << "��������ͰA��B�������Ŀ�����C��";
		cin >> a >> b >> c;
		if (a <= 0 || b <= 0 || c <= 0) {
			cout << "��������ӦΪ������" << endl;
		}
		else if (c > a && c > b) {
			cout << "Ŀ�����Ӧ��С��Ͱ���" << endl;
		}
		else {
			flag = true;
		}
	}
	vector<string> ans;
	int cur_A = 0, cur_B = 0;//��ǰͰ�ڵ�ˮ
	if (c % gcd(a, b) == 0)
	{
		char temp[30];
		while (true) {
			if (cur_A == c) break;
			if (cur_A == 0)//AͰ����װ��ˮ
			{
				cur_A = a;
				sprintf(temp, "   A:%d, B:%d\n", cur_A, cur_B);
				ans.push_back(Move[0]+temp);
			}
			else 
			{
				if (cur_A > (b - cur_B)) //AͰ����BͰ��ʣ��
				{
					if (cur_B == b)//BͰ����,�����BͰ
					{
						cur_B = 0;
						sprintf(temp, "   A:%d, B:%d\n", cur_A, cur_B);
						ans.push_back(Move[3] + temp);
					}
					else { //A����BͰ��BͰ����AͰ��ʣ��
						int rest_B = b - cur_B;
						cur_A -= rest_B;
						cur_B = b;
						sprintf(temp, "   A:%d, B:%d\n", cur_A, cur_B);
						ans.push_back(Move[4] + temp);
					}
				}
				else {//AͰ����ȫ������BͰ
					cur_B += cur_A;
					cur_A = 0;
					sprintf(temp, "   A:%d, B:%d\n", cur_A, cur_B);
					ans.push_back(Move[4] + temp);
				}
			}
		}
	}
	else {
		cout << "�޽�" << endl;
	}
	vector<string>::iterator iter = ans.begin();
	while (iter != ans.end())
	{
		cout << *iter;
		iter++;
	}
}