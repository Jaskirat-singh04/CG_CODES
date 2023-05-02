#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

float x_1, x_2, x, y_1, y_2, y;

void display()
{
    float m = (y_2 - y_1) / (x_2 - x_1);

    x = x_1;
    y = y_1;

    if (abs(m) < 1)
    {
        while (x != x_2)
        {
            cout << x << "," << y << endl;

            glBegin(GL_POINTS);
            glVertex2i(round(x), round(y));
            glEnd();

            x = x + 1;
            y = y + m;
        }
    }
    else if (abs(m) > 1)
    {
        while (y != y_2)
        {
            cout << x << "," << y << endl;

            glBegin(GL_POINTS);
            glVertex2i(round(x), round(y));
            glEnd();

            x = x + (1 / m);
            y = y + 1;
        }
    }
    else
    {
        while (x != x_2 && y != y_2)
        {
            cout << x << "," << y << endl;

            glBegin(GL_POINTS);
            glVertex2i(round(x), round(y));
            glEnd();

            x = x + 1;
            y = y + 1;
        }
    }

    cout << x << "," << y << endl;

    glBegin(GL_POINTS);
    glVertex2i(round(x), round(y));
    glEnd();

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
    glutCreateWindow("DDA Line Algo");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}