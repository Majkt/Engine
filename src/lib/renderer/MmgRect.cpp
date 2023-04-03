#include "MmgRect.h"

namespace majkt {

MmgRect MmgRect::GetUnitRect()
{
    return MmgRect(0, 0, 1, 1);
}

MmgRect::MmgRect() : left(0), top(0), bottom(0), right(0)
{
}

MmgRect::MmgRect(MmgRect &obj) : left(obj.left), top(obj.top), bottom(obj.bottom), right(obj.right)
{
}

MmgRect::MmgRect(int &left, int &top, int &bottom, int &right) : left(left), top(top), bottom(bottom), right(right)
{
}

/**
 * @brief Shifts the rectangle by the given amount.
 * 
 * @param shiftLeftRight 
 * @param shiftTopBottom 
 */
void MmgRect::ShiftRect(int &shiftLeftRight, int &shiftTopBottom)
{
    left += shiftLeftRight;
    top += shiftTopBottom;
    right += shiftLeftRight;
    bottom += shiftTopBottom;
}

/**
 * @brief Creates and returns a new rectangle at the given position.
 * 
 * @param shiftLeftRight 
 * @param shiftTopBottom 
 * @return MmgRect 
 */
MmgRect MmgRect::ToShiftedRect(int &shiftLeftRight, int &shiftTopBottom)
{
    MmgRect shifted(left + shiftLeftRight, top + shiftTopBottom, bottom + shiftTopBottom, right + shiftLeftRight);
    return shifted;
}

MmgRect MmgRect::Clone()
{
    MmgRect cloned(left, top, bottom, right);
    return cloned;
}

/**
 * @brief Returns the width of the rectangle.
 * 
 * @param inRect 
 * @param direction 
 * @param left2right 
 * @return int 
 */
int MmgRect::GetDiffX(MmgRect &inRect, int &direction, bool &opposite, bool left2right)
{
    // direction: 1 = right, -1 = left
    int diff;
    // left2right: true = left to right, false = right to left
    if (left2right) {
        // direction: right
        if (direction == 1) {
            diff = inRect.left - right; // left - right
        } else {
            // direction: left
            diff = left - inRect.right; // left - right
        }
    // right to left
    // same as left to right, but the opposite
    } else {
        if (direction == 1) {
            diff = right - inRect.left;
        } else {
            diff = inRect.right - left;
        }
    }
    // opposite: true = opposite, false = same
    // if opposite, then the difference is negative
    if (opposite) {
        diff = -diff; 
    }
    return diff;
}

/**
 * @brief Returns the width of the rectangle.
 * 
 * @param x 
 * @param direction 
 * @param opposite 
 * @return int 
 */
int MmgRect::GetDiffX(int &x, int &direction, bool &opposite)
{
    int diff;
    if (direction == 1) {
        diff = x - right;
    } else {
        diff = left - x;
    }
    if (opposite) {
        diff = -diff;
    }
    return diff;
}

int MmgRect::GetDiffY(MmgRect &inRect, int &direction, bool &opposite, bool top2bottom)
{
    int diff;
    if (top2bottom) {
        if (direction == 1) {
            diff = inRect.top - bottom;
        } else {
            diff = top - inRect.bottom;
        }
    } else {
        if (direction == 1) {
            diff = bottom - inRect.top;
        } else {
            diff = inRect.bottom - top;
        }
    }
    if (opposite) {
        diff = -diff;
    }
    return diff;
}

int MmgRect::GetDiffY(int &y, int &direction, bool &opposite)
{
    int diff;
    if (direction == 1) {
        diff = y - bottom;
    } else {
        diff = top - y;
    }
    if (opposite) {
        diff = -diff;
    }
    return diff;
}

std::string MmgRect::ApiToString()
{
    return "[" + std::to_string(left) + ", " + std::to_string(top) + ", " + std::to_string(bottom) + ", " + std::to_string(right) + "]";