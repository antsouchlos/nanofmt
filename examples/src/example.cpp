#include <iostream>

#include <nanofmt/format.h>


int main() {
    using namespace nanofmt;
    
    // auto str = format<"This is a {:08.3} test. {:024.6f} fdsa sda as {:12s}">(56, 78.0f, "asf");
    auto str = format<"someList: [{:08.2}, 0b{:06b}, {}]\n"
                      "int: {:6}\n"
                      "float: {:8.4}\n"
                      "unsigned: 0x{:07x}">(124.87, 17, 45.3, -2354, 975.2345, 0x67);

    for (const auto& c : str)
        std::cout << c;

    std::cout << std::endl;
}