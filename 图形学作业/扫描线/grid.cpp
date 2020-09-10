#include <gl/glut.h>
#include <sstream>
#include <iomanip> 
#include "grid.h"
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
	glVertex2i(x, y+1);
	glVertex2i(x+1, y+1);
	glVertex2i(x+1, y);
	glEnd();
}
void DrawPoint(Vertex a) //»­µã
{
	glPointSize(0.1);
	glBegin(GL_POINTS);
	glVertex2f(a.x, a.y);
	glEnd();
}
void DrawLine(Vertex a, Vertex b)//»­Ïß
{
	glLineWidth(0.1);
	glBegin(GL_LINES);
	glVertex2f(a.x, a.y);
	glVertex2f(b.x, b.y);
	glEnd();
}
Vertex Polygon::get_min()
{
	Vertex ans(0, 30);
	for (int curPoint = 0; curPoint < numOfVer; curPoint++)
	{
		if (point[curPoint].y < ans.y) ans = point[curPoint];
	}
	return ans;
}
Vertex Polygon::get_max()
{
	Vertex ans(0, 0);
	for (int curPoint = 0; curPoint < numOfVer; curPoint++)
	{
		if (point[curPoint].y > ans.y) ans = point[curPoint];
	}
	return ans;
}
void Polygon::insert(Vertex a)
{
	point.push_back(a);
	numOfVer++;
}
void Polygon::clear()
{
	numOfVer = 0;
	point.clear();
}