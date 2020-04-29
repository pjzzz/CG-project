//#include <bits/stdc++.h>
//#include <GL/glut.h>
#include <GL/freeglut.h>
#include "classes.cpp"

using namespace std;
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

//Initializing View
View view(-22, 0, 0, 0, 0, 0);

//rendering flooe
void drawFloor(){
    glBegin(GL_QUADS);
    glVertex3fv(fVert[0]);
    glVertex3fv(fVert[1]);
    glVertex3fv(fVert[2]);
    glVertex3fv(fVert[3]);
    glEnd();
}

//Reaction array
vector<Reaction> Reactions;

void drawReactions(){
    //Initialize if you want to use some other way @ashu
    Reaction temp("Sulphonication");
    // Reactions.emplace_back(temp);
    // for(auto i:Reactions)
    //     i.draw();
    temp.draw();
}

//main display function
void display(){
    
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
    glLoadIdentity();
    
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    gluLookAt(view.eyeX, view.eyeY, view.eyeZ, view.targetX, view.targetY, view.targetZ, 0, 0,1);
    glRotatef(view.xAngle, 0.0f, 0.0f, 1.0f);
    glRotatef(view.yAngle, 1.0f, 0.0f, 0.0f);
    glPushMatrix();
    
    glColor4f(0.3, 0.3, 0.3, 1.0);
    drawFloor();
    glPopMatrix();

    glPushMatrix();
    drawReactions();
    glPopMatrix();

    glutSwapBuffers();
}

//Called on mouse click and get the stencil index of object on which it is clicked
// void getObj(int button, int state, int x, int y){
//     if(state != GLUT_DOWN) return;
    
//     if(start ==0)
//     {
//         start = -1;
//     }else
//     {
//         int w_height = glutGet(GLUT_WINDOW_HEIGHT);

//         GLuint index;

//         glReadPixels(x, w_height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
//         atomInfoS = "Atomic Number : "+ to_string(index) +"\n"+AtomInfo[index];
//     }
//     glutPostRedisplay(); 
// }
int main(int argc, char** argv)
{
    Initialize_Detail();

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_STENCIL | GLUT_MULTISAMPLE | GLUT_DEPTH);
    glutInitWindowSize (1080, 700);
    glutInitWindowPosition (50, 50);
    glutCreateWindow ("CG-Project");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    // drawReactions();
    // glutMouseFunc(getObj);
    // glutKeyboardFunc (NormalKeyHandler);
    // glutSpecialFunc(specialKeyboard);

    glutMainLoop();
    return 0;
}