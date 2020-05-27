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

    //Distance between the current atom and the atom which is passed
    double DistanceSquared(Atom other)  
    {
        return (x-other.x)*(x-other.x)+(y-other.y)*(y-other.y)+(z-other.z)*(z-other.z);
    }

    //return true if two atoms can bond otherwise false
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

    //renders current atom in scene
    void draw(float shiftX=0,float shiftY=0,float shiftZ=0)
    {
    	float radius = atom_detail[atomic_no].radius;
		glStencilFunc(GL_ALWAYS,atomic_no, -1);
		glColor3d(1, 1, 1);
        
        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
	    glBindTexture(GL_TEXTURE_2D, texture[atomic_no]); 
        
        GLUquadric *quad;
        quad = gluNewQuadric();
        gluQuadricTexture(quad, 40);
        glTranslatef(x+(10*shiftX),y+10*shiftY,z+10*shiftZ);
        gluSphere(quad, radius*Atom_Size, 100, 100);
        gluDeleteQuadric(quad);
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

        //renders current bond in scene
		void draw(float shiftX=0,float shiftY=0,float shiftZ=0)
		{
			glStencilFunc(GL_ALWAYS, 0, -1);
                
            GLUquadricObj *quadric=gluNewQuadric();
            gluQuadricNormals(quadric, GLU_SMOOTH);
            renderCylinder(atom1.x+(10*shiftX),atom1.y+10*shiftY,atom1.z+10*shiftZ,atom2.x+(10*shiftX),atom2.y+10*shiftY,atom2.z+10*shiftZ,0.1,40,quadric);   
            gluDeleteQuadric(quadric);
		}
};


class Molecule{
public: 
	vector<Atom> atoms;
	vector<Bond> bonds;
    float x = .0f,y=.0f,z=.0f;
    float ti = 0.0f;

    Molecule(){}

    Molecule(const Molecule &molecule_copy)
    {
        int atom_size = molecule_copy.atoms.size();
        int bonds_size = molecule_copy.bonds.size();

        for(int i=0;i<atom_size;i++)
            atoms.push_back(molecule_copy.atoms[i]);
        for(int i=0;i<bonds_size;i++)
            bonds.push_back(molecule_copy.bonds[i]);
        x=molecule_copy.x;
        y=molecule_copy.y;
        z=molecule_copy.z;
        ti=molecule_copy.ti;
    }

    //renders current molecule in scene
	void draw(float shiftX=0,float shiftY=0,float shiftZ=0)
	{
		for(auto it = atoms.begin(); it != atoms.end(); it ++)
		{
			Atom atom= (*it);
			atom.draw(x+shiftX,y+shiftY,z+shiftZ);
		}

		for(auto it = bonds.begin(); it != bonds.end(); ++it)
		{
			Bond bond= (*it);
			bond.draw(x+shiftX,y+shiftY,z+shiftZ);
		}
	}

    void resetTimer(){
        if(ti != 0)
            ti = 0;
    }

    bool translateMolecule(){
        return true;
    }
};

//creates required molecules by parsing data from necessary files
Molecule ParseData(string filename);

class Reaction
{
public: 

	string Name,Info;
    string Steps[5]={"","","","",""};
	vector<Molecule> Reactants,Products,Intermidiates;
    int step = 0;
    //gets reactants for the given reaction
	void getReactants()
	{
		string filename = "./Reactions/"+Name+"_Reactants.txt";
		//cout<<filename<<endl;
		fstream file;
        file.open(filename,ios::in);

		string line;
		while(getline(file,line))
		{
			//cout<<line<<endl;
			Molecule molecule = ParseData(line);
			Reactants.emplace_back(molecule);
		}
	}

    //gets products for the reaction
	void getProducts()
	{
		string filename = "./Reactions/"+Name+"_Products.txt";
        //cout<<filename<<endl;
		fstream file;
        file.open(filename,ios::in);

		string line;
		while(getline(file,line))
		{
            //cout<<line<<endl;
			Molecule molecule= ParseData(line);
			Products.emplace_back(molecule);
		}
	} 

    void getIntermidiates()
    {
        string filename = "./Reactions/"+Name+"_Intermidiates.txt";
        //cout<<filename<<endl;
		fstream file;
        file.open(filename,ios::in);

		string line;
        Intermidiates.clear();
		while(getline(file,line))
		{
            //cout<<line<<endl;
			Molecule molecule= ParseData(line);
            molecule.ti = 0.0f;
			Intermidiates.emplace_back(molecule);
		}
    }

    void get_Steps()
    {
        string filename = "./Reactions/"+Name+"_Steps.txt";
        fstream file;
        file.open(filename,ios::in);
        string line;
        int line_count=0;
        while(getline(file,line) && line_count<5)
        {
            Steps[line_count]= line;
            line_count++;
        }
    }

    void get_Info()
    {
        string filename = "./Reactions/"+Name+"_Info.txt";
        fstream file;
        file.open(filename,ios::in);
        string line;
        while(getline(file,line))
        {   
            Info=Info+"\n"+line;
        }
    }

	Reaction(string react_name)
	{
		Name = react_name;
        Info = "";
        step = 0;
        get_Info();
		getReactants();
		getProducts();
        getIntermidiates();
        get_Steps();
	}

    //renders current reaction in scene
	void draw(float shiftX=0,float shiftY=0,float shiftZ=0)
	{
		int react = Reactants.size(),prod= Products.size();
		int num = (react+prod),half=num/2;

		int molnum = -half;

		int react_count = 1,prod_count=1;

		for(auto it = Reactants.begin(); it != Reactants.end(); it ++)
		{
			Molecule mol= (*it);
			mol.draw(shiftX+molnum,shiftY,shiftZ);

			

			if(react_count<react)
			{
				glColor3d(0.0, 0.8, 0.8);
                
                GLUquadricObj *quadric=gluNewQuadric();
                gluQuadricNormals(quadric, GLU_SMOOTH);
                renderCylinder(3+10*(molnum+shiftX),0+10*shiftY,0+10*shiftZ,4+10*(molnum+shiftX),0+10*shiftY,0+10*shiftZ,0.1,40,quadric);
                gluDeleteQuadric(quadric);
                
                quadric=gluNewQuadric();
                gluQuadricNormals(quadric, GLU_SMOOTH);
                renderCylinder(3.5+10*(molnum+shiftX),-0.5+10*shiftY,0+10*shiftZ,3.5+10*(molnum+shiftX),0.5+10*shiftY,0+10*shiftZ,0.1,40,quadric);
                gluDeleteQuadric(quadric);
                react_count++;
			}
            molnum++;
            if(molnum==0 && num%2==0)
                molnum++;
		}

        molnum--;
		glColor3d(0.0, 0.8, 0.8);
                
        GLUquadricObj *quadric=gluNewQuadric();
        gluQuadricNormals(quadric, GLU_SMOOTH);
        renderCylinder(2.5+10*(molnum+shiftX),0.25+10*shiftY,0+10*shiftZ,3.5+10*(molnum+shiftX),0.25+10*shiftY,0+10*shiftZ,0.1,40,quadric);
        gluDeleteQuadric(quadric);
        
        quadric=gluNewQuadric();
        gluQuadricNormals(quadric, GLU_SMOOTH);
        renderCylinder(2.5+10*(molnum+shiftX),-0.25+10*shiftY,0+10*shiftZ,3.5+10*(molnum+shiftX),-0.25+10*shiftY,0+10*shiftZ,0.1,40,quadric);
        gluDeleteQuadric(quadric);

        molnum++;

		for(auto it = Products.begin(); it != Products.end(); it ++)
		{
			Molecule mol= (*it);
			mol.draw(molnum+shiftX,shiftY,shiftZ);

			if(prod_count<prod)
			{
				glColor3d(0.0, 1.0, 0.0);
                
                GLUquadricObj *quadric=gluNewQuadric();
                gluQuadricNormals(quadric, GLU_SMOOTH);
                renderCylinder(1.5+10*(molnum+shiftX),0+10*shiftY,0+10*shiftZ,2.5+10*(molnum+shiftX),0+10*shiftY,0+10*shiftZ,0.1,40,quadric);
                gluDeleteQuadric(quadric);
                
                quadric=gluNewQuadric();
                gluQuadricNormals(quadric, GLU_SMOOTH);
                renderCylinder(2+10*(molnum+shiftX),-0.5+10*shiftY,0+10*shiftZ,2+10*(molnum+shiftX),0.5+10*shiftY,0+10*shiftZ,0.1,40,quadric);
                gluDeleteQuadric(quadric);
                prod_count++;
			}

            molnum++;
            if(molnum==0 && num%2==0)
                molnum++;
		}
        this->step = 0;
	}
    void draw(float cor[]){
        this->draw(cor[0],cor[1],cor[2]);
    }

    void simulate(float cor[]){//addition of coordinates still remaining

        //reset intermidiates and reseting ti values of Products
        if(step==0)
        {
            this->getIntermidiates();
            int prod_size=Products.size();
            for(int i=0;i<prod_size;i++)
                Products[i].ti=0;
        }

        //pehle sirf draw bhi rakh sakte then so on

        int intm = Intermidiates.size();
        int molnum = -(intm/4);

        //pehle break honge bonds
        //destroyBonds() // step++
        if(!step)//all bonds broken bool to be added
        {
            SimulateStart = "Starting Simutaion....";
            ReactionSteps = "";
            wait_time++;
            if(wait_time>=2*FPS)
            {
                wait_time=0;
                SimulateStart="";
                this->step++;
            }
        }

        //Molecules move to new position
        int mvMol=0;
        for(int i = 0;i<intm and this->step == 1;i+=2){

            ReactionSteps=Steps[0];

            Intermidiates[i].draw(molnum);
            float ny = interpolate(0.0f,-1.0f,Intermidiates[i+1].ti,3.0f);
            float nx = 5*ny*ny;
            Intermidiates[i+1].ti++;
            //cout<<Intermidiates[i+1].ti<<endl;
            //Intermidiates[i+1].y=ny;
            if(i%4==0)
                Intermidiates[i+1].draw(molnum-nx,ny);
            else if(i%4==2)
                Intermidiates[i+1].draw(molnum+nx,ny);
            if(ny <= -0.3f)//translateMolecule())//all broken molecules move simultaneously, if we want we can 
                mvMol++;           //break individually by using mvMol
            molnum++;
            if(molnum==0 && intm%4==0)
                molnum++;
        }

        if(mvMol == intm/2 and step == 1){
            this->step++;
            //cout<<"sad"<<endl;
        }

        //final intermidiates
        molnum = -(intm / 4);
        for(int i=0;i<intm and this->step == 2;){
            //Intermidiates[i].x=molnum;
            Intermidiates[i+1].x = 10*molnum + Intermidiates[i+1].atoms[0].x;
            Intermidiates[i+1].y = Intermidiates[i+1].atoms[0].y;
            Intermidiates[i+1].z = Intermidiates[i+1].atoms[0].z;
            //Intermidiates[i+1].draw(molnum,-0.3);
            i+=2;
            molnum++;
            if(molnum==0 && intm%4==0)
                molnum++;
        }

        if(this->step == 2){
            this->step++;
        }
        molnum = -(intm / 4);
        mvMol=0;

        for(int i=0;i<intm and this->step == 3;){

            ReactionSteps = Steps[0]+"\n"+Steps[1];

            Intermidiates[i].draw(molnum);
            //Intermidiates[i+1].draw(molnum,-0.3);
            //float ny = interpolate((float)(0),Intermidiates[i+1].y,Intermidiates[i+2].ti,0.3f);

            molnum++;
            if(molnum==0 && intm%4==0)
                molnum++;

            float nx = interpolate(molnum,Intermidiates[i+1].x/10.0,Intermidiates[i+2].ti,4.0f);
            //cout<<nx<<endl;
            float xcenter = (10*molnum+Intermidiates[i+1].x)/20.0;
            float radius =  molnum - xcenter;
            float ny = sqrt((radius*radius - (nx-xcenter)*(nx-xcenter)));
            Intermidiates[i+2].ti++;
            Intermidiates[i+2].draw(nx,ny*2.0/10.0,ny*9.5/10.0);

            if(nx < Intermidiates[i+1].x/10.0){
                mvMol++;
            }
            
            i+=4;
            //cout<<step<<endl;
        }

        if(mvMol and step == 3){
            //cout<<step<<endl;
            step++;
            Intermidiates[1].resetTimer();
        }
        //cout<<step<<endl;
        //final products
        int prod_size=Products.size();
        molnum= -(prod_size/2);
        for(int i=0;i<prod_size && this->step==4;i++)
        {
            ReactionSteps=Steps[0]+"\n"+Steps[1]+"\n"+Steps[2];
            float nx = interpolate(molnum-1,molnum,Products[i].ti,2.0f);
            Products[i].ti++;
            if(nx>molnum)
                nx=molnum;
            Products[i].draw(nx);
            molnum++;
            if(molnum==0 && prod_size%2==0)
                molnum++;
        }

        if(this->step==4)
        {
            wait_time++;
            if(wait_time>=4*FPS)
            {
                wait_time=0;
                step=0;
            }
        }
    }

};



Molecule ParseData(string filename)
{
	Molecule molecule;
    string line;

    fstream file;
    file.open(filename,ios::in);

    while (getline(file, line))
    {
    	int count;
    	double x,y,z;
        char sym[20];

    	if (sscanf(line.c_str(), "%s %lf %lf %lf", sym, &x, &y, &z) == 4)
    	{
            string symbol=sym;
			int atomic_num=atom_symbol[symbol];
			Atom newAtom(atomic_num,x,y,z);
    		molecule.atoms.emplace_back(newAtom);
    	}
    	else if(sscanf(line.c_str(), "%d", &count) == 1)
    	{
    		if(count>0)
    			molecule.atoms.reserve(count);
    	}
    }

    for (auto it = molecule.atoms.begin(); it != molecule.atoms.end(); it ++)
    {
        Atom atom = (*it);
        
        for (auto j = it+1; j != molecule.atoms.end(); j ++)
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


