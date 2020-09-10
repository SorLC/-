#pragma once
#include <vector>
float round(float src, int bits); //为数据src保留bits位小数
void Fill(float x, float y);//绘制以x，y为左下角的边长为1的矩形
struct Vertex
{
	float x, y, z;
};
struct H_vert
{
	Vertex a; //空间坐标信息
	H_edge *leave; //从此点离开的半边
};
struct H_edge
{
	H_vert *origin; //源顶点
	H_edge *next; //同一片面内的下一边
	H_edge *opposite;//对立的半边
	H_face *inface; //所属的面
};
struct H_face
{
	H_edge *edge; //该面的一条起始边
};
class Model
{
private:
	std::vector<H_vert> V;
	std::vector<H_edge> E;
	std::vector<H_face> F;
public:
	void ReadFile(std::string name);
};
void DrawPoint(Vertex a); //画点
void DrawLine(Vertex a, Vertex b);//画线