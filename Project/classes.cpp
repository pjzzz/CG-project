//#include "Data.cpp"
#include "Functions.cpp"

using namespace std;

class Atom{
public:
	int atomic_no;
    double x,y,z; //Co-ordinates of atom

    Atom(){}

    Atom(int at_no,double x_cord,double y_cord,double z_cord)
    {
    	atomic_no = at_no;
    	x = x_cord;
    	y = y_cord;
    	z = z_cord;
    }

    Atom( const Atom &atom_copy)
    {
        atomic_no=atom_copy.atomic_no;
        x = atom_copy.x;
        y = atom_copy.y;
        z = atom_copy.z;
    }

    double DistanceSquared(Atom other) //Distance between the current atom and the atom which is passed 
    {
        return (x-other.x)*(x-other.x)+(y-other.y)*(y-other.y)+(z-other.z)*(z-other.z);
    }

    bool can_bond(Atom other)
    {
    	double distance = DistanceSquared(other);
    	double radius1= atom_detail[atomic_no].bondRadius;
    	double radius2= atom_detail[other.atomic_no].bondRadius;
    	double radius =  (radius1+radius2)*(radius1+radius2) * 1.1;
        if (distance <= radius) 
            return true;
        return false;
    }

    void draw(int molnum)
    {
    	float radius = atom_detail[atomic_no].radius;
		glStencilFunc(GL_ALWAYS,atomic_no, -1);
		glColor3d(1, 1, 1);
        
        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
	    glBindTexture(GL_TEXTURE_2D, texture[atomic_no]); //getTextures
        
        GLUquadric *quad;
        quad = gluNewQuadric();
        gluQuadricTexture(quad, 40);
        glTranslatef(x+(10*molnum),y,z);
        gluSphere(quad, radius*Atom_Size, 100, 100);
        
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
};

class Bond
{
	public:
		Atom atom1,atom2;

		Bond(){}

		Bond(Atom a, Atom b)
		{
			atom1.atomic_no=a.atomic_no;
            atom1.x = a.x;
            atom1.y = a.y;
            atom1.z = a.z;
			atom2.atomic_no=b.atomic_no;
            atom2.x = b.x;
            atom2.y = b.y;
            atom2.z = b.z;
		}

		void draw(int molnum)
		{
			glStencilFunc(GL_ALWAYS, 0, -1);
                
            GLUquadricObj *quadric=gluNewQuadric();
            gluQuadricNormals(quadric, GLU_SMOOTH);
            renderCylinder(atom1.x+(10*molnum),atom1.y,atom1.z,atom2.x+(10*molnum),atom2.y,atom2.z,0.1,40,quadric);   
            gluDeleteQuadric(quadric);
		}
};


class Molecule{
public: 
	vector<Atom> atoms;
	vector<Bond> bonds;

    Molecule(){}

    Molecule(const Molecule &molecule_copy)
    {
        int atom_size = molecule_copy.atoms.size();
        int bonds_size = molecule_copy.bonds.size();

        for(int i=0;i<atom_size;i++)
            atoms.push_back(molecule_copy.atoms[i]);
        for(int i=0;i<bonds_size;i++)
            bonds.push_back(molecule_copy.bonds[i]);
    }

	void draw(int molnum)
	{
		for(auto it = atoms.begin(); it != atoms.end(); it ++)
		{
			Atom atom= (*it);
			atom.draw(molnum);
		}

		for(auto it = bonds.begin(); it != bonds.end(); ++it)
		{
			Bond bond= (*it);
			bond.draw(molnum);
		}
	}
};

Molecule ParseData(string filename);

class Reaction
{
public: 

	string Name;
	vector<Molecule> Reactants,Products;

	void getReactants()
	{
		string filename = "./Reactions/"+Name+"_Reactants.txt";
		cout<<filename<<endl;
		ifstream file(filename);

		string line;
		while(getline(file,line))
		{
			cout<<line<<endl;
			Molecule molecule = ParseData(line);
			Reactants.emplace_back(molecule);
		}
	}

	void getProducts()
	{
		string filename = "./Reactions/"+Name+"_Products.txt";
		ifstream file(filename);

		string line;
		while(getline(file,line))
		{
			Molecule molecule= ParseData(line);
			Products.emplace_back(molecule);
		}
	} 

	Reaction(string react_name)
	{
		Name = react_name;
		getReactants();
		getProducts();
	}

	void draw()
	{
		int react = Reactants.size(),prod= Products.size();
		int num = (react+prod),half=num/2;

		int molnum = -half;

		int react_count = 1,prod_count=1;

		for(auto it = Reactants.begin(); it != Reactants.end(); it ++)
		{
			Molecule mol= (*it);
			mol.draw(molnum);

			molnum++;
			if(molnum==0 && num%2==0)
				molnum++;

			if(react_count<react)
			{
				glColor3d(0.0, 1.0, 0.0);
                
                GLUquadricObj *quadric=gluNewQuadric();
                gluQuadricNormals(quadric, GLU_SMOOTH);
                renderCylinder(1.5+10*molnum,0,0,2.5+10*molnum,0,0,0.1,40,quadric);
                gluDeleteQuadric(quadric);
                
                quadric=gluNewQuadric();
                gluQuadricNormals(quadric, GLU_SMOOTH);
                renderCylinder(2+10*molnum,-0.5,0,2+10*molnum,0.5,0,0.1,40,quadric);
                gluDeleteQuadric(quadric);
                react_count++;
			}
		}

		glColor3d(1.0, 0.0, 0.0);
                
        GLUquadricObj *quadric=gluNewQuadric();
        gluQuadricNormals(quadric, GLU_SMOOTH);
        renderCylinder(1.5+10*molnum,0.25,0,2.5+10*molnum,0.25,0,0.1,40,quadric);
        gluDeleteQuadric(quadric);
        
        quadric=gluNewQuadric();
        gluQuadricNormals(quadric, GLU_SMOOTH);
        renderCylinder(1.5+10*molnum,-0.25,0,2.5+10*molnum,-0.25,0,0.1,40,quadric);
        gluDeleteQuadric(quadric);

		for(auto it = Products.begin(); it != Products.end(); it ++)
		{
			Molecule mol= (*it);
			mol.draw(molnum);

			molnum++;
			if(molnum==0 && num%2==0)
				molnum++;

			if(prod_count<prod)
			{
				glColor3d(0.0, 1.0, 0.0);
                
                GLUquadricObj *quadric=gluNewQuadric();
                gluQuadricNormals(quadric, GLU_SMOOTH);
                renderCylinder(1.5+10*molnum,0,0,2.5+10*molnum,0,0,0.1,40,quadric);
                gluDeleteQuadric(quadric);
                
                quadric=gluNewQuadric();
                gluQuadricNormals(quadric, GLU_SMOOTH);
                renderCylinder(2+10*molnum,-0.5,0,2+10*molnum,0.5,0,0.1,40,quadric);
                gluDeleteQuadric(quadric);
                prod_count++;
			}
		}

	}

};



Molecule ParseData(string filename)
{
	Molecule molecule;
    string line;

    ifstream file(filename);

    while (getline(file, line))
    {
		string symbol;
    	int count;
    	double x,y,z;

    	if (sscanf(line.c_str(), "%s %lf %lf %lf", &symbol, &x, &y, &z) == 4)
    	{
    		cout<<line<<endl;
			int atomic_num=atom_symbol[symbol];
			printf("%d %d %d\n",x,y,z);
    		//yaha se kuch error aana shuru hua hai
			Atom newAtom(atomic_num,x,y,z);
    		molecule.atoms.emplace_back(newAtom);
    	}
    	else if(sscanf(line.c_str(), "%i", &count) == 1)
    	{
    		if(count>0)
    			molecule.atoms.reserve(count);
    	}
    }

    for (auto it = molecule.atoms.begin(); it != molecule.atoms.end(); it ++)
    {
        Atom atom = (*it);
        
        for (auto j = molecule.atoms.begin(); j != molecule.atoms.end(); j ++)
        {
            Atom other = (*j);

            if(it!=j && atom.can_bond(other))
            {
            	Bond newBond(atom,other);
            	molecule.bonds.push_back(newBond);
            }
        }
    }

    return molecule;
}


