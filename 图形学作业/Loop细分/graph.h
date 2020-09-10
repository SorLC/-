#pragma once
#include <vector>
float round(float src, int bits); //Ϊ����src����bitsλС��
void Fill(float x, float y);//������x��yΪ���½ǵı߳�Ϊ1�ľ���
struct Vertex
{
	float x, y, z;
};
struct H_vert
{
	Vertex a; //�ռ�������Ϣ
	H_edge *leave; //�Ӵ˵��뿪�İ��
};
struct H_edge
{
	H_vert *origin; //Դ����
	H_edge *next; //ͬһƬ���ڵ���һ��
	H_edge *opposite;//�����İ��
	H_face *inface; //��������
};
struct H_face
{
	H_edge *edge; //�����һ����ʼ��
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
void DrawPoint(Vertex a); //����
void DrawLine(Vertex a, Vertex b);//����