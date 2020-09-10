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
void DrawPoint(Vertex a) //»­µã
{
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(a.x, a.y,a.z);
	glEnd();
}
void DrawLine(Vertex a, Vertex b)//»­Ïß
{
	glBegin(GL_LINES);
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);
	glEnd();
}