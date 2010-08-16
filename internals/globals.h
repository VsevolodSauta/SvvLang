#pragma once

#include "internals/object/interface.h"
#include "internals/allocator/interface.h"
#include "internals/mmu/interface.h"
#include "internals/char_factory/interface.h"

extern SvvInternalObject SvvInternalNothing;
extern SvvInternalAllocator SvvDefaultAllocator;
extern SvvInternalMMU SvvDefaultMMU;
extern SvvInternalCharFactory SvvDefaultCharFactory;
