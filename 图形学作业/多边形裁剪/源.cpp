#include <iostream>
#include <gl/glut.h>
#include "graph.h"
using namespace std;

const float Size = 20.0; //����ߴ�
const int Length = 600; //���ڳߴ�
const int Width = 600;
const float pre = 1e-6; //�������ȽϾ���
float mouseX, mouseY;//���˿̵�����

const int XL = 5, XR = 15, YD = 5, YU = 15;//�ü��߿�
Edge L, R, D, U;
Vertex a(-1, -1), b, first;
vector<Vertex> in_Vertex, out_Vertex;

bool inside(Vertex tmp, Edge bound) //�жϵ��Ƿ��ڲü�����
{
	if (bound == L) return tmp.x >= bound.a.x;//�ü���Ϊ���
	if (bound == R) return tmp.x <= bound.a.x;//�ü���Ϊ�ұ�
	if (bound == D) return tmp.y >= bound.a.y;//�ü���Ϊ�±�
	if (bound == U) return tmp.y <= bound.a.y;//�ü���Ϊ�ϱ�
	return false;
}
Vertex Intersect(Edge m, Edge bound) //����ü��ߵĽ���
{
	Vertex tmp;
	if (bound == L || bound == R)
	{
		tmp.x = bound.a.x;
		tmp.y = m.a.y + (bound.a.x - m.a.x)*(m.b.y - m.a.y) / (m.b.x - m.a.x);
	}
	else {
		tmp.y = bound.a.y;
		tmp.x = m.a.x + (bound.a.y - m.a.y)*(m.b.x - m.a.x) / (m.b.y - m.a.y);
	}
	return tmp;
}
void cut_Edge(vector<Vertex> &in, vector<Vertex> &out, Edge bound)
{
	int in_length = in.size();
	Vertex S = in[in_length - 1];
	Vertex P, IP;
	for (int i = 0; i < in_length; i++)
	{
		P = in[i];
		Edge tmp;
		tmp.a = S, tmp.b = P;
		if (inside(P, bound)) //P���ڲ�
		{
			if (inside(S, bound))//SP���ڲü�����
			{
				out.push_back(P);
			}
			else { //S�����ڲ�
				IP = Intersect(tmp, bound);
				out.push_back(IP);
				out.push_back(P);
			}
		}
		else { //P�����ڲ�
			if (inside(S, bound)) //S���ڲ�
			{
				IP = Intersect(tmp, bound);
				out.push_back(IP);
			}
		}
		S = P;
	}

}
void Cut()
{
	cut_Edge(in_Vertex,out_Vertex,L);
	in_Vertex.clear();
	cut_Edge(out_Vertex,in_Vertex,R);
	out_Vertex.clear();
	cut_Edge(in_Vertex,out_Vertex,U);
	in_Vertex.clear();
	cut_Edge(out_Vertex,in_Vertex,D);
	out_Vertex.clear();
}
void InitEnvironment() //��ʼ����ͼ����
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0.0, Size, 0.0, Size);
	glColor3f(1.0, 1.0, 1.0);
}
void Draw_frame()
{
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
	Fill(0, Size - 1);//��հ�ť
	glColor3f(1.0, 1.0, 1.0);
	//���βü��߿�
	Draw_frame();
	glFlush();
}
void Clear()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	Fill(0, Size - 1);//��հ�ť
	glColor3f(1.0, 1.0, 1.0);
	//���βü��߿�
	Draw_frame();
	glFlush();
}
void onMouse(int button, int state, int x, int y)
{
	mouseX = x / (Length / Size); //��ȡ�������������
	mouseY = Size - (y / (Width / Size));
	mouseX = round(mouseX, 2);
	mouseY = round(mouseY, 2);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//cout << mouseX << " " << mouseY << endl;
		if (mouseX <= 1 && mouseY >= Size - 1) Clear();
		else if (a.x == -1)
		{
			a.x = mouseX, a.y = mouseY;
			first = a;
			in_Vertex.push_back(a);
			DrawPoint(a);
		}
		else {
			if (abs(first.x - mouseX) <= 0.5 && abs(first.y - mouseY) <= 0.5)
			{
				DrawLine(b, first);
				Cut();
				glColor3f(1.0, 0.0, 0.0);
				DrawPolygon(in_Vertex);
				glColor3f(1.0, 1.0, 1.0);
				a.x = -1;
				in_Vertex.clear();
			}
			else
			{
				b.x = mouseX, b.y = mouseY;
				in_Vertex.push_back(b);
				DrawPoint(b);
				DrawLine(a, b);
				a = b;
			}
		}
		glFlush();
	}
}
int main()
{
	glutInitWindowSize(Length, Width);
	glutCreateWindow("rectangle");
	InitEnvironment();
	glutDisplayFunc(&display);
	glutMouseFunc(&onMouse);
	glutMainLoop();
}