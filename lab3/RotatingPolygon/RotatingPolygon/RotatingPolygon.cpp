// RotatingPolygon.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <glut.h>
#include <math.h>

#define PI 3.14159         //圆周率。
int n = 6;             //多边形的边数。
int R = 10;            //多边形外接圆半径。
float rotationAngle = 0.0;           //旋转角度，初始旋转角度为0.
int k = 0;             //变色器。

void Display();                      //显示回调函数。
//void myidle();
void myidle(int t);                       //闲置函数。
void Reshape(GLsizei w, GLsizei h);  //窗口改变回调函数。

int main(int argc, char** argv)
{
	glutInit(&argc, argv);          //初始化glut库。
	glutInitWindowPosition(40, 50);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);        //设置显示模式。
	glutCreateWindow("旋转多边形");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
//	glutIdleFunc(myidle);             //只有一个参数的闲置回调函数。
	glutTimerFunc(100, myidle, 10);

	glutMainLoop();                 //循环。
    return 0;
}

void Display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0, 0);           //红色画笔。

	//线框模式。
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);         //线框模式。
//	glLineWidth(3.0);                     //设置线宽。     

	//写字，待完善。
//	glColor3f(0, 0, 0);
//	glRasterPos2i(50, 60);
//	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'L');
//	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'G');
//	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'J');

	if (k == 0)
	{
		glColor3f(1, 0, 0);
		k = 1;
	}
	else if (k == 1)
	{
		glColor3f(0, 1, 0);
		k = 2;
	}
	else
	{
		glColor3f(0, 0, 1);
		k = 0;
	}

	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
		glVertex2f(R*cos(rotationAngle + i * 2 * PI / n), R*sin(rotationAngle + i * 2 * PI / n));
	glEnd();
	glutSwapBuffers();
}

void myidle(int t) 
{
	rotationAngle += 1.0;
	if (rotationAngle >= 2*PI)
	{
		rotationAngle -= 2 * PI;
	}
	glutPostRedisplay();              //重画。重新调用Display().
	glutTimerFunc(100, myidle, 10);
}

void Reshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);                         //投影矩阵模式。
	glLoadIdentity();                                //矩阵堆栈清空。
	gluOrtho2D(-1.5*R*w / h, 1.5*R*w / h, -1.5*R, 1.5*R);  //设置裁剪窗口大小。
	glViewport(0, 0, w, h);                           //设置视区大小。
	glMatrixMode(GL_MODELVIEW);                       //模型矩阵模式。
}