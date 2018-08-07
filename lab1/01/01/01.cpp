// 01.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<glut.h>

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   //设置清屏颜色
	glClear(GL_COLOR_BUFFER_BIT);   //刷新颜色缓存区。

	glFlush();    //用于刷新命令队列和缓存区，使所有尚未被执行的OpenGL命令得到执行。
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);                          //初始化glut库。
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    //设置显示模式：（缓存，颜色类型）
	glutInitWindowSize(500, 600);                   //绘图窗口大小。
	glutInitWindowPosition(1024 / 2 - 250, 768 / 2 - 250);   //设置窗口左上角在屏幕的位置。

	glutCreateWindow("暑假的第一个OpenGL程序");       //创建窗口，参数为标题。

	glutDisplayFunc(display);                         //绘制当前窗口。

	glutMainLoop();                                  //表示开始运行程序，用于程序的结尾。
}

