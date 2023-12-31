#pragma once


#include "parse.h"
#include "serialize.h"
#include "types.h"


/*
 *
 * Implementation details
 *
 */


namespace nanofmt { namespace nanofmt_detail {


/**
 * @brief Calculate the length of the string template
 * @tparam t_s ConstString holding the string input
 * @tparam t_fmt_data array of RepFieldData objects
 */
template <ConstString t_s, std::array t_fmt_data>
consteval std::size_t calc_template_length() {
    std::size_t result = t_s.size();

    for (const auto& repFieldData : t_fmt_data) {
        result -= (repFieldData.getStopIndex() - repFieldData.getStartIndex());
        result += repFieldData.getWidth();
    }

    return result;
}

/**
 * @brief Generate an array of characters with placeholders of the appropriate
 * size where the replacement fields are
 * @tparam t_s ConstString holding the string input
 * @tparam t_fmt_data array of RepFieldData objects
 */
template <ConstString t_s, std::array t_fmt_data>
consteval inline auto generate_string_template() {
    std::array<char, calc_template_length<t_s, t_fmt_data>() + 1> result = {0};
    std::fill(result.begin(), result.end() - 1, ' ');

    auto resultIt   = result.begin();
    auto repFieldIt = t_fmt_data.begin();
    auto inputIt    = t_s.begin();

    while (inputIt != t_s.end()) {
        if (*inputIt == '{') {
            inputIt = std::find(inputIt, t_s.end(), '}');
            ++inputIt;

            if (repFieldIt->getZeroPadding())
                std::fill_n(resultIt, repFieldIt->getWidth(), '0');

            resultIt += (repFieldIt++)->getWidth();
        } else {
            *(resultIt++) = *(inputIt++);
        }
    }

    return result;
}

/**
 * @brief Change the start and stop indices of the rep field elements to match
 * the output instead of the input string
 */
template <std::array t_fmt_data>
consteval inline auto adjust_fmt_data_indices() {
    auto result = t_fmt_data;

    std::size_t currentOffset = 0;

    for (auto& repFieldData : result) {
        int tempStart = repFieldData.getStartIndex();
        int tempStop  = repFieldData.getStopIndex();

        repFieldData.setStartIndex(repFieldData.getStartIndex() +
                                   currentOffset);
        repFieldData.setStopIndex(repFieldData.getStartIndex() +
                                  repFieldData.getWidth());

        currentOffset -= (tempStop - tempStart);
        currentOffset += repFieldData.getWidth();
    }

    return result;
}

/**
 * @brief Format the arguments according to the format spec and write them into
 * the corresponding placeholder in the previously generated string template
 */
// TODO: Validate arg types against format specs
template <std::array t_str_template, std::array t_fmt_data, typename... args_t>
inline auto populate_template(args_t... args) {
    /// Adjust the start and stop indices to match the output instead of the
    /// input string
    constexpr auto fmtDataAdjusted = adjust_fmt_data_indices<t_fmt_data>();

    std::array<char, t_str_template.size()> result = t_str_template;

    static_assert(sizeof...(args_t) == fmtDataAdjusted.size(),
                  "The number of arguments has to match the number of "
                  "replacement fields");

    int repFieldIndex = 0;
    (
        [&] {
            serialize(result.data(), args, fmtDataAdjusted[repFieldIndex]);
            ++repFieldIndex;
        }(),
        ...);

    return result;
}

/**
 * @brief Check for syntax errors and semantic errors
 */
template <std::array t_fmt_data, int I = 0>
consteval void validate_fmt_data() {
    if constexpr (t_fmt_data.size() > I)
        static_assert(t_fmt_data[I].isValid(),
                      "Syntax error in format specification: ");

    // TODO: Various other checks (precision > width, etc.)

    if constexpr (I + 1 < t_fmt_data.size())
        validate_fmt_data<t_fmt_data, I + 1>();
}


}} // namespace nanofmt::nanofmt_detail


/*
 *
 * Public interface
 *
 */


namespace nanofmt {


template <nanofmt_detail::ConstString t_s, typename... args_t>
inline auto format(args_t... args) {
    using namespace nanofmt_detail;

    constexpr auto fmtData = generate_fmt_data<t_s>();
    validate_fmt_data<fmtData>();

    constexpr auto templateStr = generate_string_template<t_s, fmtData>();

    return populate_template<templateStr, fmtData>(
        std::forward<args_t>(args)...);
}


namespace nanofmt_detail {

/**
 * @brief Helper object used to invoke 'format()' with a UDL
 */
template <nanofmt_detail::ConstString t_s>
class const_fmt_literal_obj_t {
public:
    template <typename... args_t>
    constexpr auto operator()(args_t... args) {
        return format<t_s>(args...);
    }
};

} // namespace nanofmt_detail

namespace literals {

template <nanofmt_detail::ConstString t_s>
constexpr auto operator""_fmt() {
    return nanofmt_detail::const_fmt_literal_obj_t<t_s>{};
}

} // namespace literals


} // namespace nanofmt
