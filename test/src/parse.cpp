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

    EXPECT_EQ(fmtDataValid1[0].isValid(), true);
    EXPECT_EQ(fmtDataValid2[0].isValid(), true);
    EXPECT_EQ(fmtDataValid3[0].isValid(), true);
    EXPECT_EQ(fmtDataValid4[0].isValid(), true);
    EXPECT_EQ(fmtDataValid5[0].isValid(), true);
    EXPECT_EQ(fmtDataValid6[0].isValid(), true);
}

TEST(Parse, update_number) {
    constexpr auto fmtData1 =
        nanofmt::nanofmt_detail::generate_fmt_data<"{:023}{:1}{:0867}">();
    constexpr auto fmtData2 =
        nanofmt::nanofmt_detail::generate_fmt_data<"{:0.2}{:034.43}{:.123}">();

    EXPECT_EQ(fmtData1[0].getWidth(), 23);
    EXPECT_EQ(fmtData1[1].getWidth(), 1);
    EXPECT_EQ(fmtData1[2].getWidth(), 867);

    EXPECT_EQ(fmtData2[0].getPrecision(), 2);
    EXPECT_EQ(fmtData2[1].getPrecision(), 43);
    EXPECT_EQ(fmtData2[2].getPrecision(), 123);
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

    EXPECT_EQ(fmtData1[0].isValid(), true);
    EXPECT_EQ(fmtData1[0].getZeroPadding(),
              nanofmt::nanofmt_detail::RepFieldData::def().getZeroPadding());
    EXPECT_EQ(fmtData1[0].getWidth(),
              nanofmt::nanofmt_detail::RepFieldData::def().getWidth());
    EXPECT_EQ(fmtData1[0].getPrecision(),
              nanofmt::nanofmt_detail::RepFieldData::def().getPrecision());
    EXPECT_EQ(fmtData1[0].getType(),
              nanofmt::nanofmt_detail::RepFieldData::def().getType());

    EXPECT_EQ(fmtData2[0].isValid(), true);
    EXPECT_EQ(fmtData2[0].getZeroPadding(), true);
    EXPECT_EQ(fmtData2[0].getWidth(), 12);
    EXPECT_EQ(fmtData2[0].getPrecision(), 4);
    EXPECT_EQ(fmtData2[0].getType(), nanofmt::nanofmt_detail::FormatType::f);

    EXPECT_EQ(fmtData3[0].isValid(), true);
    EXPECT_EQ(fmtData3[0].getZeroPadding(), false);
    EXPECT_EQ(fmtData3[0].getWidth(), 8);
    EXPECT_EQ(fmtData3[0].getPrecision(), 2);
    EXPECT_EQ(fmtData3[0].getType(), nanofmt::nanofmt_detail::FormatType::b);

    EXPECT_EQ(fmtData4[0].isValid(), true);
    EXPECT_EQ(fmtData4[0].getZeroPadding(), false);
    EXPECT_EQ(fmtData4[0].getWidth(), 56);
    EXPECT_EQ(fmtData4[0].getPrecision(), 34);
    EXPECT_EQ(fmtData4[0].getType(), nanofmt::nanofmt_detail::FormatType::d);

    EXPECT_EQ(fmtData5[0].isValid(), true);
    EXPECT_EQ(fmtData5[0].getZeroPadding(), true);
    EXPECT_EQ(fmtData5[0].getWidth(), 1234);
    EXPECT_EQ(fmtData5[0].getPrecision(),
              nanofmt::nanofmt_detail::RepFieldData::def().getPrecision());
    EXPECT_EQ(fmtData5[0].getType(), nanofmt::nanofmt_detail::FormatType::x);

    EXPECT_EQ(fmtData6[0].isValid(), true);
    EXPECT_EQ(fmtData6[0].getZeroPadding(), false);
    EXPECT_EQ(fmtData6[0].getWidth(), 6);
    EXPECT_EQ(fmtData6[0].getPrecision(),
              nanofmt::nanofmt_detail::RepFieldData::def().getPrecision());
    EXPECT_EQ(fmtData6[0].getType(), nanofmt::nanofmt_detail::FormatType::def);
}
