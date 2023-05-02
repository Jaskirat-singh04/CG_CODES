#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

int **arr;
float m, n, s, theta, a, b, c, d;
int ch, ne;
float **R;

void multiply(int **arr, float T[3][3])
{
    R = new float *[ne];
    for (int i = 0; i < ne; i++)
    {
        R[i] = new float[3];
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                R[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < ne; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                R[i][j] += arr[i][k] * T[k][j];
            }
        }
    }
}

void translate()
{
    cout << "\nEnter translation points... ";
    cin >> m >> n;

    float T[3][3] = {{1, 0, 0}, {0, 1, 0}, {m, n, 1}};
    multiply(arr, T);
}

void rotate()
{
    cout << "\nEnter theta... ";
    cin >> theta;
    theta = theta * (3.14 / 180);

    float T[3][3] = {{cos(theta), sin(theta), 0}, {-sin(theta), cos(theta), 0}, {0, 0, 1}};
    multiply(arr, T);
}

void reflect()
{
    cout << "\nEnter reflection parameters... ";
    cin >> a >> b >> c >> d;

    float T[3][3] = {{a, b, 0}, {c, d, 0}, {0, 0, 1}};
    multiply(arr, T);
}

void scale()
{
    cout << "\nEnter a and d... ";
    cin >> a >> d;

    float T[3][3] = {{a, 0, 0}, {0, d, 0}, {0, 0, 1}};
    multiply(arr, T);
}

void overallscale()
{
    cout << "\nEnter s... ";
    cin >> s;

    float T[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, s}};
    multiply(arr, T);

    for (int i = 0; i < ne; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            R[i][j] /= s;
        }
    }
}

void display()
{
    do
    {
        cout << "\nMENU";
        cout << "\n0. Translate";
        cout << "\n1. Rotate";
        cout << "\n2. Reflect";
        cout << "\n3. Scale";
        cout << "\n4. Overall Scale";
        cout << "\n5. exit";
        cout << "\nEnter your choice... ";
        cin >> ch;

        switch (ch)
        {
        case 0:
            translate();
            break;
        case 1:
            rotate();
            break;
        case 2:
            reflect();
            break;
        case 3:
            scale();
            break;
        case 4:
            overallscale();
            break;
        default:
            exit(100);
            break;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_LINES);
        glVertex2i(-480, 0);
        glVertex2i(480, 0);
        glEnd();

        glBegin(GL_LINES);
        glVertex2i(0, -480);
        glVertex2i(0, 480);
        glEnd();

        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < ne; i++)
        {
            glVertex2i(arr[i][0], arr[i][1]);
        }
        glEnd();

        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < ne; i++)
        {
            glVertex2i(R[i][0], R[i][1]);
        }
        glEnd();
        glFlush();

    } while (ch >= 0 && ch < 5);

    glFlush();
}

void init()
{
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-480, 480, -480, 480);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
    cout << "Enter number of vertices... ";
    cin >> ne;

    cout << "Enter vertices... ";
    arr = new int *[ne];
    for (int i = 0; i < ne; i++)
    {
        arr[i] = new int[3];
        for (int j = 0; j < 3; j++)
        {
            cin >> arr[i][j];
        }
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Transformations");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}