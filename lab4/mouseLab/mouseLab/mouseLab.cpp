// mouseLab.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <glut.h>

#define N 1000
int ww, hh;
int line[N][4];
int k = 0;

void init();
void display();
void myMouse(int button, int state, int x, int y);
void myMotion(int x, int y);
void myReshape(int w, int h);
void drawLines();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 40);
	glutInitWindowSize(800, 600);
	glutCreateWindow("鼠标交互");

	init();
	glutDisplayFunc(display);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);
	glutReshapeFunc(myReshape);

	glutMainLoop();
    return 0;
}

void init()
{
	glClearColor(0, 0, 0, 0);
	glLineWidth(4.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawLines();
	glutSwapBuffers();
}

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		line[k][0] = x;
		line[k][1] = hh - y;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		line[k][2] = x;
		line[k][3] = hh - y;
		k++;
		glutPostRedisplay();
	}
}

void myMotion(int x, int y)
{
	line[k][2] = x;
	line[k][3] = hh - y;
	glutPostRedisplay();
}

void myReshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluOrtho2D(0, w, 0, h);
	ww = w;
	hh = h;
}

void drawLines()
{
	for (int i = 0; i <= k; i++)
	{
		glBegin(GL_LINES);
		glVertex2f(line[i][0], line[i][1]);
		glVertex2f(line[i][2], line[i][3]);
		glEnd();
	}
}