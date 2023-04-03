#include "MmgObj.h"
#include <iostream>
#include <cassert>

using namespace majkt;

int main() {

  // create a new MmgObj instance with default values
  MmgObj obj1 = MmgObj(MmgVector2(), 0, 0, false, MmgColor(), "", "");
  // test the GetVersion method
  assert(obj1.GetVersion() == "1.0");

  // create a new MmgObj instance with custom values
  MmgVector2 pos(10, 20);
  int w = 30;
  int h = 40;
  bool isVisible = true;
  MmgColor color(255, 0, 0);
  std::string name = "obj2";
  std::string id = "id2";
  MmgObj obj2 = MmgObj(pos, w, h, isVisible, color, name, id);

  // test the GetIsVisible and SetIsVisible methods
  assert(obj2.GetIsVisible() == true);
  obj2.SetIsVisible(false);
  assert(obj2.GetIsVisible() == false);

  // test the GetWidth and SetWidth methods
  assert(obj2.GetWidth() == 30);
  obj2.SetWidth(50);
  assert(obj2.GetWidth() == 50);

  // test the GetHeight and SetHeight methods
  assert(obj2.GetHeight() == 40);
  obj2.SetHeight(60);
  assert(obj2.GetHeight() == 60);

  // test the GetPosition and SetPosition methods
  assert(obj2.GetPosition().GetX() == 10);
  assert(obj2.GetPosition().GetY() == 20);
  MmgVector2 newPos(30, 40);
  obj2.SetPosition(newPos);
  assert(obj2.GetPosition().GetX() == 30);
  assert(obj2.GetPosition().GetY() == 40);

  // test the GetMmgColor and SetMmgColor methods
  assert(obj2.GetMmgColor().GetRed() == 255);
  assert(obj2.GetMmgColor().GetGreen() == 0);
  assert(obj2.GetMmgColor().GetBlue() == 0);
  MmgColor newColor(0, 0, 255);
  obj2.SetMmgColor(newColor);
  assert(obj2.GetMmgColor().GetRed() == 0);
  assert(obj2.GetMmgColor().GetGreen() == 0);
  assert(obj2.GetMmgColor().GetBlue() == 255);

  // test the GetName and SetName methods
  assert(obj2.GetName() == "obj2");
  obj2.SetName("newName");
  assert(obj2.GetName() == "newName");

  // test the GetId and SetId methods
  assert(obj2.GetId() == "id2");
  obj2.SetId("newId");
  assert(obj2.GetId() == "newId");

  // test the SetX and GetX methods
  assert(obj2.GetX() == 30);
  obj2.SetX(50);
  assert(obj2.GetX() == 50);

  // test the SetY and GetY methods
  assert(obj2.GetY() == 40);
  obj2.SetY(60);
  assert(obj2.GetY() == 60);

  // test the GetHasParent and SetHasParent methods
  assert(obj2.GetHasParent() == false);
  obj2.SetHasParent(true);
  assert(obj2.GetHasParent() == true);

  // Create parent object
    MmgVector2 parentPos(0, 0);
    int parentWidth = 100;
    int parentHeight = 100;
    bool parentVisible = true;
    MmgColor parentColor(255, 255, 255);
    std::string parentName = "parent";
    std::string parentId = "p001";
    MmgObj parent(parentPos, parentWidth, parentHeight, parentVisible, parentColor, parentName, parentId);

    // Create child object
    MmgVector2 childPos(10, 10);
    int childWidth = 50;
    int childHeight = 50;
    bool childVisible = true;
    MmgColor childColor(0, 0, 0);
    std::string childName = "child";
    std::string childId = "c001";
    MmgObj child(childPos, childWidth, childHeight, childVisible, childColor, childName, childId);

    // Set parent for child
    child.SetParent(parent);

    // Test GetParent
    assert(child.GetParent().GetName() == parentName);

    // Test SetParent
    MmgObj newParent(MmgVector2(50, 50), 75, 75, true, MmgColor(255, 0, 0), "new parent", "p002");
    child.SetParent(newParent);
    assert(child.GetParent().GetName() == "new parent");

    return 0;
}
