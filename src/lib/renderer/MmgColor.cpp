#include "MmgColor.h"


namespace majkt {

// Static class methods for quick access to colors from the textbook
MmgColor MmgColor::GetYellow()
{
    return MmgColor(sf::Color::Yellow);
}

MmgColor MmgColor::GetLimeGreen()
{
    return MmgColor(sf::Color(50, 205, 50));
}

MmgColor MmgColor::GetDecodedColor(std::string htmlColor)
{
    // to get the decoded color we will use SFML
    // SFML has a function that takes a string and returns a color
    // we will use that function to get the decoded color
    return MmgColor(sf::Color::Color(htmlColor));
}

MmgColor MmgColor::GetTransparent()
{
    return MmgColor(sf::Color::Transparent);
}

// Constructors
MmgColor::MmgColor() : color(sf::Color::White)
{
}

MmgColor::MmgColor(const MmgColor &obj) : color(obj.color)
{
}

MmgColor::MmgColor(sf::Color color) : color(color)
{
}

// Other member functions
MmgColor MmgColor::Clone()
{
    return MmgColor(color);
}

std::string MmgColor::ApiToString()
{
    // to convert the color to a string we will use SFML
    // SFML has a function that takes a color and returns a string
    // we will use that function to get the string representation of the color
    return color.toString();
}

bool MmgColor::ApiEquals(const MmgColor& obj) const
{
    return color == obj.color;
}

// Getters and Setters
sf::Color MmgColor::GetColor()
{
    return color;
}

void MmgColor::SetColor(sf::Color color)
{
    this->color = color;
}

} // namespace majkt
