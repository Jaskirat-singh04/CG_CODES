#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

float xi, yi, a, b;

void display()
{
    float x = 0;
    float y = b;
    float xp, yp;

    cout << "x  y  p" << endl;
    float p = (b * b) - (a * a * b) + ((a * a) / 4);

    cout << round(x) << "," << round(y) << "," << p << endl;
    glBegin(GL_POINTS);
    glVertex2i(round(x) + xi, round(y) + yi);
    glVertex2i(round(x) + xi, round(-y) + yi);
    glEnd();

    while ((a * a * y) > (b * b * x))
    {
        cout << round(x) << "," << round(y) << "," << p << endl;

        if (p < 0)
        {
            p = p + (2 * b * b * x) + (3 * b * b);
            xp = x;
            yp = y;
            x = x + 1;
            y = y;
        }
        else
        {
            p = p + (2 * b * b * x) + (3 * b * b) - (2 * a * a * y) + (2 * a * a);
            xp = x;
            yp = y;
            x = x + 1;
            y = y - 1;
        }

        glBegin(GL_POINTS);
        glVertex2i(round(xp) + xi, round(yp) + yi);
        glVertex2i(round(xp) + xi, round(-yp) + yi);
        glVertex2i(round(-xp) + xi, round(-yp) + yi);
        glVertex2i(round(-xp) + xi, round(yp) + yi);
        glEnd();
    }

    x = xp;
    y = yp;
    p = ((b * b) * (x + 0.5) * (x + 0.5)) + ((a * a) * (y - 1) * (y - 1)) - (a * a * b * b);

    while (y > 0)
    {
        cout << round(x) << "," << round(y) << "," << p << endl;

        if (p < 0)
        {
            p = p + (2 * b * b * x) + (2 * b * b) - (2 * a * a * y) + (3 * a * a);
            x = x + 1;
            y = y - 1;
        }
        else
        {
            p = p - (2 * a * a * y) + (3 * a * a);
            x = x;
            y = y - 1;
        }

        glBegin(GL_POINTS);
        glVertex2i(round(x) + xi, round(y) + yi);
        glVertex2i(round(x) + xi, round(-y) + yi);
        glVertex2i(round(-x) + xi, round(-y) + yi);
        glVertex2i(round(-x) + xi, round(y) + yi);
        glEnd();
    }

    cout << round(x) << "," << round(y) << endl;
    glBegin(GL_POINTS);
    glVertex2i(round(x) + xi, round(y) + yi);
    glVertex2i(round(-x) + xi, round(y) + yi);
    glEnd();

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
    cout << "Enter (a,b) and midpoint(x,y)... : ";
    cin >> a >> b >> xi >> yi;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("ellipse");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}