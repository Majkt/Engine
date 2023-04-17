#ifndef MAJKT_MMGVECTOR2_H_
#define MAJKT_MMGVECTOR2_H_

#include <array>
#include <string>

namespace majkt {

class MmgVector2
{
    public:
        MmgVector2(std::array<double, 2> &vec); // constructor that takes a vector of type T which is for x and y coords
        MmgVector2(); // default constructor
        MmgVector2(MmgVector2 &vec); // copy constructor
        MmgVector2(int x, int y); // constructor that takes x and y coords as ints
        MmgVector2(float x, float y); // constructor that takes x and y coords as floats
        MmgVector2(double x, double y); // constructor that takes x and y coords as doubles
        MmgVector2 Clone(); // returns a clone of this instance
        MmgVector2 CloneInt(); // returns a clone of this instance as an int vector
        MmgVector2 CloneFloat(); // returns a clone of this instance as a float vector
        MmgVector2 CloneDouble(); // returns a clone of this instance as a double vector
    
        static MmgVector2 GetOriginVec(); // returns MmgVector2 instance pointing to origin (0,0)
        static MmgVector2 GetUnitVec(); // returns MmgVector2 instance pointing to unit vector (1,1)
        
        std::array<double, 2> GetVector(); // returns the vector as an array of doubles
        
        void SetVector(std::array<double, 2> &vec); // sets the vector to the given array of doubles
        
        int GetX(); // returns the x coord of the vector as an int
        int GetY(); // returns the y coord of the vector as an int

        float GetXFloat(); // returns the y coord of the vector as a float
        float GetYFloat(); // returns the y coord of the vector as a float

        double GetXDouble(); // returns the x coord of the vector as a double
        double GetYDouble(); // returns the y coord of the vector as a double


        void SetX(int &x); // sets the x coord of the vector to the given int
        void SetY(int &y); // sets the y coord of the vector to the given int
        void SetX(double &x); // sets the x coord of the vector to the given double
        void SetY(double &y); // sets the y coord of the vector to the given double
        void SetX(float &x); // sets the x coord of the vector to the given float
        void SetY(float &y); // sets the y coord of the vector to the given float

        virtual std::string ApiToString(); // returns a string representation of this instance
        virtual bool ApiEquals(MmgVector2 *obj); // returns true if the given instance is equal to this instance

        
        private:
            std::array<double, 2> mVec; // the vector
            char mType; // the type of the vector (int, float, double);
};

} // namespace majkt

#endif // MAJKT_MMGVECTOR2_H_