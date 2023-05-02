#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

int P1[2], P4[2], P2[2], P3[2], R1[2], R4[2];
float x, y;

void hermite()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2i(-250, 0);
    glVertex2i(250, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(0, -250);
    glVertex2i(0, 250);
    glEnd();

    for (float t = 0; t <= 1; t += 0.01)
    {

        x = (2 * pow(t, 3) - 3 * pow(t, 2) + 1) * P1[0] + (-2 * pow(t, 3) + 3 * pow(t, 2)) * P4[0] + (pow(t, 3) - 2 * pow(t, 2) + t) * R1[0] + (pow(t, 3) - pow(t, 2)) * R4[0];
        y = (2 * pow(t, 3) - 3 * pow(t, 2) + 1) * P1[1] + (-2 * pow(t, 3) + 3 * pow(t, 2)) * P4[1] + (pow(t, 3) - 2 * pow(t, 2) + t) * R1[1] + (pow(t, 3) - pow(t, 2)) * R4[1];

        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
    }
}

void bezier()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2i(-250, 0);
    glVertex2i(250, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(0, -250);
    glVertex2i(0, 250);
    glEnd();

    for (float t = 0; t <= 1; t = t + .01)
    {
        x = pow((1 - t), 3) * P1[0] + 3 * t * (1 - pow(t, 2)) * P2[0] + 3 * pow(t, 2) * (1 - t) * P3[0] + pow(t, 3) * P4[0];
        y = pow((1 - t), 3) * P1[1] + 3 * t * (1 - pow(t, 2)) * P2[1] + 3 * pow(t, 2) * (1 - t) * P3[1] + pow(t, 3) * P4[1];

        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
    }
}

void choices(unsigned char key, int x, int y)
{
    int c;
    cout << "\nEnter your choice: \n1. Hermite\n2. Bezier \n";
    cin >> c;

    switch (c)
    {
    case 1:
        cout << "\nEnter Points... (P1, P4, R1, R4)";
        cin >> P1[0] >> P1[1] >> P4[0] >> P4[1] >> R1[0] >> R1[1] >> R4[0] >> R4[1];
        // 20 20 60 80 120 100 10 30
        hermite();
        break;
    case 2:
        cout << "\nEnter Points... (P1, P2, P3, P4)";
        cin >> P1[0] >> P1[1] >> P2[0] >> P2[1] >> P3[0] >> P3[1] >> P4[0] >> P4[1];
        // 20 20 60 80 10 30 120 100
        bezier();
        break;

    default:
        cout << "\nPlease enter a correct value";
    }

    glFlush();
}

void display()
{
    glBegin(GL_LINES);
    glVertex2i(-250, 0);
    glVertex2i(250, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(0, -250);
    glVertex2i(0, 250);
    glEnd();

    glFlush();
}

void init()
{
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Curves");
    glutDisplayFunc(display);

    glutKeyboardFunc(choices);
    init();
    glutMainLoop();

    return 0;
}
