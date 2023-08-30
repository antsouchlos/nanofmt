#include <nanofmt/format.h>
#include <gtest/gtest.h>


using namespace nanofmt;
using namespace nanofmt::nanofmt_detail;


TEST(FormatDecimal, positive_int) {
    constexpr std::array<char, 8> control1   = {'0', '0', '0', '0',
                                              '0', '0', '0', '2'};
    std::array<char, 8> formatted1 = format<"{:08}">(2);

    constexpr std::array<char, 8> control2   = {' ', ' ', ' ', '2',
                                              '2', '2', '2', '2'};
    std::array<char, 8> formatted2 = format<"{:8}">(22222);

    constexpr std::array<char, 8> control3   = {'0', '0', '0', '1',
                                              '2', '3', '4', '5'};
    std::array<char, 8> formatted3 = format<"{:08.4}">(12345);

    constexpr std::array<char, 4> control4   = {'6', '7', '8', '9'};
    std::array<char, 4> formatted4 = format<"{:4}">(6789);

    constexpr std::array<char, 4> control5   = {'x', 'x', 'x', 'x'};
    std::array<char, 4> formatted5 = format<"{:4}">(67895);

    EXPECT_EQ(control1, formatted1);
    EXPECT_EQ(control2, formatted2);
    EXPECT_EQ(control3, formatted3);
    EXPECT_EQ(control4, formatted4);
    EXPECT_EQ(control5, formatted5);
}

// TEST(FormatDecimal, negative_int) {
//     constexpr std::array<char, 8> control1   = {'-', '0', '0', '0',
//                                               '0', '0', '0', '2'};
//     std::array<char, 8> formatted1 = format<"{:08}">(-2);

//     constexpr std::array<char, 8> control2   = {' ', ' ', '-', '2',
//                                               '2', '2', '2', '2'};
//     std::array<char, 8> formatted2 = format<"{:8}">(-22222);

//     constexpr std::array<char, 8> control3   = {'-', '0', '0', '1',
//                                               '2', '3', '4', '5'};
//     std::array<char, 8> formatted3 = format<"{:08.4}">(-12345);

//     constexpr std::array<char, 5> control4   = {'-', '6', '7', '8', '9'};
//     std::array<char, 5> formatted4 = format<"{:5}">(-6789);

//     constexpr std::array<char, 5> control5   = {'-', 'f', 'f', 'f', 'f'};
//     std::array<char, 5> formatted5 = format<"{:05}">(-66789);

//     EXPECT_EQ(control1, formatted1);
//     EXPECT_EQ(control2, formatted2);
//     EXPECT_EQ(control3, formatted3);
//     EXPECT_EQ(control4, formatted4);
//     EXPECT_EQ(control5, formatted5);
// }

// TEST(FormatDecimal, positive_float) {
//     constexpr std::array<char, 8> control1   = {'0', '0', '2', '.',
//                                               '3', '4', '5', '6'};
//     std::array<char, 8> formatted1 = format<"{:08.4}">(2.3456);

//     // Float error: 2323.2 -> 2323.1
//     constexpr std::array<char, 8> control2   = {' ', ' ', '2', '3',
//                                               '2', '3', '.', '1'};
//     std::array<char, 8> formatted2 = format<"{:8.1}">(2323.2);

//     constexpr std::array<char, 8> control3   = {'1', '2', '3', '4',
//                                               '.', '5', '0', '0'};
//     std::array<char, 8> formatted3 = format<"{:08.3}">(1234.5);

//     // Float error: .9 -> .8
//     constexpr std::array<char, 4> control4   = {'f', 'f', '.', '8'};
//     std::array<char, 4> formatted4 = format<"{:4.1}">(678.9);

//     EXPECT_EQ(control1, formatted1);
//     EXPECT_EQ(control2, formatted2);
//     EXPECT_EQ(control3, formatted3);
//     EXPECT_EQ(control4, formatted4);
// }

// TEST(FormatDecimal, negative_float) {
//     constexpr std::array<char, 8> control1   = {'-', '0', '2', '.',
//                                                 '3', '4', '5', '6'};
//     std::array<char, 8> formatted1 = format<"{:08.4}">(-2.3456);

//     // Float error: 2323.2 -> 2323.1
//     constexpr std::array<char, 8> control2   = {' ', '-', '2', '3',
//                                                 '2', '3', '.', '1'};
//     std::array<char, 8> formatted2 = format<"{:8.1}">(-2323.2);

//     constexpr std::array<char, 8> control3   = {'-', 'f', 'f', 'f',
//                                                 '.', '5', '0', '0'};
//     std::array<char, 8> formatted3 = format<"{:08.3}">(-1234.5);


//     EXPECT_EQ(control1, formatted1);
//     EXPECT_EQ(control2, formatted2);
//     EXPECT_EQ(control3, formatted3);
// }