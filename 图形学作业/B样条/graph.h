#pragma once
float round(float src, int bits); //为数据src保留bits位小数
void Fill(float x, float y);//绘制以x，y为左下角的边长为1的矩形
struct Vertex
{
	float x, y;
	Vertex(const float _x = 0, const float _y = 0) :x(_x), y(_y)
	{}
	bool operator == (const Vertex a)
	{
		return x == a.x && y == a.y;
	}
	bool operator != (const Vertex a)
	{
		return x != a.x || y != a.y;
	}
}; //点
void DrawPoint(Vertex a); //画点
void DrawLine(Vertex a, Vertex b);//画线