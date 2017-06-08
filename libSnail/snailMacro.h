#pragma once
#include <iostream>

#define _Log(vStr) { std::cout << vStr << std::endl; }
#define _Delete_If_Not_Empty(vP) { if (vP); delete(vP); vP = nullptr; }

namespace snail
{

}