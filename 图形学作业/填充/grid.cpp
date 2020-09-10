#include <gl/glut.h>
#include <algorithm>
#include <math.h>
void fill(int x, int y)
{
	//glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex2i(x, y);
	glVertex2i(x + 1, y);
	glVertex2i(x + 1, y + 1);
	glVertex2i(x, y + 1);
	glEnd();
}

void init_gid(int length)
{
	for (int i = 0; i <= length; i++)//Íø¸ñ
	{
		glBegin(GL_LINES);
		glVertex2i(0, i);
		glVertex2i(length, i);
		glEnd();
		glBegin(GL_LINES);
		glVertex2i(i, 0);
		glVertex2i(i, length);
		glEnd();
	}
}
void swap(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}

