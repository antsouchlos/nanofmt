#include <iostream>

#include <nanofmt/format.h>


int main() {
    /// Function call syntax

    const auto str = nanofmt::format<"Signed: {:05}\n"
                                     "Unsigned: {:4}\n"
                                     "Float: {:08.3}">(145, -54, -123.4);

    /// User defined literal syntax

    using namespace nanofmt::literals;

    const auto str2 = "Binary: 0b{:08b}\n"
                      "Hexadecimal: 0x{:04x}\n"
                      "Overflow: {:4}"_fmt(123, 0xfa, 12345);

    std::cout << str.data() << std::endl;
    std::cout << str2.data() << std::endl;
}