#include <gl/glut.h>
#include "grid.h"
#include <iostream>
#include <math.h>
using namespace std;

int x_0, y_0, x_1, y_1;
void InitEnvironment()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0.0, 20.0, 0.0, 20.0);
	glColor3f(1.0, 1.0, 1.0);
}
void swap(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}
void BresenhamLine(int x_0, int y_0, int x_1, int y_1)
{
	int x, y, dx, dy;
	float k, e;
	dx = x_1 - x_0;
	dy = y_1 - y_0;
	if (dx == 0 && dy != 0)
	{
		if (y_0 > y_1)
		{
			swap(y_0, y_1);
			dy = y_1 - y_0;
		}
		x = x_0, y = y_0;
		for (int i = 0; i <= dy; i++)
		{
			fill(x, y++);
		}
	}
	else {
		k = (float)dy / dx;
		if (k >= 0) //斜率大于0
		{
			x = x_0, y = y_0;
			if (dx >= dy) //斜率小于1
			{
				e = -dx;
				for (int i = 0; i <= dx; i++)
				{
					fill(x++, y);
					e = e + 2*dy;
					if (e >= 0)
					{
						y++, e = e - 2*dx;
					}
				}
			}
			else //斜率大于1
			{
				e = -dy;
				for (int i = 0; i <= dy; i++)
				{
					fill(x, y++);
					e = e + 2 * dx;
					if (e >= 0)
					{
						x++, e = e - 2*dy;
					}
				}
			}
		}
		else if (k < 0) //斜率小于0
		{
			x = x_1, y = y_1;
			e = -dx;
			if (abs(dx) >= abs(dy))
			{
				for (int i = dx; i >= 0; i--)
				{
					fill(x--, y);
					e += -2 * dy;
					if (e >= 0)
					{
						y++;
						e = e - 2*dx;
					}
				}
			}
			else
			{
				e = dy;
				for (int i = abs(dy); i >= 0; i--)
				{
					fill(x, y++);
					e = e + 2*dx;
					if (e >= 0)
					{
						x--;
						e = e + 2 * dy;
					}
				}
			}
		}
	}
	
}
void onMouse(int button, int state, int x, int y)
{
	//init_gid(20);
	static int con = 0;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (con == 0)
		{
			x_0 = (int)x / 30;
			y_0 = 19 - (int)y / 30;
			cout << x_0 << " " << y_0 << " " << con << endl;
			con++;
		}
		else if (con == 1)
		{
			x_1 = (int)x / 30;
			y_1 = 19 - (int)y / 30;
			cout << x_1 << " " << y_1 << " " << con << endl;
			if (x_0 != x_1 || y_0 != y_1)
			{
				if (x_0 > x_1)
				{
					swap(x_0, x_1);
					swap(y_0, y_1);
				}
				glColor3f(0.5, 0.5, 0.5);
				BresenhamLine(x_0, y_0, x_1, y_1);
				glFlush();
				con = 0;
			}
		}
		
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	init_gid(20);
	glFlush();
}

int main()
{
	glutInitWindowSize(600, 600);
	glutCreateWindow("Line");
	InitEnvironment();
	glutDisplayFunc(&display);
	glutMouseFunc(&onMouse);
	glutMainLoop();
}