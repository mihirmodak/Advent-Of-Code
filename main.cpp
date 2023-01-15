#include <iostream>
#include "src/src.h"
#include "timing.hpp"

using namespace std;

int main() {
    timing::start();
    day6();
    timing::end();
    system("pause");
    return 0;
}
