#include <gl/glut.h>
#include <iostream>
#include <math.h>
#include <queue>
#include <list>
#include "grid.h"
using namespace std;

const float Size = 20.0; //坐标尺寸
const int Length = 600; //窗口尺寸
const int Width = 600;
const float pre = 1e-6;

Vertex a(-1,-1), b;
Polygon pol;
struct AET_
{
	float x, Dx, Ymax;
	bool operator < (const AET_ a)
	{
		return x < a.x;
	}
	AET_(float x_,float Dx_,float Ymax_):x(x_),Dx(Dx_),Ymax(Ymax_) {}
};
list<AET_> AET;
list<AET_> *NET;
list<Edge> E;
void Scaning_Line(float min, float max)
{
	E.clear();
	int size = (int)((max - min) * 10) + 1; //扫描线条数
	NET = new list<AET_>[size];//各扫描线的新边表
	Polygon::Myiterator *iter = pol.iterator();
	Edge temp;
	while ((temp = iter->next()).a != temp.b)
	{//取得多边形所有边，剔除平行于扫面线的边
		temp.swap();
		if (temp.a.y != temp.b.y) E.push_back(temp);
	}
	for (int i = 0; i < size; i++) //为每一条扫描线建立新边表
	{//扫描线每次增加0.1
		float temp = (float)i / 10 + min;
		list<Edge>::iterator iter = E.begin();
		while (iter != E.end())
		{
			if (abs(iter->a.y - temp) < pre)
			{
				float a = iter->a.x;
				float b = (iter->a.x - iter->b.x) / (iter->a.y - iter->b.y);
				float c = iter->b.y;
				NET[i].push_back(AET_(a, b, c));
				//cout << iter->a.x << "," << iter->a.y << "||" << iter->b.x << "," << iter->b.y << endl;
				iter = E.erase(iter);//删除已加入NET的边					
			}
			else iter++;
		}
		if (E.empty()) break;
	}
	AET.clear(); //初始化活性边表头
	for (int i = 0; i < size; i++)//遍历每一条扫描线
	{   
		list<AET_>::iterator iter = AET.begin();
		while (iter != AET.end())
		{
			//cout << AET.size() << endl;
			if (abs(iter->Ymax - (((float)i / 10) + min)) <= pre)
			{//删除到顶的边
				iter = AET.erase(iter);
			}
			else {
				iter->x += iter->Dx / 10;
				iter++;
			}
		}
	    iter = NET[i].begin();
		while (iter != NET[i].end())//遍历当前扫描线NET并将其中元素插入AET
		{ 
			AET_ temp(iter->x, iter->Dx, iter->Ymax);
			AET.push_back(temp);
			iter++;
		}
		//cout << i << endl;
		//对AET排序
		AET.sort();
		iter = AET.begin();
		//cout << AET.size() << endl;
		while (iter != AET.end())
		{
			float x1 = iter->x;
			iter++;
			float x2 = iter->x;
			iter++;
			DrawLine(Vertex(x1, ((float)i / 10) + min), Vertex(x2, ((float)i / 10) + min));
		}
		glFlush();
	}
	pol.clear();
	delete[]NET;
}
void InitEnvironment() //初始化绘图窗口
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0.0, Size, 0.0, Size);
	glColor3f(1.0, 1.0, 1.0);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Fill(0, Size - 1);//清空按钮
	glColor3f(1.0, 0.0, 0.0);
	Fill(0, Size - 2);
	glColor3f(0.0, 1.0, 0.0);
	Fill(0, Size - 3);
	glColor3f(0.0, 0.0, 1.0);
	Fill(0, Size - 4);
	glColor3f(1.0, 1.0, 1.0);
	glFlush();
}
void onMouse(int button, int state, int x, int y)//鼠标点击事件
{
	static bool flag = false;
	static Vertex first; //静态存储第一个点
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		b.x = x / (Length / Size); //获取鼠标点击处的坐标
		b.y = Size - (y / (Width /Size ));
		b.x = round(b.x, 1); //将坐标点精确于一位小数
		b.y = round(b.y, 1);
		//cout << b.x << " " << b.y << endl;
		if (b.x <= 1 && b.y >= Size - 4 && b.y <= Size - 1)//更改颜色
		{
			if (b.y <= Size - 3) glColor3f(0.0, 0.0, 1.0);
			else if (b.y <= Size - 2) glColor3f(0.0, 1.0, 0.0);
			else if (b.y <= Size - 1) glColor3f(1.0, 0.0, 0.0);
		}
		else if (b.x <= 1 && b.y >= Size - 1) //清空
		{
			glClearColor(0.0, 0.0, 0.0, 0.0);
			glColor3f(1.0, 1.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);
			Fill(0, Size - 1);//清空按钮
			glColor3f(1.0, 0.0, 0.0);
			Fill(0, Size - 2);
			glColor3f(0.0, 1.0, 0.0);
			Fill(0, Size - 3);
			glColor3f(0.0, 0.0, 1.0);
			Fill(0, Size - 4);
			glColor3f(1.0, 1.0, 1.0);
			glFlush();
			flag = false;
			a.x = -1, a.y = -1;
		}
		else if(!flag) //画多边形
		{
			if (a.x == -1) //第一个点
			{
				a = b;
				first = b;
				DrawPoint(a);
				pol.insert(a);			
			}
			else if (a.x == b.x && a.y == b.y)
			{}//忽略重复点
			else {
				if (abs(first.x - b.x) <= 0.4 && abs(first.y - b.y) <= 0.4)
				{//确定终点
					DrawLine(a, first);
					flag = true;
					a.x = -1, a.y = -1;
				}
				else {//正常边
					DrawLine(a, b);
					pol.insert(b);
					a = b;
				}
			}
		}
		else if (flag) //开始扫描线填充
		{
			Scaning_Line(pol.get_min().y, pol.get_max().y);
			flag = false;
		}
	}
	glFlush();
}

int main()
{
	glutInitWindowSize(Length, Width);
	glutCreateWindow("Scaning_Line");
	InitEnvironment();
	glutDisplayFunc(&display);
	glutMouseFunc(&onMouse);
	glutMainLoop();
}