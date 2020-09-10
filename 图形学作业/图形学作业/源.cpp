#include <gl/glut.h>
#include <stdio.h>
#include <cmath>

float point = 0.5;
float R = 0.4;
float x1 = point - R, y_1 = point;
float x2 = point, y_2 = point - R;
float x3 = point + R, y_3 = point;
float x4 = point, y_4 = point + R;

float Pi = 3.1415926f;
float dis(float x1, float y_1, float x2, float y_2)
{
	float d = sqrt(pow(x1 - x2, 2) + pow(y_1 - y_2, 2)) / 2;
	return sqrt(pow(R, 2) - pow(d, 2));
}
void display()
{
	while (R > 0.1)
	{
		//glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_LINE_LOOP); //
		glVertex3f(x1, y_1, 0.0); //多边形的顶点1
		glVertex3f(x2, y_2, 0.0); //顶点2
		glVertex3f(x3, y_3, 0.0);
		glVertex3f(x4, y_4, 0.0);
		glEnd(); //结束多边形绘制

		glBegin(GL_LINE_LOOP); //圆
		int n = 3600;
		for (int i = 0; i < n; i++)
		{
			glVertex2f(R * cos(2 * Pi*i / n) + 0.5, R * sin(2 * Pi*i / n) + 0.5);
		}
		glEnd();
		R = dis(x1, y_1, x2, y_2);
		x1 = point - R, y_1 = point;
		x2 = point, y_2 = point - R;
		x3 = point + R, y_3 = point;
		x4 = point, y_4 = point + R;
	}

	glFlush(); //保证绘图命令执行
}

int main(int argc, char **argv)
{
	//glutInit(&argc, argv);	//初始化窗口
	glutCreateWindow("hello"); //创建窗口
	glClearColor(0.0, 0.0, 0.0, 0.0); //窗口擦除颜色
	glClear(GL_COLOR_BUFFER_BIT); //完成清除窗口的任务
	glColor3f(1.0, 1.0, 1.0); //绘制物体的颜色为白色
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0); //OpenGL绘制图像时所使用的坐标系统
	glutDisplayFunc(display); //指定OpenGL的显示函数，函数中指定显示内容
	glutMainLoop(); //进入消息循环，一般窗口系统都有这个
}
