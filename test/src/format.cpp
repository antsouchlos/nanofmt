#include <gtest/gtest.h>

#include <nanofmt/format.h>
#include <nanofmt/types.h>


TEST(Format, template_str) {
    constexpr nanofmt::nanofmt_detail::ConstString constStr{
        "This is a {:08.3} test. And another{:2} one {:04.67x}"};

    constexpr auto fmtData =
        nanofmt::nanofmt_detail::generate_fmt_data<constStr>();
    constexpr auto str =
        nanofmt::nanofmt_detail::generate_string_template<constStr, fmtData>();

    nanofmt::nanofmt_detail::ConstString expected{"This is a          test. And another   one     "};

    ASSERT_EQ(str.size(), expected.size());

    for (std::size_t i = 0; i < str.size(); ++i) {
        EXPECT_EQ(str[i], expected[i]) << "Arrays differ at index " << i;
    }
}