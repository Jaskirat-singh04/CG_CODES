#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

float x_1, x_2, x, y_1, y_2, y;

void display()
{
    float dx = (x_2 - x_1);
    float dy = (y_2 - y_1);
    float m = dy / dx;

    float a = abs(dx);
    float b = abs(dy);

    float p;

    x = x_1;
    y = y_1;

    cout << "x  y  p" << endl;

    if (m > 0 && m < 1)
    {
        p = 2 * dy - dx;
        cout << round(x) << "," << round(y) << "," << p << endl;
        glBegin(GL_POINTS);
        glVertex2i(round(x), round(y));
        glEnd();

        while (a)
        {
            if (p <= 0)
            {
                x = x + 1;
                y = y;
                p = p + 2 * dy;
            }
            else
            {
                x = x + 1;
                y = y + 1;
                p = p + 2 * dy - 2 * dx;
            }

            cout << round(x) << "," << round(y) << "," << p << endl;
            glBegin(GL_POINTS);
            glVertex2i(round(x), round(y));
            glEnd();

            a--;
        }
    }

    else if (m > -1 && m < 0)
    {
        p = -2 * dy - dx;
        cout << round(x) << "," << round(y) << "," << p << endl;
        glBegin(GL_POINTS);
        glVertex2i(round(x), round(y));
        glEnd();

        while (a)
        {
            if (p <= 0)
            {
                x = x + 1;
                y = y;
                p = p - 2 * dy;
            }
            else
            {
                x = x + 1;
                y = y - 1;
                p = p - 2 * dy - 2 * dx;
            }

            cout << round(x) << "," << round(y) << "," << p << endl;
            glBegin(GL_POINTS);
            glVertex2i(round(x), round(y));
            glEnd();

            a--;
        }
    }

    else if (m > 1)
    {
        p = 2 * dx - dy;
        cout << round(x) << "," << round(y) << "," << p << endl;
        glBegin(GL_POINTS);
        glVertex2i(round(x), round(y));
        glEnd();

        while (b)
        {
            if (p <= 0)
            {
                x = x;
                y = y + 1;
                p = p + 2 * dx;
            }
            else
            {
                x = x + 1;
                y = y + 1;
                p = p - 2 * dx;
            }

            cout << round(x) << "," << round(y) << "," << p << endl;
            glBegin(GL_POINTS);
            glVertex2i(round(x), round(y));
            glEnd();

            b--;
        }
    }

    else if (m < -1)
    {
        p = -2 * dx - dy;
        cout << round(x) << "," << round(y) << "," << p << endl;
        glBegin(GL_POINTS);
        glVertex2i(round(x), round(y));
        glEnd();

        while (b)
        {
            if (p <= 0)
            {
                x = x + 1;
                y = y - 1;
                p = p - 2 * dx - 2 * dy;
            }
            else
            {
                x = x;
                y = y - 1;
                p = p - 2 * dx;
            }

            cout << round(x) << "," << round(y) << "," << p << endl;
            glBegin(GL_POINTS);
            glVertex2i(round(x), round(y));
            glEnd();

            b--;
        }
    }

    else
    {
    }

    glFlush();
}

void init()
{
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
    cout << "Enter the value of (x1,y1) and (x2,y2) : ";
    cin >> x_1 >> y_1 >> x_2 >> y_2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("bresenhem");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}