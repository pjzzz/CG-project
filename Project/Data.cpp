#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;

float Atom_Size=0.4;

struct Atom_Detail
{
    string symbol; //Atom Symbol
    double radius,bondRadius; //Atomic Radius && Atom Bond Radius
    string info;
} atom_detail[120];

map<string,int> atom_symbol;

GLuint texture[120];

//View Details for ModelView Matrix
struct View
{
    View(double x, double y, double z, double tx, double ty, double tz)
    : eyeX(x), eyeY(y), eyeZ(z), targetX(tx), targetY(ty), targetZ(tz), xAngle(270), yAngle(270)
    { }
    double eyeX,eyeY,eyeZ,targetX,targetY,targetZ,xAngle,yAngle;
    int width,height;
};

//Initializing View
View view(-22, 0, 0, 0, 0, 0);

bool maxFPS=false;
const int FPS = 120;
int frame = 0, Time = 0, timebase=0;
float SCRW=1080,centerX;
float SCRH=700,centerY;
float pitch= 0.f,yaw=0.f;
float scrollmult=.3f;

//atom_detail[1]={"H", 0.6, .37, "Hydrogen: \n1. It is a colourless,odourless and tasteless gas.\n2. It is the lightest gas known.\n3. It is only very slightly soluble in water.\n4. It can be liquefied under high pressure and at low temperature."};


