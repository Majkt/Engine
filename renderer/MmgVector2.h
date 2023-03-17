#ifndef _MMGVECTOR2_H
#define _MMGVECTOR2_H

#include <array>

class MmgVector2
{
    public:
        MmgVector2(std::array<double, 2> &vec); // constructor that takes a vector of type T which is for x and y coords
        MmgVector2(); // default constructor
        MmgVector2(MmgVector2 &vec); // copy constructor
        MmgVector2(int &x, int &y); // constructor that takes x and y coords as ints
        MmgVector2(float &x, float &y); // constructor that takes x and y coords as floats
        MmgVector2(double &x, double &y); // constructor that takes x and y coords as doubles
        MmgVector2 Clone(); // returns a clone of this instance
        MmgVector2 CloneFloat(); // returns a clone of this instance as a float
        MmgVector2 CloneDouble(); // returns a clone of this instance as a double
        MmgVector2 CloneInt(); // returns a clone of this instance as an int

        static MmgVector2 GetOriginVec(); // returns MmgVector2 instance pointing to origin (0,0)
        static MmgVector2 GetUnitVec(); // returns MmgVector2 instance pointing to unit vector (1,1)
        
        std::array<double, 2> GetVector(); // returns the vector as an array of doubles
        
        void SetVector(std::array<double, 2> &vec); // sets the vector to the given array of doubles
        
        int GetX(); // returns the x coord of the vector as an int
        int GetY(); // returns the y coord of the vector as an int

        void SetX(int &x); // sets the x coord of the vector to the given int
        void SetY(int &y); // sets the y coord of the vector to the given int

        float GetXFloat(); // returns the y coord of the vector as a float
        float GetYFloat(); // returns the y coord of the vector as a float

        void SetXFloat(float &x); // sets the x coord of the vector to the given float
        void SetYFloat(float &y); // sets the y coord of the vector to the given float

        double GetXDouble(); // returns the x coord of the vector as a double
        double GetYDouble(); // returns the y coord of the vector as a double

        void SetXDouble(double &x); // sets the x coord of the vector to the given double
        void SetYDouble(double &y); // sets the y coord of the vector to the given double

};

#endif