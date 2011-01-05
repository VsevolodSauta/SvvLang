#pragma once

// #include <unistd.h>
// #include <sys/mman.h>
// #include <fcntl.h>

#include "os_dependent/linux.h"

#include "internals/debug.h"

#include "internals/Object/interface.h"
#include "internals/Number/interface.h"
#include "internals/Allocator/interface.h"
#include "internals/NumberFactory/interface.h"
#include "internals/StringFactory/interface.h"
#include "internals/LogicFactory/interface.h"
#include "internals/Logic/interface.h"
#include "internals/File/interface.h"
#include "internals/Comparation/interface.h"
#include "internals/Undestroyable/interface.h"

#include "internals/globals.h"

typedef Object (*BasicMethod)(Object, Object);