#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "classes.cpp"

//Reaction array
vector<Reaction> Reactions;

void drawReactions(){
    for(int i=0;i<total_reactions;i++)
        if ((i+react_number)%total_reactions == react_info_number and simulation and (react_info_number==3))
        {
            SimulateStart="Simulation Not Available";
            ReactionSteps="";
        }
        else if((i+react_number)%total_reactions == react_info_number and simulation)
            Reactions[react_info_number].simulate(reaction_cordinates[i]);
        else
            Reactions[(i+react_number)%total_reactions].draw(reaction_cordinates[i]);

}

//main display function
void display(){
    
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
    glLoadIdentity();
    
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    adjustCam();
    gluLookAt(view.eyeX, view.eyeY, view.eyeZ, view.targetX, view.targetY, view.targetZ, 0, 0,1);
    glRotatef(view.xAngle, 0.0f, 0.0f, 1.0f);
    glRotatef(view.yAngle, 1.0f, 0.0f, 0.0f);

    if(mouseMove)
        glutSetCursor(GLUT_CURSOR_NONE);
    else
        glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
    
    glPushMatrix();
    glColor4f(0.3, 0.3, 0.3, 1.0);
    drawFloor();
    glPopMatrix();

    glPushMatrix();
    glColor4f(0.3, 0.3, 0.3, 1.0);
    drawWalls();
    glPopMatrix();

    glPushMatrix();
    glColor4f(0.3, 0.3, 0.3, 1.0);
    drawRoof();
    glPopMatrix();

    glPushMatrix();
    drawReactions();
    glPopMatrix();
    
    renderStrings(Reactions[react_info_number].Name,Reactions[react_info_number].Info);

    if(maxFPS)
        glutPostRedisplay();
    fps();

    glutSwapBuffers();
}


int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_STENCIL | GLUT_MULTISAMPLE | GLUT_DEPTH);
    glutInitWindowSize (1080, 700);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("CG-Project");
    glutFullScreen();
    

    Initialize_Detail();


    Reaction react1("Sulphonication");
    Reaction react2("Hydrogenation");
    Reaction react3("Bromination");
    Reaction react4("Simmon-Smith");
    Reaction react5("Friedel-Craft");
    Reactions.emplace_back(react1);
    Reactions.emplace_back(react2);
    Reactions.emplace_back(react3);
    Reactions.emplace_back(react4);
    Reactions.emplace_back(react5);

    timer(0);

    glutIdleFunc(display);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(getObj);
    glutKeyboardFunc (NormalKeyHandler);
    //glutMotionFunc(mouseMovement);
	glutPassiveMotionFunc(mouseMovement);
    mousetoCenter();

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}