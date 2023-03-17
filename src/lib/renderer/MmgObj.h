#ifndef MAJKT_MMGOBJ_H_
#define MAJKT_MMGOBJ_H_

#include <string>
#include "MmgVector2.H"
#include "MmgColor.H"

namespace majkt {

class MmgObj
{

public:

    MmgVector2 pos; // used to store the current position of the MmgObj on the screen 
    int w;
    int h;
    bool isVisible;
    MmgColor color; // used to represent the color of this object
    std::string GetVersion();  
    bool GetIsVisible(); 
    void SetIsVisible(bool bl); 

    // getting dimensions of the  a 2d object 
    int GetWidth(); 
    void SetWidth(int W); 
    int GetHeight(); 
    void SetHeight(int H); //


 // getting the corrnations of the object as well as the color paltte

    void SetPosition(MmgVector2 v);// 
    MmgVector2 GetPosition();//
    MmgColor GetMmgColor(); //
    void SetMmgColor(MmgColor c);// 
    



//// GET AND SET METHODS used to interact with  the X and Y coordinate values directly
std::string GetName(); //
 void SetName(std::string n);// 
 std::string GetId();// 
 void SetId(std::string i);

    void SetX(int inX);
     int GetX() ;
     void SetY(int inY); 
     int GetY() ;

 // created for the purpose of having different relations with game objects
 bool GetHasParent(); 
 void SetHasParent(bool b); 
 MmgObj GetParent(); 
 void SetParent(MmgObj o); 

    MmgObj(MmgVector2 v2, int W, int H, bool isv, MmgColor c, std::string n, std::string i); //sets class fields to an initial value using either a default or argument value.
    MmgObj(MmgObj obj);  //takes an MmgObj instance as an argument. This is a specialized constructor that creates a new class instance based on the passed-in object. 
  
  // return a new MmgObj instance, the Clone method 
//returns a new MmgObj instance, and the CloneTyped method returns a new instance of 
//the extended class. In this case, the typed class is also MmgObj,
    MmgObj Clone(); 
    MmgObj CloneTyped(); 
 
    void MmgDraw(MmgPen p); // NOT INCLUDED YET 
    //The MmgUpdate method is part of the game engine drawing routine. The drawing 
//routine consists of a set of standard methods that are called a certain number of times a 
//second to maintain the desired frame rate. The updateTick argument is an index of the 
//number of times the update method was called. In other words, if you run your game at 
//60 frames per second, then the updateTick argument will increase by roughly 60 each 
//second.
    bool MmgUpdate(int updateTick, long currentTimeMs, long msSinceLastFrame); 
    std::string ApiToString(); 
    bool ApiEquals(MmgObj obj);
};


} // namespace majkt

#endif; // MAJKT_MMGOBJ_H_