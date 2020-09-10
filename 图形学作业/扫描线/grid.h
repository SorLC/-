#include <vector>

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
struct Edge 
{
	Vertex a, b;
	void swap()
	{
		if (a.y > b.y) { //����b����a���Ϸ�
			Vertex temp = a;
			a = b;
			b = temp;
		}
	}
}; //��
class Polygon //�����
{
private:
	int numOfVer; //���������
	std::vector<Vertex> point; //��������
public:
	Polygon(int num = 0) :numOfVer(num)
	{}
	void insert(Vertex a); //����㵽������ĩβ
	Vertex get_min(); //����yֵ��С�Ķ���
	Vertex get_max(); //����yֵ���Ķ���
	void clear(); //���
	class Myiterator //�ߵĵ�����
	{
	private:
		Vertex *The_point;
		int num;
		int current;
	public:
		Myiterator(std::vector<Vertex> a, int The_num)
		{
			current = 1;
			num = The_num;
			The_point = new Vertex[num];
			for (int i = 0; i < num; i++)
			{
				The_point[i] = a[i];
			}
		}
		~Myiterator()
		{
			delete[]The_point;
		}
		Edge next()//����ÿһ����
		{
			Edge temp;
			if (current > num ) return temp;
			temp.a = The_point[current - 1];
			temp.b = The_point[(current++) % num];
			return temp;
		}
	};
	Myiterator* iterator()
	{
		return new Myiterator(point, numOfVer);
	}
};//�������
