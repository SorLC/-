#include <iostream>
#include <list>
#include <gl/glut.h>
#include "graph.h"
using namespace std;

const float Size = 20.0; //坐标尺寸
const int Length = 600; //窗口尺寸
const int Width = 600;
const float pre = 1e-6; //浮点数比较精度
float mouseX, mouseY;//鼠标此刻的坐标
bool modification = false;//修改模式
bool leftButton = false;
bool rightButton = false;

const int XL = 5, XR = 15, YD = 5, YU = 15;//裁剪边框
Vertex a(-1, -1), b;
bool flag = false;
list<Edge> All_edge;

bool Clip(float p, float q, float *u1, float *u2) // up <= q
{
	float r;
	if (p < 0) 
	{
		r = q / p;
		if (r > *u2) return false;
		if (r > *u1) *u1 = r;
	}
	else if (p > 0)
	{
		r = q / p;
		if (r < *u1) return false;
		if (r < *u2) *u2 = r;
		else return (q >= 0);
		return true;
	}
	else return(q >= 0);
	return true;
}
void CutLine()
{
	float dx, dy, u1, u2;
	u1 = 0, u2 = 1;
	dx = b.x - a.x;
	dy = b.y - a.y;
	if (Clip(-dx, a.x - XL, &u1, &u2)) {
		if (Clip(dx, XR - a.x, &u1, &u2)) {
			if (Clip(-dy, a.y - YD, &u1, &u2)) {
				if (Clip(dy, YU - a.y, &u1, &u2)) {
					DrawLine(Vertex(a.x + u1 * dx, a.y + u1 * dy), Vertex(a.x + u2 * dx, a.y + u2 * dy));
				}
			}
		}
	}
}
void InitEnvironment() //初始化绘图窗口
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0.0, Size, 0.0, Size);
	glColor3f(1.0, 1.0, 1.0);
}
void Draw_frame()
{
	Edge L, R, D, U;
	L.a.x = L.b.x = XL, L.a.y = YD, L.b.y = YU;
	R.a.x = R.b.x = XR, R.a.y = YD, R.b.y = YU;
	D.a.x = XL, D.b.x = XR, D.a.y = D.b.y = YD;
	U.a.x = XL, U.b.x = XR, U.a.y = U.b.y = YU;
	DrawLine(L.a, L.b);
	DrawLine(R.a, R.b);
	DrawLine(D.a, D.b);
	DrawLine(U.a, U.b);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Fill(0, Size - 1);//清空按钮
	glColor3f(1.0, 1.0, 1.0);
	//矩形裁剪边框
	Draw_frame();
	glFlush();
}
void update()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	display();
	list<Edge>::iterator iter = All_edge.begin();
	while (iter != All_edge.end())
	{
		a = iter->a, b = iter->b;
		DrawPoint(a), DrawPoint(b);
		DrawLine(a, b);
		glColor3f(0.0, 0.0, 1.0);
		CutLine();
		glColor3f(1.0, 1.0, 1.0);
		iter++;
		glFlush();
	}
	a.x = -1;
}
void onMouse(int button, int state, int x, int y)//鼠标点击事件
{
	mouseX = x / (Length / Size); //获取鼠标点击处的坐标
	mouseY = Size - (y / (Width / Size));
	mouseX = round(mouseX, 2);
	mouseY = round(mouseY, 2);
	if (!modification) //画图模式
	{
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
			modification = true;
			cout << "修改模式" << endl;
		}//画图模式下，右键启动修改模式
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			/*if (mouseX <= 1 && mouseY >= Size - 4 && mouseY <= Size - 1)//更改颜色
			{
				if (mouseY <= Size - 3) glColor3f(0.0, 0.0, 1.0);
				else if (mouseY <= Size - 2) glColor3f(0.0, 1.0, 0.0);
				else if (mouseY <= Size - 1) glColor3f(1.0, 0.0, 0.0);
			}*/
			if (mouseX <= 1 && mouseY >= Size - 1) //清空,回到初始状态
			{
				glClearColor(0.0, 0.0, 0.0, 0.0);
				glColor3f(1.0, 1.0, 1.0);
				glClear(GL_COLOR_BUFFER_BIT);
				flag = false;
				display();
				All_edge.clear();
			}
			else {
				if (a.x == -1) {
					a.x = mouseX;
					a.y = mouseY;
					DrawPoint(a);
				}
				else {
					b.x = mouseX;
					b.y = mouseY;
					Edge temp;
					temp.a = a, temp.b = b;
					All_edge.push_back(temp);
					DrawPoint(b);
					DrawLine(a, b);
					glColor3f(0.0, 0.0, 1.0);
					CutLine();
					a.x = -1, a.y = -1;
					glColor3f(1.0, 1.0, 1.0);
				}
				glFlush();
			}
		}
	}
	else//修改模式
	{
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{
			modification = false;
			cout << "退出修改模式" << endl;
			a.x = -1, a.y = -1;
		}
		else if (button == GLUT_LEFT_BUTTON)
		{
			if (state == GLUT_DOWN)
			{
				leftButton = true;
			}
			else if (state == GLUT_UP) leftButton = false;
		}
	}
	
}
void mouseMove(int x, int y)
{
	mouseX = x / (Length / Size); //获取鼠标处的坐标
	mouseY = Size - (y / (Width / Size));
	mouseX = round(mouseX, 2);
	mouseY = round(mouseY, 2);
	if (leftButton && modification) //左键拖动点
	{
		list<Edge>::iterator iter = All_edge.begin();
		while (iter != All_edge.end())
		{
			if (abs(mouseX - iter->a.x) <= 0.5 && abs(mouseY - iter->a.y) <= 0.5)
			{
				iter->a.x = mouseX, iter->a.y = mouseY;
				update();
				//glFlush();
				break;
			}
			else if (abs(mouseX - iter->b.x) <= 0.5 && abs(mouseY - iter->b.y) <= 0.5)
			{
				iter->b.x = mouseX, iter->b.y = mouseY;
				update();
				//glFlush();
				break;
			}
			else {
				iter++;
			}
		}
	}
}

int main()
{
	glutInitWindowSize(Length, Width);
	glutCreateWindow("Scaning_Line");
	InitEnvironment();
	glutDisplayFunc(&display);
	glutMouseFunc(&onMouse);
	glutMotionFunc(&mouseMove);
	glutMainLoop();
}