#include <iostream>
#include "Server.h"

using namespace std;
using namespace boot;
int main(int argc, char *argv[]) {
    if (argc > 1) {
        boot::Main::main(argc, atoi(argv[1]));
    }
    else {
        boot::Main::main(0, 0);
    }
}