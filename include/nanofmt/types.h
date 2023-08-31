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
    bool        mZeroPadding = false;
    std::size_t mWidth       = 0;
    std::size_t mPrecision   = 0;
    FormatType  mType        = FormatType::def;

    bool        mValid     = true;
    std::size_t mStartIndex = 0;
    std::size_t mStopIndex  = 0;

    // clang-format off
    constexpr void setWidth(std::size_t width)             { mWidth = width; }
    constexpr void setPrecision(std::size_t precision)     { mPrecision = precision; }
    constexpr void setZeroPadding(std::size_t zeroPadding) { mZeroPadding = zeroPadding; }
    constexpr void setType(FormatType type)                { mType = type; }
    constexpr void setStartIndex(std::size_t startIndex)   { mStartIndex = startIndex; }
    constexpr void setStopIndex(std::size_t stopIndex)     { mStopIndex = stopIndex; }

    constexpr std::size_t getWidth()       const { return (mWidth != 0) ? mWidth : def().mWidth; }
    constexpr std::size_t getPrecision()   const { return (mPrecision != 0) ? mPrecision : def().mPrecision; }
    constexpr bool        getZeroPadding() const { return mZeroPadding; }
    constexpr FormatType  getType()        const { return (mType != FormatType::def) ? mType : def().mType; }
    constexpr bool        isValid()        const { return mValid; }
    constexpr std::size_t getStartIndex()  const { return mStartIndex; }
    constexpr std::size_t getStopIndex()   const { return mStopIndex; }
    // clang-format on

    constexpr static RepFieldData invalid() {
        return {.mValid = false};
    }

    constexpr static RepFieldData def() {
        return {.mZeroPadding = false,
                .mWidth       = 6,
                .mPrecision   = 2,
                .mType        = FormatType::def};
    }
};


}} // namespace nanofmt::nanofmt_detail