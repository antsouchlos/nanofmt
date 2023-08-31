#include <stdint.h>
#include <string.h>

#include <nanofmt/serialize.h>
#include <nanofmt/types.h>
#include <nanofmt/utility.h>


/*
 *
 * ****************************************************************
 * Disclaimer: Most of this code is shamelessly stolen from fmtlib
 * ****************************************************************
 *
 */


namespace {


using namespace nanofmt;
using namespace nanofmt::nanofmt_detail;


#define FMT_POWERS_OF_10(factor)                                              \
    factor * 10, (factor)*100, (factor)*1000, (factor)*10000,                 \
        (factor)*100000, (factor)*1000000, (factor)*10000000,                 \
        (factor)*100000000, (factor)*1000000000

inline int count_digits_decimal(uint64_t n) {
    // Maps bsr(n) to ceil(log10(pow(2, bsr(n) + 1) - 1)).
    static constexpr uint8_t bsr2log10[] = {
        1,  1,  1,  2,  2,  2,  3,  3,  3,  4,  4,  4,  4,  5,  5,  5,
        6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9,  10, 10, 10,
        10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 15, 15,
        15, 16, 16, 16, 16, 17, 17, 17, 18, 18, 18, 19, 19, 19, 19, 20};

    auto t = bsr2log10[__builtin_clzll(n | 1) ^ 63];

    static constexpr const uint64_t zero_or_powers_of_10[] = {
        0, 0, FMT_POWERS_OF_10(1U), FMT_POWERS_OF_10(1000000000ULL),
        10000000000000000000ULL};

    return t - (n < zero_or_powers_of_10[t]);
}

constexpr inline int count_digits_base(uint64_t n, FormatType formatType) {
    if (formatType == FormatType::b) {
        int result = 0;

        while (n) {
            n = n >> 1;
            result += 1;
        }

        return result;
    } else if (formatType == FormatType::x) {
        int result = 0;

        while (n) {
            n = n >> 4;
            result += 1;
        }

        return result;
    } else {
        return count_digits_decimal(n);
    }
}


// Converts value in the range [0, base^2) to a string.
constexpr inline const char* digits2_base(size_t     value,
                                          FormatType formatType) {
    // GCC generates slightly better code when value is pointer-size.
    if (formatType == FormatType::b) {
        return &"00011011"[value * 2];
    } else {
        if (formatType == FormatType::x) {
            // clang-format off
            return &"000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F"
                    "202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F"
                    "404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F"
                    "606162636465666768696A6B6C6D6E6F707172737475767778797A7B7C7D7E7F"
                    "808182838485868788898A8B8C8D8E8F909192939495969798999A9B9C9D9E9F"
                    "A0A1A2A3A4A5A6A7A8A9AAABACADAEAFB0B1B2B3B4B5B6B7B8B9BABBBCBDBEBF"
                    "C0C1C2C3C4C5C6C7C8C9CACBCCCDCECFD0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF"
                    "E0E1E2E3E4E5E6E7E8E9EAEBECEDEEEFF0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF"[value * 2];
            // clang-format on
        } else {
            return &"0001020304050607080910111213141516171819"
                    "2021222324252627282930313233343536373839"
                    "4041424344454647484950515253545556575859"
                    "6061626364656667686970717273747576777879"
                    "8081828384858687888990919293949596979899"[value * 2];
        }
    }
}


constexpr inline void copy2(char* dst, const char* src) {
    if (!std::is_constant_evaluated()) {
        memcpy(dst, src, 2);
        return;
    }
    *dst++ = static_cast<char>(*src++);
    *dst   = static_cast<char>(*src);
}

constexpr inline unsigned get_base_divisor(FormatType formatType) {
    switch (formatType) {
    case FormatType::b:
        return 2;
    case FormatType::x:
        return 16;
    default:
        return 10;
    }
}

constexpr inline void format_base(char* out, uint64_t value, int size,
                                  FormatType formatType) {

    /// Ensure the number fits into the allocated space

    int n_digits = count_digits_base(value, formatType);
    if (n_digits > size) {
        for (int i = 0; i < size; ++i) {
            *(out++) = 'x';
        }
        return;
    }

    /// Format number

    unsigned divisor        = get_base_divisor(formatType);
    unsigned square_divisor = const_pow(divisor, 2);

    out += size;
    while (value >= square_divisor) {
        out -= 2;
        copy2(out, digits2_base(static_cast<size_t>(value % square_divisor),
                                formatType));
        value /= square_divisor;
    }

    if (value < divisor) {
        *--out = digits2_base(value * divisor, formatType)[0];
        return;
    }

    out -= 2;
    copy2(out, digits2_base(static_cast<size_t>(value), formatType));
}


constexpr std::pair<uint32_t, bool> get_abs_value(int64_t value) {
    auto abs_value = static_cast<uint32_t>(value);

    const bool negative = value < 0;
    if (negative) abs_value = 0 - abs_value;

    return {abs_value, negative};
}


} // namespace


namespace nanofmt { namespace nanofmt_detail {


void serialize_unsigned(char* templateStr, uint64_t arg,
                        RepFieldData repFieldData) {

    char* out = templateStr + repFieldData.startIndex;
    format_base(out, arg, repFieldData.getWidth(), repFieldData.type);
}

void serialize_signed(char* templateStr, int64_t arg,
                      RepFieldData repFieldData) {

    char* out = templateStr + repFieldData.startIndex;

    /// Format number

    const auto [abs_value, negative] = get_abs_value(arg);

    format_base(templateStr + repFieldData.startIndex + 1 * (negative),
                abs_value, repFieldData.width - 1 * (negative),
                repFieldData.type);

    /// Handle sign

    const std::size_t n_digits =
        count_digits_base(abs_value, repFieldData.type);

    if (repFieldData.has_zero_padding) {
        if (negative) *(out) = '-';
    } else {
        if (n_digits < repFieldData.width)
            if (negative) *(out + repFieldData.width - n_digits - 1) = '-';
    }
}

void serialize_double(char* templateStr, double arg,
                      RepFieldData repFieldData) {

    char* out = templateStr + repFieldData.startIndex;

    // clang-format off
    const RepFieldData fmtDataIntegral = {
        .has_zero_padding = repFieldData.has_zero_padding,
        .width            = repFieldData.width - repFieldData.precision - 1,
        .precision        = repFieldData.precision,
        .type             = FormatType::d,
        .valid            = true,
        .startIndex       = repFieldData.startIndex,
        .stopIndex        = repFieldData.startIndex + repFieldData.width - repFieldData.precision - 1
    };
    const RepFieldData fmtDataFractional = {
        .has_zero_padding = true,
        .width            = repFieldData.precision,
        .precision        = 0, // ignored
        .type             = FormatType::d,
        .valid            = true,
        .startIndex       = repFieldData.startIndex + repFieldData.width - repFieldData.precision,
        .stopIndex        = repFieldData.startIndex + repFieldData.width
    };
    // clang-format on

    *(out + repFieldData.width - repFieldData.precision - 1) = '.';

    const int64_t integral = static_cast<int64_t>(arg);

    const uint64_t factor = const_pow(10, repFieldData.precision);

    const int64_t fractional =
        static_cast<int64_t>((arg - integral) * factor);

    const auto [fractional_abs, fractional_negative] =
        get_abs_value(fractional);

    serialize_signed(templateStr, integral, fmtDataIntegral);
    serialize_signed(templateStr, fractional_abs, fmtDataFractional);
}


}} // namespace nanofmt::nanofmt_detail