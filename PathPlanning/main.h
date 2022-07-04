#ifndef PATH_PLANNING_MAIN_H
#define PATH_PLANNING_MAIN_H
#include "node.h"
#include "DxLib.h"
#include<array>
#include<random>

namespace pathPlanning {
    namespace system {
        bool update();
    }

    void  setCoord(int& x, int& y, const field_array& field);

    void main();
}

#endif // !PATH_PLANNING_MAIN_H