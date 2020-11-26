#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>

typedef int Outcode;

const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;
int xmin, ymin, xmax, ymax, x0, a, x1, b;

void init()
{
	glClearColor(1, 2, 3, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
}

Outcode Computecode(double x, double y)
{
	Outcode code = INSIDE;

	if (x < xmin)
		code |= LEFT;
	else if (x > xmax)
		code |= RIGHT;
	else if (y < ymin)
		code |= BOTTOM;
	else if (y > ymax)
		code |= TOP;

	return code;
}

void CohenSutherlandline()
{

	bool accept = false;
	Outcode outcode0 = Computecode(x0, a);
	Outcode outcode1 = Computecode(x1, b);
	double x, y;

	while (true)
	{
		if (!(outcode0 | outcode1))
		{
			accept = true;
			break;
		}
		else if (outcode0 & outcode1)
		{
			break;
		}
		else
		{

			Outcode outcodeout = outcode0 ? outcode0 : outcode1;
			if (outcodeout & TOP)
			{
				x = x0 + (x1 - x0) * (ymax - a) / (b - a);
				y = ymax;
			}
			else if (outcodeout & BOTTOM)
			{
				x = x0 + (x1 - x0) * (ymin - a) / (b - a);
				y = ymin;
			}
			else if (outcodeout & RIGHT)
			{
				y = a + (b - a) * (xmax - x0) / (x1 - x0);
				x = xmax;
			}
			else if (outcodeout & LEFT)
			{
				y = a + (b - a) * (xmin - x0) / (x1 - x0);
				x = xmin;
			}
			if (outcodeout == outcode0)
			{
				x0 = x;
				a = y;
				outcode0 = Computecode(x0, a);
			}
			else
			{
				x1 = x;
				b = y;
				outcode1 = Computecode(x1, b);
			}
		}
	}
	if (accept)
	{
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(4 * xmin, 4 * ymin);
		glVertex2f(4 * xmax, 4 * ymin);
		glVertex2f(4 * xmax, 4 * ymax);
		glVertex2f(4 * xmin, 4 * ymax);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(4 * x0, 4 * a);
		glVertex2f(4 * x1, 4 * b);
		glEnd();
	}
}

void display()
{
	//double x0=60,a=20,x1=80,b=120;
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(xmin, ymin);
	glVertex2f(xmax, ymin);
	glVertex2f(xmax, ymax);
	glVertex2f(xmin, ymax);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(x0, a);
	glVertex2f(x1, b);
	glEnd();

	CohenSutherlandline(x0, a, x1, b);
	glFlush();
}

int main(int argc, char **argv)
{
	printf("Enter the window coordinates");
	scanf("%d%d%d%d", &xmin, &ymin, &xmax, &ymax);
	printf("Enter End Points:");
	scanf("%d%d%d%d", &x0, &a, &x1, &b);
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Cohen Sutherland line clipping window");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
