#include <gtest/gtest.h>

#include <nanofmt/parse.h>
#include <nanofmt/types.h>


TEST(Parse, fmt_data_len) {
    constexpr auto fmtData1 =
        nanofmt::nanofmt_detail::generate_fmt_data<"{:08.3}{}{:08}{:.16}">();

    constexpr auto fmtData2 = nanofmt::nanofmt_detail::generate_fmt_data<
        "This {:08.3} is {} a {:08} test {}">();

    EXPECT_EQ(fmtData1.size(), 4);
    EXPECT_EQ(fmtData2.size(), 4);
}

TEST(Parse, fmt_data_valid) {
    constexpr auto fmtDataValid1 =
        nanofmt::nanofmt_detail::generate_fmt_data<"{}">();
    constexpr auto fmtDataValid2 =
        nanofmt::nanofmt_detail::generate_fmt_data<"{:}">();
    constexpr auto fmtDataValid3 =
        nanofmt::nanofmt_detail::generate_fmt_data<"{:0}">();
    constexpr auto fmtDataValid4 =
        nanofmt::nanofmt_detail::generate_fmt_data<"{:012}">();
    constexpr auto fmtDataValid5 =
        nanofmt::nanofmt_detail::generate_fmt_data<"{:014.6}">();
    constexpr auto fmtDataValid6 =
        nanofmt::nanofmt_detail::generate_fmt_data<"{:08.2b}">();

    EXPECT_EQ(fmtDataValid1[0].valid, true);
    EXPECT_EQ(fmtDataValid2[0].valid, true);
    EXPECT_EQ(fmtDataValid3[0].valid, true);
    EXPECT_EQ(fmtDataValid4[0].valid, true);
    EXPECT_EQ(fmtDataValid5[0].valid, true);
    EXPECT_EQ(fmtDataValid6[0].valid, true);
}

TEST(Parse, update_number) {
    constexpr auto fmtData1 =
        nanofmt::nanofmt_detail::generate_fmt_data<"{:023}{:1}{:0867}">();
    constexpr auto fmtData2 =
        nanofmt::nanofmt_detail::generate_fmt_data<"{:0.2}{:034.43}{:.123}">();

    EXPECT_EQ(fmtData1[0].width, 23);
    EXPECT_EQ(fmtData1[1].width, 1);
    EXPECT_EQ(fmtData1[2].width, 867);

    EXPECT_EQ(fmtData2[0].precision, 2);
    EXPECT_EQ(fmtData2[1].precision, 43);
    EXPECT_EQ(fmtData2[2].precision, 123);
}

TEST(Pars, overall) {
    constexpr auto fmtData1 =
        nanofmt::nanofmt_detail::generate_fmt_data<"{}">();
    constexpr auto fmtData2 =
        nanofmt::nanofmt_detail::generate_fmt_data<"{:012.4f}">();
    constexpr auto fmtData3 =
        nanofmt::nanofmt_detail::generate_fmt_data<"{:8.2b}">();
    constexpr auto fmtData4 =
        nanofmt::nanofmt_detail::generate_fmt_data<"{:56.34d}">();
    constexpr auto fmtData5 =
        nanofmt::nanofmt_detail::generate_fmt_data<"{:01234x}">();
    constexpr auto fmtData6 =
        nanofmt::nanofmt_detail::generate_fmt_data<"{:6}">();

    EXPECT_EQ(fmtData1[0].valid, true);
    EXPECT_EQ(fmtData1[0].has_zero_padding, false);
    EXPECT_EQ(fmtData1[0].width, 0);
    EXPECT_EQ(fmtData1[0].precision, 0);
    EXPECT_EQ(fmtData1[0].type, nanofmt::nanofmt_detail::FormatType::def);
    
    EXPECT_EQ(fmtData2[0].valid, true);
    EXPECT_EQ(fmtData2[0].has_zero_padding, true);
    EXPECT_EQ(fmtData2[0].width, 12);
    EXPECT_EQ(fmtData2[0].precision, 4);
    EXPECT_EQ(fmtData2[0].type, nanofmt::nanofmt_detail::FormatType::f);

    EXPECT_EQ(fmtData3[0].valid, true);
    EXPECT_EQ(fmtData3[0].has_zero_padding, false);
    EXPECT_EQ(fmtData3[0].width, 8);
    EXPECT_EQ(fmtData3[0].precision, 2);
    EXPECT_EQ(fmtData3[0].type, nanofmt::nanofmt_detail::FormatType::b);

    EXPECT_EQ(fmtData4[0].valid, true);
    EXPECT_EQ(fmtData4[0].has_zero_padding, false);
    EXPECT_EQ(fmtData4[0].width, 56);
    EXPECT_EQ(fmtData4[0].precision, 34);
    EXPECT_EQ(fmtData4[0].type, nanofmt::nanofmt_detail::FormatType::d);

    EXPECT_EQ(fmtData5[0].valid, true);
    EXPECT_EQ(fmtData5[0].has_zero_padding, true);
    EXPECT_EQ(fmtData5[0].width, 1234);
    EXPECT_EQ(fmtData5[0].precision, 0);
    EXPECT_EQ(fmtData5[0].type, nanofmt::nanofmt_detail::FormatType::x);

    EXPECT_EQ(fmtData6[0].valid, true);
    EXPECT_EQ(fmtData6[0].has_zero_padding, false);
    EXPECT_EQ(fmtData6[0].width, 6);
    EXPECT_EQ(fmtData6[0].precision, 0);
    EXPECT_EQ(fmtData6[0].type, nanofmt::nanofmt_detail::FormatType::def);
}
