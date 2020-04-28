#include "Data.cpp"
#include "lib/RgbImage.cpp"
#include "lib/RgbImage.h"


//Loading and returning texture for the filname
GLuint loadTextureFromFile(char *filename)
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

	string tex_namestr[7]={"./textures/hydrogen.bmp","./textures/carbon.bmp","./textures/nitrogen.bmp","./textures/oxygen.bmp","./textures/sulfur.bmp","./textures/chlorine.bmp","./textures/bromine.bmp"};
    char tex_names[7][1024];
    for(int tex_count=0;tex_count<7;tex_count++)
        strcpy(tex_names[tex_count],tex_namestr[tex_count].c_str());

    //texture array
    texture[1] = loadTextureFromFile(tex_names[0]);
    texture[6] = loadTextureFromFile(tex_names[1]);
    texture[7] = loadTextureFromFile(tex_names[2]);
    texture[8] = loadTextureFromFile(tex_names[3]);
    texture[16] = loadTextureFromFile(tex_names[4]);
    texture[17] = loadTextureFromFile(tex_names[5]);
    texture[35] = loadTextureFromFile(tex_names[6]);
	
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