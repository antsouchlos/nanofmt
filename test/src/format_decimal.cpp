#include <gtest/gtest.h>
#include <nanofmt/format.h>


using namespace nanofmt;
using namespace nanofmt::nanofmt_detail;


TEST(FormatDecimal, positive_int) {
    // clang-format off
    constexpr std::array<char, 9> control1   = {'0', '0', '0', '0', '0', '0', '0', '2', '\0'};
    std::array<char, 9>           formatted1 = format<"{:08}">(2);

    constexpr std::array<char, 9> control2   = {' ', ' ', ' ', '2', '2', '2', '2', '2', '\0'};
    std::array<char, 9>           formatted2 = format<"{:8}">(22222);

    constexpr std::array<char, 9> control3   = {'0', '0', '0', '1', '2', '3', '4', '5', '\0'};
    std::array<char, 9>           formatted3 = format<"{:08.4}">(12345);

    constexpr std::array<char, 5> control4   = {'6', '7', '8', '9', '\0'};
    std::array<char, 5>           formatted4 = format<"{:4}">(6789);

    constexpr std::array<char, 5> control5   = {'x', 'x', 'x', 'x', '\0'};
    std::array<char, 5>           formatted5 = format<"{:4}">(67895);
    // clang-format on

    EXPECT_EQ(control1, formatted1);
    EXPECT_EQ(control2, formatted2);
    EXPECT_EQ(control3, formatted3);
    EXPECT_EQ(control4, formatted4);
    EXPECT_EQ(control5, formatted5);
}

TEST(FormatDecimal, negative_int) {
    // clang-format off
    constexpr std::array<char, 9> control1   = {'-', '0', '0', '0', '0', '0', '0', '2', '\0'};
    std::array<char, 9>           formatted1 = format<"{:08}">(-2);

    constexpr std::array<char, 9> control2   = {' ', ' ', '-', '2', '2', '2', '2', '2', '\0'};
    std::array<char, 9>           formatted2 = format<"{:8}">(-22222);

    constexpr std::array<char, 9> control3   = {'-', '0', '0', '1', '2', '3', '4', '5', '\0'};
    std::array<char, 9>           formatted3 = format<"{:08.4}">(-12345);

    constexpr std::array<char, 6> control4   = {'-', '6', '7', '8', '9', '\0'};
    std::array<char, 6>           formatted4 = format<"{:5}">(-6789);

    constexpr std::array<char, 6> control5   = {'-', 'x', 'x', 'x', 'x', '\0'};
    std::array<char, 6>           formatted5 = format<"{:05}">(-66789);
    // clang-format on

    EXPECT_EQ(control1, formatted1);
    EXPECT_EQ(control2, formatted2);
    EXPECT_EQ(control3, formatted3);
    EXPECT_EQ(control4, formatted4);
    EXPECT_EQ(control5, formatted5);
}

TEST(FormatDecimal, positive_float) {
    // clang-format off
    constexpr std::array<char, 9> control1   = {'0', '0', '2', '.', '3', '4', '5', '6', '\0'};
    std::array<char, 9>           formatted1 = format<"{:08.4}">(2.3456);

    // Float error: 2323.2 -> 2323.1
    constexpr std::array<char, 9> control2   = {' ', ' ', '2', '3', '2', '3', '.', '1', '\0'};
    std::array<char, 9>           formatted2 = format<"{:8.1}">(2323.2);

    constexpr std::array<char, 9> control3   = {'1', '2', '3', '4', '.', '5', '0', '0', '\0'};
    std::array<char, 9>           formatted3 = format<"{:08.3}">(1234.5);

    // Float error: .9 -> .8
    constexpr std::array<char, 5> control4   = {'x', 'x', '.', '8', '\0'};
    std::array<char, 5>           formatted4 = format<"{:4.1}">(678.9);
    // clang-format on

    EXPECT_EQ(control1, formatted1);
    EXPECT_EQ(control2, formatted2);
    EXPECT_EQ(control3, formatted3);
    EXPECT_EQ(control4, formatted4);
}

TEST(FormatDecimal, negative_float) {
    // clang-format off
    constexpr std::array<char, 9> control1   = {'-', '0', '2', '.', '3', '4', '5', '6', '\0'};
    std::array<char, 9>           formatted1 = format<"{:08.4}">(-2.3456);

    // Float error: 2323.2 -> 2323.1
    constexpr std::array<char, 9> control2   = {' ', '-', '2', '3', '2', '3', '.', '1', '\0'};
    std::array<char, 9>           formatted2 = format<"{:8.1}">(-2323.2);

    constexpr std::array<char, 9> control3   = {'-', 'x', 'x', 'x', '.', '5', '0', '0', '\0'};
    std::array<char, 9>           formatted3 = format<"{:08.3}">(-1234.5);
    // clang-format on


    EXPECT_EQ(control1, formatted1);
    EXPECT_EQ(control2, formatted2);
    EXPECT_EQ(control3, formatted3);
}
