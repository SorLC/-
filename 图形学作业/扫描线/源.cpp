#include <gl/glut.h>
#include <iostream>
#include <math.h>
#include <queue>
#include <list>
#include "grid.h"
using namespace std;

const float Size = 20.0; //����ߴ�
const int Length = 600; //���ڳߴ�
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
	int size = (int)((max - min) * 10) + 1; //ɨ��������
	NET = new list<AET_>[size];//��ɨ���ߵ��±߱�
	Polygon::Myiterator *iter = pol.iterator();
	Edge temp;
	while ((temp = iter->next()).a != temp.b)
	{//ȡ�ö�������бߣ��޳�ƽ����ɨ���ߵı�
		temp.swap();
		if (temp.a.y != temp.b.y) E.push_back(temp);
	}
	for (int i = 0; i < size; i++) //Ϊÿһ��ɨ���߽����±߱�
	{//ɨ����ÿ������0.1
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
				iter = E.erase(iter);//ɾ���Ѽ���NET�ı�					
			}
			else iter++;
		}
		if (E.empty()) break;
	}
	AET.clear(); //��ʼ�����Ա߱�ͷ
	for (int i = 0; i < size; i++)//����ÿһ��ɨ����
	{   
		list<AET_>::iterator iter = AET.begin();
		while (iter != AET.end())
		{
			//cout << AET.size() << endl;
			if (abs(iter->Ymax - (((float)i / 10) + min)) <= pre)
			{//ɾ�������ı�
				iter = AET.erase(iter);
			}
			else {
				iter->x += iter->Dx / 10;
				iter++;
			}
		}
	    iter = NET[i].begin();
		while (iter != NET[i].end())//������ǰɨ����NET��������Ԫ�ز���AET
		{ 
			AET_ temp(iter->x, iter->Dx, iter->Ymax);
			AET.push_back(temp);
			iter++;
		}
		//cout << i << endl;
		//��AET����
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
void InitEnvironment() //��ʼ����ͼ����
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0.0, Size, 0.0, Size);
	glColor3f(1.0, 1.0, 1.0);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Fill(0, Size - 1);//��հ�ť
	glColor3f(1.0, 0.0, 0.0);
	Fill(0, Size - 2);
	glColor3f(0.0, 1.0, 0.0);
	Fill(0, Size - 3);
	glColor3f(0.0, 0.0, 1.0);
	Fill(0, Size - 4);
	glColor3f(1.0, 1.0, 1.0);
	glFlush();
}
void onMouse(int button, int state, int x, int y)//������¼�
{
	static bool flag = false;
	static Vertex first; //��̬�洢��һ����
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		b.x = x / (Length / Size); //��ȡ�������������
		b.y = Size - (y / (Width /Size ));
		b.x = round(b.x, 1); //������㾫ȷ��һλС��
		b.y = round(b.y, 1);
		//cout << b.x << " " << b.y << endl;
		if (b.x <= 1 && b.y >= Size - 4 && b.y <= Size - 1)//������ɫ
		{
			if (b.y <= Size - 3) glColor3f(0.0, 0.0, 1.0);
			else if (b.y <= Size - 2) glColor3f(0.0, 1.0, 0.0);
			else if (b.y <= Size - 1) glColor3f(1.0, 0.0, 0.0);
		}
		else if (b.x <= 1 && b.y >= Size - 1) //���
		{
			glClearColor(0.0, 0.0, 0.0, 0.0);
			glColor3f(1.0, 1.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);
			Fill(0, Size - 1);//��հ�ť
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
		else if(!flag) //�������
		{
			if (a.x == -1) //��һ����
			{
				a = b;
				first = b;
				DrawPoint(a);
				pol.insert(a);			
			}
			else if (a.x == b.x && a.y == b.y)
			{}//�����ظ���
			else {
				if (abs(first.x - b.x) <= 0.4 && abs(first.y - b.y) <= 0.4)
				{//ȷ���յ�
					DrawLine(a, first);
					flag = true;
					a.x = -1, a.y = -1;
				}
				else {//������
					DrawLine(a, b);
					pol.insert(b);
					a = b;
				}
			}
		}
		else if (flag) //��ʼɨ�������
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