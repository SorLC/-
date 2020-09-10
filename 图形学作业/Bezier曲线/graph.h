#pragma once
float round(float src, int bits); //Ϊ����src����bitsλС��
void Fill(float x, float y);//������x��yΪ���½ǵı߳�Ϊ1�ľ���
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
}; //��
void DrawPoint(Vertex a); //����
void DrawLine(Vertex a, Vertex b);//����