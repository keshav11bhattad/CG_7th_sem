#include<glut/glut.h>

void display(){
	glClearColor(0.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

int main(int argc, char** argv){
	glutInit(&argc,argv);
	glutCreateWindow("Sample 1");
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutDisplayFunc(display);
	glutMainLoop();
}