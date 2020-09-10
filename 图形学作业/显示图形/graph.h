#pragma once
#include <vector>
#include <string>
struct point
{
	double x, y, z;
};
struct wenli
{
	double tu, tv;
};
struct faxiangliang
{
	double nx, ny, nz;
};
struct face
{
	int V[3];
	int T[3];
	int N[3];
};
class PIC
{
private:
	std::vector<point> V; //����
	std::vector<wenli> VT; //��������
	std::vector<faxiangliang> VN; //������
	std::vector<face> F; //��
public:
	void ReadPIC(std::string name);
	void Draw();
};