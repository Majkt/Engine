#include "MmgRect.h"
#include <iostream>

using namespace std;
using namespace majkt;

int main()
{
    // Test default constructor
    MmgRect rect1;
    cout << rect1.ApiToString() << endl; // Expected output: "[0, 0, 0, 0]"

    // Test parameterized constructor
    MmgRect rect2(1, 2, 3, 4);
    cout << rect2.ApiToString() << endl; // Expected output: "[1, 2, 3, 4]"

    // Test copy constructor
    MmgRect rect3(rect2);
    cout << rect3.ApiToString() << endl; // Expected output: "[1, 2, 3, 4]"

    // Test GetUnitRect() method
    MmgRect rect4 = MmgRect::GetUnitRect();
    cout << rect4.ApiToString() << endl; // Expected output: "[0, 0, 1, 1]"

    // Test ShiftRect() method
    rect3.ShiftRect(1, 2);
    cout << rect3.ApiToString() << endl; // Expected output: "[2, 4, 5, 6]"

    // Test ToShiftedRect() method
    MmgRect rect5 = rect4.ToShiftedRect(1, 2);
    cout << rect5.ApiToString() << endl; // Expected output: "[1, 2, 3, 3]"

    // Test Clone() method
    MmgRect rect6 = rect2.Clone();
    cout << rect6.ApiToString() << endl; // Expected output: "[1, 2, 3, 4]"

    // Test GetDiffX() method
    MmgRect rect7(2, 2, 3, 3);
    int direction = 1; // Right
    bool opposite = false;
    bool left2right = true;
    int diffX = rect2.GetDiffX(rect7, direction, opposite, left2right);
    cout << "diffX: " << diffX << endl; // Expected output: "-1"

    // Test GetDiffX() method with integer input
    int x = 2;
    int diffX2 = rect2.GetDiffX(x, direction, opposite);
    cout << "diffX2: " << diffX2 << endl; // Expected output: "2"

    // Test GetDiffY() method
    int diffY = rect2.GetDiffY(rect7, direction, opposite, true);
    cout << "diffY: " << diffY << endl; // Expected output: "-1"

    // Test GetDiffY() method with integer input
    int y = 2;
    int diffY2 = rect2.GetDiffY(y, direction, opposite);
    cout << "diffY2: " << diffY2 << endl; // Expected output: "0"

    return 0;
}