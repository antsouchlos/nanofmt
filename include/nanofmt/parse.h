#pragma once


#include <algorithm>

#include "types.h"


// clang-format off

/*
 *
 *  fmtlib grammar:
 *      replacement_field ::=  "{" [arg_id] [":" (format_spec | chrono_format_spec)] "}"
 *      arg_id            ::=  integer | identifier
 *      integer           ::=  digit+
 *      digit             ::=  "0"..."9"
 *      identifier        ::=  id_start id_continue*
 *      id_start          ::=  "a"..."z" | "A"..."Z" | "_"
 *      id_continue       ::=  id_start | digit
 *
 *      format_spec ::=  [[fill]align][sign]["#"]["0"][width]["." precision]["L"][type]
 *      fill        ::=  <a character other than '{' or '}'>
 *      align       ::=  "<" | ">" | "^"
 *      sign        ::=  "+" | "-" | " "
 *      width       ::=  integer | "{" [arg_id] "}"
 *      precision   ::=  integer | "{" [arg_id] "}"
 *      type        ::=  "a" | "A" | "b" | "B" | "c" | "d" | "e" | "E" | "f" | "F" | "g" | "G" |
 *                       "o" | "p" | "s" | "x" | "X"
 *
 *  nanofmt grammar:
 *      string            ::= { replacement_field | <a character other than '{'> }
 *      replacement_field ::= "{" [":" format_spec] "}"
 *      format_spec       ::= ["0"][width]["." precision][type]
 *      type              ::= "s" | "c" | "b" | "d" | "x" | "f" 
 *
 */

// clang-format on


/*
 *
 * Helper types and functions
 *
 */


namespace nanofmt { namespace nanofmt_detail {


/**
 * @brief Update the value of an integer based on an additional parsed digit
 */
consteval inline void update_number(std::size_t& result, char c) {
    int num = c - '0';
    result *= 10;
    result += num;
}


/**
 * @brief Parse a replacement field
 * @tparam t_s ConstString holding the string input
 * @param startIndex Index at which to start parsing
 */
template <ConstString t_s>
consteval inline RepFieldData parseRepField(std::size_t startIndex) {
    /// Variable initialization and helper constructs

    RepFieldData result{.startIndex = startIndex};
    std::size_t  parseIndex = startIndex;

    auto match   = [&parseIndex](char c) { return t_s[parseIndex] == c; };
    auto consume = [&parseIndex](char c) {
        return t_s[parseIndex] == c && (++parseIndex);
    };
    auto match_num = [&parseIndex]() {
        return (('0' <= t_s[parseIndex]) && ('9' >= t_s[parseIndex]));
    };
    auto adjust_stop_index = [&parseIndex](const RepFieldData& repFieldData) {
        RepFieldData result{repFieldData};
        result.stopIndex = parseIndex;
        return result;
    };

    /// Parse replacement field

    consume('{');

    if (consume('}')) {
        return adjust_stop_index(result);
    }

    /// Parse format spec

    if (!consume(':')) return RepFieldData::invalid();

    if (consume('0')) result.has_zero_padding = true;

    while (!match('.') && !match('}') && match_num())
        update_number(result.width, t_s[parseIndex++]);

    if (consume('.'))
        while (match_num())
            update_number(result.precision, t_s[parseIndex++]);

    if (consume('}')) return adjust_stop_index(result);

    if (consume('b'))
        result.type = FormatType::b;
    else if (consume('d'))
        result.type = FormatType::d;
    else if (consume('x'))
        result.type = FormatType::x;
    else if (consume('f'))
        result.type = FormatType::f;

    if (!consume('}')) return RepFieldData::invalid();

    return adjust_stop_index(result);
}


/**
 * @brief Class implementing a parser for replacement fields
 * @details Implemented as custom container with a forward iterator to loop over
 * the parsed replacement fields
 * @tparam t_s ConstString holding the string input
 */
// TODO: Make sure this is a standard conform container
template <ConstString t_s>
class RepFieldParser {
private:
    /**
     * @brief Forward iterator
     */
    class Iterator {
    public:
        consteval Iterator(std::size_t startIndex) noexcept
            : mStartIndex(startIndex) {
            skipToNextField();
        }

        consteval RepFieldData operator*() const {
            return parseRepField<t_s>(mStartIndex);
        }

        consteval Iterator& operator++() {
            ++mStartIndex;
            skipToNextField();
            return *this;
        }

        consteval bool operator==(const Iterator& other) const {
            return other.mStartIndex == mStartIndex;
        }

    private:
        std::size_t mStartIndex;

        consteval void skipToNextField() {
            while (mStartIndex < t_s.size() && t_s[mStartIndex] != '{')
                ++mStartIndex;
        }
    };

public:
    consteval Iterator begin() const {
        return Iterator(0);
    }

    consteval Iterator end() const {
        return Iterator(t_s.size());
    }

    consteval std::size_t count_fields() const {
        return std::count(t_s.begin(), t_s.end(), '{');
    }
};


/**
 * @brief Generate an array of RepFieldData objects, describing the format
 * specification of each replacement field
 * @tparam t_s ConstString holding the string input
 */
template <ConstString t_s>
consteval inline auto generate_fmt_data() {
    constexpr RepFieldParser<t_s> parser;

    std::array<RepFieldData, parser.count_fields()> result;

    auto it = result.begin();
    for (const auto& repFieldData : parser) {
        *(it++) = repFieldData;
    }

    return result;
}


}} // namespace nanofmt::nanofmt_detail