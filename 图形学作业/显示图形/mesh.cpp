#include "graph.h"
#include <gl/glut.h>
#include <iostream>
using namespace std;

const int Length = 600; //窗口尺寸
const int Width = 600;
const string File = "1.obj";
PIC OB;
bool modification = false;
bool Leftbutton = false;
bool Rightbutton = false;
GLfloat mouseX, mouseY;
GLfloat roate = 0.0;// 设置旋转速率
GLfloat rote = 0.0;//旋转角度
GLfloat anglex = 0.0;//X 轴旋转
GLfloat angley = 0.0;//Y 轴旋转
GLfloat anglez = 0.0;//Z 轴旋转
GLint WinW = 400;
GLint WinH = 400;

void InitEnvironment() //初始化绘图窗口
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glOrtho(-10, 10, -10, 10, -10, 10);
	glColor3f(1.0, 1.0, 1.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	OB.ReadPIC(File);
	OB.Draw();
	glLoadIdentity();  //加载单位矩阵  
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(rote, 0.0f, 1.0f, 0.0f);
	glRotatef(anglex, 1.0, 0.0, 0.0);
	glRotatef(angley, 0.0, 1.0, 0.0);
	glRotatef(anglez, 0.0, 0.0, 1.0);
	glutWireTeapot(2);
	rote += roate;
	//glRotatef(angle, 0.0, 1.0, 0.0);
	//angle += 1.0f;
	glutSwapBuffers();
	glFlush();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
	else if (button == 'q') exit(0);
}
void onMouse(int button, int state, int x, int y)
{
	if (modification)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			if (state == GLUT_DOWN)
			{
				Leftbutton = true;
				roate = 0;
				rote = 0;
				mouseX = x;
				mouseY = y;
				cout << mouseX << " " << mouseY << endl;
			}
			else if (state == GLUT_UP) Leftbutton = false;
		}
		if (button == GLUT_RIGHT_BUTTON)
		{
			if (state == GLUT_DOWN)
			{
				roate += 1.0f;
				Rightbutton = true;
			}
			else if (state == GLUT_UP) Rightbutton = false;
		}
	}
	glFlush();
}
void motion(int x, int y)
{
	GLint deltax = mouseX - x;
	GLint deltay = mouseY - y;
	anglex += 360 * (GLfloat)deltax / (GLfloat)WinW;//根据屏幕上鼠标滑动的距离来设置旋转的角度  
	angley += 360 * (GLfloat)deltay / (GLfloat)WinH;
	anglez += 360 * (GLfloat)deltay / (GLfloat)WinH;
	mouseX = x;//记录此时的鼠标坐标，更新鼠标坐标  
	mouseY = y;  
	glutPostRedisplay();
	glutPostRedisplay();
}
int main()
{
	glutInitWindowSize(Length, Width);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Show_image");
	InitEnvironment();
	glutDisplayFunc(&display);
	glutMouseFunc(&onMouse);
	glutMotionFunc(&motion);
	glutKeyboardFunc(&onKeyBoard);
	//glutIdleFunc(display);
	glutMainLoop();
}