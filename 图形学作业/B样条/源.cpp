#include <iostream>
#include <gl/glut.h>
#include "graph.h"
#include <vector>
#include <list>
using namespace std;

const float Size = 20.0; //坐标尺寸
const int Length = 600; //窗口尺寸
const int Width = 600;
const float pre = 1e-6; //浮点数比较精度
float mouseX, mouseY;//鼠标此刻的坐标
bool modification = false;
bool insert = false;
bool Forward = false;
bool del = false;
bool leftButton = false;

int K = 2; //阶
vector<float> T; //非递减参数t序列
vector<Vertex> Control; //控制点
vector<Vertex> out; //样条点
Vertex **base;
vector<Vertex> *point;
Vertex a(-1, -1), b;

float Div(float a, float b)
{
	if (abs(b - 0) < pre) return 0;
	else return a / b;
}
void update()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	Fill(0, Size - 1);//清空按钮
	Vertex S, P;
	int num = Control.size();
	S = Control[0];
	DrawPoint(S);
	for (int i = 1; i < num; i++)
	{
		P = Control[i];
		DrawPoint(P);
		DrawLine(S, P);
		S = P;
	}
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i <= 1000; i++)
	{
		for (int j = 0; j < (int)point[i].size(); j++)
		{
			S = point[i][j];
			glPointSize(3);
			glBegin(GL_POINTS);
			glVertex2f(S.x, S.y);
			glEnd();
		}
	}
	glColor3f(1.0, 1.0, 1.0);
}
void P(float t)
{
	int r = 1;
	while (r <= K-1 )
	{
		for (int j = K - 1; j < (int)Control.size(); j++)
		{
			Vertex tmp;
			for (int i = j - K + r + 1; i <= j; i++)
			{	
				if (t < T[j] || t >= T[j + 1]) continue;
				tmp.x = Div(t - T[i], T[i + K - r] - T[i])*base[r - 1][i].x + Div(T[i + K - r] - t, T[i + K - r] - T[i])*base[r - 1][i - 1].x;
				tmp.y = Div(t - T[i], T[i + K - r] - T[i])*base[r - 1][i].y + Div(T[i + K - r] - t, T[i + K - r] - T[i])*base[r - 1][i - 1].y;
				base[r][i] = tmp;
			}
		}
		r++;
	}
	r--;
	for (int i = r; i < (int)Control.size(); i++)
	{
		point[(int)(t * 1000)].push_back(base[r][i]);
		//out.push_back(base[r][i]);
	}
}
void Cal()
{
	if ((int)Control.size() < K) K = (int)Control.size();
	//else if ((int)Control.size() == 4) K = 4;
	cout << "目前为" << K << "阶" << endl;

	float tmp = 1 / (float)(K + (int)Control.size());
	T.clear();
	float ti = 0;
	//for (int i = 1; i < K; i++) T.push_back(ti);
	for (int i = 0; i < (K + (int)Control.size()); i++)
	{
		T.push_back(ti);
		ti += tmp;
	}
	//for (int i = 1; i < K; i++) T.push_back(1);
	out.clear();
	base = new Vertex*[K];
	for (int i = 0; i < K; i++)
	{
		base[i] = new Vertex[(int)Control.size()];
	}
	for (int i = 0; i < (int)Control.size(); i++) base[0][i] = Control[i];
	point = new vector<Vertex>[1001];
	for (int i = 0;i <= 1000;i++)
	{
		P(i/1000.0);
	}
	update();
	glFlush();
	delete[]base;
	delete[]point;
}
void Clear()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	Fill(0, Size - 1);//清空按钮
	modification = false;
	insert = false;
	del = false;
	leftButton = false;
	Forward = false;
	glFlush();
	//out.clear();
	Control.clear();
	a.x = -1;
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
	glFlush();
}

void onKeyBoard(unsigned char button, int x, int y)
{
	if (button == 'm')
	{
		if (!modification) {
			modification = true;
			cout << "修改模式" << endl;
		}
		else {
			modification = false;
			cout << "退出修改模式" << endl;
		}
	}
	else if (button == 'i' && modification && !del)
	{
		if (!insert) {
			insert = true;
			cout << "插入控制点" << endl;
		}
		else {
			insert = false;
			cout << "结束插入" << endl;
		}
	}
	else if (button == 'd' && modification && !insert)
	{
		if (!del) {
			del = true;
			cout << "删除控制点" << endl;
		}
		else {
			cout << "结束删除" << endl;
			del = false;
		}
	}
	else if (button == '1' && modification && !del && !insert)
	{
		if (K < (int)Control.size()) {
			K++;
			cout << "阶次加一" << endl;
			Cal();
		}
		else cout << "最大阶次" << endl;
	}
	else if (button == '2' && modification && !del && !insert)
	{
		if (K > 2) {
			K--;
			cout << "阶次减一" << endl;
			Cal();
		}
		else {
			cout << "最小阶次" << endl;
		}
	}
	else if (button == 'q') exit(0);
}
void onMouse(int button, int state, int x, int y)
{
	mouseX = x / (Length / Size); //获取鼠标点击处的坐标
	mouseY = Size - (y / (Width / Size));
	mouseX = round(mouseX, 2);
	mouseY = round(mouseY, 2);
	if (!modification)//添加控制点
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			
			if (mouseX <= 1 && mouseY >= Size - 1)
			{
				Clear();
			}
			else if (a.x == -1) {
				a.x = mouseX, a.y = mouseY;
				Control.push_back(a);
				DrawPoint(a);
			}
			else {
				b.x = mouseX, b.y = mouseY;
				Control.push_back(b);
				DrawPoint(b);
				DrawLine(a, b);
				a = b;
				Cal();
			}
		}
	}
	else //修改模式
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			if (state == GLUT_DOWN)
			{
				leftButton = true;
				if (del && !insert) //删除控制点
				{
					vector<Vertex>::iterator iter = Control.begin();
					while (iter != Control.end())
					{
						if (abs(mouseX - iter->x) < 0.5 && abs(mouseY - iter->y) < 0.5)
						{
							iter = Control.erase(iter);
							Cal();
							break;
						}
						else iter++;
					}
				}
				if (!del && insert)
				{
					static int con = 0;
					if (!Forward)
					{
						for (int i = 0; i < (int)Control.size(); i++)
						{
							if (abs(Control[i].x - mouseX) < 0.5 && abs(Control[i].y - mouseY) < 0.5)
							{
								cout << "已确认前驱点" << endl;
								con = i;
								Forward = true;
								break;
							}
						}
					}
					else
					{
						Vertex tmp;
						tmp.x = mouseX, tmp.y = mouseY;
						Control.insert(Control.begin() + con + 1, tmp);
						Cal();
						Forward = false;
					}
				}
			}
			else if (state == GLUT_UP) leftButton = false;
		}	
	}
	glFlush();
}
void onMouseMove(int x, int y)
{
	mouseX = x / (Length / Size); //获取鼠标点击处的坐标
	mouseY = Size - (y / (Width / Size));
	mouseX = round(mouseX, 2);
	mouseY = round(mouseY, 2);
	if (leftButton && modification)
	{
		vector<Vertex>::iterator iter = Control.begin();
		while (iter != Control.end())
		{
			if (abs(mouseX - iter->x) < 0.5 && abs(iter->y - mouseY) < 0.5)
			{
				iter->x = mouseX;
				iter->y = mouseY;
				Cal();
				break;
			}
			else iter++;
		}
	}
}

int main()
{
	glutInitWindowSize(Length, Width);
	glutCreateWindow("rectangle");
	InitEnvironment();
	glutDisplayFunc(&display);
	glutMouseFunc(&onMouse);
	glutMotionFunc(&onMouseMove);
	glutKeyboardFunc(&onKeyBoard);
	glutMainLoop();
}