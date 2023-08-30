#include <iostream>

#include <nanofmt/format.h>


int main() {
    using namespace nanofmt;
    
    // auto str = format<"This is a {:08.3} test. {:024.6f} fdsa sda as {:12s}">(56, 78.0f, "asf");
    auto str = format<"Unsigned integer: 0b{:012b}. Another one: 0x{:0x} sdfg">(1023, 0xfa);

    for (const auto& c : str)
        std::cout << c;

    std::cout << std::endl;
}