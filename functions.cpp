#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "data.cpp"

using namespace std;

void adjustCam()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    //y=-z,z=y;
    // up.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    // front.y = -sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    // front.z = sin(glm::radians(pitch));
    
    
    dirn = glm::normalize(front);
    // up = glm::normalize(cross(dirn,cross(up,dirn)));
    view = glm::lookAt(camera, camera+dirn, up);
    // view = glm::lookAt(-10.f*sundirn,glm::vec3(0.f,0.f,0.f),glm::vec3(0.f,1.f,1.f));
    glUniformMatrix4fv(glGetUniformLocation(programID, "view"), 1, GL_FALSE, glm::value_ptr(view));
}

void changeSize(int w, int h) {
    if (h == 0)
        h = 1;
        
    scrheight = h;
    scrwidth = w;
    float ratio =  w * 1.0 / h;
    centerX = w/2;
    centerY = max(1,h/2);
    glViewport(0, 0, w, h);
    projection = glm::perspective(45.0f, ratio, 0.1f, 100.0f);
    // projection = glm::ortho(-INF,+INF,-INF,+INF,.1f,100.f);
    glUniformMatrix4fv(glGetUniformLocation(programID, "proj"), 1, GL_FALSE, glm::value_ptr(projection));
}

void clampCam(glm::vec3 &cam)
{
    for(int i=0;i<3;i++)
        cam[i] = max(min(cameramax[i],cam[i]),cameramin[i]);
}

//render cylinder by getting the distance and angle between the passed vertices then use it to create a cylinder followed by disc at endpoints
void renderCylinder(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions,GLUquadricObj *quadric) 
{
    float vx = x2-x1;
    float vy = y2-y1;
    float vz = z2-z1;

    if(vz == 0)
        vz = .0001;

    float v = sqrt( vx * vx + vy * vy + vz * vz );
    float ax = 57.2957795*acos( vz/v );
    if ( vz < 0.0 )
        ax = -ax;
    float rx = -vy*vz;
    float ry = vx*vz;
    glPushMatrix();

    glTranslatef( x1,y1,z1 );
    glRotatef(ax, rx, ry, 0.0);
    gluQuadricOrientation(quadric,GLU_OUTSIDE);
    gluCylinder(quadric, radius, radius, v, subdivisions, 1);

    gluQuadricOrientation(quadric,GLU_INSIDE);
    gluDisk( quadric, 0.0, radius, subdivisions, 1);
    glTranslatef( 0,0,v );

    gluQuadricOrientation(quadric,GLU_OUTSIDE);
    gluDisk( quadric, 0.0, radius, subdivisions, 1);
    glPopMatrix();
}

float getNoise(float x,float y){
    // return 0;
    int seed=1e7+321523;
    srand(seed-x*345-y*1752);
    return (double)(rand()%100 -50)/50.;
}

float getSmoothNoise(float x,float y, float c){
    // return 1;
    float corners =(getNoise(x+c,y+c) + getNoise(x-c,y-c) +getNoise(x-c,y+c)+getNoise(x+c,y-c))/16.;
    float sides = (getNoise(x,y+c) + getNoise(x,y-c) +getNoise(x-c,y)+getNoise(x+c,y))/8.;
    float center = getNoise(x,y)/4.;
    // cerr<<corners+sides+center<<endl;
    // return abs(corners+sides+center);
    return (1.5*corners+center+1.5*sides);
}

float height(float x, float y, float eps=1.f)
{
    const int mult1 = 1, mult2 = 1;
    // return sin(mult1*x+mult2*y);
    // return getNoise(x,y);
    // return 0;
    if(x>0&&x<19&&y>0&&y<19)
        return -2;
    return getSmoothNoise(x,y,eps);
}

void drawFloor(){

    glBegin(GL_QUADS);
    glVertex3fv(fVert[0]);
    glVertex3fv(fVert[1]);
    glVertex3fv(fVert[2]);
    glVertex3fv(fVert[3]);
    glEnd();
}