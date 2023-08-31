#pragma once


#include <array>
#include <cstddef>


namespace nanofmt { namespace nanofmt_detail {


template <std::size_t N>
class ConstString {
public:
    constexpr ConstString(const char (&content)[N]) noexcept {
        std::copy(&content[0], (&content[N - 1] + 1), mContent.begin());
    }

    constexpr char operator[](std::size_t index) const noexcept {
        return mContent[index];
    }

    constexpr std::size_t size() const noexcept {
        return N - 1;
    }

    constexpr auto begin() {
        return mContent.begin();
    }

    constexpr auto end() {
        return mContent.begin() + size();
    }

    constexpr auto begin() const {
        return mContent.begin();
    }

    constexpr auto end() const {
        return mContent.begin() + size();
    }

    std::array<char, N> mContent;
};


template <std::size_t N>
ConstString(const char (&)[N]) -> ConstString<N>;


enum class FormatType { def, b, d, x, f };


struct RepFieldData {
    /// Format specification

    bool        has_zero_padding = false;
    std::size_t width            = 0;
    std::size_t precision        = 0;
    FormatType  type             = FormatType::def;

    /// Metadata

    bool valid = true;

    std::size_t startIndex = 0;
    std::size_t stopIndex  = 0;

    constexpr std::size_t getWidth() const {
        if (width == 0)
            return def().width;
        else
            return width;
    }

    constexpr std::size_t getPrecision() const {
        if (precision == 0)
            return def().precision;
        else
            return precision;
    }

    constexpr static RepFieldData invalid() {
        RepFieldData result;
        result.valid = false;
        return result;
    }

    constexpr static RepFieldData def() {
        RepFieldData result = {.has_zero_padding = false,
                               .width            = 6,
                               .precision        = 2,
                               .type             = FormatType::def};
        return result;
    }
};


}} // namespace nanofmt::nanofmt_detail