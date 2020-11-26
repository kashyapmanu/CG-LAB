
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
GLfloat wh=500, ww=500;
GLfloat size=10.0;

void init()
{

    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,1,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,ww,0,wh);

}

void myReshape(GLint w, GLint h)
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,(w),0.0,(h));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w,h);
    ww=w;
    wh=h;

}
void draw(int x, int y)
{

    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    y=wh-y;
    glBegin(GL_POLYGON);
    glVertex2f(x+size, y+size);
    glVertex2f(x-size, y+size);
    glVertex2f(x-size, y-size);
    glVertex2f(x+size, y-size);
    glEnd();
    glFlush();
}

void mymouse(int btn, int state, int x, int y)
{

    if(btn==GLUT_RIGHT_BUTTON && state== GLUT_DOWN)
        draw(x,y);


}

void display()
{

    glClearColor(1,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);

    glFlush();

}



int main(int argc, char ** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
    glutInitWindowSize(wh,ww);
    glutInitWindowPosition(0,0);
    glutCreateWindow("NITTE");
    init();
    glutDisplayFunc(display);

    glutMouseFunc(mymouse);
    glutReshapeFunc(myReshape);
    glutMainLoop();

}
