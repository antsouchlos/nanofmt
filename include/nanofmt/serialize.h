#pragma once


#include "types.h"


namespace nanofmt { namespace nanofmt_detail {


// void serialize(char* templateStr, unsigned long long arg, RepFieldData repFieldData);
void serialize(char* templateStr, int64_t arg, RepFieldData repFieldData);
// void serialize(char* templateStr, float arg, RepFieldData repFieldData);
// void serialize(char* templateStr, const char* arg, RepFieldData repFieldData);

// TODO: Define for all necessary types


}} // namespace nanofmt::nanofmt_detail
