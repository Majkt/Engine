#include "MmgColor.h"
#include <cassert>

int main()
{
    // Test GetYellow()
    MmgColor yellow = MmgColor::GetYellow();
    assert(yellow.GetColor() == sf::Color::Yellow);

    // Test GetLimeGreen()
    MmgColor limeGreen = MmgColor::GetLimeGreen();
    assert(limeGreen.GetColor() == sf::Color(50, 205, 50));

    // Test GetDecodedColor()
    MmgColor decodedColor = MmgColor::GetDecodedColor("#FF0000");
    assert(decodedColor.GetColor() == sf::Color::Red);

    // Test GetTransparent()
    MmgColor transparent = MmgColor::GetTransparent();
    assert(transparent.GetColor() == sf::Color::Transparent);

    // Test constructors and Clone()
    MmgColor white;
    MmgColor clonedColor = white.Clone();
    assert(clonedColor.GetColor() == white.GetColor());

    MmgColor red(sf::Color::Red);
    MmgColor copiedColor(red);
    assert(copiedColor.GetColor() == red.GetColor());

    // Test ApiToString() and ApiEquals()
    MmgColor color1(sf::Color::Cyan);
    std::string color1String = color1.ApiToString();
    assert(color1String == "cyan");
    
    MmgColor color2 = MmgColor::GetLimeGreen();
    assert(color2.ApiEquals(color2));
    assert(!color1.ApiEquals(color2));

    return 0;
}
