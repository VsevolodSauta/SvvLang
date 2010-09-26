#include "internals/object/interface.h"
#include "internals/actions.h"

Creator(AutoreleasePool);
Action(AutoreleasePool, Add, Object);
Action(AutoreleasePool, Remove, Object);
Action(AutoreleasePool, Drain);
