#include <gl/glut.h>
#include <iostream>
#include <math.h>
#include "grid.h"
using namespace std;

int x_0, y_0, x_1, y_1;
void InitEnvironment()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0.0, 20.0, 0.0, 20.0);
	glColor3f(1.0, 1.0, 1.0);
}

void DrowPoint(int x0, int y0,int x,int y)
{
	fill(x+x0, y+y0);
	fill(y+y0, x+x0);
	fill(x0-x, y+y0);
	fill(y+y0, x0-x);
	fill(x+x0, y0-y);
	fill(y0-y, x+x0);
	fill(x0-x, y0-y);
	fill(y0-y, x0-x);
}
void midPointCircle(int x0, int y0, int R)
{
	int x, y;
	float d;
	x = 0, y = R;
	d = 1.25 - R;
	DrowPoint(x0,y0,x,y);
	while(x <= y)
	{
		if (d < 0)
		{
			d += 2 * x + 3;
		}
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		DrowPoint(x0,y0,x,y);
	}
}
void onMouse(int button, int state, int x, int y)
{
	static int con = 0;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (con == 0)
		{
			x_0 = (int)x / 30;
			y_0 = 19 - (int)y / 30;
			con++;
		}
		else if (con == 1)
		{
			x_1 = (int)x / 30;
			y_1 = 19 - (int)y / 30;
			if (x_0 != x_1 || y_0 != y_1)
			{
				con = 0;
				int R = abs(x_1 - x_0) + abs(y_1 - y_0);
				//cout << "(" << x_0 << "," << y_0 << ")" << " " << R << endl;
				glColor3f(0.5, 0.5, 0.5);
				midPointCircle(x_0, y_0, R);
				glFlush();
			}
		}
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	init_gid(20);
	fill(9, 9);
	glFlush();
}

int main()
{
	glutInitWindowSize(600, 600);
	glutCreateWindow("Circle");
	InitEnvironment();
	glutDisplayFunc(&display);
	glutMouseFunc(&onMouse);
	glutMainLoop();
}