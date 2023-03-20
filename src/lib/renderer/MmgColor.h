/**
 * @file MmgColor.h
 * @author Thomas Tsangou
 * @brief The MmgColor class is used to wrap the framework's color class and provide color 
 * support to the API. 
 * @version 0.1
 * @date 2023-02-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MAJKT_MMGCOLOR_H_
#define MAJKT_MMGCOLOR_H_

namespace majkt {


/**
 * @brief SFML is a free, open-source software dev kit for multimedia applications.
 * it provides modules like graphics, audio, network, window, system, and network.
 * it is written in C++ and is cross-platform.
 * popular in game development.
 * link: https://www.sfml-dev.org/
 */
#include <string>
#include "SFML\src\include\SFML\Graphics.hpp"

class MmgColor 
{
    public:

    // examples of Static class methods for quick access to colors from the textbook
    static MmgColor GetYellow(); // returns a yellow color
    static MmgColor GetLimeGreen(); // returns a lime green color
    static MmgColor GetDecodedColor(std::string htmlColor); // returns a color decoded from a string
    static MmgColor GetTransparent(); // returns a transparent color

    // constructors
    MmgColor(); // default constructor
    MmgColor(const MmgColor &obj); // copy constructor
    MmgColor(sf::Color color); // constructor that takes a sf::Color object

    // Other Member functions 
    MmgColor Clone(); // returns a clone of this instance
    std::string ApiToString(); // convert and returns the MmgColor object into a string representation that is compatible with the API
    bool ApiEquals(const MmgColor& obj) const; // compares the given MmgColor object to this instance and returns true if they are equal



    // Getters and Setters
    sf::Color GetColor(); // returns the color as a sf::Color object if there isn't a need to get it from a string
    void SetColor(sf::Color color); // sets the color to the given sf::Color object 

    private:
    sf::Color color; // the color object


        
        
};

} // namespace majkt

#endif // MAJKT_MMGCOLOR_H_