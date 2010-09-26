#pragma once

#include "internals/basics.h"
#include "internals/string/interface.h"

typedef SvvInternalObject SvvInternalStringFactory;

SvvInternalAction(SvvInternalStringFactory, GetFromASCIIString, SvvInternalString, char* AsciiString);

extern SvvInternalStringFactory SvvDefaultStringFactory;
