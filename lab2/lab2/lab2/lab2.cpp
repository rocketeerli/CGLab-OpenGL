// lab2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<glut.h>
#include<math.h>

int flag = 2, cx = 150, cy = 150 , radius = 80, n = 5;
int ww, hh;

void Myinit();
void Display();
void DrawCircle(int cx, int cy, int radius);         //画圆。
void DrawPolygon(int n, int cx, int cy, int radius); //画多边形。
void DrawSampleCircle();                             //画胖圆。
void DrawLines();                                    //鼠标画线。
void Reshape(int w, int h);
void DrawOneLine(int xa, int ya, int xb, int yb);

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 800);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("基本图元的生成");

	Myinit();               //初始化。

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMainLoop();

    return 0;
}
///初始化。
void Myinit() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);        //设置背景色为黑色。
	glLineWidth(4.0);                            //设置线宽。
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);          //设置矩阵模式为模型变换模式，
	glLoadIdentity();                    //表示在世界坐标系下将当前矩阵设置为单位矩阵。

	if (flag == 1) {           //画圆。
		DrawCircle(cx, cy, radius);
	}
	else if (flag == 2) {      //画多边形。
		DrawPolygon(n, cx, cy, radius);
	}
	else if (flag == 3) {      //画胖圆。

	}
	else if (flag == 4) {      //鼠标画线。

	}
	glutSwapBuffers();
}
///画圆。
void DrawCircle(int cx, int cy, int radius) {
	glColor3f(1, 1, 1);
	glTranslatef(cx, cy, 0);
	glutWireSphere(radius, 40, 40);
}
///画多边形。
void DrawPolygon(int n, int cx, int cy, int radius) {
	int x[100], y[100];
	double angle;

	angle = 2 * 3.1415926 / n;
	glColor3f(1, 1, 1);
	for (int i = 0; i <= n; i++) {
		x[i] = (int)(cx + radius * cos(i*angle));
		y[i] = (int)(cy + radius * sin(i*angle));
	}
	for (int i = 0; i < n; i++) {
		DrawOneLine(x[i], y[i], x[i + 1], y[i + 1]);
	}
}
///画胖圆。
void DrawSampleCircle() {

}
///鼠标画线。
void DrawLines() {

}

void Reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluOrtho2D(0, w, 0, h);
	ww = w;
	hh = h;
	cx = w / 2;
	cy = h / 2;
}

void DrawOneLine(int xa, int ya, int xb, int yb) {
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
		glVertex2f(xa, ya);
		glVertex2f(xb, yb);
	glEnd();
}