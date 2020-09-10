#include <vector>

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
struct Edge 
{
	Vertex a, b;
	void swap()
	{
		if (a.y > b.y) { //调整b点在a点上方
			Vertex temp = a;
			a = b;
			b = temp;
		}
	}
}; //边
class Polygon //多边形
{
private:
	int numOfVer; //顶点的数量
	std::vector<Vertex> point; //顶点序列
public:
	Polygon(int num = 0) :numOfVer(num)
	{}
	void insert(Vertex a); //插入点到点序列末尾
	Vertex get_min(); //返回y值最小的顶点
	Vertex get_max(); //返回y值最大的顶点
	void clear(); //清空
	class Myiterator //边的迭代器
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
		Edge next()//遍历每一条边
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
};//多边形类
