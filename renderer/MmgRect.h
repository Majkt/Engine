/**
 * @file MmgRect.h
 * @author Thomas Tsangou
 * @brief The MmgRect class is a class that represents a rectangle in the MmgBase API.
 * - can be drawn to the screen to show size and position
 * - can be used in calculations like collision detection 
 * - it can be used as a UI element like a border and divider 
 * @version 0.1
 * @date 2023-02-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _MMGRECT_H
#define _MMGRECT_H

// May need to include more stuff here 
#include <string>


class MmgRect {
    public:
    // static class members 
    static MmgRect GetUnitRect(); // returns a MmgRect instance positioned at (0, 0, 0) with a size of 1,1
    
    // Main methods 
    MmgRect(); // default constructor
    MmgRect(MmgRect &obj); // copy constructor
    MmgRect(int &left, int &top, int &bottom, int &right); // constructor that takes left, top, bottom, and right coords as ints
    void ShiftRect(int &shiftLeftRight, int &shiftTopBottom); // shifts the rect by the given amount
    MmgRect ToShiftedRect(int &shiftLeftRight, int &shiftTopBottom); // creates and returns a new rect at the given position
    MmgRect Clone(); // returns a clone of this instance
    /**
     * @brief The follwoing methods quickly calculate the horizontal difference between 2 MmgRect objects.
     * using the parameters of the first method, you can compare rectangles using the left and right 
     * cordinates.You can also specify which object is used first in the comparison and the direction of 
     * the comparison itself. This gives you a lot of power on how to compare two rectangles.
     */
    int GetDiffX(MmgRect &inRect, int &direction, bool &opposite, bool left2right);
    int GetDiffX(int &x, int &direction, bool &opposite); 
    /**
     * @brief The follwoing methods quickly calculate the vertical difference between 2 MmgRect objects.
     * using the parameters of the first method, you can compare rectangles using the top and bottom 
     * cordinates.You can also specify which object is used first in the comparison and the direction of 
     * the comparison itself. This gives you a lot of power on how to compare two rectangles.
     */
    int GetDiffY(MmgRect &inRect, int &direction, bool &opposite, bool top2bottom); // check textbook for correctedness 
    int GetDiffY(int &y, int &direction, bool &opposite); // check textbook for correctedness
    std::string ApiToString(); // returns a string representation of this object
    bool ApiEquals(MmgRect &obj); // checks if the given object is equal to this object

    private:
    // private class members
    int left; // the left coordinate of the rectangle
    int top; // the top coordinate of the rectangle
    int bottom; // the bottom coordinate of the rectangle
    int right; // the right coordinate of the rectangle



};
#endif // _MMGRECT_H