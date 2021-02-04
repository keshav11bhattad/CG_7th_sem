#include<gl/glut.h>
#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<Windows.h>

int n, m;
int wx = 500, wy = 500;
float x[120], y[120];
static float intx[100] = {0}; // x intercepts of polygon with scanline


void draw_line(float x1, float y1, float x2, float y2) {
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();
	glFlush();
}

// finds the intersection of scanline with each edge of a polygon
void edgeDetect(float x1, float y1, float x2, float y2, int scanline) {
	float temp;
	if (y2 < y1) {
		temp = x1; x1 = x2; x2 = temp;
		temp = y1; y1 = y2; y2 = temp;
	}
	if (scanline > y1 && scanline < y2)
		intx[m++] = x1 + (scanline - y1) * (x2 - x1) / (y2 - y1);
}

// implements scan-line area fill algorithm
void scanfill(float x[], float y[]) {
	for (int s1 = 0; s1 <= wy; s1++) {
		m = 0;
		for (int i = 0; i < n; i++)	
			edgeDetect(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n], s1);
		std::sort(intx, (intx + m));
		if (m >= 2)
			for (int i = 0; i < m; i = i + 2)	
				draw_line(intx[i], s1, intx[i + 1], s1);
	}
}


void myInit() {
	glClearColor(1, 1, 1, 1);
	glPointSize(1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, wx, 0, wy);
}

void display_filled_polygon() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2);
	glColor3f(1, 0, 0);
	//draw the boundary of the polygon
	glBegin(GL_LINE_LOOP);
		for (int i = 0; i < n; i++)	glVertex2f(x[i], y[i]);
	glEnd();
	glColor3f(0, 0, 1);
	scanfill(x, y);
}

int main(int argc, char* argv[]) {
	printf_s("Enter no. of sides: ");
	scanf_s("%d", &n);
	printf_s("Enter coordinates of endpoints: \n");
	for (int i = 0; i < n; i++){
		printf_s("X-coord Y-coord: ");
		scanf_s("%f %f", &x[i], &y[i]);
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(wx, wy);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Scanline fill algorithm");
	glutDisplayFunc(display_filled_polygon);
	myInit();
	glutMainLoop();
}
