#include <iostream>
#include <gl/glut.h>
#include "graph.h"
#include <vector>
using namespace std;

const float Size = 20.0; //����ߴ�
const int Length = 600; //���ڳߴ�
const int Width = 600;
const float pre = 1e-6; //�������ȽϾ���
float mouseX, mouseY;//���˿̵�����
bool modification = false;
bool insert = false;
bool Forward = false;
bool del = false;
bool leftButton = false;

Vertex a(-1, -1), b;
vector<Vertex> control;
vector<Vertex> out;
vector<Vertex> before;
vector<Vertex> after;

Vertex P(float t)
{
	before = control;
	while ((int)before.size() != 1)
	{
		int num = before.size();
		Vertex tmp;
		for (int i = 0; i < num-1; i++)
		{
			tmp.x = (1 - t)*before[i].x + t * before[i + 1].x;
			tmp.y = (1 - t)*before[i].y + t * before[i + 1].y;
			after.push_back(tmp);
		}
		before.clear();
		before = after;
		after.clear();
	}
	return before[0];
}
void Cal()
{
	Vertex tmp;
	out.clear();
	for (float t = 0; abs(t - 1) > pre; t = t + 0.01)
	{
		tmp = P(t);
		out.push_back(tmp);
	}
}
void update()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	Fill(0, Size - 1);//��հ�ť
	Vertex S, P;
	int num = control.size();
	S = control[0];
	DrawPoint(S);
	for (int i = 1; i < num; i++)
	{
		P = control[i];
		DrawPoint(P);
		DrawLine(S, P);
		S = P;
	}
	glColor3f(1.0, 0.0, 0.0);
	num = out.size();
	for (int i = 0; i < num - 1; i++)
	{
		S = out[i];
		P = out[i + 1];
		DrawLine(S, P);
	}
	glColor3f(1.0, 1.0, 1.0);
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
	glFlush();
}

void Clear()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	Fill(0, Size - 1);//��հ�ť
	modification = false;
	insert = false;
	del = false;
	leftButton = false;
	glFlush();
	out.clear();
	control.clear();
	a.x = -1;
}
void onKeyBoard(unsigned char button,int x,int y)
{
	if (button == 'm')
	{
		if (!modification) {
			modification = true;
			cout << "�޸�ģʽ" << endl;
		}
		else {
			modification = false;
			cout << "�˳��޸�ģʽ" << endl;
		}
	}
	else if (button == 'i' && modification && !del)
	{
		if (!insert) {
			insert = true;
			cout << "������Ƶ�" << endl;
		}
		else {
			insert = false;
			cout << "��������" << endl;
		}
	}
	else if (button == 'd' && modification && !insert)
	{
		if (!del) {
			del = true;
			cout << "ɾ�����Ƶ�" << endl;
		}
		else {
			cout << "����ɾ��" << endl;
			del = false;
		}
	}
	else if (button == 'q') exit(0);
}
void onMouse(int button, int state, int x, int y)
{
	mouseX = x / (Length / Size); //��ȡ�������������
	mouseY = Size - (y / (Width / Size));
	mouseX = round(mouseX, 2);
	mouseY = round(mouseY, 2);
	if (!modification)//��ӿ��Ƶ�
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (mouseX <= 1 && mouseY >= Size - 1)
			{
				Clear();
			}
			else if (a.x == -1) {
				a.x = mouseX, a.y = mouseY;
				control.push_back(a);
				DrawPoint(a);
			}
			else {
				b.x = mouseX, b.y = mouseY;
				control.push_back(b);
				DrawPoint(b);
				DrawLine(a, b);
				a = b;
				Cal();
				update();
			}
		}
	}
	else//�޸�ģʽ
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			if (state == GLUT_DOWN) {
				leftButton = true;
				if (del && !insert) //ɾ�����Ƶ�
				{
					Vertex tmp;
					tmp.x = mouseX, tmp.y = mouseY;
					vector<Vertex>::iterator iter = control.begin();
					while (iter != control.end())
					{
						if (abs(iter->x - tmp.x) < 0.5 && abs(iter->y - tmp.y) < 0.5)
						{
							iter = control.erase(iter);
							Cal();
							update();
							break;
						}
						else {
							iter++;
						}
					}
				}
				else if (!del && insert) //������Ƶ�
				{
					Vertex S;
					static int con;
					if (!Forward)//ǰ����δȷ��
					{
						con = 0;
						while (con < (int)control.size())
						{
							S.x = mouseX, S.y = mouseY;
							if (abs(S.x - control[con].x) < 0.5 && abs(S.y - control[con].y) < 0.5)
							{
								Forward = true;
								cout << "��ȷ��ǰ����" << endl;
								break;
							}
							else con++;
						}
					}
					else//ǰ����ȷ��
					{
						S.x = mouseX, S.y = mouseY;
						control.insert(control.begin() + con + 1, S);
						cout << "�������" << endl;
						Cal();
						update();
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
	mouseX = x / (Length / Size); //��ȡ�������������
	mouseY = Size - (y / (Width / Size));
	mouseX = round(mouseX, 2);
	mouseY = round(mouseY, 2);
	if (leftButton && modification)
	{
		vector<Vertex>::iterator iter = control.begin();
		while (iter != control.end())
		{
			if (abs(iter->x - mouseX) < 0.5 && abs(iter->y - mouseY) < 0.5)
			{
				iter->x = mouseX;
				iter->y = mouseY;
				Cal();
				update();
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
	glutMotionFunc(onMouseMove);
	glutKeyboardFunc(&onKeyBoard);
	glutMainLoop();
}