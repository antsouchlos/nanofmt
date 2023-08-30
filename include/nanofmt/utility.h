#pragma once


#include <string.h>

#include "stdlib.h"


namespace nanofmt { namespace nanofmt_detail {


constexpr inline std::size_t const_pow(std::size_t base, std::size_t pow) {
    if (pow == 0)
        return 1;
    else
        return base * const_pow(base, pow - 1);
}


}} // namespace nanofmt::nanofmt_detail
