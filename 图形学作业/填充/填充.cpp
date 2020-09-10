#include <gl/glut.h>
#include <iostream>
#include <math.h>
#include "grid.h"
using namespace std;

bool fit[20][20];
int x_0 = -1, y_0 = -1, x_1, y_1;
void InitEnvironment()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0.0, 20.0, 0.0, 20.0);
	glColor3f(1.0, 1.0, 1.0);
}
void BresenhamLine(int x_0, int y_0, int x_1, int y_1)
{
	int x, y, dx, dy;
	float k, e;
	if (x_0 > x_1) {
		swap(x_0, x_1);
		swap(y_0, y_1);
	}
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
			fit[x][y] = true;
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
					fit[x][y] = true;
					fill(x++, y);
					e = e + 2 * dy;
					if (e >= 0)
					{
						y++, e = e - 2 * dx;
					}
				}
			}
			else //斜率大于1
			{
				e = -dy;
				for (int i = 0; i <= dy; i++)
				{
					fit[x][y] = true;
					fill(x, y++);
					e = e + 2 * dx;
					if (e >= 0)
					{
						x++, e = e - 2 * dy;
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
					fit[x][y] = true;
					fill(x--, y);
					e += -2 * dy;
					if (e >= 0)
					{
						y++;
						e = e - 2 * dx;
					}
				}
			}
			else
			{
				e = dy;
				for (int i = abs(dy); i >= 0; i--)
				{
					fit[x][y] = true;
					fill(x, y++);
					e = e + 2 * dx;
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
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	init_gid(20);
	glFlush();
}
void bfs_fill(int x, int y)//填充
{
	if (!fit[x][y])
	{
		fit[x][y] = true;
		fill(x, y);
		bfs_fill(x + 1, y);
		bfs_fill(x - 1, y);
		bfs_fill(x, y + 1);
		bfs_fill(x, y - 1);
	}
}
void onMouse(int button, int state, int x, int y)
{
	static bool flag = false;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x_1 = (int)x / 30;
		y_1 = 19 - (int)y / 30;
		if (!fit[x_1][y_1] && x_0 == -1 && !flag)
		{
			x_0 = x_1, y_0 = y_1;
		}
		else if (!fit[x_1][y_1] && !fit[x_0][y_0] && !flag)
		{
			glColor3f(0.5, 0.5, 0.5);
			BresenhamLine(x_0, y_0, x_1, y_1);
			glFlush();
			x_0 = x_1, y_0 = y_1;
		}
		else if (!fit[x_1][y_1] && fit[x_0][y_0] && !flag)
		{
			glColor3f(0.5, 0.5, 0.5);
			BresenhamLine(x_0, y_0, x_1, y_1);
			glFlush();
			x_0 = x_1, y_0 = y_1;
		}
		else if (fit[x_1][y_1] && fit[x_0][y_0] && !flag)
		{
			glColor3f(0.5, 0.5, 0.5);
			BresenhamLine(x_0, y_0, x_1, y_1);
			glFlush();
			flag = true;
		}
		else if (flag == true)
		{
			glColor3f(1.0, 0.0, 0.0);
			bfs_fill(x_1, y_1);
			glFlush();
			flag = false;
			x_0 = y_0 = -1;
		}
	}
}
int main()
{
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			fit[i][j] = false;
		}
	}
	glutInitWindowSize(600, 600);
	glutCreateWindow("Circle");
	InitEnvironment();
	glutDisplayFunc(&display);
	glutMouseFunc(&onMouse);
	glutMainLoop();
}