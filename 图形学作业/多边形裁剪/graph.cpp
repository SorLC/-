#include <gl/glut.h>
#include "graph.h"
#include <sstream>
#include <iomanip> 
using namespace std;
float round(float src, int bits)
{
	stringstream ss;
	float f;
	ss << fixed << setprecision(bits) << src;
	ss >> f;
	return f;
}
void Fill(float x, float y)
{
	glBegin(GL_POLYGON);
	glVertex2i(x, y);
	glVertex2i(x, y + 1);
	glVertex2i(x + 1, y + 1);
	glVertex2i(x + 1, y);
	glEnd();
}
void DrawPoint(Vertex a) //»­µã
{
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(a.x, a.y);
	glEnd();
}
void DrawLine(Vertex a, Vertex b)//»­Ïß
{
	glBegin(GL_LINES);
	glVertex2f(a.x, a.y);
	glVertex2f(b.x, b.y);
	glEnd();
}
void DrawPolygon(vector<Vertex> a)
{
	int num = (int)a.size();
	Vertex S, P;
	S = a[num - 1];
	for (int i = 0; i < num; i++)
	{
		P = a[i];
		DrawLine(S, P);
		S = P;
	}
}