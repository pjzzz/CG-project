class Atom{
    int atomic_no;
    double x,y,z; //Co-ordinates of atom
    double DistanceSquared(Atom other) //Distance between the current atom and the atom which is passed 
    {
        return (x-other.x)*(x-other.x)+(y-other.y)*(y-other.y)+(z-other.z)*(z-other.z);
    }
};