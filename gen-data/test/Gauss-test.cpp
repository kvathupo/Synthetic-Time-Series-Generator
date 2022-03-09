#include <iostream>
#include "GaussSeq.h"

int main() {
    GaussSeq g(200, 1);

    std::cout << "Are these values about 200?\n";
    for (auto i = 0; i < 10; i++) {
        std::cout << g.next() << "\n";
    }

    return 0;
}
