#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

int r = 8, c = 4;

float vertices[8][4] = {{70, 70, 50, 1},
                        {120, 70, 50, 1},
                        {120, 120, 50, 1},
                        {70, 120, 50, 1},
                        {50, 50, 0, 1},
                        {100, 50, 0, 1},
                        {100, 100, 0, 1},
                        {50, 100, 0, 1}};
float output[8][4];

void printPolygon(float vertices[8][4])
{
    // Printing the Coordinates
    for (int i = 0; i < r; i++)
    {
        cout <<setw(6)<<vertices[i][0] << " " <<setw(6)<< vertices[i][1] << " " <<setw(6)<< vertices[i][2] << endl;
    }

    // FACE ABCD
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++)
    {
        glVertex3i(vertices[i][0], vertices[i][1], vertices[i][2]);
    }
    glEnd();

    // Face ABFE
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP);
    glVertex3i(vertices[0][0], vertices[0][1], vertices[0][2]);
    glVertex3i(vertices[1][0], vertices[1][1], vertices[1][2]);
    glVertex3i(vertices[5][0], vertices[5][1], vertices[5][2]);
    glVertex3i(vertices[4][0], vertices[4][1], vertices[4][2]);
    glEnd();

    // Face CDHG
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex3i(vertices[2][0], vertices[2][1], vertices[2][2]);
    glVertex3i(vertices[3][0], vertices[3][1], vertices[3][2]);
    glVertex3i(vertices[7][0], vertices[7][1], vertices[7][2]);
    glVertex3i(vertices[6][0], vertices[6][1], vertices[6][2]);
    glEnd();

    // Face BCGF
    glColor3f(1, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex3i(vertices[1][0], vertices[1][1], vertices[1][2]);
    glVertex3i(vertices[2][0], vertices[2][1], vertices[2][2]);
    glVertex3i(vertices[6][0], vertices[6][1], vertices[6][2]);
    glVertex3i(vertices[5][0], vertices[5][1], vertices[5][2]);
    glEnd();

    // Face ADHE
    glColor3f(1, 1, 0.5);
    glBegin(GL_LINE_LOOP);
    glVertex3i(vertices[0][0], vertices[0][1], vertices[0][2]);
    glVertex3i(vertices[3][0], vertices[3][1], vertices[3][2]);
    glVertex3i(vertices[7][0], vertices[7][1], vertices[7][2]);
    glVertex3i(vertices[4][0], vertices[4][1], vertices[4][2]);
    glEnd();

    // FACE EFGH
    glColor3f(0, 1, 1);
    glBegin(GL_LINE_LOOP);
    for (int i = 4; i < r; i++)
    {
        glVertex3i(vertices[i][0], vertices[i][1], vertices[i][2]);
    }
    glEnd();
}

float radian(int degree)
{
    // converting degrees to radians
    return degree * 3.14159 / 180;
}

void multiply(float mat1[][4], float mat2[][4], float result[][4])
{
    int i, j, k;
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            result[i][j] = 0;
            for (k = 0; k < c; k++)
            {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void rotation(int angle, int axis)
{
    if (axis = 0)
    {
        // for x-axis
        float T[4][4] = {{1, 0, 0, 0},
                         {0, cos(radian(angle)), sin(radian(angle)), 0},
                         {0, -1 * sin(radian(angle)), cos(radian(angle)), 0},
                         {0, 0, 0, 1}};

        multiply(vertices, T, output);
    }
    else if (axis = 1)
    {
        // for y-axis
        float T[4][4] = {
            {cos(radian(angle)), 0, -1 * sin(radian(angle)), 0},
            {0, 1, 0, 0},
            {sin(radian(angle)), 0, cos(radian(angle)), 0},
            {0, 0, 0, 1}};

        multiply(vertices, T, output);
    }
    else if (axis = 2)
    {
        // for z-axis
        float T[4][4] = {
            {cos(radian(angle)), sin(radian(angle)), 0, 0},
            {-1 * sin(radian(angle)), cos(radian(angle)), 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}};

        multiply(vertices, T, output);
    }

    cout << "\nRotation coordinates: \n";
    glColor3f(0, 1, 0);
    printPolygon(output);
    glFlush();
}

void scaling(float a, float e, float j)
{
    float T[4][4] = {{a, 0, 0, 0},
                     {0, e, 0, 0},
                     {0, 0, j, 0},
                     {0, 0, 0, 1}};

    multiply(vertices, T, output);

    cout << "\nScaling coordinates: \n";
    glColor3f(0.5, 0, 0);
    printPolygon(output);
    glFlush();
}

void translation(float l, float m, float n)
{
    float T[4][4] = {{1, 0, 0, 0},
                     {0, 1, 0, 0},
                     {0, 0, 1, 0},
                     {l, m, n, 1}};

    multiply(vertices, T, output);

    cout << "\nTranslation coordinates: \n";
    glColor3f(0, 0.5, 0);
    printPolygon(output);
    glFlush();
}

void reflection(int plane)
{
    if (plane = 0)
    {
        // for xy-axis
        float T[4][4] = {{1, 0, 0, 0},
                         {0, 1, 0, 0},
                         {0, 0, -1, 0},
                         {0, 0, 0, 1}};

        multiply(vertices, T, output);
    }
    else if(plane = 1)
    {
        // for yz-axis
        float T[4][4] = {{-1, 0, 0, 0},
                         {0, 1, 0, 0},
                         {0, 0, 1, 0},
                         {0, 0, 0, 1}};

        multiply(vertices, T, output);

    }else if(plane = 2){
        // for xz-axis
        float T[4][4] = {{1, 0, 0, 0},
                         {0, -1, 0, 0},
                         {0, 0, 1, 0},
                         {0, 0, 0, 1}};

        multiply(vertices, T, output);
    }

    cout << "\nReflection coordinates: \n";
    glColor3f(0, 0, 1);
    printPolygon(output);
    glFlush();
}

void overAllScaling(float s)
{
    float T[4][4] = {{1 / s, 0, 0, 0},
                     {0, 1 / s, 0, 0},
                     {0, 0, 1 / s, 0},
                     {0, 0, 0, 1}};

    multiply(vertices, T, output);

    cout << "\nOverall Scaling coordinates: \n";
    glColor3f(0.7, 0.4, 0.5);
    printPolygon(output);
    glFlush();
}

void choices(unsigned char key, int x, int y)
{
    int c;
    cout << "\nEnter your choice: \n1. Rotation\n2. Scaling \n3. Translation \n4. Reflection \n5. Overall Scaling\n";
    cin >> c;

    switch (c)
    {
    case 1:
        int axis;
        cout << "\nEnter axis (0 -> x, 1 -> y, 2 -> z): " << endl;
        cin >> axis;

        int angle;
        cout << "\nEnter the value of angle: " << endl;
        cin >> angle;

        rotation(angle, axis);

        break;
    case 2:
        float a, e, j;
        cout << "\nEnter the value of a, e & j: " << endl;
        cin >> a >> e >> j;

        scaling(a, e, j);

        break;
    case 3:
        float l, m, n;
        cout << "\nEnter the value of l, m & n : " << endl;
        cin >> l >> m >> n;

        translation(l, m, n);

        break;
    case 4:
        int plane;
        cout << "\nEnter plane: (0 -> xy | 1 -> yz | 2 -> xz\n";
        cin >> plane;

        reflection(plane);

        break;
    case 5:
        float s;
        cout << "Enter the value of s for Overall Scaling: \n";
        cin >> s;

        overAllScaling(s);

        break;
    default:
        cout << "\nPlease enter a correct value";
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1, 0, 0);

    glBegin(GL_LINES);

    glVertex3i(-250, 0, 0);
    glVertex3i(250, 0, 0);

    glVertex3i(0, -250, 0);
    glVertex3i(0, 250, 0);

    glVertex3i(0, 0, -250);
    glVertex3i(0, 0, 250);

    glEnd();

    printPolygon(vertices);

    glFlush();
}

void init()
{
    glClearColor(1, 1, 1, 1);
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glOrtho(-250, 250, -250, 250, -250, 250);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("3D Transformation");
    glutDisplayFunc(display);

    glutKeyboardFunc(choices);
    init();
    glutMainLoop();

    return 0;
}
