#ifndef SPEC_C_H
#define SPEC_C_H

#include <wchar.h>

#include "../common/basetypes.h"
#include "set_specs.h"

void specC(char* str, char arg, int* shiftStr, const Spec* spec);
void specLC(char* str, wchar_t arg, int* shiftStr, const Spec* spec);


#endif