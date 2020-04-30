#include "Data.cpp"
#include "lib/RgbImage.cpp"
#include "lib/RgbImage.h"


//Loading and returning texture for the filname
GLuint loadTextureFromFile(const char *filename)
{   
	GLuint temp = 0;
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	RgbImage theTexMap( filename );

	glGenTextures(1, &temp);		
	glBindTexture(GL_TEXTURE_2D, temp);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );
	return temp;
}

void Initialize_Detail()
{
    fVert[0][0] = -50.0;
    fVert[0][1] = 6.0;
    fVert[0][2] = -50.0;

    fVert[2][0] = +50.0;
    fVert[1][1] = 6.0;
    fVert[1][2] = -50.0;

    fVert[2][0] = +50.0;
    fVert[2][1] = 6.0;
    fVert[2][2] = +50.0;

    fVert[3][0] = -50.0;
    fVert[3][1] = 6.0;
    fVert[3][2] = +50.0;

	atom_detail[1]={"H", 0.6, .37, "Hydrogen: \n1. It is a colourless,odourless and tasteless gas.\n2. It is the lightest gas known.\n3. It is only very slightly soluble in water.\n4. It can be liquefied under high pressure and at low temperature."};
	atom_detail[6]={"C", 0.91, .77, "Carbon:\n1. It is a non-metallic element.\n2. It occurs both in free as well as combined state.\n3. Air also contain carbon as carbon-di-oxide.\n4. In free state it occurs as diamond,coal and graphite.\n5. Carbon forms hydrites known as hydrocarbon."};
	atom_detail[7]={"N", 0.92, .75, "Nitrogen:\n1. It is a typical non-metal.\n2. It exists as diatomic molecule.\n3. It is highly electronegative element.\n4. The oxidation state of nitrogen varies from -3 to +5.\n5. Molecular nitrogen is called dinitrogen."};
	atom_detail[8]={"O", 0.80, .73, "Oxygen:\n1. It is a non-metal.\n2. It is paramagnatic in nature.\n3. It is most abundant element in earth's crust.\n4. It is di-atomic in nature.\n5. Molecular oxygen is also called dioxygen."};
	atom_detail[16]={"S", 1.6, 1.02, "Sulphur:\n1.)It is present in small proportion\n2.)It is used as disinfectant for destroying bacteria,fungi\n3.)It is used in vulcanisation of rubber\n4.)It is a constituent of medicines for skin diseases\n5.)It is used in manufacture of matches,fire-works,etc"};
	atom_detail[17]={"Cl", 1.55, .99, "Chlorine:\n1.)It is a non-metallic element\n2.)It is used in bleaching textile,yarn,paper,pulp\n3.)It is used in the sterilization of drinking water\n4.)It is used in the manufacture of vinyl chloride\n5.)It is used in preparing insecticides such as D.D.T. & B.H.C"};
	atom_detail[35]={"Br", 1.45, 1.14, "Bromine:\n1.)It's atomic radius is 101.4pm\n2.)It's ionisation energy is 1142 KJ/mol\n3.)It is reddish brown in colour\n4.)It makes bromo compounds in organic chemistry\n5.)It finds use in medicine\n6.)It is a liquid with obnoxious smel"};
	
	atom_symbol.insert({"H",1});
	atom_symbol.insert({"C",6});
	atom_symbol.insert({"N",7});
	atom_symbol.insert({"O",8});
	atom_symbol.insert({"S",16});
	atom_symbol.insert({"Cl",17});
	atom_symbol.insert({"Br",35});

	//string tex_namestr[7]={"./textures/hydrogen.bmp","./textures/carbon.bmp","./textures/nitrogen.bmp","./textures/oxygen.bmp","./textures/sulfur.bmp","./textures/chlorine.bmp","./textures/bromine.bmp"};
    //char* tex_names[7]={"./textures/hydrogen.bmp","./textures/carbon.bmp","./textures/nitrogen.bmp","./textures/oxygen.bmp","./textures/sulfur.bmp","./textures/chlorine.bmp","./textures/bromine.bmp"};
    // for(int tex_count=0;tex_count<7;tex_count++)
    //     strcpy(tex_names[tex_count],tex_namestr[tex_count].c_str());

    const char* tex_name1="./textures/hydrogen.bmp";
    const char* tex_name6="./textures/carbon.bmp";
    const char* tex_name7="./textures/nitrogen.bmp";
    const char* tex_name8="./textures/oxygen.bmp";
    const char* tex_name16="./textures/sulfur.bmp";
    const char* tex_name17="./textures/chlorine.bmp";
    const char* tex_name35="./textures/bromine.bmp";

    //texture array
    texture[1] = loadTextureFromFile(tex_name1);
    texture[6] = loadTextureFromFile(tex_name6);
    texture[7] = loadTextureFromFile(tex_name7);
    texture[8] = loadTextureFromFile(tex_name8);
    texture[16] = loadTextureFromFile(tex_name16);
    texture[17] = loadTextureFromFile(tex_name17);
    texture[35] = loadTextureFromFile(tex_name35);
	
	//Reaction array
	
}

//render cylinder by getting the distance and angle between the passed vertices then use it to create a cylinder followed by disc at endpoints
void renderCylinder(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions,GLUquadricObj *quadric) 
{
	float x_dir = x2-x1;
	float y_dir = y2-y1;
	float z_dir = z2-z1;

	if(z_dir == 0)
	    z_dir = .0001;

	float dir = sqrt( x_dir*x_dir + y_dir*y_dir + z_dir*z_dir );
	float angle = 57.2957795*acos( z_dir/dir );
	if ( z_dir < 0.0 )
	    angle = -angle;
	float rx = -y_dir*z_dir;
	float ry = x_dir*z_dir;
	glPushMatrix();

	glTranslatef( x1,y1,z1 );
	glRotatef(angle, rx, ry, 0.0);
	gluQuadricOrientation(quadric,GLU_OUTSIDE);
	gluCylinder(quadric, radius, radius, dir, subdivisions, 1);

	gluQuadricOrientation(quadric,GLU_INSIDE);
	gluDisk( quadric, 0.0, radius, subdivisions, 1);
	glTranslatef( 0,0,dir );

	gluQuadricOrientation(quadric,GLU_OUTSIDE);
	gluDisk( quadric, 0.0, radius, subdivisions, 1);
	glPopMatrix();
}

void reshape(int w, int h){
    if(h == 0)    h = 1;
    
    float ratio = w * 1.0 / h;
	SCRW=w;
	SCRH=h;
	centerX=w/2;
    centerY=max(1,h/2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0, ratio, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// void mouseMove(int x, int y) { 	

//          // this will only be true when the left button is down
//          if (xOrigin >= 0) {

// 		// update deltaAngle
// 		deltaAngle = (x - xOrigin) * 0.001f;

// 		// update camera's direction
// 		lx = sin(angle + deltaAngle);
// 		lz = -cos(angle + deltaAngle);
// 	}
// }

// void mouseButton(int button, int state, int x, int y) {

// 	// only start motion if the left button is pressed
// 	if (button == GLUT_LEFT_BUTTON) {

// 		// when the button is released
// 		if (state == GLUT_UP) {
// 			angle += deltaAngle;
// 			xOrigin = -1;
// 		}
// 		else  {// state = GLUT_DOWN
// 			xOrigin = x;
// 		}
// 	}
// }

//Called on mouse click and get the stencil index of object on which it is clicked
void getObj(int button, int state, int x, int y){
    if(state != GLUT_DOWN) return;
    
    if(!mouseMove)
    {
        int w_height = glutGet(GLUT_WINDOW_HEIGHT);

        GLuint index;

        glReadPixels(x, w_height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

        string atomic_num = to_string(index);
        if(atomic_num=="0")
            SelectedAtomInfo = "-";
        else
            SelectedAtomInfo = "Atomic Number : "+ to_string(index) +"\n"+atom_detail[index].info;
    }

    else
        SelectedAtomInfo = "--";
        
    glutPostRedisplay(); 
}

void NormalKeyHandler (unsigned char key, int x, int y)
{
    if (key == 'w')
    {
		view.eyeX += 1;
    }
    if (key == 's')
    {
		view.eyeX -= 1;
    }
    if (key == 'a')
    {
		view.eyeY += 1;
    }
    if (key == 'd')
    {
        view.eyeY -= 1;
    }
    if (key == 'q')
    {
        view.eyeZ += 1;
    }
    if (key == 'e')
    {
        view.eyeZ -= 1;
    }
    if (key == 'f')
    {
    	if(!fullScreen)
        {
            glutFullScreen();
            fullScreen=1;
        }
        else
        {
            glutPositionWindow(270,175);
            glutReshapeWindow(glutGet(GLUT_SCREEN_WIDTH)/2, glutGet(GLUT_SCREEN_HEIGHT)/2);
            fullScreen=0;
        }
    }

    if (key == 'm')
    {
    	yaw=0,pitch=0;
    	view.eyeX = -22;
    	view.eyeY = 0;
    	view.eyeZ = 0;

    	mouseMove = 1- mouseMove;
    }
    
    glutPostRedisplay(); 
}

void adjustCam()
{
    //glm::vec3 front;
	double fx,fy,fz;
    fx = cos((M_PI/180.0)*(yaw)) * cos((M_PI/180.0)*(pitch));
    fy = sin((M_PI/180.0)*(pitch));
    fz = sin((M_PI/180.0)*(yaw)) * cos((M_PI/180.0)*(pitch));
    //y=-z,z=y;
    // up.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    // front.y = -sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    // front.z = sin(glm::radians(pitch));
    double nf = sqrt(fx*fx+fy*fy+fz*fz);

    view.targetX=view.eyeX+fx/nf;
	view.targetY=view.eyeY+fy/nf;
	view.targetZ=view.eyeZ+fz/nf;
}

void mousetoCenter()
{
    glutWarpPointer(490,550);
}

void mouseMovement(int x, int y) 
{
	if(mouseMove)
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
        yaw -= lasty;
        pitch -= lastx;
        // if (pitch > 89.0f)
        //     pitch = 89.0f;
        // if (pitch < -89.0f)
        //     pitch = -89.0f;
        // if(mouseLock)
        // {
        //     mousetoCenter();
        //     warpCall = true;
        //     x = 10;
        //     y = 10;
        // }
        lastx = (float)x;
        lasty = (float)y;
    	
    	//Check if we need really need to call glutPostDisplay again anf again or not
    	glutPostRedisplay();
    }
}

void timer(int) {
    // yaw+=.1;
    glutPostRedisplay();
    if(!maxFPS)
        glutTimerFunc(1000/FPS, timer, 0);
}

void fps()
{
    frame++;
	Time=glutGet(GLUT_ELAPSED_TIME);
    //if (Time - timebase > 1000) {
        char s[1000];
		sprintf(s,"KEMIStri FPS:%4.2f",
			frame*1000.0/(Time-timebase));
		timebase = Time;
		frame = 0;
        glutSetWindowTitle(s);
	//}
}

//render string at passed cordinated with passed rgb value, it change the x value with every new line
void PrintString(string s,int x,int y,int r,int g, int b)
{
    void* font = GLUT_BITMAP_9_BY_15;
    int next_line =0;

    glRasterPos2i(x, y);

    int len= s.length();
    for (int i=0;i<len;i++)
    {
        char c = s[i];
        if(c=='\n')
        {
            next_line+=20;
            glRasterPos2i(x, y-next_line);
        }
        else
        {
            glColor3d(r, g, b);
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
        }
    }
}

void renderStrings()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 1080, 0.0, 700);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    PrintString(SelectedAtomInfo,10,130,0.0,1.0,0.0);
    PrintString(ProjectInfo,10,660,0.0,1.0,1.0);
    PrintString(Help,700,120,1.0,1.0,0.0);

    glMatrixMode(GL_PROJECTION); 
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}