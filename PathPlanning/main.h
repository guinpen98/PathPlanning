#ifndef PATH_PLANNING_MAIN_H
#define PATH_PLANNING_MAIN_H
#include "node_array.h"
#include "DxLib.h"
#include<array>
#include<random>

namespace path_planning {
    namespace system {
        bool update();
    }

    void  setCoord(int& x, int& y, const field_array& field);

    void main();
}

#endif // !PATH_PLANNING_MAIN_H