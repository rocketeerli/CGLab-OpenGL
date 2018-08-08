// lab2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<glut.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

#define N 1000

int flag = 1, cx = 150, cy = 150 , radius = 80, n = 5, samples = 10,ri = 50;
int ww, hh;
int line[N][4], k = 0;

void Myinit();
void Display();                      //绘画函数。
void DrawCircle(int cx, int cy, int radius);                                //画圆。
void DrawPolygon(int n, int cx, int cy, int radius);                        //画多边形。
void DrawSampleCircle(int inner, int outer, int samples, int cx, int cy);   //画圆环。
void DrawLines();                                                           //鼠标画线。
void Reshape(int w, int h);
void DrawOneLine(int xa, int ya, int xb, int yb);         //辅助函数，只画一条线。
void myMouse(int button, int state, int x, int y);        //鼠标按钮响应事件。
void Keyboard(unsigned char key, int x, int y);           //键盘响应函数。
void myMotion(int x, int y);                              //获得鼠标移动时的坐标。

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("基本图元的生成");

	Myinit();               //初始化。

	glutDisplayFunc(Display);          //注册绘制响应回调函数。
	glutReshapeFunc(Reshape);          //注册窗口改变回调函数。
	glutMouseFunc(myMouse);            //注册鼠标按钮回调函数。
	glutKeyboardFunc(Keyboard);        //注册键盘响应回调函数。
	glutMotionFunc(myMotion);          //注册鼠标移动回调函数。

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
	else if (flag == 3) {      //画圆环。
		DrawSampleCircle(ri, radius, samples, cx, cy);
	}
	else if (flag == 4) {      //鼠标画线。
		DrawLines();
	}
	glutSwapBuffers();
}
///键盘响应函数。
void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		flag = 1;       //画圆。
		break;
	case '2':
		flag = 2;       //画多边形。
		break;
	case '3':
		flag = 3;       //画圆环。
		break;
	case '4':
		flag = 4;       //鼠标画线。
		//更新line数组内的数据。
		for (int i = 0; i < k;i++) {
			for (int j = 0; j < 4; j++) {
				line[i][j] = 0;
			}
		}
		k = 0;
		break;
	case 'r':                               //圆的半径递减。
		if (flag == 1 && radius > 1) {
			radius--;
		}
		else if (flag == 3 && radius > 1) {
			radius--;
		}
		break;
	case 'R':
		if (radius < cx && radius < cy) {         //未超边框。
			radius++;                            //半径递增。
		}
		break;
	case 'n':
		if (flag == 2 && n > 3){
			n--;                           //多边形边数递减。
		}
		break;
	case 'N':
		if (flag == 2) {
			n++;                          //多边形边数递增。
		}
		break;
	case 'i':
		if (flag == 3 && ri > 1) {
			ri--;                      //圆环内半径递减。
		}
		break;
	case 'I':
		if (flag == 3 && ri < radius) {
			ri++;                     //圆环内半径递增。
		}
		break;
	case 's':
		if (samples > 1) {
			samples--;               //圆环反走样采样数递减。
		}
		break;
	case 'S':
		samples++;                  //圆环反走样采样数递增。
		break;
	case 'a':
		glDisable(GL_BLEND);
		glDisable(GL_LINE_SMOOTH);
		glDisable(GL_POINT_SMOOTH);
		glDisable(GL_POLYGON_SMOOTH);
		break;
	case 'A':
		//启用反走样。
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_POINT_SMOOTH);
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_POLYGON_SMOOTH);
		break;
	case 27:
		exit(0);
	default:
		break;
	}
}

///画圆。
void DrawCircle(int cx, int cy, int radius) {
	glColor3f(1, 1, 1);
	glTranslatef(cx, cy, 0);
	glutWireSphere(radius, 40, 40);
	glutPostRedisplay();
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
	glutPostRedisplay();
}
///画圆环。
void DrawSampleCircle(int inner, int outer, int samples, int cx, int cy) {
	float r2, ro2, ri2;
	int i,j, nx, ny;
	float color_value;
	int count;

	ro2 = outer * outer;
	ri2 = inner * inner;

	for (i = 0; i < outer; i++) {
		for (j = 0; j <= outer; j++) {
			count = 0;
			//每个点切成samples*samples个子像素
			//判断子像素是否在胖圆内。
			for (nx = 0; nx < samples; nx++) {
				for (ny = 0; ny < samples; ny++) {
					float r2_1 = (i + (float)nx / (float)samples) * (i + (float)nx / (float)samples);
					float r2_2 = (j + (float)ny / (float)samples) * (j + (float)ny / (float)samples);
					r2 = r2_1 + r2_2;

					//计算合格的子像素。
					if (r2 <= ro2 && r2 >= ri2) {
						count++;
					}
				}
			}
			//计算每个像素的亮度等级。
			color_value = ((float)count) / (float)(samples * samples);
			glColor3f(color_value, color_value, color_value);

			//对称画点。
			glBegin(GL_POINTS);
				glVertex2f(cx + i, cy + j);
				glVertex2f(cx + i, cy - j);
				glVertex2f(cx - i, cy + j);
				glVertex2f(cx - i, cy - j);
			glEnd();
		}
	}
	glutPostRedisplay();
}
///鼠标画线。
void DrawLines() {
	for (int i = 0; i <= k; i++) {
		DrawOneLine(line[i][0], line[i][1], line[i][2], line[i][3]);
	}
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
///画一条线。
void DrawOneLine(int xa, int ya, int xb, int yb) {
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
		glVertex2f(xa, ya);
		glVertex2f(xb, yb);
	glEnd();
}

///鼠标按钮响应事件。
void myMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		line[k][0] = x;             //线段起点x坐标。
		line[k][1] = hh - y;        //线段起点y坐标。
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		line[k][2] = x;
		line[k][3] = hh - y;
		if (flag == 4){
			k++;
		}
		glutPostRedisplay();
	}
}

///获得鼠标移动时的坐标。
void myMotion(int x, int y) {
	line[k][2] = x;
	line[k][3] = hh - y;
	glutPostRedisplay();
}