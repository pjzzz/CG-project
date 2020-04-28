#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

GLuint texture[120];

//Floor Vertices
float fVert[4][3] = {
    {-50.0,6.0, -50.0},
    {+50.0,6.0, -50.0},
    {+50.0,6.0, +50.0},
    {-50.0,6.0, +50.0}
};


//View Details for ModelView Matrix
struct View
{
    View(double x, double y, double z, double tx, double ty, double tz)
    : eyeX(x), eyeY(y), eyeZ(z), targetX(tx), targetY(ty), targetZ(tz), xAngle(90), yAngle(270)
    { }
    double eyeX,eyeY,eyeZ,targetX,targetY,targetZ,xAngle,yAngle;
    int width,height;
};

//rendering flooe
void drawFloor(){
    glBegin(GL_QUADS);
    glVertex3fv(fVert[0]);
    glVertex3fv(fVert[1]);
    glVertex3fv(fVert[2]);
    glVertex3fv(fVert[3]);
    glEnd();
}