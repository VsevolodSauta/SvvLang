#pragma once

#include "internals/basics.h"
#include "internals/string/interface.h"

typedef SvvInternalObject SvvInternalStringFactory;

extern SvvInternalStringFactory SvvDefaultStringFactory;

SvvInternalAction(SvvInternalStringFactory, GetFromASCIIString, SvvInternalString, char* AsciiString);