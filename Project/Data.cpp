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

//atom_detail[1]={"H", 0.6, .37, "Hydrogen: \n1. It is a colourless,odourless and tasteless gas.\n2. It is the lightest gas known.\n3. It is only very slightly soluble in water.\n4. It can be liquefied under high pressure and at low temperature."};


