#include <graphics.h>
#include <conio.h>
#include <math.h>

typedef struct
{
    int x, y, z;
} Point3D;

void drawLine3D(Point3D p1, Point3D p2, int scale, int offsetX, int offsetY)
{
    // Perspective projection
    int x1_2d = p1.x * scale / (p1.z + scale) + offsetX;
    int y1_2d = p1.y * scale / (p1.z + scale) + offsetY;
    int x2_2d = p2.x * scale / (p2.z + scale) + offsetX;
    int y2_2d = p2.y * scale / (p2.z + scale) + offsetY;

    // Draw the line
    line(x1_2d, y1_2d, x2_2d, y2_2d);
}

void drawCube(Point3D points[], int scale, int offsetX, int offsetY)
{
    // Draw front face
    drawLine3D(points[0], points[1], scale, offsetX, offsetY);
    drawLine3D(points[1], points[2], scale, offsetX, offsetY);
    drawLine3D(points[2], points[3], scale, offsetX, offsetY);
    drawLine3D(points[3], points[0], scale, offsetX, offsetY);

    // Draw back face
    drawLine3D(points[4], points[5], scale, offsetX, offsetY);
    drawLine3D(points[5], points[6], scale, offsetX, offsetY);
    drawLine3D(points[6], points[7], scale, offsetX, offsetY);
    drawLine3D(points[7], points[4], scale, offsetX, offsetY);

    // Connect front and back faces
    drawLine3D(points[0], points[4], scale, offsetX, offsetY);
    drawLine3D(points[1], points[5], scale, offsetX, offsetY);
    drawLine3D(points[2], points[6], scale, offsetX, offsetY);
    drawLine3D(points[3], points[7], scale, offsetX, offsetY);
}

void translate(Point3D points[], int tx, int ty, int tz, int numPoints)
{
    int i;
    for (i = 0; i < numPoints; i++)
    {
        points[i].x += tx;
        points[i].y += ty;
        points[i].z += tz;
    }
}

void rotateX(Point3D points[], double angle, int numPoints)
{
    double rad = angle * M_PI / 180.0;
    int i, y, z;
    for (i = 0; i < numPoints; i++)
    {
        y = points[i].y;
        z = points[i].z;
        points[i].y = y * cos(rad) - z * sin(rad);
        points[i].z = y * sin(rad) + z * cos(rad);
    }
}

void rotateY(Point3D points[], double angle, int numPoints)
{
    int x, z, i;
    double rad = angle * M_PI / 180.0;
    for (i = 0; i < numPoints; i++)
    {
        x = points[i].x;
        z = points[i].z;
        points[i].x = x * cos(rad) + z * sin(rad);
        points[i].z = -x * sin(rad) + z * cos(rad);
    }
}

void rotateZ(Point3D points[], double angle, int numPoints)
{
    int i, x, y;
    double rad = angle * M_PI / 180.0;
    for (i = 0; i < numPoints; i++)
    {
        x = points[i].x;
        y = points[i].y;
        points[i].x = x * cos(rad) - y * sin(rad);
        points[i].y = x * sin(rad) + y * cos(rad);
    }
}

void scaling(Point3D points[], double sx, double sy, double sz, int numPoints, int offsetX, int offsetY)
{
    int i;
    // Translate points to the origin

    // Scale the points
    for (i = 0; i < numPoints; i++)
    {
        points[i].x = points[i].x * sx;
        points[i].y = points[i].y * sy;
        points[i].z = points[i].z * sz;
    }

    // Translate points back to
}

int main()
{
    int gd = DETECT, gm;

    int scale = 300;
    int offsetX = 200; // Set origin X to 200
    int offsetY = 200; // Set origin Y to 200

    Point3D cube[8] = {
        {-50, -50, -50}, {50, -50, -50}, {50, 50, -50}, {-50, 50, -50}, {-50, -50, 50}, {50, -50, 50}, {50, 50, 50}, {-50, 50, 50}};
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    // Initial draw
    setcolor(WHITE);
    drawCube(cube, scale, offsetX, offsetY);

    getch();

    // Apply transformations
    // Clear screen before each transformation and redraw
    cleardevice();
    translate(cube, 20, 20, 20, 8);
    // setcolor(YELLOW);
    drawCube(cube, scale, offsetX, offsetY);

    getch();

    cleardevice();
    rotateY(cube, 30, 8);
    // setcolor(GREEN);F
    drawCube(cube, scale, offsetX, offsetY);

    getch();

    cleardevice();
    rotateX(cube, 180, 8);
    // setcolor(RED);
    drawCube(cube, scale, offsetX, offsetY);

    getch();

    cleardevice();
   scaling(cube, 0.5, 0.5, 0.5, 8, offsetX, offsetY);
     //scaling(cube, 2, 2, 2, 8, offsetX, offsetY);
    // setcolor(BLUE);
    drawCube(cube, scale, offsetX, offsetY);

    getch();

    closegraph();
    return 0;
}
