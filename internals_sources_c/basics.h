#pragma once

#include "os_dependent/linux.h"
#include "hardware_dependent/proto.h"

#include "internals/debug.h"

#include "internals/Object/interface.h"
#include "internals/Number/interface.h"
#include "internals/Allocator/interface.h"
#include "internals/AllocatorForStack/interface.h"
#include "internals/NumberFactory/interface.h"
#include "internals/StringFactory/interface.h"
#include "internals/LogicFactory/interface.h"
#include "internals/CharFactory/interface.h"
#include "internals/File/interface.h"
// #include "internals/Comparison/interface.h"
#include "internals/Method/interface.h"
#include "internals/MethodFactory/interface.h"

#include "internals/globals.h"

typedef Object (*BasicMethod)(Object, Object, Object);
