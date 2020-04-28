#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include "Objects/Atom.cpp"
#include "Objects/Bond.cpp"
#include "functions.cpp"

using namespace std;

void timer(int) {
    // yaw+=.1;
    glutPostRedisplay();
    if(!maxFPS)
        glutTimerFunc(1000/FPS, timer, 0);
}

void drawSnowMan() {

	glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);

// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);

// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f,0.5f,10,2);
}

void displayMe()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	camera.x, 1.0f, camera.z,
			camera.x+lx, 1.0f,  camera.z+lz,
			0.0f, 1.0f,  0.0f);

// Draw ground

	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

// Draw 36 SnowMen

	for(int i = -3; i < 3; i++)
		for(int j=-3; j < 3; j++) {
                     glPushMatrix();
                     glTranslatef(i*10.0,0,j * 10.0);
                     drawSnowMan();
                     glPopMatrix();
               }
        glutSwapBuffers();
}
void keyboard(unsigned char c, int x, int y)
{
    // io.lock();
    // translate(-origin.x,-origin.y,-origin.z);
    switch(c)
    {
        case 'Q':case 'q':exit(0);
        // case 'x':scale(1./scale_ratio,1,1);break;
        // case 'X':scale(scale_ratio,1,1);break;
        // case 'y':scale(1,1./scale_ratio,1);break;
        // case 'Y':scale(1,scale_ratio,1);break;
        // case 'z':scale(1,1,1./scale_ratio);break;
        // case 'Z':scale(1,1,scale_ratio);break;
        // case 'w':case 'W':reflectXZ();break;
        // case 'e':case 'E':reflectXY();break;
        // case 'r':case 'R':reflectYZ();break;
        // case 'j':case 'J':Shear(-scale_ratio,0,0);break;
        // case 'l':case 'L':Shear(scale_ratio,0,0);break;
        // case 'i':case 'I':Shear(0,-scale_ratio,0);break;
        // case 'k':case 'K':Shear(0,scale_ratio,0);break;
        // case 'o':case 'O':Shear(0,0,-scale_ratio);break;
        // case 'm':case 'M':Shear(0,0,scale_ratio);break;
        // case ';':translate(translate_val,0,0);break;
        // case ':':translate(-translate_val,0,0);break;
        // case '\'':translate(0,translate_val,0);break;
        // case '\"':translate(0,-translate_val,0);break;
        // case '/':translate(0,0,translate_val);break;
        // case '?':translate(0,0,-translate_val);break;
        // case '6':rotateZ(theta);break;
        // case '4':rotateZ(-theta);break;
        // case '2':rotateX(theta);break;
        // case '8':rotateX(-theta);break;
        // case '5':rotateY(theta);break;
        // case '0':rotateY(-theta);break;
        // case '.':rotate(6,2,0,theta);break;
        // case '3':rotate(6,2,0,-theta);break;
        // case '1':reflect(6,2,0);break;
        case 'f':case 'F':
        fullScreen = !fullScreen;
        if(fullScreen)
        {
            glutFullScreen();
        }
        else
        {
            glutPositionWindow(0,0);
            glutReshapeWindow(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
        }
        break;
        case 'h':case 'H':
        showHelp = !showHelp;
        break;
        case 'u':case 'U':
        maxFPS = !maxFPS;
        if(!maxFPS)
        {
            timer(0);
        }
        break;
        case ' ':
        wireframe = !wireframe;
        if(wireframe)
        {
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        }
        break;
        case 'c': mouseLock = !mouseLock;
        if(mouseLock)
        {
            glutSetCursor(GLUT_CURSOR_NONE);
        }
        else
        {
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        }
        break;
        case '+':
        scaleFac+=.1;
        break;
        case '-':
        if(scaleFac>.2f)
            scaleFac-=.1;
        break;
        case 'w':case 'W': camera+=scrollmult*glm::normalize(glm::vec3(dirn.x,0,dirn.z));
        clampCam(camera);
        break;
        case 's':case 'S': camera-=scrollmult*glm::normalize(glm::vec3(dirn.x,0,dirn.z));
        clampCam(camera);
        break;
        case 'a':case 'A': camera-=scrollmult*glm::normalize(glm::vec3(-dirn.z,0,dirn.x));
        clampCam(camera);
        break;
        case 'd':case 'D': camera+=scrollmult*glm::normalize(glm::vec3(-dirn.z,0,dirn.x));
        clampCam(camera);
        break;
        case 'z':case 'Z': camera.y+=scrollmult;
        clampCam(camera);
        break;
        case 'x':case 'X': camera.y-=scrollmult;
        clampCam(camera);
        break;
    }
    // translate(origin.x,origin.y,origin.z);
    // io.unlock();
    // glutPostRedisplay();
}

void mousetoCenter()
{
    glutWarpPointer(centerX,centerY);
}

void mouseFunc(int button, int state, int x, int y)
{
    glm::vec3 temp;
    switch(button)
    {
        case 3:
                camera+=scrollmult*dirn;
            break; //scroll down
        case 4:
                camera+=-scrollmult*dirn;
                break; //scroll up
        case 5:
        temp =glm::normalize(cross(up,dirn));
            camera-=scrollmult*temp;
        break; //scroll left
        case 6:
        temp =glm::normalize(cross(up,dirn));
            camera+=scrollmult*temp;
        break; //scroll right
        // case GLUT_RIGHT_BUTTON:camera.z++;break;
    }
    clampCam(camera);
}
void mouseMovement(int x, int y) 
{
    static bool warpCall = true;
    static float lastx = x;
    static float lasty = y;
    if(warpCall)
    {
        warpCall = false;
        lastx = centerX;
        lasty = centerY;
        return;
    }
    lastx = (float)x - lastx;
    lasty = (float)y - lasty;
    float sensitivity = 0.1f;
    lastx *= sensitivity;
    lasty *= sensitivity;
    yaw += lastx;
    pitch -= lasty;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    if(mouseLock)
    {
        mousetoCenter();
        warpCall = true;
        x = 10;
        y = 10;
    }
    lastx = (float)x;
    lasty = (float)y;
}

int main(int argc, char **argv){

    float val = height(10,10);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutCreateWindow("kemastri");
    glutFullScreen();
    glutSetCursor(GLUT_CURSOR_NONE);
    GLenum glewError = glewInit();
    if(glewError!= GLEW_OK)
    {
        throw GlewInitError();
    }
    glutReshapeFunc(changeSize);
    glutDisplayFunc(displayMe);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(mouseMovement);
    glutPassiveMotionFunc(mouseMovement);
    glutMainLoop();
    return 0;
}