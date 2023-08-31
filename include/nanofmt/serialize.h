#pragma once

#include "types.h"
#include <stdint.h>


namespace nanofmt { namespace nanofmt_detail {


void serialize_unsigned(char* templateStr, uint64_t arg,
                        RepFieldData repFieldData);

void serialize_signed(char* templateStr, int64_t arg,
                      RepFieldData repFieldData);

void serialize_double(char* templateStr, double arg,
                      RepFieldData repFieldData);



template <std::unsigned_integral uint_t>
constexpr inline void serialize(char* templateStr, uint_t arg,
                                RepFieldData repFieldData) {

    serialize_unsigned(templateStr, arg, repFieldData);
}

template <std::signed_integral uint_t>
constexpr inline void serialize(char* templateStr, uint_t arg,
                                RepFieldData repFieldData) {

    serialize_signed(templateStr, arg, repFieldData);
}

template <std::floating_point uint_t>
constexpr inline void serialize(char* templateStr, uint_t arg,
                                RepFieldData repFieldData) {

    serialize_double(templateStr, arg, repFieldData);
}


}} // namespace nanofmt::nanofmt_detail
