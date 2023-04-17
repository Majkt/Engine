#include "MmgVector2.h"
#include <iostream>
using namespace majkt;

int main()
{
    MmgVector2 vec = MmgVector2(1, 2);
    MmgVector2 vec2 = MmgVector2(3.1111, 4.2222);
    MmgVector2 vec3 = MmgVector2(5.31, 3.11);
    MmgVector2 vec4 = vec.Clone();

    std::cout << "vec1 x: " << vec.GetX() << std::endl;
    std::cout << "vec1 y: " << vec.GetY() << std::endl;

    std::cout << "vec2 x: " << vec2.GetXFloat() << std::endl;
    std::cout << "vec2 y: " << vec2.GetYFloat() << std::endl;

    std::cout << "vec3 x: " << vec3.GetXFloat() << std::endl;
    std::cout << "vec3 y: " << vec3.GetYFloat() << std::endl;

    float tfloat = 10.1000;
    vec3.SetX(tfloat);

    std::cout << "vec3 x: " << vec3.GetXFloat() << std::endl;

    std::cout << vec.ApiToString() << std::endl;

    std::cout << vec2.ApiToString() << std::endl;

    std::cout << vec3.ApiToString() << std::endl;

    std::cout << vec4.ApiToString() << std::endl;

    std::cout << vec4.ApiEquals(&vec) << std::endl;
    std::cout << vec4.ApiEquals(&vec2) << std::endl;

    return 0;
}
