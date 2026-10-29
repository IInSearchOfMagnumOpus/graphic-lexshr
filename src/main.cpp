#include <iostream>
#include <glex/mathem/vec2.h>

namespace gm = glex::mathem;

int main() {
    const gm::Vec2
    vector1{3.0f, 4.0f};

    std::cout << vector1.x() << '\n';
    return 0;
}