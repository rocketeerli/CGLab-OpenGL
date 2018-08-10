// poloygon.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<glut.h>

void Display();
void Poloygon();
void Reshape(int w, int h);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);         //窗口左上角位置。
	glutInitWindowSize(800, 600);          //窗口大小。
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);         //设置双缓存。
	glutCreateWindow("多边形绘制");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMainLoop();

    return 0;
}
///绘图函数。
void Display() 
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Poloygon();
	glFlush();
}

void Poloygon()
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(-0.5, -0.5); //点P1,左下角
	glVertex2f(-0.5, 0.5);  //点P2,左上角
	glVertex2f(0.5, 0.5);   //点P3,右上角            
	glVertex2f(0.5, -0.5); //点P4,右下角
	glEnd();
}

void Reshape(int w, int h)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
