#include <iostream>

#include <nanofmt/format.h>


int main() {
    using namespace nanofmt;
    
    // auto str = format<"This is a {:08.3} test. {:024.6f} fdsa sda as {:12s}">(56, 78.0f, "asf");
    auto str = format<"Unsigned integer: {:06}. Another one: 0x{:02x} sdfg">(1638494, 0xfaf);

    for (const auto& c : str)
        std::cout << c;

    std::cout << std::endl;
}