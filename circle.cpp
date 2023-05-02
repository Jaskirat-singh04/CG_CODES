#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

float xi, yi, r;

void display()
{
    float x = 0;
    float y = r;

    float p = 1 - r;
    cout << "x  y  p" << endl;

    cout << round(x) << "," << round(y) << "," << p << endl;
    glBegin(GL_POINTS);
    glVertex2i(round(x) + xi, round(y) + yi);
    glVertex2i(round(y) + xi, round(x) + yi);
    glVertex2i(round(y) + xi, round(-x) + yi);
    glVertex2i(round(x) + xi, round(-y) + yi);
    glEnd();

    while (x < y)
    {
        if (p < 0)
        {
            x = x + 1;
            y = y;
            p = p + 2 * x + 1;
        }
        else
        {
            x = x + 1;
            y = y - 1;
            p = p + 2 * x + 1 - 2 * y;
        }

        cout << round(x) << "," << round(y) << "," << p << endl;
        glBegin(GL_POINTS);
        glVertex2i(round(x) + xi, round(y) + yi);
        glVertex2i(round(y) + xi, round(x) + yi);
        glVertex2i(round(y) + xi, round(-x) + yi);
        glVertex2i(round(x) + xi, round(-y) + yi);
        glVertex2i(round(-x) + xi, round(-y) + yi);
        glVertex2i(round(-y) + xi, round(-x) + yi);
        glVertex2i(round(-y) + xi, round(x) + yi);
        glVertex2i(round(-x) + xi, round(y) + yi);
        glEnd();
    }

    glFlush();
}

void init()
{
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 480, 0, 480);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
    cout << "Enter radius and midpoint(x,y)... : ";
    cin >> r >> xi >> yi;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("circle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}