// keyboardLab.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <glut.h>

float x1 = -0.5, y1 = -0.5, x2 = 0.5, y2 = 0.5;

void display();
void myKeyboard(unsigned char key, int x, int y);
void myReshape(GLsizei w, GLsizei h);

int main(int argv, char** argc)
{
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(30, 20);
	glutInitWindowSize(800, 600);
	glutCreateWindow("实验四——键盘交互");
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboard);
	glutReshapeFunc(myReshape);

	glutMainLoop();
    return 0;
}

void display()
{
	glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glRectf(x1, y1, x2, y2);
	glFlush();
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	case 'W':
		y1 += 0.1;
		y2 += 0.1;
		break;
	case 'a':
	case 'A':
		x1 -= 0.1;
		x2 -= 0.1;
		break;
	case 's':
	case 'S':
		y1 -= 0.1;
		y2 -= 0.1;
		break;
	case 'd':
	case 'D':
		x1 += 0.1;
		x2 += 0.1;
		break;
	default:
		break;
	}
//	glColor3f(1, 0, 0);
//	glRasterPos2i((x1 + x2) / 2, (y1 + y2) / 2);
//	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'L');
	glutPostRedisplay();
}

void myReshape(GLsizei w, GLsizei h)
{
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(0, 300, 0, 300);
//	glMatrixMode(GL_MODELVIEW);                       //模型矩阵模式。
}