#include "graph.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <gl/glut.h>
using namespace std;

void PIC::ReadPIC(string name)
{
	ifstream ifs(name);
	string s;
	face *f;
	point *v;
	faxiangliang *vn;
	wenli *vt;
	while (getline(ifs, s))
	{
		if (s.length() < 2) continue;
		if (s[0] == 'v') //��
		{
			if (s[1] == 't')//��������
			{
				istringstream in(s);
				vt = new wenli();
				string head;
				in >> head >> vt->tu >> vt->tv;
				VT.push_back(*vt);
			}
			else if (s[1] == 'n') //������
			{
				istringstream in(s);
				vn = new faxiangliang();
				string head;
				in >> head >> vn->nx >> vn->ny >> vn->nz;
				VN.push_back(*vn);
			}
			else //����
			{
				istringstream in(s);
				v = new point();
				string head;
				in >> head >> v->x >> v->y >> v->z;
				V.push_back(*v);
			}
		}
		else if (s[0] == 'f') //��
		{
			for (int k = s.size() - 1; k >= 0; k--)
			{
				if (s[k] == '/') s[k] = ' ';
			}
			istringstream in(s);
			f = new face();
			string head;
			in >> head;
			int i = 0;
			while (i < 3)
			{
				if (V.size() != 0)
				{
					in >> f->V[i];
					f->V[i] -= 1;
				}
				if (VT.size() != 0)
				{
					in >> f->T[i];
					f->T[i] -= 1;
				}
				if (VN.size() != 0)
				{
					in >> f->N[i];
					f->N[i] -= 1;
				}
				i++;
			}
			F.push_back(*f);
		}
	}
}
void PIC::Draw()
{
	for (int i = 0; i < F.size(); i++)
	{
		glBegin(GL_POINTS);
		if (VT.size() != 0)glTexCoord2f(VT[F[i].T[0]].tu, VT[F[i].T[0]].tv); //����
		if (VN.size() != 0)glNormal3f(VN[F[i].N[0]].nx, VN[F[i].N[0]].ny, VN[F[i].N[0]].nz);//������
		glVertex3f(V[F[i].V[0]].x, V[F[i].V[0]].y, V[F[i].V[0]].z);        // �϶���
		if (VT.size() != 0)glTexCoord2f(VT[F[i].T[1]].tu, VT[F[i].T[1]].tv); //����
		if (VN.size() != 0)glNormal3f(VN[F[i].N[1]].nx, VN[F[i].N[1]].ny, VN[F[i].N[1]].nz);//������
		glVertex3f(V[F[i].V[1]].x, V[F[i].V[1]].y, V[F[i].V[1]].z);        // ���¶���
		if (VT.size() != 0)glTexCoord2f(VT[F[i].T[2]].tu, VT[F[i].T[2]].tv); //����
		if (VN.size() != 0)glNormal3f(VN[F[i].N[2]].nx, VN[F[i].N[2]].ny, VN[F[i].N[2]].nz);//������
		glVertex3f(V[F[i].V[2]].x, V[F[i].V[2]].y, V[F[i].V[2]].z);        // ���¶���
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(V[F[i].V[0]].x, V[F[i].V[0]].y, V[F[i].V[0]].z);
		glVertex3f(V[F[i].V[1]].x, V[F[i].V[1]].y, V[F[i].V[1]].z);
		glVertex3f(V[F[i].V[2]].x, V[F[i].V[2]].y, V[F[i].V[2]].z);
		glVertex3f(V[F[i].V[0]].x, V[F[i].V[0]].y, V[F[i].V[0]].z);
		glEnd();
	}
}