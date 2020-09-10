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
//const int Length = 600; //���ڳߴ�
//const int Width = 600;
//
//void readfile(string file) {
//	// ���󶥵㷨�� vertex normals
//	mesh.request_vertex_normals();
//	//��������ڶ��㷨�ߣ��򱨴� 
//	if (!mesh.has_vertex_normals())
//	{
//		cout << "���󣺱�׼�������� �����ߡ�������" << endl;
//		return;
//	}
//	// ����ж��㷢�����ȡ�ļ� 
//	OpenMesh::IO::Options opt;
//	if (!OpenMesh::IO::read_mesh(mesh, file, opt))
//	{
//		cout << "�޷���ȡ�ļ�:" << file << endl;
//		return;
//	}
//	else cout << "�ɹ���ȡ�ļ�:" << file << endl;
//	cout << endl; // Ϊ��ui��ʾ�ÿ�һЩ
//				  //��������ڶ��㷨�ߣ�������
//	if (!opt.check(OpenMesh::IO::Options::VertexNormal))
//	{
//		// ͨ���淨�߼��㶥�㷨��
//		mesh.request_face_normals();
//		// mesh��������㷨��
//		mesh.update_normals();
//		// �ͷ��淨��
//		mesh.release_face_normals();
//	}
//}
//void initGL()
//{
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glClearDepth(2.0);
//	glShadeModel(GL_SMOOTH);
//	//glEnable(GL_DEPTH_TEST); //����������Ȼ������Ĺ��ܣ�������OPengl�Ϳ��Ը���Z���ϵ����أ���ô��ֻ����ǰ��û�ж���������²Ż����������أ��ڻ���3dʱ��������ã��Ӿ�Ч����Ƚ���ʵ
//							 // ------------------- Lighting  
//	//glEnable(GL_LIGHTING); // ���enbale��ô��ʹ�õ�ǰ�Ĺ��ղ���ȥ�Ƶ��������ɫ
//	//glEnable(GL_LIGHT0); //��һ����Դ����GL_LIGHT1��ʾ�ڶ�����Դ
//						 // ------------------- Display List  
//	showFaceList = glGenLists(1);
//	showWireList = glGenLists(1);
//	int temp = mesh.n_edges();
//
//	// ���� wire 
//	glNewList(showWireList, GL_COMPILE);
//	glDisable(GL_LIGHTING);
//	glLineWidth(1.0f);
//	glColor3f(0.5f, 0.5f, 0.5f);
//	glBegin(GL_LINES);
//	for (MyMesh::HalfedgeIter he_it = mesh.halfedges_begin(); he_it != mesh.halfedges_end(); ++he_it) {
//		//�����������ߵ������յ�
//		glVertex3fv(mesh.point(mesh.from_vertex_handle(*he_it)).data());
//		glVertex3fv(mesh.point(mesh.to_vertex_handle(*he_it)).data());
//	}
//	glEnd();
//	glEnable(GL_LIGHTING);
//	glEndList();
//
//	// ����flat
//	glNewList(showFaceList, GL_COMPILE);
//	for (MyMesh::FaceIter f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it) {
//		glBegin(GL_TRIANGLES); //������ģʽ
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
//	//Ҫ���֮ǰ����Ȼ���
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();
//	//����ʾ��صĺ���
//	//glRotatef(xRotate, 1.0f, 0.0f, 0.0f); // ��������ת�ĺ��� ��һ�������ǽǶȴ�С������Ĳ�������ת�ķ�����
//	//glRotatef(yRotate, 0.0f, 1.0f, 0.0f);
//	//glTranslatef(0.0f, 0.0f, ty);
//	//glScalef(scale, scale, scale); // ����
//
//								   //ÿ��display��Ҫʹ��glcalllist�ص�������ʾ����ʾ�Ķ����б�
//	if (showFace)
//		glCallList(showFaceList);
//	if (showFlatlines) {
//		glCallList(showFaceList);
//		glCallList(showWireList);
//	}
//	if (showWire)
//		glCallList(showWireList);
//
//	glutSwapBuffers(); //����Opengl������ʵ��˫���漼����һ����Ҫ����
//}
//
//int main()
//{
//	//glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // GLUT_Double ��ʾʹ��˫������ǵ�����
//	//glutInitWindowPosition(100, 100);
//	glutInitWindowSize(800, 500);
//	glutCreateWindow("Mesh Viewer");
//	//һ��ʼĬ�϶�ȡ�ļ�1
//	//readfile(File);
//	//initGL();
//	//glutMouseFunc(myMouse);
//	//glutMotionFunc(onMouseMove); // ����ƶ���ʱ��ĺ���
//	//glutSpecialFunc(&mySpecial);
//	//glutReshapeFunc(&myReshape);
//	//glutDisplayFunc(&Display);
//
//	glutMainLoop();
//	return 0;
//}