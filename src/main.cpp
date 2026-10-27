#include <iostream>
#include <glex/math/vec2.h>

int main() {
    const glex::Vec2 v{3.0f, 4.0f};

    // return static_cast<int>(v.x());
    std::cout << v.x() << std::endl;
    return 0;
}