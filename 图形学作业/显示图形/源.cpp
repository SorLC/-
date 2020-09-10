//#include <iostream>
//#include <OpenMesh/Core/IO/MeshIO.hh>
//#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
//#include <gl/glut.h>
//#include <string>
//using namespace std;
//
//typedef OpenMesh::TriMesh_ArrayKernelT<> MyMesh;
//MyMesh mesh;
//const string File = "1.obj";
//GLuint showFaceList, showWireList;
//int showstate = 1;
//bool showFace = true;
//bool showWire = false;
//bool showFlatlines = false;
//float MouseX, MouseY;
//bool LeftButton;
//const int Length = 600; //窗口尺寸
//const int Width = 600;
//
//void readfile(string file) {
//	// 请求顶点法线 vertex normals
//	mesh.request_vertex_normals();
//	//如果不存在顶点法线，则报错 
//	if (!mesh.has_vertex_normals())
//	{
//		cout << "错误：标准定点属性 “法线”不存在" << endl;
//		return;
//	}
//	// 如果有顶点发现则读取文件 
//	OpenMesh::IO::Options opt;
//	if (!OpenMesh::IO::read_mesh(mesh, file, opt))
//	{
//		cout << "无法读取文件:" << file << endl;
//		return;
//	}
//	else cout << "成功读取文件:" << file << endl;
//	cout << endl; // 为了ui显示好看一些
//				  //如果不存在顶点法线，则计算出
//	if (!opt.check(OpenMesh::IO::Options::VertexNormal))
//	{
//		// 通过面法线计算顶点法线
//		mesh.request_face_normals();
//		// mesh计算出顶点法线
//		mesh.update_normals();
//		// 释放面法线
//		mesh.release_face_normals();
//	}
//}
//void initGL()
//{
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glClearDepth(2.0);
//	glShadeModel(GL_SMOOTH);
//	//glEnable(GL_DEPTH_TEST); //用来开启深度缓冲区的功能，启动后OPengl就可以跟踪Z轴上的像素，那么它只有在前面没有东西的情况下才会绘制这个像素，在绘制3d时，最好启用，视觉效果会比较真实
//							 // ------------------- Lighting  
//	//glEnable(GL_LIGHTING); // 如果enbale那么就使用当前的光照参数去推导顶点的颜色
//	//glEnable(GL_LIGHT0); //第一个光源，而GL_LIGHT1表示第二个光源
//						 // ------------------- Display List  
//	showFaceList = glGenLists(1);
//	showWireList = glGenLists(1);
//	int temp = mesh.n_edges();
//
//	// 绘制 wire 
//	glNewList(showWireList, GL_COMPILE);
//	glDisable(GL_LIGHTING);
//	glLineWidth(1.0f);
//	glColor3f(0.5f, 0.5f, 0.5f);
//	glBegin(GL_LINES);
//	for (MyMesh::HalfedgeIter he_it = mesh.halfedges_begin(); he_it != mesh.halfedges_end(); ++he_it) {
//		//链接这个有向边的起点和终点
//		glVertex3fv(mesh.point(mesh.from_vertex_handle(*he_it)).data());
//		glVertex3fv(mesh.point(mesh.to_vertex_handle(*he_it)).data());
//	}
//	glEnd();
//	glEnable(GL_LIGHTING);
//	glEndList();
//
//	// 绘制flat
//	glNewList(showFaceList, GL_COMPILE);
//	for (MyMesh::FaceIter f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it) {
//		glBegin(GL_TRIANGLES); //三角形模式
//		for (MyMesh::FaceVertexIter fv_it = mesh.fv_iter(*f_it); fv_it.is_valid(); ++fv_it) {
//			glNormal3fv(mesh.normal(*fv_it).data());
//			glVertex3fv(mesh.point(*fv_it).data());
//		}
//		glEnd();
//	}
//	glEndList();
//}
//void Display()
//{
//	//要清除之前的深度缓存
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();
//	//与显示相关的函数
//	//glRotatef(xRotate, 1.0f, 0.0f, 0.0f); // 让物体旋转的函数 第一个参数是角度大小，后面的参数是旋转的法向量
//	//glRotatef(yRotate, 0.0f, 1.0f, 0.0f);
//	//glTranslatef(0.0f, 0.0f, ty);
//	//glScalef(scale, scale, scale); // 缩放
//
//								   //每次display都要使用glcalllist回调函数显示想显示的顶点列表
//	if (showFace)
//		glCallList(showFaceList);
//	if (showFlatlines) {
//		glCallList(showFaceList);
//		glCallList(showWireList);
//	}
//	if (showWire)
//		glCallList(showWireList);
//
//	glutSwapBuffers(); //这是Opengl中用于实现双缓存技术的一个重要函数
//}
//
//int main()
//{
//	//glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // GLUT_Double 表示使用双缓存而非单缓存
//	//glutInitWindowPosition(100, 100);
//	glutInitWindowSize(800, 500);
//	glutCreateWindow("Mesh Viewer");
//	//一开始默认读取文件1
//	//readfile(File);
//	//initGL();
//	//glutMouseFunc(myMouse);
//	//glutMotionFunc(onMouseMove); // 鼠标移动的时候的函数
//	//glutSpecialFunc(&mySpecial);
//	//glutReshapeFunc(&myReshape);
//	//glutDisplayFunc(&Display);
//
//	glutMainLoop();
//	return 0;
//}