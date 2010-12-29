#pragma once

#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "internals/Object/interface.h"
#include "internals/Number/interface.h"
#include "internals/Allocator/interface.h"
#include "internals/NumberFactory/interface.h"
#include "internals/StringFactory/interface.h"
#include "internals/LogicFactory/interface.h"
#include "internals/Logic/interface.h"
#include "internals/Console/interface.h"
#include "internals/Comparation/interface.h"
#include "internals/Undestroyable/interface.h"

#include "internals/globals.h"
#include "internals/debug.h"

typedef Object (*BasicMethod)(Object, Object);