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
	std::vector<point> V; //顶点
	std::vector<wenli> VT; //纹理坐标
	std::vector<faxiangliang> VN; //法向量
	std::vector<face> F; //面
public:
	void ReadPIC(std::string name);
	void Draw();
};