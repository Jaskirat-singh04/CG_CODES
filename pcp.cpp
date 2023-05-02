#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// command: g++ pcp.cpp -o pcp -mconsole glut32.lib -lopengl32 -lglu32
class Point
{
public:
    float x;
    float y;

    Point() {}

    Point(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
};

class Edge
{
public:
    Point start;
    Point end;

    Edge() {}
    Edge(Point s, Point e)
    {
        this->start = s;
        this->end = e;
    }
};

vector<Point> org_vertices;
float xmin, ymin, xmax, ymax;
vector<Point> out_vertices;

bool Inside(Point &testVertex, Edge &clipEdge)
{
    return ((clipEdge.end.x - clipEdge.start.x) * (testVertex.y - clipEdge.start.y) -
            (clipEdge.end.y - clipEdge.start.y) * (testVertex.x - clipEdge.start.x)) >= 0;
}

Point Intersect(Point &first, Point &second, Edge &clipEdge)
{
    // float x1 = first.x, y1 = first.y, x2 = second.x, y2 = second.y;
    // float x3 = clipEdge.start.x, y3 = clipEdge.start.y, x4 = clipEdge.end.x, y4 = clipEdge.end.y;

    // float m1 = (y2 - y1) / (x2 - x1);
    // float b1 = y1 - m1 * x1;

    // float m2 = (y4 - y3) / (x4 - x3);
    // float b2 = y3 - m2 * x3;

    // float x = (b2 - b1) / (m1 - m2);
    // float y = m1 * x + b1;

    // return Point(x, y);

    Point intersectPt;

    float dx = second.x - first.x;
    float dy = second.y - first.y;
    float clipDx = clipEdge.end.x - clipEdge.start.x;
    float clipDy = clipEdge.end.y - clipEdge.start.y;

    float t = ((clipEdge.start.x - first.x) * clipDy - (clipEdge.start.y - first.y) * clipDx) / (dx * clipDy - dy * clipDx);

    intersectPt.x = first.x + t * dx;
    intersectPt.y = first.y + t * dy;

    return intersectPt;
}

void clip_polygon(vector<Edge> &clipEdges)
{
    out_vertices = org_vertices;

    for (Edge &clipEdge : clipEdges)
    {
        vector<Point> inVertices = out_vertices;
        out_vertices.clear();

        if (inVertices.empty())
        {
            break;
        }

        Point s = inVertices.back();
        for (Point &p : inVertices)
        {
            if (Inside(p, clipEdge))
            {
                if (Inside(s, clipEdge))
                {
                    out_vertices.push_back(p);
                }
                else
                {
                    Point intersection = Intersect(s, p, clipEdge);
                    out_vertices.push_back(intersection);
                    out_vertices.push_back(p);
                }
            }
            else
            {
                if (Inside(s, clipEdge))
                {
                    Point intersection = Intersect(s, p, clipEdge);
                    out_vertices.push_back(intersection);
                }
            }

            s = p;
        }
    }
}

void display()
{
    glBegin(GL_LINE_LOOP);

    glVertex2i(xmin, ymin);
    glVertex2i(xmax, ymin);
    glVertex2i(xmax, ymax);
    glVertex2i(xmin, ymax);

    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < org_vertices.size(); i++)
    {
        Point p = org_vertices[i];
        glVertex2i(p.x, p.y);
    }
    glEnd();

    glFlush();
}

void startClipping(unsigned char key, int x, int y)
{
    vector<Edge> clipEdges;
    clipEdges.push_back(Edge(Point(xmin, ymin), Point(xmax, ymin)));
    clipEdges.push_back(Edge(Point(xmax, ymin), Point(xmax, ymax)));
    clipEdges.push_back(Edge(Point(xmax, ymax), Point(xmin, ymax)));
    clipEdges.push_back(Edge(Point(xmin, ymax), Point(xmin, ymin)));

    clip_polygon(clipEdges);

    cout << "\nClipped Polygon Vertices: \n";
    for (int i = 0; i < out_vertices.size(); i++)
    {
        Point p = out_vertices[i];
        cout << p.x << " " << p.y << endl;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINE_LOOP);

    glVertex2i(xmin, ymin);
    glVertex2i(xmax, ymin);
    glVertex2i(xmax, ymax);
    glVertex2i(xmin, ymax);

    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < out_vertices.size(); i++)
    {
        Point p = out_vertices[i];
        glVertex2i(p.x, p.y);
    }
    glEnd();

    glFlush();
}

void init()
{
    glClearColor(0.000, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, -1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char *argv[])
{
    int n;
    cout << "\nEnter number of vertices in the polygon\n";
    cin >> n;

    cout << "Enter vertices of the polygon one by one: \n";
    while (n--)
    {
        float x, y;
        cin >> x >> y;

        org_vertices.push_back(Point(x, y));
    }

    cout << "\nEnter xmin, ymin, xmax, ymax: \n";
    cin >> xmin >> ymin >> xmax >> ymax;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Polygon Clipping");
    glutDisplayFunc(display);

    glutKeyboardFunc(startClipping);
    init();
    glutMainLoop();

    return 0;
}