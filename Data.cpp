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
GLuint floortexture,walltexture,rooftexture;

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
View view(-20, 0, 0, 0, 0, 0);

bool maxFPS=false;
int FPS = 30;
int frame = 0, Time = 0, timebase=0;
float SCRW=1080,centerX;
float SCRH=700,centerY;
double fx,fy,fz;
float pitch= 0.f,yaw=0.f;
float mult=1.0f;

int wait_time=0;


int fullScreen=1;
int mouseMove=1;

bool simulation=0;

int react_number=0;
int react_info_number=0;
const int total_reactions=5;
//Floor Vertices
float fVert[4][3]= {
    {-80.0,6.0, -50.0},
    {+80.0,6.0, -50.0},
    {+80.0,6.0, +50.0},
    {-80.0,6.0, +50.0}
};

float reaction_cordinates[total_reactions][3]= {
    {0.0,0.0,0.0},
    {+5.0,0.0, 3.0},
    {+5.0,0.0, -3.0},
    {-5.0,0.0, -3.0},
    {-5.0,0.0, +3.0}
};

float walls[4][4][3]={
	{{-80.0,6.0,-50},{-80.0,-18.0,-50},{-80.0,-18.0,+50.0},{-80.0,6.0,+50.0}},
	{{+80.0,6.0,-50},{+80.0,-18.0,-50},{+80.0,-18.0,+50.0},{+80.0,6.0,+50.0}},
	{{-80.0,6.0,-50},{-80.0,-18.0,-50},{+80.0,-18.0,-50.0},{+80.0,6.0,-50.0}},
	{{-80.0,6.0,+50.0},{-80.0,-18.0,+50.0},{+80.0,-18.0,+50.0},{+80.0,6.0,+50.0}},
};

float roof[4][3]= {
	{-80.0,-18.0, -50.0},
    {+80.0,-18.0, -50.0},
    {+80.0,-18.0, +50.0},
    {-80.0,-18.0, +50.0}
};

string SelectedAtomInfo="---";
string SimulateStart="";
string ReactionSteps=""; 
string ProjectInfo="Chemical Reaction View\nSubmitted by :- \n  Ashutosh Anshul - 170001011 \n  Prayag Jain - 170001037\nSupervised by :- \n  Dr. Somnath Dey";
string Help="Instructions :-\nClick on atom to get it's info\nw,a,s,d,q,e: Camera Movement\nf: Toggle fullscreen\nm: Toggle mouse movement/selection\nn: Next Reaction\np: Previous Reaction\nesc: Exit";

