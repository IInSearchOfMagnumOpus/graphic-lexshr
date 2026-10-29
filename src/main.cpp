#include <iostream>
#include <glex/mathem/vec2.h>

int main() {
    const mathem::Vec2
    vector1{3.0f, 4.0f};

    // return static_cast<int>(v.x());
    std::cout << vector1.x() << std::endl;
    return 0;
}